/*
 *S1øÿ÷∆n1£¨s1øÿ÷∆¥ÛLEDµ∆
 */
#include <msp430.h> 
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
    P1DIR|=BIT5; //p8.1 output/L1
    P1OUT|=BIT5;
    P2DIR|=BIT4; //p8.1 output/L1
    P2OUT&=~BIT4;
    P2DIR|=BIT5; //p8.1 output/L1
    P2OUT|=BIT5;

P1DIR&=~BIT2; //p1.2 input,pull up/s1
P1REN|=BIT2;
P1OUT|=BIT2;
P1IE|=BIT2; //enable P1.2 interrupt
P1IES|=BIT2; //high-low transition
P1IFG&=~BIT2;



_enable_interrupt();
return 0;
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
if(P1IFG&BIT2){

P2OUT^=BIT4;

P1IFG&=~BIT2;
}
}
