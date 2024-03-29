/**
 * @file PCA9531.cpp.
 * @brief PCA9531 class source file
*/

#include "PCA9531.h"

PCA9531::PCA9531(I2C *i2c, char address)
{
    _i2c = i2c;
    addr = address;
}

PCA9531::~PCA9531()
{
}

void PCA9531::setLEDs(uint16_t state)
{
    setSelectorLEDs(state, LS0_REG);
    setSelectorLEDs((state >> 8), LS1_REG);
}

void PCA9531::setSelectorLEDs(uint8_t state, uint8_t selector)
{
    char temp[2];

    temp[0] = selector;
    temp[1] = state;

    _i2c->write(addr, temp, 2);
}

void PCA9531::setPrescaler(uint8_t prescaler, uint8_t pwm_register)
{
    char temp[2];

    if(pwm_register == 1)
    {
        temp[0] = PSC1_REG;
    }
    else
    {
        temp[0] = PSC0_REG;
    }

    temp[1] = prescaler;

    _i2c->write(addr, temp, 2);
}

void PCA9531::setDutyCycle(uint8_t duty_cycle, uint8_t pwm_register)
{
    char temp[2];

    if(pwm_register == 1)
    {
        temp[0] = PWM1_REG;
    }
    else
    {
        temp[0] = PWM0_REG;
    }

    temp[1] = duty_cycle;

    _i2c->write(addr, temp, 2);    
}