#ifndef TC74A5_H
#define TC74A5_H

#include "mbed.h"

#define CONFIGT 0x01
#define TEMP 0x00

/** @file
 * @brief TC74A5 I2C
 */

class TC74A5 
{
private :
    char adrr; 
    I2C * _i2c;

public :
    /**
     * Init of the class
     * 
     * @param i2c pointer of the bus used on the microcontroller
     * @param address of the TC74A5 
    */
    TC74A5(I2C * i2c, char address);

    /**
     * Get the temperature of the board
     *  
     * @return data from the sensor in char
    */
    char getTemp();

};

#endif