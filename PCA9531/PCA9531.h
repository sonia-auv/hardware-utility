/**
 * @file PCA9531.h
 * @brief The header file for the PCA9531
 */

#ifndef PCA9531_H
#define PCA9531_H

#include "mbed.h"

#define INPUT_REG 0x00 // Input register
#define PSC0_REG 0x01 // Frequency prescaler 0
#define PWM0_REG 0x02 // PWM register 0
#define PSC1_REG 0x03 // Frequency prescaler 1
#define PWM1_REG 0x04 // PWM register 1
#define LS0_REG 0x05 // LED0 to LED3
#define LS1_REG 0x06 // LED4 to LED7

/**
 * @brief PCA9531 I2C class
 *  LED Driver 
 */

class PCA9531
{

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
 */

    void setLEDs(uint16_t state);

/**
 * @brief Set LEDs of one selector register
 * 
 * @param state array of the state of the leds to set
 * @param selector selector to set the register 
 */

    void setSelectorLEDs(uint8_t state, uint8_t selector);

/**
 * @brief
 * 
 * @param prescaler value of the prescaler for the period of the PWM
 * @param pwm_register select the register (0 or 1)
 */

    void setPrescaler(uint8_t prescaler, uint8_t pwm_register);

/**
 * @brief 
 * 
 * @param duty_cycle value on 256 for the duty cycle of the pwm
 * @param pwm_register select the register (0 or 1)
 */

    void setDutyCycle(uint8_t duty_cycle, uint8_t pwm_register);
    
private:
    char addr;
    I2C *_i2c;
};

#endif
