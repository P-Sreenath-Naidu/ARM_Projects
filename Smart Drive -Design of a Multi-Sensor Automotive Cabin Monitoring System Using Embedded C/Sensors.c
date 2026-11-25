#include <lpc21xx.h>
#include "header.h"

// PIR SENSOR
#define PIR_SW ((IOPIN0 >> 6) & 1)

// ALCOHOL SENSOR 
float alcohol_read(void)
{
    unsigned int adc_value;
    float voltage;

    adc_value = adc_read(1);

    voltage = (adc_value * 3.3) / 1023;

    return voltage;
}

// GAS SENSOR 
float gas_read(void)
{
    unsigned int adc_value;
    float voltage;

    adc_value = adc_read(2);

    voltage = (adc_value * 3.3) / 1023;

    return voltage;
}

// PIR SENSOR
unsigned int PIR_sensor(void)
{
    if(PIR_SW == 0)
        return 1;

    return 0;
}

