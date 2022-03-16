/**
 * @file TMP100.h
 * @brief The header file for the TMP100
 */

#ifndef TMP100_H
#define TMP100_H

#include "mbed.h"


typedef enum TMP100_error_code{
    NO_ERROR            = 0,
    ERR_NULL_PTR        =-1,
    ERR_INVALID_READ    =-2.
} TMP100_error_code_t;


/**
 * @brief TMP100 I2C class
 *  LED Driver 
 */

class TMP100
{
public:
/**
 * @brief TMP100 Constructor
 * 
 * @param i2c pointer of the bus used on the microcontroller 
 * @param address of the TMP100
 */

    TMP100(I2C *i2c, char address);
    
/**
 * @brief Destroy the TMP100 object
 * 
 */
    ~TMP100();

/**
 * @brief read the Temperature for the sensor
 * 
 * @return float temperature (in celsius)
 */
    float getTemperature(void);

private:
    char _addr;
    I2C *_i2c;

    const float MIN_TEMP = -128;

    /**
     * @brief Convert the value of a temperature register to float (temperature in celsius)
     * 
     * @param reg value of the temperature register
     * @return float    temprature represented by the temperature register
     */
    float TempRegToFloat(uint16_t reg);    

    /**
     * @brief Convert a negative two's complement value to a positive value and vice versa
     * 
     * @param val       value that will be converted
     * @return uint16_t converted value
     */
    uint16_t TwosComplementConvert(uint16_t val);
    

    /**
     * @brief Read a 16 bit value (2 consecutive register)
     * 
     * @param cmd 
     * @param value 
     */
    void TMP100::readTMP100(char cmd, uint16_t *value);


    //register definition
    const uint8_t REG_TEMP      = 0x00;
    const uint8_t REG_CONFIG    = 0x01;
    const uint8_t REG_T_LOW     = 0x02;
    const uint8_t REG_T_HICH    = 0x02;




};

#endif
