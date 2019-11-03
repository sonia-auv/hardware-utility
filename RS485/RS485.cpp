/**
 * @file RS485.cpp
 * @brief The source file for the RS485 firmware interface
 * 
 * To start the RS485 thread call the RS485::init() before initializing other thread in the main function.
 * To read bytes, use the RS485::read() function the priority of your thread must be higher than osPriorityBelowNormal.
 * To write bytes, use the RS485::write() function.
 * 
 * never call write and read function inside an interrupt
 * 
 */

#include "mbed.h"
#include "rtos.h"

#include "RS485.h"
#include "pinDef.h"

namespace RS485
{
    RawSerial rs485(RS485_TX_PIN, RS485_RX_PIN, 115200);
    DigitalOut re(RS485_RE_PIN);
    DigitalOut te(RS485_TE_PIN);
    DigitalOut de(RS485_DE_PIN);

    Thread readThread;
    EventFlags event;

    uint8_t packet_count = 0;
    uint32_t event_flag = 0;
    uint8_t board_adress;
    uint32_t sleep_time;

    Mutex writer_mutex;

    RS485_reader_message packet_array[PACKET_ARRAY_SIZE];

    /**
     * @brief calculate the checksum 
     * 
     * @param slave 
     * @param cmd 
     * @param nbByte 
     * @param data 
     * @return uint16_t 
     */
    uint16_t calculateCheckSum(uint8_t slave, uint8_t cmd, uint8_t nbByte, uint8_t* data)
    {
        uint16_t check = (uint16_t)(0x3A+slave+cmd+nbByte+0x0D);
        for(uint8_t i = 0; i < nbByte; ++i)
        {
            check += data[i];
        }

        return check;
    }

    /**
     * @brief function that wakeup the thread waiting for a packet
     * 
     */
    void send_packet()
    {
        event.set(event_flag);

        // wait for all thread to finish getting their data before erasing
        while(event.get() != 0)
        {
            ThisThread::sleep_for(sleep_time);
        }
        event_flag = 0;
        packet_count = 0;
    }

    /**
     * @brief a blocking call that wait for a byte to be read
     * 
     * @return uint8_t the value that've been read
     */
    uint8_t serial_read()
    {
        while(1)
        {
            if(rs485.readable())
            {
                return rs485.getc();
                break;
            }
            else
            {
                if(packet_count)
                {
                    send_packet();
                }
                else
                {
                    #ifdef RELEASE
                        ThisThread::sleep_for(sleep_time);
                    #endif
                }
            }
        }
    }

    /**
     * @brief a blocking call that wait to send a byte 
     * 
     * @param data the byte to be send
     */
    void serial_write(uint8_t data)
    {
        while(1)
        {
            if(rs485.writeable())
            {
                if(rs485.putc(data) != -1)
                {
                    break;
                }
            }
            else
            {
                #ifdef RELEASE
                    ThisThread::sleep_for(sleep_time);
                #endif
            }
        }
    }

    /**
     * @brief the main reader thread
     * 
     */
    void read_thread()
    {
        uint8_t local_slave;
        uint8_t local_cmd;
        uint8_t local_nb_byte;
        uint8_t local_data[255];
        uint16_t local_checksum;

        while(1)
        {
            // search for the start byte
            while(serial_read() != 0x3A);

            // collect all the information
            local_slave = serial_read();
            local_cmd = serial_read();
            local_nb_byte = serial_read();

            for(uint8_t i = 0; i < local_nb_byte; ++i)
            {
                local_data[i] = serial_read();
            }

            local_checksum = (uint16_t)(serial_read()<<8);
            local_checksum += serial_read();

            //discard the end byte
            serial_read();

            // validate the data
            if(local_slave != board_adress || calculateCheckSum(local_slave, local_cmd, local_nb_byte, local_data) != local_checksum)
            {
                continue;
            }

            // if the packet is good send it in the packet array
            packet_array[packet_count].cmd = local_cmd;
            packet_array[packet_count].nb_byte = local_nb_byte;
            for(uint8_t i = 0; i < local_nb_byte; ++i)
            {
                packet_array[packet_count].data[i] = local_data[i];
            }

            // add the command to the event_flag
            event_flag = event_flag | (1 << local_cmd);

            packet_count++;

            if(packet_count >= PACKET_ARRAY_SIZE)
            {
                send_packet();
            }
        }
    }

    /**
     * @brief the user function to read on RS485
     * 
     * @param cmd_array an array that contains the command the thread need to receive to wakeup.
     * @param nb_command the number of command.
     * @param data_buffer the buffer where the byte gonna be written. The buffer should be of size 255.
     * @return uint8_t the number of byte received.
     */
    uint8_t read(uint8_t* cmd_array, uint8_t nb_command, uint8_t* data_buffer)
    {
        uint32_t cmd_flag = 0;

        //detect what flag the user is waiting for
        for(uint8_t i = 0; i < nb_command; ++i)
        {
            cmd_flag = cmd_flag | (1 << cmd_array[i]);
        }

        while(1)
        {
            event.wait_any(cmd_flag, osWaitForever, false);

            // check for the good packet in the array
            for(int8_t i = packet_count-1; i >= 0; --i)
            {
                for(uint8_t j = 0; j < nb_command; ++j)
                {
                    if(packet_array[i].cmd == cmd_array[j])
                    {
                        // the good packet is found, transfert the data
                        for(uint8_t x = 0; x < packet_array[i].nb_byte; ++x)
                        {
                            data_buffer[x] = packet_array[i].data[x];
                        }

                        event.clear(cmd_flag);
                        return packet_array[i].nb_byte;
                    }
                }
            }
        }
    }

    /**
     * @brief the user function to write on RS485
     * 
     * @param slave the slave address the message should be send to
     * @param cmd the cmd to send to the message
     * @param nb_byte the number of byte to be send
     * @param data_buffer the buffer of the data to be send
     */
    void write(uint8_t slave, uint8_t cmd, uint8_t nb_byte, uint8_t* data_buffer)
    {
        uint16_t checksum = calculateCheckSum(slave, cmd, nb_byte, data_buffer);

        writer_mutex.lock();
        serial_write(0x3A);
        serial_write(slave);
        serial_write(cmd);
        serial_write(nb_byte);
        for(uint8_t i = 0; i < nb_byte; ++i)
        {
            serial_write(data_buffer[i]);
        }
        serial_write((uint8_t)(checksum >> 8));
        serial_write((uint8_t)(checksum & 0xFF));
        serial_write(0x0D);
        writer_mutex.unlock();
    }

    /**
     * @brief the init function for RS485
     * 
     * @param adress the slave address of the current board
     * @param prefered_sleep_time the time(in ms) that the writer and reader thread should wait if there's no data to process.
     */
    void init(uint8_t adress, uint32_t prefered_sleep_time)
    {
        board_adress = adress;
        sleep_time = prefered_sleep_time;

        re.write(0);
        te.write(1);
        de.write(1);

        readThread.start(read_thread);
        readThread.set_priority(osPriorityBelowNormal);
    }
}