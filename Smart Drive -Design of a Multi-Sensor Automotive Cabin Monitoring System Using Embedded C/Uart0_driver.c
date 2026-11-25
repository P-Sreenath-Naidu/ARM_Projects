#include <lpc21xx.h>
#include "header.h"
#define THRE ((U0LSR>>5)&1)
#define RDR (U0LSR&1)
void uart0_init(unsigned int baud)
{
     int pclk,result=0;
		 
		 if(VPBDIV==0x0)
		 pclk=15000000;
		 else if(VPBDIV==0x1)
		 pclk=60000000;
		 else if(VPBDIV==0x2)
		 pclk=30000000;
		 
		 result=pclk/(16*baud);
		 
		 PINSEL0 |=0x05;
		 U0LCR=0x83;
		 U0DLL=result&0x00ff;
		 U0DLM=result&0xff00;
		 U0LCR=0x03;
		 
}
void uart0_tx(unsigned char data)
{
    U0THR=data;
		while(THRE==0);
}
unsigned char uart0_rx()
{
   while(RDR==0);
	 return U0RBR;
}
void uart0_tx_string(unsigned char *p)
{
     while(*p!=0)
		 {
		    uart0_tx(*p);
				p++;
		 }
}
void uart0_integer(int n)
{
    int a[10], i;
		
		if(n==0)
		{
		   uart0_tx('0');
		}
		if(n<0)
		{
		   n=-n;
			 uart0_tx('-');
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
		    uart0_tx(a[i]);
		}

}

