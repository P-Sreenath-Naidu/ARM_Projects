extern void delay_ms(unsigned int ms);
extern void lcd_cmd(unsigned char cmd );
extern void lcd_data(unsigned char data);
extern void lcd_init(void);
extern void uart0_init(unsigned int baud);
extern void uart0_tx(unsigned char data);
extern unsigned char uart0_rx(void);
extern void uart0_tx_string(unsigned char*p);

