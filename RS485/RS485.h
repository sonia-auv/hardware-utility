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

    void init(const uint8_t adress, const uint32_t prefered_sleep_time = 20);
    uint8_t read(const uint8_t* cmd_array, const uint8_t nb_command, uint8_t* data_buffer);
    void write(const uint8_t slave, const uint8_t cmd, const uint8_t nb_byte, const uint8_t* data_buffer);

    typedef struct RS485_reader_message_struct
    {
        uint8_t cmd;
        uint8_t nb_byte;
        uint8_t data[255];
    } RS485_reader_message;

#endif