#include <lpc21xx.h>
void uart0_init(unsigned int baud)
{
     unsigned int pclk,result=0;
	 
	    if(VPBDIV==0x0)
	    pclk=15000000;
	    else if(VPBDIV==0x1)
      pclk=60000000;
      else if(VPBDIV==0x2)
      pclk=30000000;

      result=pclk/(16*baud);
	 
	    PINSEL0|=0x05;
	 
	 U0LCR=0x83;
	 U0DLL=result&0xff;
	 U0DLM=(result>>8)&0xff;
	 U0LCR=0x03;
}
#define THRE ((U0LSR>>5)&1)
void uart0_tx(unsigned char data)
{
	  U0THR=data;
	  while(THRE==0);
	 
}
#define RDR (U0LSR&1)
unsigned char uart0_rx()
{
     while(RDR==0);
	 return U0RBR;
}
void uart0_tx_string(unsigned char*p )
{
    while(*p)
		{
		    uart0_tx(*p);
			p++;
		}
}


