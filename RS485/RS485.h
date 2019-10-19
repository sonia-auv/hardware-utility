/**
 * @file RS485.h
 * @brief RS485 header
 * 
 */

#ifndef RS485_H
#define RS485_H

#include "mbed.h"

namespace RS485
{
    #define PACKET_ARRAY_SIZE 5
    #define WRITER_QUEUE_SIZE 5

    void init(uint8_t adress, uint32_t prefered_sleep_time = 20);
    uint8_t read(uint8_t* cmd_array, uint8_t nb_command, uint8_t* data_buffer);
    void write(uint8_t slave, uint8_t cmd, uint8_t nb_byte, uint8_t* data_buffer);

    typedef struct RS485_reader_message_struct
    {
        uint8_t cmd;
        uint8_t nb_byte;
        uint8_t data[255];
    } RS485_reader_message;

    typedef struct RS485_writer_message_struct
    {
        uint8_t slave;
        uint8_t cmd;
        uint8_t nb_byte;
        uint8_t data[255];
        uint16_t checksum;
    } RS485_writer_message;
}

#endif