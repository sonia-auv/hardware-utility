/**
 * @file TMP100.cpp.
 * @brief TMP100 class source file
*/

#include "TMP100.h"

TMP100::TMP100(I2C *i2c, char address)
{
    _i2c = i2c;
    _addr = address;
}

TMP100::TMP100(I2C *i2c, char address, TMP100_resolution_t resolution,TMP100_ShutdownMode_t shutDownMode)
{
    _i2c = i2c;
    _addr = address;

    setResolution(resolution);
    setShutdownMode(shutDownMode);
}

TMP100::~TMP100()
{
}

float TMP100::getTemperature(void)
{
    uint16_t val_reg=0;

    if(readTMP100(REG_TEMP, &val_reg) != NO_ERROR){
        return MIN_TEMP;
    }

    return TempRegToFloat(val_reg);
}

void TMP100::setResolution(TMP100_resolution_t resolution)
{
    uint8_t currentConfig;
    bool unexpextedValue = false;
    readTMP100(REG_CONFIG, &currentConfig);
    currentConfig &= ~MASK_CONFIG_RES; //remove current resolution config

    switch (resolution)
    {
    case 9_BITS:
        currentConfig |= 0b00;
        break;
    case 10_BITS:
        currentConfig |= 0b01;
        break;    
    case 11_BITS:
        currentConfig |= 0b10;
        break;
    case 12_BITS:
        currentConfig |= 0b11;
        break;   
    default:
        unexpextedValue = true;
        break;
    }

    if(!unexpextedValue){
        writeTMP100(REG_CONFIG, &currentConfig);
    }
}

void TMP100::setShutdownMode(TMP100_ShutdownMode_t mode)
{
    uint8_t currentConfig;
    bool unexpextedValue = false;
    readTMP100(REG_CONFIG, &currentConfig);
    currentConfig &= ~MASK_CONFIG_SD; //remove current shotdown config

    switch (mode)
    {
    case CONTINUOUS:
        currentConfig |= 0;
        break;
    case SINGLE:
        currentConfig |= 1;
        break;
    default:
        unexpextedValue = true;
        break;
    }

    if(!unexpextedValue){
        writeTMP100(REG_CONFIG, &currentConfig);
    }
}

TMP100_error_code_t TMP100::readTMP100(char cmd, uint16_t *value)
{
    char buff[2];
    int16_t status;

    if(value == NULL){
        return ERR_NULL_PTR;
    }

    if(_i2c->write(_addr,&cmd,1,true)){
        return ERR_INVALID_READ;
    }

    _i2c->read(_addr+1,buff,2);
    *value = (buff[0] << 8) | buff[1]; 
}

TMP100_error_code_t TMP100::readTMP100(char cmd, uint8_t *value)
{
    char buff;
    int16_t status;

    if(value == NULL){
        return ERR_NULL_PTR;
    }

    if(_i2c->write(_addr,&cmd,1,true)){
        return ERR_INVALID_READ;
    }

    _i2c->read(_addr+1,&buff,1);
    *value = buff; 
}


void TMP100::writeTMP100(char cmd, uint16_t reg)
{
    char buffer[3];
    buffer[0] = cmd;
    buffer[1] = (char) ((reg & 0xFF00) >> 8);
    buffer[2] = (char) (reg & 0x00FF);
    _i2c->write(_addr,buffer,3);
}

void TMP100::writeTMP100(char cmd, uint8_t reg)
{
    char buffer[2];
    buffer[0] = cmd;
    buffer[1] = (char) (reg);
    _i2c->write(_addr,buffer,2);
}

float TMP100::TempRegToFloat(uint16_t reg)
{
    bool isNegative = (reg >> 15);
    float temp=0;

    reg = reg >> 4;

    if(isNegative){
        reg = TwosComplementConvert(reg) & 0x0FFF;
    }

    temp = ((float)reg)/16.0

    if(isNegative){
        temp*=-1.0;
    }

    return temp;

}

uint16_t TMP100::TwosComplementConvert(uint16_t val)
{
    return (~val) +1;
}

