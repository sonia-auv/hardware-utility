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

int8_t SD_Card::SD_Card(SDBlockDevice *sd, LittleFileSystem *fs, bool open_files)
{
    _sd = sd;
    _fs = fs;
    _fs->mount(&(*_sd));
}

void SD_Card::~SD_Card()
{
    _fs->umount(&(*_sd));
}