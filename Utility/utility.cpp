/***
 * 
 * Author : Francis Alonzo
 * 
 * Utilities for multiple boards
 * 
 ***/

#include "utility.h"

float_t calcul_tension(double_t value, double_t voltageRef, double_t R1, double_t R2)
{
    return (voltageRef*value*(R1+R2))/R2;
}

void putFloatInArray(uint8_t * array, float_t value, uint8_t offset)
{
    union{
        uint8_t sending[4];
        float_t data;
    } temp;

    temp.data = value;

    for(uint8_t i=0;i<4;++i)
    {
        array[i+offset] = temp.sending[i];
    }
}


void putCharInArray(uint8_t * array, char * data, float_t multiplicator)
{
    float_t value = putCharInFloat(data,multiplicator);
    putFloatInArray(array,value);
}

float_t putCharInFloat(char * data, float_t multiplicator)
{
    float_t value =0;

    for(uint8_t i=15;i>0;--i)
    {
        value += pow(data[i],15-i);
    }

    return value*multiplicator;
}

double_t readfromAnalog(AnalogIn input, double_t voltageRef, double_t R1, double_t R2)
{
    double_t voltage_battery = 0;
    uint8_t i;

    for(i = 0; i < 10; ++i)
    {
      voltage_battery += calcul_tension(input.read(), voltageRef, R1, R2);
      ThisThread::sleep_for(20);
    }
    return voltage_battery / (double_t)i;
}

void isAliveThread(RS485* rs)
{
    uint8_t cmd_array[1]={CMD_IS_ALIVE};
    uint8_t buffer[255]={0};

    while(true)
    {
        rs->read(cmd_array, 1, buffer);
        rs->write(rs->getBoardAdress(), CMD_IS_ALIVE, 0, buffer);
    }
}