/**
 * @file RS485.cpp
 * @brief The source file for the RS485 firmware interface
 * 
 */

#include "mbed.h"
#include "rtos.h"
#include "RS485.h"

namespace RS485
{
    RawSerial rs485;
    Thread readThread;
    Thread writeThread;
    EventFlags event;

    uint8_t packet_count = 0;
    uint32_t event_flag = 0;
    uint8_t board_adress;
    uint32_t sleep_time;

    RS485_message packet_array[PACKET_ARRAY_SIZE];

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
     * @return uint8_t 
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
                    ThisThread::sleep_for(sleep_time);
                }
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

            if(packet_count > PACKET_ARRAY_SIZE)
            {
                send_packet();
            }
        }
    }

    /**
     * @brief the main writer thread
     * 
     */
    void write_thread()
    {

    }

    uint8_t read(uint8_t* cmd_array, uint8_t nb_command, uint8_t* data_buffer)
    {
        uint8_t data_size = 0;
        uint32_t cmd_flag = 0;

        //detect what flag the user is waiting for
        for(uint8_t i = 0; i < nb_command; ++i)
        {
            cmd_flag = cmd_flag | (1 << cmd_array[i])
        }

        while(1)
        {
            event.wait_any(cmd_flag, osWaitForever, false);

            // check for the good packet in the array
            for(uint8_t i = packet_count-1; i >= 0; --i)
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

    void write()
    {

    }

    /**
     * @brief the init function for RS485
     * 
     * @param tx 
     * @param rx 
     */
    void init(PinName &tx, PinName &rx, uint8_t adress, uint32_t prefered_sleep_time = 20)
    {
        rs485 = RawSerial(tx, rx, 115200);
        board_adress = adress;
        sleep_time = prefered_sleep_time;

        readThread.set_priority(osPriorityBelowNormal);
        writeThread.set_priority(osPriorityBelowNormal1);

        readThread.start(read_thread);
        writeThread.start(write_thread);
    }
}