/**
 * @file RS485.cpp
 * @brief The source file for the RS485 firmware interface
 * 
 */

#include "mbed.h"
#include "rtos.h"

namespace RS485
{

    RawSerial rs485;
    Thread readThread;
    Thread writeThread;


    uint8_t packet_count = 0;


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

#ifdef SLEEP_TIME
            ThisThread::sleep_for(SLEEP_MS);
#endif

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

    /**
     * @brief the main reader thread
     * 
     */
    void read_thread()
    {

    }

    /**
     * @brief 
     * 
     */
    void write_thread()
    {

    }

    /**
     * @brief the init function for RS485
     * 
     * @param tx 
     * @param rx 
     */
    void init(PinName &tx, PinName &rx)
    {
        rs485 = RawSerial(tx, rx, 115200);
        readThread.set_priority(osPriorityBelowNormal);
        writeThread.set_priority(osPriorityBelowNormal1);

        readThread.start(read_thread);
        writeThread.start(write_thread);
    }
}