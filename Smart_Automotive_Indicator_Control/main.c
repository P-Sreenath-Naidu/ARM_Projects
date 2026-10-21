#include <lpc21xx.h>
#include "header.h"

#define LEFT_LED  (1<<8)   // P0.8
#define RIGHT_LED (1<<9)   // P0.9

#define OFF    0
#define LEFT   1
#define RIGHT  2
#define HAZARD 3

int main(void)
{
    unsigned char cmd;
    unsigned int mode = OFF;
    unsigned int count = 0;
    unsigned int led_state = 0;

    // Configure LEDs as outputs
    IODIR0 = LEFT_LED | RIGHT_LED;

    // Active-low: HIGH means OFF
    IOSET0 = LEFT_LED | RIGHT_LED;

    lcd_init();
    uart0_init(9600);

    lcd_cmd(0x80);
    lcd_string("Indicator System");
    lcd_cmd(0xC0);
    lcd_string("Mode: OFF");

    uart0_tx_string("\r\nAutomotive Indicator Controller\r\n");
    uart0_tx_string("L - Left Indicator\r\n");
    uart0_tx_string("R - Right Indicator\r\n");
    uart0_tx_string("H - Hazard Lights\r\n");
    uart0_tx_string("O - Indicators OFF\r\n");
    uart0_tx_string("S - Display Status\r\n");
		

    while (1)
    {
        if (U0LSR & 0x01)
        {
            cmd = uart0_rx();

            if (cmd >= 'a' && cmd <= 'z')
                cmd =cmd-32;

            switch (cmd)
            {
                case 'L':
                    mode = LEFT;
                    uart0_tx_string("\r\nLeft Indicator Selected\r\n");
                    break;

                case 'R':
                    mode = RIGHT;
                    uart0_tx_string("\r\nRight Indicator Selected\r\n");
                    break;

                case 'H':
                    mode = HAZARD;
                    uart0_tx_string("\r\nHazard Lights Selected\r\n");
                    break;

                case 'O':
                    mode = OFF;
                    uart0_tx_string("\r\nIndicators OFF\r\n");
                    break;

                case 'S':
                    uart0_tx_string("\r\nCurrent Mode: ");

                    if (mode == LEFT)
                        uart0_tx_string("LEFT\r\n");
                    else if (mode == RIGHT)
                        uart0_tx_string("RIGHT\r\n");
                    else if (mode == HAZARD)
                        uart0_tx_string("HAZARD\r\n");
                    else
                        uart0_tx_string("OFF\r\n");

                    break;

                case '\r':
                case '\n':
                    break;

                default:
                    uart0_tx_string("\r\nInvalid Command\r\n");
                    break;
            }

            count = 0;
            led_state = 0;

            // Active-low: set HIGH to turn both LEDs OFF
            IOSET0 = LEFT_LED | RIGHT_LED;

            lcd_cmd(0x80);
            lcd_string("Indicator System");

            lcd_cmd(0xC0);

            if (mode == LEFT)
                lcd_string("Mode: LEFT      ");
            else if (mode == RIGHT)
                lcd_string("Mode: RIGHT     ");
            else if (mode == HAZARD)
                lcd_string("Mode: HAZARD    ");
            else
                lcd_string("Mode: OFF       ");
        }

        delay_ms(10);
        count += 10;

        if (count >= 500)
        {
            count = 0;
            led_state = !led_state;

            // First turn both LEDs OFF
            IOSET0 = LEFT_LED | RIGHT_LED;

            if (led_state)
            {
                // Active-low: clear the pin to turn LED ON
                if (mode == LEFT)
                    IOCLR0 = LEFT_LED;

                else if (mode == RIGHT)
                    IOCLR0 = RIGHT_LED;

                else if (mode == HAZARD)
                    IOCLR0 = LEFT_LED | RIGHT_LED;
            }
        }

        if (mode == OFF)
            IOSET0 = LEFT_LED | RIGHT_LED;
    }
}

