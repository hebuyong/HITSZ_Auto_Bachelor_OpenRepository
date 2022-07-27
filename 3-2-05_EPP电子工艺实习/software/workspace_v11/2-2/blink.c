
/*
 * 延时1s控制led1
 */
#include <msp430.h>				



void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	P1DIR |=BIT0;					// configure P1.0 as output


//	ClockInit();
	while(1)
	{
		P1OUT ^= BIT0;				// toggle P1.0
		__delay_cycles(1e6);     // delay
	}
}

void ClockInit()
{//最终MCLK:16MHZ,SMCLK:8MHZ,ACLK:32KHZ
     UCSCTL6 &= ~XT1OFF;       //启动XT1
     P5SEL |= BIT2 + BIT3;     //XT2引脚功能选择
     UCSCTL6 &= ~XT2OFF;       //打开XT2
     __bis_SR_register(SCG0);
     UCSCTL0 = DCO0+DCO1+DCO2+DCO3+DCO4;
     UCSCTL1 = DCORSEL_4;  //DCO频率范围在28.2MHZ以下
     UCSCTL2 = FLLD_5 + 1;       //D=16，N=1

     //n=8,FLLREFCLK时钟源为XT2CLK；
     //DCOCLK=D*(N+1)*(FLLREFCLK/n);
     //DCOCLKDIV=(N+1)*(FLLREFCLK/n);
     UCSCTL3 = SELREF_5 + FLLREFDIV_3;

     //ACLK的时钟源为DCOCLKDIV,
     //MCLK\SMCLK的时钟源为DCOCLK
     UCSCTL4 = SELA_4 + SELS_3 +SELM_3;

     //ACLK由DCOCLKDIV的32分频得到，
     //SMCLK由DCOCLK的2分频得到
     UCSCTL5 = DIVA_5 +DIVS_1;
}

