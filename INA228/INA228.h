/*
 * Texas Instruments INA228 voltage/ current/ power monitor library
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
 * @brief INA228 I2C
 */
 
#ifndef INA228_H
#define INA228_H

#include "mbed.h"

#define CONF 0x00
#define ADC_CONFIG 0x01
#define SHUNT_CAL 0x02
#define SHUNT_TEMPCO 0x03
#define VSHUNT 0x04
#define VBUS 0x05
#define DIETEMP 0x06
#define CURRENT 0x07
#define POWER 0x08
#define ENERGY 0x09
#define CHARGE 0x0A
#define DIAG_ALRT 0x0B
#define SOVL 0x0C
#define SUVL 0x0D
#define BOVL 0x0E
#define BUVL 0x0F
#define TEMP_LIMIT 0x10
#define PWR_LIMIT 0x11
#define MANUFACTURER_ID 0x3E
#define DEVICE_ID 0x3F

#define SHUNT_LSB 0.000000078125 //ADCRANGE = 1
#define BUS_LSB 0.0001953125
#define TEMP_LSB 0.0078125
#define SHUNT_OVER_UNDER_VOLTAGE_LSB 0.00000125 // ADCRANGE = 1
#define BUS_OVER_UNDER_VOLTAGE_LSB 0.003125

/** INA228 class 
 */
class INA228 {
public:
    /** init INA228 class
     * @param *i2c pointer to I2C serial interface
     * @param addr sensor I2C address
     */
    INA228 (I2C* i2c, char addr); 

    /** Set the configuration of the device
     * @param reg desired Configure Register bits
     */
    void setConfig (uint16_t reg);
    
    /** Get device Configuration register
     */  
    uint16_t getConfig();
    
    void setConfigADC(uint16_t reg);

    uint16_t getConfigADC();

    void setShuntCal(uint16_t reg);

    uint16_t getShuntCal();

    void setTempCo(uint16_t reg);

    uint16_t getTempCo();
    
    /** Get the voltage over the shunt
    */
    float_t getShuntVolt();

    /** Get the voltage of the bus rail
     */
    float_t getBusVolt();

    float_t getDieTemp();
    
    /** Get the current measured through the shunt.
     * in order to get the current you need to set the shut resistor value first
     */  
    float_t getCurrent();
    
    float_t getPower();

    float_t getEnergy();

    float_t getCharge();

    void setAlertFlags(uint16_t reg);
    
    uint16_t getAlertFlags();

    void setSOVL(uint16_t reg);

    float_t getSOVL();

    void setSUVL(uint16_t reg);

    float_t getSUVL();

    void setBOVL(uint16_t reg);

    float_t getBOVL();

    void setBUVL(uint16_t reg);

    float_t getBUVL();

    void setOverTempLimit(uint16_t reg);

    float_t getOverTempLimit();

    void setOverPowerLimit(uint16_t reg);

    float_t getOverPowerLimit();

    uint16_t getManufacturer();
    
    /** Get the unique ID of the device
    */
    uint16_t getID();
    
    /** Set the shunt resistor
    *@param val value in ohm
    */
    void setShuntRValue(float_t val);
    
    float_t getShuntRValue(void);
    
    /** Set the current LSB for maximum current in decimal
    */
    void setCurrentLSB(float_t val);

    float_t getCurrentLSB();
    
protected:


private:
    char _addr;
    I2C *_i2c;
    float_t _ShuntR;
    float_t _CURR_LSB;
    float_t _POWER_LSB;
    float_t _ENERGY_LSB;
    float_t _CHARGE_LSB;
    
    void writeINA228(char cmd, uint16_t reg);
    void readINA228(char cmd, uint16_t *value);

    void writeINA228(char cmd, uint32_t reg);
    void readINA228(char cmd, uint32_t *value);

    void writeINA228(char cmd, uint64_t reg);
    void readINA228(char cmd, uint64_t *value);

    uint32_t invert_data(uint32_t data);
};
    
#endif