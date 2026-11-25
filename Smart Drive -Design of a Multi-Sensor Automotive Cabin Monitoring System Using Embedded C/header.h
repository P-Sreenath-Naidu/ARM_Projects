#ifndef HEADER_H
#define HEADER_H

// TIMER DELAY
extern void delay_ms(unsigned int ms);
extern void delay_sec(unsigned int sec);

// LCD DRIVER
extern void lcd_data(unsigned char data);
extern void lcd_cmd(unsigned char cmd);
extern void lcd_init(void);
extern void lcd_string(char *p);
extern void lcd_integer(int n);

// UART DRIVER
extern void uart0_init(unsigned int baud);
extern void uart0_tx(unsigned char data);
extern unsigned char uart0_rx(void);
extern void uart0_tx_string(unsigned char *p);
extern void uart0_integer(int n);

// ADC DRIVER
extern void adc_init(void);
extern unsigned int adc_read(unsigned int ch_num);

// SENSOR FUNCTIONS
extern float alcohol_read(void);
extern float gas_read(void);
extern unsigned int PIR_sensor(void);

#endif



