/**
 * @file PCA9531.h
 * @brief The header file for the PCA9531
 */

#ifndef PCA9531_H
#define PCA9531_H

#include "mbed.h"

#define LS0 0x05 // LED0 to LED3
#define LS1 0x06 // LED4 to LED7

/**
 * @brief PCA9531 I2C class
 *  LED Driver 
 */

class PCA9531
{
private:
    char addr;
    I2C *_i2c;

/**
 * @brief Set LEDs of one selector register
 * 
 * @param state array of the state of the leds to set
 * @param selector selector to set the register 
 */

    void setSelectorLEDs(uint8_t state, uint8_t selector);

public:
/**
 * @brief PCA9531 Constructor
 * 
 * @param i2c pointer of the bus used on the microcontroller 
 * @param address of the PCA9531
 */

    PCA9531(I2C *i2c, char address);
    
/**
 * @brief Destroy the PCA9531 object
 * 
 */

    ~PCA9531();

/**
 * @brief Set LEDs of the driver
 * 
 * @param state array of the state of the leds to set
 * 
 * @return uint8_t acknowledge of the send
 */

    void setLEDs(uint16_t state);
    
};

#endif