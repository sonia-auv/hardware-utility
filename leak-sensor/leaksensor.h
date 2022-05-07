#ifndef LEAKSENSOR_H
#define LEAKSENSOR_H
#include "mbed.h"
class leaksensor
{
private:
    DigitalIn _pin;
public:
/**
     * Init of the class
     * 
     * @param pin pin connected to the leak sensor 
    */
    leaksensor(DigitalIn pin);
    /**
     * Get the status of the leak sensor
     *  
     * @return if leak is detected. return 1 otherwise 0
    */
    char getStatus();
    /**
     * @brief Destroy the leaksensor object
     * 
     */
    ~leaksensor();
};



#endif

