/**
 * @file RS485.h
 * @brief The header file for the RS485 firmware interface
 * 
 * To start the RS485 thread call the RS485::init() before initializing other thread in the main function.
 * To read bytes, use the RS485::read() function the priority of your thread must be higher than osPriorityBelowNormal.
 * To write bytes, use the RS485::write() function.
 * 
 * @warning never call write and read function inside an interrupt.
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


        /**
         * @brief RS485 constructor.
         * 
         * @param board_adress the slave address of the current board
         * @param prefered_sleep_time the time(in ms) that the writer and reader thread should wait if there's no data to process.
         * @param packet_array_size the number of packet RS485 can process at the same time.
         * @param te_value define if the terminal resistor need to be enabled on this board.
         */
        RS485(const uint8_t board_adress, const uint32_t prefered_sleep_time = 20, const uint8_t packet_array_size = 5, const uint8_t te_value = 1);

        /**
         * @brief Destroy the RS485::RS485 object
         * 
         */
        ~RS485();

        /**
         * @brief the user function to read on RS485
         * 
         * @param cmd_array an array that contains the command the thread need to receive to wakeup.
         * @param nb_command the number of command.
         * @param data_buffer the buffer where the byte gonna be written. The buffer should be of size 255.
         * @param returned_slave the slave that been returned by the command.
         * @return uint8_t the number of byte received.
         */
        uint8_t read(const uint8_t* cmd_array, const uint8_t nb_command, uint8_t* data_buffer);

        /**
         * @brief the user function to read on RS485 that also return the slave
         * 
         * @param cmd_array an array that contains the command the thread need to receive to wakeup.
         * @param nb_command the number of command.
         * @param data_buffer the buffer where the byte gonna be written. The buffer should be of size 255.
         * @param returned_slave the slave that been returned by the command.
         * @return uint8_t the number of byte received.
         */
        uint8_t read(const uint8_t* cmd_array, const uint8_t nb_command, uint8_t& returned_slave, uint8_t* data_buffer);

        /**
         * @brief the user function to write on RS485
         * 
         * @param slave the slave address the message should be send to
         * @param cmd the cmd to send to the message
         * @param nb_byte the number of byte to be send
         * @param data_buffer the buffer of the data to be send
         */
        void write(const uint8_t slave, const uint8_t cmd, const uint8_t nb_byte, const uint8_t* data_buffer);

        /**
         * @brief getter to have the slave id of the current board
         * 
         * @return the slave id
         */
        uint8_t getBoardAdress();
    
    private:

        /**
         * @brief structure for one packet message.
         * 
         */
        typedef struct RS485_reader_message_struct
        {
            uint8_t slave;
            uint8_t cmd;
            uint8_t nb_byte;
            uint8_t data[255];
        } RS485_reader_message;

        uint8_t packet_array_size;
        uint32_t prefered_sleep_time;

        UnbufferedSerial* rs485;
        DigitalOut* re;
        DigitalOut* te;
        DigitalOut* de;

        Thread readThread;
        EventFlags event;

        uint8_t packet_count = 0;
        uint32_t event_flag = 0;
        uint8_t board_adress;
        uint32_t sleep_time;

        Mutex writer_mutex;

        RS485_reader_message* packet_array = NULL;

        /**
         * @brief calculate the checksum 
         * 
         * @param slave 
         * @param cmd 
         * @param nbByte 
         * @param data 
         * @return uint16_t 
         */
        uint16_t calculateCheckSum(const uint8_t slave, const uint8_t cmd, const uint8_t nbByte, const uint8_t* data);

        /**
         * @brief function that wakeup the thread waiting for a packet
         * 
         */
        void send_packet();

        /**
         * @brief a blocking call that wait for a byte to be read
         * 
         * @return uint8_t the value that've been read
         */
        uint8_t serial_read();

        /**
         * @brief a blocking call that wait to send a byte 
         * 
         * @param data the byte to be send
         */
        void serial_write(const uint8_t data);

        /**
         * @brief the main reader thread
         * 
         */
        void read_thread();

};

#endif