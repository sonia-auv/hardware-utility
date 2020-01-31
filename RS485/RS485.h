/**
 * @file RS485.h
 * @brief RS485 class header
 * 
 */

#ifndef RS485_H
#define RS485_H

#include "mbed.h"
#include "rtos.h"

/**
 * @brief the main class for RS485
 * 
 */
class RS485
{
    public:

        RS485(const uint8_t board_adress, const uint32_t prefered_sleep_time = 20, const uint8_t packet_array_size = 5);
        ~RS485();
        uint8_t read(const uint8_t* cmd_array, const uint8_t nb_command, uint8_t& returned_slave, uint8_t* data_buffer);
        void write(const uint8_t slave, const uint8_t cmd, const uint8_t nb_byte, const uint8_t* data_buffer);
    
    private:
        typedef struct RS485_reader_message_struct
        {
            uint8_t slave;
            uint8_t cmd;
            uint8_t nb_byte;
            uint8_t data[255];
        } RS485_reader_message;

        uint8_t packet_array_size;
        uint32_t prefered_sleep_time;

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

        RS485_reader_message* packet_array = NULL;

        uint16_t calculateCheckSum(const uint8_t slave, const uint8_t cmd, const uint8_t nbByte, const uint8_t* data);
        void send_packet();
        uint8_t serial_read();
        void serial_write(const uint8_t data);
        void read_thread();

}

#endif