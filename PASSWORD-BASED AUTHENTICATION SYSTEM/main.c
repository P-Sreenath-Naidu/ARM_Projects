#include <lpc21xx.h>
#include "header.h"

#define GREEN_LED (1<<8)   // P0.8 - Active LOW
#define RED_LED   (1<<9)   // P0.9 - Active LOW

#define MAX_ATTEMPTS 3
#define MAX_PASSWORD_LENGTH 16

// Change your password here
#define PASSWORD "sai"

int main(void)
{
    unsigned char ch;
    char entered[MAX_PASSWORD_LENGTH + 1];

    unsigned int i, j;
    unsigned int attempts = 0;
    unsigned int correct;

    // Configure LEDs as outputs
    IODIR0 |= GREEN_LED | RED_LED;

    // Turn both LEDs OFF
    IOSET0 = GREEN_LED | RED_LED;

    // Initialize LCD and UART
    lcd_init();
    uart0_init(9600);

    lcd_cmd(0x01);
    lcd_string("Password System");

    uart0_tx_string("\r\nPassword Authentication System\r\n");

    while (1)
    {
        lcd_cmd(0x01);
        lcd_cmd(0x80);
        lcd_string("Enter Password:");

        uart0_tx_string("\r\nEnter password: ");

        i = 0;

        // Receive password from UART
        while (1)
        {
            ch = uart0_rx();

            // Enter key ends password input
            if (ch == '\r' || ch == '\n')
                break;

            // Store characters up to the maximum length
            if (i < MAX_PASSWORD_LENGTH)
            {
                entered[i] = ch;
                i++;

                // Display * instead of the password
                uart0_tx('*');
            }
        }

        entered[i] = '\0';

        // Compare entered password with stored password
        correct = 1;

        for (j = 0; PASSWORD[j] != '\0'; j++)
        {
            if (entered[j] != PASSWORD[j])
            {
                correct = 0;
                break;
            }
        }

        // Check whether both strings have the same length
        if (i != j && correct == 1)
        {
            correct = 0;
        }

        if (correct == 1)
        {
            attempts = 0;

            // Green LED ON, red LED OFF
            IOCLR0 = GREEN_LED;
            IOSET0 = RED_LED;

            lcd_cmd(0x01);
            lcd_cmd(0x80);
            lcd_string("Access Granted");

            uart0_tx_string("\r\nACCESS GRANTED\r\n");

            delay_ms(3000);

            IOSET0 = GREEN_LED;
        }
        else
        {
            attempts++;

            // Green LED OFF, red LED ON
            IOSET0 = GREEN_LED;
            IOCLR0 = RED_LED;

            lcd_cmd(0x01);
            lcd_cmd(0x80);
            lcd_string("Access Denied");

            uart0_tx_string("\r\nACCESS DENIED\r\n");

            delay_ms(1000);

            IOSET0 = RED_LED;

            // Lock after three incorrect attempts
            if (attempts >= MAX_ATTEMPTS)
            {
                lcd_cmd(0x01);
                lcd_cmd(0x80);
                lcd_string("System Locked");

                lcd_cmd(0xC0);
                lcd_string("Wait 10 seconds");

                uart0_tx_string(
                    "\r\nSystem locked for 10 seconds.\r\n"
                );

                delay_ms(10000);

                attempts = 0;

                lcd_cmd(0x01);
                lcd_cmd(0x80);
                lcd_string("Try Again");

                uart0_tx_string(
                    "\r\nLockout ended. Try again.\r\n"
                );
            }
        }
    }
}