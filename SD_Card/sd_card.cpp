/**
 * @file sd_card.cpp
 * @author Francis Alonzo (francisalonzo29@gmail.com)
 * @brief Driver to support Sd card for our custom board and reduce run time errors
 * @version 0.1
 * @date 2022-01-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "sd_card.h"

SD_Card::SD_Card(SDBlockDevice *sd, LittleFileSystem *fs)
{
    _sd = sd;
    _fs = fs;
}

SD_Card::~SD_Card()
{
    _fs->unmount(_sd);
}

int8_t SD_Card::initializeSD(bool create_files)
{
    int error = _fs->mount(_sd);

    if(error < 0)
    {
        error = _fs->reformat(_sd);

        if(error < 0)
        {        
            return -ENODEV;
        }
    }

    if(create_files)
    {
        for(uint8_t i = 0; i < NB_FILES; ++i)
        {
            FILE *fd = fopen(array + i, "w+");
            if(fd == NULL)
            {
                return -EAGAIN;
            }
            fclose(fd);
        }
    }
}

int8_t SD_Card::create_file(const char *file_name)
{

}

int8_t SD_Card::write_to_SD(const char *file_name ,char *data, size_t size)
{

}

int8_t SD_Card::read_from_SD(char *data, size_t size)
{

}