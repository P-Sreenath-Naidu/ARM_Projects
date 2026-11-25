#include <lpc21xx.h>
#include "header.h"
void delay_ms(unsigned int ms)
{
      T0PR=15000-1;
	  T0TC=T0PC=0;
	  T0TCR=1;
	  while(T0TC<ms);
	  T0TCR=0;
}


