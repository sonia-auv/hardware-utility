#ifndef UTILITY_H
#define UTILITY_H

#include "RS485/RS485_definition.h"
#include "RS485/RS485.h"
#include "mbed.h"

/**
 * Calculation of voltage at the input of a voltage divider
 * 
 * @param value obtained value from the divider
 * @return voltage at R1 of the voltage divider
*/
float_t calcul_tension(double_t value, double_t votlageRef, double_t R1, double_t R2);

/**
 * Puts a float in a array
 * 
 * @param array pointer of the array to put data value in
 * @param value float that has to be put in the array 
*/
void putFloatInArray(uint8_t * array, float_t value, uint8_t offset = 0);

/**
 * Put a char array in a array
 * 
 * @param array pointer of the array for the converted data
 * @param data pointer of an array of char
 * @param multiplicator float that can multiply the end result (optional)
*/
void putCharInArray(uint8_t * array, char * data, float_t multiplicator = 1);

/**
 * Transform a char array in a float
 * 
 * @param data pointer of an array of char
 * @param multiplicator float that can multiply the end result (optional)
 * @return value of the transformation
*/
float_t putCharInFloat(char * data, float_t multiplicator = 1);

/**
 * @brief Read from analog
 * 
 * Read from an analog pin and compute an average  
 * 
 * @param input Analog pin 
 * @param voltageref Reference voltage of the board
 * @return double_t Out value of the average
 */
double_t readfromAnalog(AnalogIn input, double_t voltageref, double_t R1, double_t R2);

/**
 * @brief thread to detect if the board is alive
 * 
 * Thread that wait for a is alive packet and return is alive to the master  
 * 
 * @param rs
 */
void isAliveThread(RS485* rs);

#endif 