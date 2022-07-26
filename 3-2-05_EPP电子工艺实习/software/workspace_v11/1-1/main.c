#include <msp430.h> 


/**
 * main.c
 * s2¿ØÖÆL2ÁÁÃð
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer


	P3DIR |= BIT7;
	P3OUT&=~BIT7;

	P1REN|=BIT3;
	P1OUT|=BIT3;
	while(1)
	{
	    if(!(P1IN&BIT3))
	        P3OUT|=BIT7;
	    else
	        P3OUT&=~BIT7;

	}

	
	return 0;
}
