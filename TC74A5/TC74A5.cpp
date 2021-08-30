
#include "TC74A5.h"

TC74A5::TC74A5(I2C * i2c, char address)
{
    _i2c = i2c;
    adrr = address;
}

char TC74A5::getTemp()
{
    char cmd[3];

    cmd[0] = TEMP;
    cmd[1] = adrr; 

    _i2c->read(adrr+1,cmd,3);

    return cmd[0];
}