#include <lpc21xx.h>
#include "header.h"
void lcd_data(unsigned char data)
{
//Higher nibble

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
void lcd_cmd(unsigned char cmd)
{
//Higher nibble

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
void lcd_integer(int n)
{
    int a[20], i;
		
		if(n==0)
		{
		  lcd_data('0');
		}
		if(n<0)
		{
		   n=-n;
		   lcd_data('-');
		}
		
		i=0;
		while(n>0)
		{
		   a[i]=n%10+48;
			 n=n/10;
			 i++;
		}
		for(i=i-1; i>=0; i--)
		{
		    lcd_data(a[i]);
		}
}

