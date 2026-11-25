#include <lpc21xx.h>
#include <stdio.h>
#include "header.h"

#define GREEN_LED  (1 << 17)
#define YELLOW_LED (1 << 18)
#define RED_LED    (1 << 19)


#define TEMP_LIMIT     40
#define ALCOHOL_LIMIT  1.5
#define GAS_LIMIT      1.5

int main(void)
{
    unsigned int adc_val;
    unsigned int PIR;
    unsigned int status;

    float Vout, temperature;
    float alcohol, gas;

    IODIR0 |= GREEN_LED | YELLOW_LED | RED_LED;
    IOSET0 = GREEN_LED | YELLOW_LED | RED_LED;
	
    // INITIALIZATION
    uart0_init(9600);
    adc_init();
    lcd_init();

    while(1)
    {
        // LM35 TEMPERATURE READING
        adc_val = adc_read(0);

        Vout = (adc_val * 3.3) / 1023;

        temperature = Vout * 100;

        // ALCOHOL SENSOR READING
        alcohol = alcohol_read();

        // GAS SENSOR READING
        gas = gas_read();

        // PIR SENSOR READING
        PIR = PIR_sensor();

        // STATUS CHECKING
        if(temperature >= TEMP_LIMIT)
        {
            status = 3;
        }
        else if(gas >= GAS_LIMIT)
        {
            status = 3;
        }
        else if(alcohol >= ALCOHOL_LIMIT)
        {
            status = 3;
        }
        else if(PIR == 1)
        {
            status = 2;
        }
        else
        {
            status = 1;
        }

        // LED INDICATION
        IOSET0 = GREEN_LED | YELLOW_LED | RED_LED;

        if(status == 1)
        {
            IOCLR0 = GREEN_LED;
        }
        else if(status == 2)
        {
            IOCLR0 = YELLOW_LED;
        }
        else if(status == 3)
        {
            IOCLR0 = RED_LED;
        }

        // LCD DISPLAY
        lcd_cmd(0x80);

        lcd_string("TEMP: ");
        lcd_integer(temperature);
        lcd_string(" C ");

        lcd_cmd(0xC0);

        if(status == 1)
        {
            lcd_string("STATUS: NORMAL ");
        }
        else if(status == 2)
        {
            lcd_string("MOTION DETECTED");
        }
        else
        {
            lcd_string("WARNING DETECTED");
        }

        // UART DISPLAY
				uart0_tx_string("\r\n<------------------------------------------------------>\r\n");
				
        uart0_tx_string("Temperature:  ");
        uart0_integer(temperature);

        uart0_tx_string(" C \r\nAlcohol: ");
        uart0_integer(alcohol * 1000);

        uart0_tx_string(" mV \r\nGas: ");
        uart0_integer(gas * 1000);

        uart0_tx_string(" mV \r\nPIR: ");
        uart0_integer(PIR);

        uart0_tx_string("\r\n");
				
//				uart0_tx_string("\r\n<------------------------------------------------------>\r\n");

        delay_ms(750);
    }
}


