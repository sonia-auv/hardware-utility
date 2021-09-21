/*
 * INA228 voltage/temprature monitor library
 *
 *
 * Copyright (c) 2013 Davy Van Belle, MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
 * and associated documentation files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, 
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or 
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/** @file
 * @brief LTC29990 I2C
 */
 
#include "mbed.h"
#include "INA228.h"

INA228::INA228 (I2C* i2c, char addr)
{
    _i2c = i2c;
    _addr = addr;

    _ShuntR = 0;
    _CURR_LSB = 0;
}

void INA228::setConfig (uint16_t reg)
{
    writeINA228(CONF, reg);
}    

uint16_t INA228::getConfig()
{
    uint16_t value;
    readINA228(CONF, &value);
    return value;
}

void INA228::setConfigADC(uint16_t reg)
{
    writeINA228(ADC_CONFIG, reg);
}

uint16_t INA228::getConfigADC()
{
    uint16_t value;
    readINA228(ADC_CONFIG, &value);
    return value;
}

void INA228::setShuntCal(uint16_t reg)
{
    writeINA228(SHUNT_CAL, reg);
}

uint16_t INA228::getShuntCal()
{
    uint16_t value;
    readINA228(SHUNT_CAL, &value);
    return value;
}

void INA228::setTempCo(uint16_t reg)
{
    writeINA228(SHUNT_TEMPCO, reg);
}

uint16_t INA228::getTempCo()
{
    uint16_t value;
    readINA228(SHUNT_TEMPCO, &value);
    return value;
}

float_t INA228::getShuntVolt() // To be reviewed for negation
{
    uint32_t value;
    readINA228(VSHUNT, &value);
    return (float_t)(value >> 4)*SHUNT_LSB;
}

float_t INA228::getBusVolt() // To be reviewed for negation
{
    uint32_t value;
    readINA228(VBUS, &value);
    return (float_t)(value >> 4)*BUS_LSB;
}

float_t INA228::getDieTemp()
{
    uint16_t value;
    readINA228(DIETEMP, &value);
    return (float_t)value*TEMP_LSB;
}

float_t INA228::getCurrent() // To be reviewed for negation
{
    uint32_t value;
    readINA228(CURRENT, &value);
    
    float_t data = (float_t)((value >> 4) & 0x7FFFF);
    uint8_t sign = (value >> 23) & 0x1;
    
    if(sign) return -data*_CURR_LSB;
    else return data*_CURR_LSB;
}

float_t INA228::getPower()
{
    uint32_t value;
    readINA228(POWER, &value);
    return (float_t)value*_POWER_LSB;
}

float_t INA228::getEnergy()
{
    uint64_t value;
    readINA228(ENERGY, &value);
    return (float_t)value*_ENERGY_LSB;
}

float_t INA228::getCharge() // To be reviewed for negation
{
    uint64_t value;
    readINA228(CHARGE, &value);
    return (float_t)value*_CHARGE_LSB;
}

void INA228::setAlertFlags(uint16_t reg)
{
    writeINA228(DIAG_ALRT, reg);
} 

uint16_t INA228::getAlertFlags()
{
    uint16_t value;
    readINA228(DIAG_ALRT, &value);
    return value;
}

void INA228::setSOVL(uint16_t reg)
{
    writeINA228(SOVL, reg);
}

float_t INA228::getSOVL() // Conversion factor
{
    uint16_t value;
    readINA228(SOVL, &value);
    return (float_t)value*SHUNT_OVER_UNDER_VOLTAGE_LSB;
}

void INA228::setSUVL(uint16_t reg)
{
    writeINA228(SUVL, reg);
}

float_t INA228::getSUVL() // Conversion factor
{
    uint16_t value;
    readINA228(SUVL, &value);
    return (float_t)value*SHUNT_OVER_UNDER_VOLTAGE_LSB;
}

void INA228::setBOVL(uint16_t reg)
{
    writeINA228(BOVL, reg);
}

float_t INA228::getBOVL() // Conversion factor
{
    uint16_t value;
    readINA228(BOVL, &value);
    return (float_t)value*BUS_OVER_UNDER_VOLTAGE_LSB;
}

void INA228::setBUVL(uint16_t reg)
{
    writeINA228(BUVL, reg);
}

float_t INA228::getBUVL() // Conversion factor
{
    uint16_t value;
    readINA228(BUVL, &value);
    return (float_t)value*BUS_OVER_UNDER_VOLTAGE_LSB;
}

void INA228::setOverTempLimit(uint16_t reg)
{
    writeINA228(TEMP_LIMIT, reg);
}

float_t INA228::getOverTempLimit() // Conversion factor
{
    uint16_t value;
    readINA228(TEMP_LIMIT, &value);
    return (float_t)value;
}

void INA228::setOverPowerLimit(uint16_t reg)
{
    writeINA228(PWR_LIMIT, reg);
}

float_t INA228::getOverPowerLimit() // Conversion factor
{
    uint16_t value;
    readINA228(PWR_LIMIT, &value);
    return value;
}

uint16_t INA228::getManufacturer()
{
    uint16_t value;
    readINA228(MANUFACTURER_ID, &value);
    return value;
}

uint16_t INA228::getID()
{
    uint16_t value;
    readINA228(DEVICE_ID, &value);
    return value;
}

void INA228::setShuntRValue(float_t val)
{
    _ShuntR = val;
}

float_t INA228::getShuntRValue(void)
{
    return _ShuntR;
}


void INA228::setCurrentLSB(float_t val)
{
    _CURR_LSB = val;
    _POWER_LSB = _CURR_LSB*3.2;
    _ENERGY_LSB = _POWER_LSB*16.0;
    _CHARGE_LSB = _CURR_LSB;
}

float_t INA228::getCurrentLSB()
{
    return _CURR_LSB;
}

void INA228::writeINA228(char cmd, uint16_t reg)
{
    char buffer[3];
    buffer[0] = cmd;
    buffer[1] = (char) ((reg & 0xFF00) >> 8);
    buffer[2] = (char) (reg & 0x00FF);
    _i2c->write(_addr,buffer,3);
}

void INA228::readINA228(char cmd, uint16_t *value)
{
    char buff[2];
    _i2c->write(_addr,&cmd,1,true);
    _i2c->read(_addr+1,buff,2);
    *value = (buff[0] << 8) | buff[1];
}

void INA228::writeINA228(char cmd, uint32_t reg)
{
    // Not used
}

void INA228::readINA228(char cmd, uint32_t *value)
{
    char buff[3];
    _i2c->write(_addr,&cmd,1,true);
    _i2c->read(_addr+1,buff,3);
    *value = (buff[0] << 16) | (buff[1] << 8) | buff[2];
}

void INA228::writeINA228(char cmd, uint64_t reg)
{
    // Not used
}

void INA228::readINA228(char cmd, uint64_t *value)
{
    char buff[5];
    _i2c->write(_addr,&cmd,1,true);
    _i2c->read(_addr+1,buff,5);
    *value = (buff[0] << 32) | (buff[1] << 24) | (buff[2] << 16) | (buff[4] << 8) | buff[5];
}