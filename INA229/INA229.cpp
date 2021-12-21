/*
 * INA229 voltage/temprature monitor library
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
 * @brief INA229 I2C
 */
 
#include "INA229.h"

INA229::INA229(SPI* spi, DigitalOut *cs)
{
    _spi = spi;
    _cs = cs;

    _ShuntR = 0;
    _CURR_LSB = 0;
}

void INA229::setConfig(uint16_t reg)
{
    writeINA229(CONF, reg);
}    

uint16_t INA229::getConfig()
{
    uint16_t value;
    readINA229(CONF, &value);
    return value;
}

void INA229::setConfigADC(uint16_t reg)
{
    writeINA229(ADC_CONFIG, reg);
}

uint16_t INA229::getConfigADC()
{
    uint16_t value;
    readINA229(ADC_CONFIG, &value);
    return value;
}

void INA229::setShuntCal(uint16_t reg)
{
    writeINA229(SHUNT_CAL, reg);
}

uint16_t INA229::getShuntCal()
{
    uint16_t value;
    readINA229(SHUNT_CAL, &value);
    return value;
}

void INA229::setTempCo(uint16_t reg)
{
    writeINA229(SHUNT_TEMPCO, reg);
}

uint16_t INA229::getTempCo()
{
    uint16_t value;
    readINA229(SHUNT_TEMPCO, &value);
    return value;
}

float_t INA229::getShuntVolt() // To be reviewed for negation
{
    uint32_t value;
    readINA229(VSHUNT, &value);
    return (float_t)(value >> 4)*SHUNT_LSB;
}

float_t INA229::getBusVolt() // To be reviewed for negation
{
    uint32_t value;
    readINA229(VBUS, &value);
    return (float_t)(value >> 4)*BUS_LSB;
}

float_t INA229::getDieTemp()
{
    uint16_t value;
    readINA229(DIETEMP, &value);
    return (float_t)value*TEMP_LSB;
}

float_t INA229::getCurrent() // To be reviewed for negation
{
    uint32_t value;
    readINA229(CURRENT, &value);
    
    uint8_t sign = (value >> 23) & 0x1;
    value = (value >> 4) & 0x7FFFF;
    
    if(sign) return (float_t)(~value & 0x7FFFF)*_CURR_LSB*-1.0;
    else return (float_t)value*_CURR_LSB;
}

float_t INA229::getPower()
{
    uint32_t value;
    readINA229(POWER, &value);
    return (float_t)value*_POWER_LSB;
}

float_t INA229::getEnergy()
{
    uint64_t value;
    readINA229(ENERGY, &value);
    return (float_t)value*_ENERGY_LSB;
}

float_t INA229::getCharge() // To be reviewed for negation
{
    uint64_t value;
    readINA229(CHARGE, &value);
    return (float_t)value*_CHARGE_LSB;
}

void INA229::setAlertFlags(uint16_t reg)
{
    writeINA229(DIAG_ALRT, reg);
} 

uint16_t INA229::getAlertFlags()
{
    uint16_t value;
    readINA229(DIAG_ALRT, &value);
    return value;
}

void INA229::setSOVL(uint16_t reg)
{
    writeINA229(SOVL, reg);
}

float_t INA229::getSOVL() // Conversion factor
{
    uint16_t value;
    readINA229(SOVL, &value);
    return (float_t)value*SHUNT_OVER_UNDER_VOLTAGE_LSB;
}

void INA229::setSUVL(uint16_t reg)
{
    writeINA229(SUVL, reg);
}

float_t INA229::getSUVL() // Conversion factor
{
    uint16_t value;
    readINA229(SUVL, &value);
    return (float_t)value*SHUNT_OVER_UNDER_VOLTAGE_LSB;
}

void INA229::setBOVL(uint16_t reg)
{
    writeINA229(BOVL, reg);
}

float_t INA229::getBOVL() // Conversion factor
{
    uint16_t value;
    readINA229(BOVL, &value);
    return (float_t)value*BUS_OVER_UNDER_VOLTAGE_LSB;
}

void INA229::setBUVL(uint16_t reg)
{
    writeINA229(BUVL, reg);
}

float_t INA229::getBUVL() // Conversion factor
{
    uint16_t value;
    readINA229(BUVL, &value);
    return (float_t)value*BUS_OVER_UNDER_VOLTAGE_LSB;
}

void INA229::setOverTempLimit(uint16_t reg)
{
    writeINA229(TEMP_LIMIT, reg);
}

float_t INA229::getOverTempLimit() // Conversion factor
{
    uint16_t value;
    readINA229(TEMP_LIMIT, &value);
    return (float_t)value;
}

void INA229::setOverPowerLimit(uint16_t reg)
{
    writeINA229(PWR_LIMIT, reg);
}

float_t INA229::getOverPowerLimit() // Conversion factor
{
    uint16_t value;
    readINA229(PWR_LIMIT, &value);
    return value;
}

uint16_t INA229::getManufacturer()
{
    uint16_t value;
    readINA229(MANUFACTURER_ID, &value);
    return value;
}

uint16_t INA229::getID()
{
    uint16_t value;
    readINA229(DEVICE_ID, &value);
    return value;
}

void INA229::setShuntRValue(float_t val)
{
    _ShuntR = val;
}

float_t INA229::getShuntRValue(void)
{
    return _ShuntR;
}


void INA229::setCurrentLSB(float_t val)
{
    _CURR_LSB = val;
    _POWER_LSB = _CURR_LSB*3.2;
    _ENERGY_LSB = _POWER_LSB*16.0;
    _CHARGE_LSB = _CURR_LSB;
}

float_t INA229::getCurrentLSB()
{
    return _CURR_LSB;
}

void INA229::writeINA229(char cmd, uint16_t reg)
{
    // char buffer[3];
    // buffer[0] = cmd;
    // buffer[1] = (char) ((reg & 0xFF00) >> 8);
    // buffer[2] = (char) (reg & 0x00FF);
    // _i2c->write(_addr,buffer,3);
}

void INA229::readINA229(char cmd, uint16_t *value)
{
    // char buff[2];
    // _i2c->write(_addr,&cmd,1,true);
    // _i2c->read(_addr+1,buff,2);
    // *value = (buff[0] << 8) | buff[1];
}

void INA229::readINA229(char cmd, uint32_t *value)
{
    // char buff[3];
    // _i2c->write(_addr,&cmd,1,true);
    // _i2c->read(_addr+1,buff,3);
    // *value = (buff[0] << 16) | (buff[1] << 8) | buff[2];
}

void INA229::readINA229(char cmd, uint64_t *value)
{
    // char buff[5];
    // _i2c->write(_addr,&cmd,1,true);
    // _i2c->read(_addr+1,buff,5);
    // *value = (buff[0] << 32) | (buff[1] << 24) | (buff[2] << 16) | (buff[4] << 8) | buff[5];
}