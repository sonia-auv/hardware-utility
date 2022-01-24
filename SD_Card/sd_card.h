/**
 * @file sd_card.h
 * @author Francis Alonzo (francisalonzo29@gmail.com)
 * @brief Driver to support Sd card for our custom board and reduce run time errors
 * @version 0.1
 * @date 2022-01-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SD_CARD_H
#define SD_CARD_H

#include "mbed.h"
#include "LittleFileSystem.h"
#include "SDBlockDevice.h"
#include <stdio.h>
#include <errno.h>

#define VOLTAGE_FILE "/sd/monitor/voltage.txt"
#define CURRENT_FILE "/sd/monitor/current.txt"
#define TEMPERATURE_FILE "/sd/monitor/temperature.txt"
#define FLAGS_FILE "/sd/monitor/flags.txt"

#define NB_FILES 4
#define MAX_FILES_NAME 256

/**
 * @brief SD _Card Class
 * 
 */

class SD_Card
{
    public:
    
    /**
     * @brief Constructor for the SD Card
     * 
     * @param sd pointer to the object SDBlockDevice for communication to the sd card
     * @param fs pointer to the object Little file system for writing on the sd card
     */
    SD_Card(SDBlockDevice *sd, LittleFileSystem *fs);

    ~SD_Card();

    int8_t initializeSD(bool create_files = false);
    
    int8_t create_file(const char *file_name);

    /**
     * @brief Write to the SD Card at the specified file name
     * 
     * @param file_name charater array for the specified file_name
     * @param data charater array with the data to write
     * @param size size of the array
     * @return int8_t 
     */
    int8_t write_to_SD(const char *file_name ,char *data, size_t size);

    /**
     * @brief Not implemented for the moment
     * 
     * @param data 
     * @param size 
     * @return int8_t 
     */
    int8_t read_from_SD(char *data, size_t size);

    private:

    SDBlockDevice *_sd;
    LittleFileSystem *_fs;
    FILE *_file_opened;

    const char array[NB_FILES][MAX_FILES_NAME] = {VOLTAGE_FILE, CURRENT_FILE, 
                                                    TEMPERATURE_FILE, FLAGS_FILE};

};

#endif // SD_CARD_H