#include <lpc21xx.h>
#include "header.h"
void lcd_data(unsigned char data)
{
   //Higher Nibble 
   
        IOCLR1=0xfe<<16;
		IOSET1=(data&0xf0)<<16;
		IOSET1=1<<17;
		IOCLR1=1<<18;
		IOSET1=1<<19;
		delay_ms(2);
		IOCLR1=1<<19;

//Lower nibble 

        IOCLR1=0xfe<<16;
		IOSET1=(data&0x0f)<<20;
		IOSET1=1<<17;
		IOCLR1=1<<18;
		IOSET1=1<<19;
		delay_ms(2);
		IOCLR1=1<<19;
}
void lcd_cmd(unsigned char cmd )
{
       //Higher Nibble 
   
        IOCLR1=0xfe<<16;
		IOSET1=(cmd&0xf0)<<16;
		IOCLR1=1<<17;
		IOCLR1=1<<18;
		IOSET1=1<<19;
		delay_ms(2);
		IOCLR1=1<<19;

//Lower nibble 

        IOCLR1=0xfe<<16;
		IOSET1=(cmd&0x0f)<<20;
		IOCLR1=1<<17;
		IOCLR1=1<<18;
		IOSET1=1<<19;
		delay_ms(2);
		IOCLR1=1<<19;
}
void lcd_init()
{
      IODIR1=0xfe<<16;
	  lcd_cmd(0x02);
	  lcd_cmd(0x28);
	  lcd_cmd(0x0e);
}
void lcd_string(char *p)
{
      while(*p!=0)
			{
			    lcd_data(*p);
				  p++;
			}

}

