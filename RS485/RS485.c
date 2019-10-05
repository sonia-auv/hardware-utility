/**
 * @file RS485.c
 * @brief The source file for the RS485 firmware interface
 * 
 */

#include "mbed.h"
#include "rtos.h"

namespace RS485
{

    RawSerial rs485;
    uint8_t packet_count;


    /**
     * @brief this function analyse what to do when there's no more byte are on rx
     * 
     */
    inline void analyse_dead_time()
    {
        if(packet_count)
        {
            send_packet();
        }
        else
        {
            ThisThread::sleep_for(20);
        }
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
                analyse_dead_time();
            }
        }
    }
}