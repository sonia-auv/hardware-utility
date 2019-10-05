#ifndef RS485_H
#define RS485_H

#include "mbed.h"

namespace RS485
{
    #define PACKET_ARRAY_SIZE 5

    typedef struct RS485_message_struct
    {
        uint8_t cmd;
        uint8_t nb_byte;
        uint8_t data[255];
    } RS485_message;
}

#endif