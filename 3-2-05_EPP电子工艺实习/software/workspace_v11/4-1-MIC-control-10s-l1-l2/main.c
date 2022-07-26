#include <msp430.h> 
#include "ADC12.h"

unsigned int icnt;
void IO_Init(void)
{
    P8DIR |= BIT1;                          // 设置P8.1口为输出模式  控制LED灯
    P8OUT &= ~BIT1;                          // 选中P8.1为输出方式
    P3DIR |= BIT7;
    P3OUT &= ~BIT7;

    P3DIR |= BIT6;                          // 设置P3.6口为输出模式  控制蜂鸣器
    P3OUT |= BIT6;                          // 选中P3.6为输出方式

    P2DIR &= ~(BIT3+BIT6);
    P2REN |= BIT3+BIT6;
    P2OUT |= BIT3+BIT6;

    P1DIR &=~( BIT3+BIT2);
    P1REN = BIT3+BIT2;
    P1OUT |= BIT3+BIT2;
}

int apInterface_Key( void )
{
   return 0;
}

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    IO_Init();

    ADInit(ADC12INCH_2);

    TA0CTL |= MC_1 + TASSEL_2 + TACLR;      //时钟为SMCLK,比较模式，开始时清零计数器
    TA0CCTL0 = CCIE;                        //比较器中断使能
    TA0CCR0  = 50000;                       //比较值设为50000，相当于50ms的时间间隔
    __enable_interrupt();

    unsigned int ivalue = 0;              //设置判断变量
    while(1)
    {
        //  ivalue = GetAD();               //没有软件滤波
        ivalue = Filter( );                 //软件滤波
        if(ivalue>=2500)
        {
            P8OUT |= BIT1;
            P3OUT |= BIT7;
            TA0CTL |= MC_1 + TASSEL_2 + TACLR;      //时钟为SMCLK,比较模式，开始时清零计数器
            icnt=0;
        }
    }

}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    icnt++;
    if(icnt==200)
    {//10s关灯
       P8OUT &= ~BIT1;
       P3OUT &= ~BIT7;
       icnt=0;
    }
}
