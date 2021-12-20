/*
 * Texas Instruments INA229 voltage/ current/ power monitor library
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
 
#ifndef INA229_H
#define INA229_H

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

/** INA229 class 
 */
class INA229 {
public:
    /**
     * @brief Constructor of the object INA229
     * 
     * @param i2c pointer to I2C serial interface
     * @param addr sensor I2C address
     */
    INA229 (I2C* i2c, char addr); 

    /**
     * @brief Set the configuration
     * 
     * @param reg desired Configure Register bits
     */
    void setConfig (uint16_t reg);
    
    /**
     * @brief Get the Configuration 
     * 
     * @return uint16_t Configuration
     */  
    uint16_t getConfig();
    
    /**
     * @brief Set the ADC configuration
     * 
     * @param reg Desired ADC configuration bits
     */
    void setConfigADC(uint16_t reg);

    /**
     * @brief Get the ADC configuration
     * 
     * @return uint16_t ADC configuration
     */
    uint16_t getConfigADC();

    /**
     * @brief Set the shunt calibration of the current calculation
     * 
     * @param reg Value calculated for the shunt calibration
     */
    void setShuntCal(uint16_t reg);

    /**
     * @brief Get the Shunt calibration
     * 
     * @return uint16_t Value of the shunt calibration
     */
    uint16_t getShuntCal();

    /**
     * @brief Set the shunt temperature coefficient for the temperature compensation
     * 
     * @param reg The shunt temperature coefficient calculated at 25°C
     */
    void setTempCo(uint16_t reg);

    /**
     * @brief Get the shunt temperature coefficient
     * 
     * @return uint16_t Value of the shunt temperature coefficient
     */
    uint16_t getTempCo();
    
    /**
     * @brief Get the shunt voltage
     * 
     * @return float_t Value of the shunt voltage
     */
    float_t getShuntVolt();

    /**
     * @brief Get the bus voltage
     * 
     * @return float_t Value of the bus voltage
     */
    float_t getBusVolt();

    /**
     * @brief Get the temperature of the die
     * 
     * @return float_t Value of the temperature
     */
    float_t getDieTemp();
    
    /**
     * @brief Get the current calculated with the drop voltage of the shunt
     * 
     * @return float_t Value of the current through the shunt in Amperes
     */
    float_t getCurrent();
    
    /**
     * @brief Get the calculated power
     * 
     * @return float_t Value of the power in Watts
     */
    float_t getPower();

    /**
     * @brief Get the calculated energy
     * 
     * @return float_t Value of the energy in Joules
     */
    float_t getEnergy();

    /**
     * @brief Get the calculated charge
     * 
     * @return float_t Value of the charge in Coulombs
     */
    float_t getCharge();

    /**
     * @brief Set the diagnostic flags and alert
     * 
     * @param reg Value of the diagnostic flags register
     */
    void setAlertFlags(uint16_t reg);
    
    /**
     * @brief Get the diagnostic falgs and alert
     * 
     * @return uint16_t Value of the register
     */
    uint16_t getAlertFlags();

    /**
     * @brief Set the shunt overvoltage threshold
     * 
     * @param reg Value of the shunt overvoltage threshold for the register
     */
    void setSOVL(uint16_t reg);

    /**
     * @brief Get the shunt overvoltage threshold
     * 
     * @return float_t Value of the shunt overvoltage threshold
     */
    float_t getSOVL();

    /**
     * @brief Set the shunt undervoltage threshold
     * 
     * @param reg Value of the shunt undervoltage threshold for the register
     */
    void setSUVL(uint16_t reg);

    /**
     * @brief Get the shunt undervoltage threshold
     * 
     * @return float_t Value of the shunt undervoltage threshold
     */
    float_t getSUVL();

    /**
     * @brief Set the bus overvoltage threshold
     * 
     * @param reg Value of the bus overvoltage threshold for the register
     */
    void setBOVL(uint16_t reg);

    /**
     * @brief Get the bus overvoltage threshold
     * 
     * @return float_t Value of the bus overvotlage threshold
     */
    float_t getBOVL();

    /**
     * @brief Set the bus undervoltage threshold
     * 
     * @param reg Value of the undervoltage threshold for the register
     */
    void setBUVL(uint16_t reg);

    /**
     * @brief Get the bus undervoltage threshold
     * 
     * @return float_t Value of the bus undervoltage threshold
     */
    float_t getBUVL();

    /**
     * @brief Set the temperature over-limit threshold
     * 
     * @param reg Value of the temperature over-limit threshold for the register
     */
    void setOverTempLimit(uint16_t reg);

    /**
     * @brief Get the temperature over-limit threshold
     * 
     * @return float_t Value of the temperature over-limit threshold
     */
    float_t getOverTempLimit();

    /**
     * @brief Set the power over-limit threshold
     * 
     * @param reg Value of the power over-limit threshold for the register
     */
    void setOverPowerLimit(uint16_t reg);

    /**
     * @brief Get the power over-limit threshold
     * 
     * @return float_t Value of the power over-limit threshold
     */
    float_t getOverPowerLimit();

    /**
     * @brief Get the Manufacturer ID
     * 
     * @return uint16_t TI in Ascii
     */
    uint16_t getManufacturer();
    
    /**
     * @brief Get the ID of
     * 
     * @return uint16_t Value of the ID
     */
    uint16_t getID();
    
    /** 
     * @brief Set the value for the shunt resistor
     * 
     * @param val Value of the shunt resistor in Ohms
     */
    void setShuntRValue(float_t val);
    
    /**
     * @brief Get the value of the shunt value programmed
     * 
     * @return float_t Shunt value 
     */
    float_t getShuntRValue(void);
    
    /**
     * @brief Set the Current LSB for calculation
     * 
     * @param val LSB value
     */
    void setCurrentLSB(float_t val);

    /**
     * @brief Get the Current LSB
     * 
     * @return float_t Current LSB
     */
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
    
    /**
     * @brief Write uint16_t to the INA229 with I2C
     * 
     * @param cmd Command
     * @param reg Value for the register
     */
    void writeINA229(char cmd, uint16_t reg);

    /**
     * @brief Read uint16_t to the INA229 with I2C
     * 
     * @param cmd Command
     * @param value pointer for the value of the register
     */
    void readINA229(char cmd, uint16_t *value);

    /**
     * @brief Read uint32_t to the INA229 with I2C
     * 
     * @param cmd Command
     * @param value pointer for the value of the register
     */
    void readINA229(char cmd, uint32_t *value);

    /**
     * @brief Read uint64_t to the INA229 with I2C
     * 
     * @param cmd Command
     * @param value pointer for the value of the register
     */
    void readINA229(char cmd, uint64_t *value);
};
    
#endif