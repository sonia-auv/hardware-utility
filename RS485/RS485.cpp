/**
 * @file RS485.h
 * @brief RS485 class source file
 * 
 */

#include "mbed.h"
#include "rtos.h"

#include "RS485_definition.h"
#include "RS485.h"
#include "pinDef.h"

//###################################################
//
// PUBLIC FUNCTION
//
//###################################################

RS485::RS485(const uint8_t board_address, const uint32_t prefered_sleep_time, const uint8_t packet_array_size, const uint8_t te_value)
{
    rs485 = new UnbufferedSerial(RS485_TX_PIN, RS485_RX_PIN, 115200);
    re = new DigitalOut(RS485_RE_PIN, 0);
    te = new DigitalOut(RS485_TE_PIN, te_value);
    de = new DigitalOut(RS485_DE_PIN, 0);

    rs485->set_flow_control(mbed::SerialBase::Disabled, NC, NC);
    rs485->setBlocking(true);
    this->board_adress = board_address;
    this->prefered_sleep_time = prefered_sleep_time;
    this->packet_array_size = packet_array_size;

    packet_array = (RS485_reader_message*)malloc(sizeof(RS485_reader_message)*packet_array_size);

    readThread.start(this, &RS485::read_thread);
    readThread.set_priority(osPriorityBelowNormal);
}

RS485::~RS485()
{
    delete rs485;
    delete re;
    delete te;
    delete de;

    free(packet_array);
    packet_array = NULL;
}

uint8_t RS485::read(const uint8_t* cmd_array, const uint8_t nb_command, uint8_t* data_buffer)
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

uint8_t RS485::read(const uint8_t* cmd_array, const uint8_t nb_command, uint8_t& returned_slave, uint8_t* data_buffer)
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
                    returned_slave = packet_array[i].slave;

                    event.clear(cmd_flag);
                    return packet_array[i].nb_byte;
                }
            }
        }
    }
}

void RS485::write(const uint8_t slave, const uint8_t cmd, const uint8_t nb_byte, const uint8_t* data_buffer)
{
    uint16_t checksum = calculateCheckSum(slave, cmd, nb_byte, data_buffer);

    writer_mutex.lock();
    de->write(1);
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
    ThisThread::sleep_for(20ms);
    de->write(0);
    writer_mutex.unlock();
}

uint8_t RS485::getBoardAdress()
{
    return board_adress;
}

//###################################################
//
// PRIVATE FUNCTION
//
//###################################################

uint16_t RS485::calculateCheckSum(const uint8_t slave, const uint8_t cmd, const uint8_t nbByte, const uint8_t* data)
{
    uint16_t check = (uint16_t)(0x3A+slave+cmd+nbByte+0x0D);
    for(uint8_t i = 0; i < nbByte; ++i)
    {
        check += data[i];
    }

    return check;
}

void RS485::send_packet()
{
    event.set(event_flag);

    event_flag = 0;
    packet_count = 0;
}

uint8_t RS485::serial_read()
{
    uint8_t data;
    while(1)
    {
        if(rs485->readable())
        {
            rs485->read(&data, 1);
            return data;
        }
        else
        {
            if(packet_count)
            {
                send_packet();
            }
        }
    }
}

void RS485::serial_write(const uint8_t data)
{
    while(1)
    {
        if(rs485->writeable())
        {
            if(rs485->write(&data, 1) != -1)
            {
                break;
            }
        }
    }
}

void RS485::read_thread()
{
    uint16_t local_checksum;

    while(1)
    {
        // search for the start byte
        while(serial_read() != 0x3A);

        // collect all the information
        packet_array[packet_count].slave = serial_read();
        packet_array[packet_count].cmd = serial_read();
        packet_array[packet_count].nb_byte = serial_read();

        for(uint8_t i = 0; i < packet_array[packet_count].nb_byte; ++i)
        {
            packet_array[packet_count].data[i] = serial_read();
        }

        local_checksum = (uint16_t)(serial_read()<<8);
        local_checksum += serial_read();

        // validate the data
        if(serial_read() != 0x0D || 
            (packet_array[packet_count].slave != board_adress && board_adress != SLAVE_STATE_SCREEN) || 
            calculateCheckSum(packet_array[packet_count].slave, packet_array[packet_count].cmd, packet_array[packet_count].nb_byte, packet_array[packet_count].data) != local_checksum)
        {
            continue;
        }

        // if the packet is good, add the command to the event_flag
        event_flag = event_flag | (1 << packet_array[packet_count].cmd);

        packet_count++;

        if(packet_count >= packet_array_size)
        {
            send_packet();
        }
    }
}