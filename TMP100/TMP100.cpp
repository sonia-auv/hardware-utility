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

