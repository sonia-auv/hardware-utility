leaksensor::leaksensor(DigitalIn pin)
{
    _pin= pin;

    
}
char leaksensor::getStatus()
{
    if(_pin)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
leaksensor::~leaksensor()
{
}