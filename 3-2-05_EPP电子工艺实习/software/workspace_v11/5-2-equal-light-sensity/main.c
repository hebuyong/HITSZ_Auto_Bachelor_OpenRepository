/*
 * p6.1-光敏AO
 * p6.2-前置放大器OPA_OUT
 */
#include <msp430.h> 
#include "ADC12.h"
#include <stdio.h>
unsigned int icnt;
unsigned int flag;
void ClockInit()
{ //最终MCLK:16MHz,   SMCLK:8MHz,   ACLK:32KHz
    UCSCTL6 &= ~XT1OFF;          //启动XT1
    P5SEL |= BIT2 + BIT3;             //XT2引脚功能选择
    UCSCTL6 &= ~XT2OFF;          //打开XT2
    __bis_SR_register(SCG0);
    UCSCTL0 = DCO0 + DCO1 + DCO2 + DCO3 + DCO4;
    UCSCTL1 = DCORSEL_4;       //DCO频率范围在28.2MHZ以下
    UCSCTL2 = FLLD_5 + 1;          //D=16，N=1

    //n=8,FLLREFCLK时钟源为XT2CLK；
    //DCOCLK=D*(N+1)*(FLLREFCLK/n);DCOCLKDIV=(N+1)*(FLLREFCLK/n);
    UCSCTL3 = SELREF_5 + FLLREFDIV_3;
    //ACLK的时钟源为DCOCLKDIV,MCLK\SMCLK的时钟源为DCOCLK
    UCSCTL4 = SELA_4 + SELS_3 + SELM_3;
    //ACLK由DCOCLKDIV的32分频得到，SMCLK由DCOCLK的2分频得到
    UCSCTL5 = DIVA_5 + DIVS_1;
}
void IO_Init(void)
{
    P8DIR |= BIT1;                          // 设置P8.1口为输出模式  控制LED灯
    P8OUT &= ~BIT1;                          // 选中P8.1为输出方式
    P3DIR |= BIT7;
    P3OUT &= ~BIT7;
    P7DIR |= BIT4;                          // 设置P8.1口为输出模式  控制LED灯
    P7OUT &= ~BIT4;                          // 选中P8.1为输出方式
    P6DIR |= BIT3;
    P6OUT &= ~BIT3;
    P6DIR |= BIT4;                          // 设置P8.1口为输出模式  控制LED灯
    P6OUT &= ~BIT4;                          // 选中P8.1为输出方式
    P3DIR |= BIT5;
    P3OUT &= ~BIT5;

    P3DIR |= BIT6;                          // 设置P3.6口为输出模式  控制蜂鸣器
    P3OUT |= BIT6;                          // 选中P3.6为输出方式

//    P1DIR |= BIT0;                          // 设置P8.1口为输出模式  控制LED灯
//    P1OUT &= ~BIT0;                          // 选中P8.1为输出方式

    P2DIR &= ~(BIT3 + BIT6);
    P2REN |= BIT3 + BIT6;
    P2OUT |= BIT3 + BIT6;

    P1DIR &= ~( BIT3 + BIT2);
    P1REN = BIT3 + BIT2;
    P1OUT |= BIT3 + BIT2;

    //大功率led
    P1DIR |= BIT5; //p8.1 output/L1
    P1OUT |= BIT5;
    P2DIR |= BIT4; //p8.1 output/L1
    P2OUT &= ~BIT4;
}

int apInterface_Key(void)
{
    return 0;
}

/**
 * main.c
 */

int main(void)
{
//    ClockInit();
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    IO_Init();

    InitAD();

    TA0CTL |= MC_1 + TASSEL_2 + TACLR;      //时钟为SMCLK,比较模式，开始时清零计数器
    TA0CCTL0 = CCIE;                        //比较器中断使能
    TA0CCR0 = 0.5 * 50000;                       //比较值设为50000，相当于50ms的时间间隔

    //大功率led pwm
    TA2CTL = TASSEL_2 + TACLR + MC0;
    unsigned int period = 4095;
    TA2CCR0 = period;   // PWM周期
    TA2CCTL2 = OUTMOD_7;   // 输出模式7
    __enable_interrupt();

    unsigned int ivalue = 0;              //设置判断变量
    unsigned int ivalue2 = 0;              //设置判断变量mic
    flag = 0;

    while (1)
    {

        //  ivalue = GetAD();               //没有软件滤波
        ivalue = Filter1();                 //软件滤波
        ivalue2 = Filter2();                 //软件滤波

        if (ivalue2 >= 2500)
        {

//            P1OUT |= BIT0;

            TA0CTL |= MC_1 + TASSEL_2 + TACLR;      //时钟为SMCLK,比较模式，开始时清零计数器
            icnt = 0;
            flag = 1;
            TA2CCR2 = 1000;
        }
//        printf("%d\t%d\t%d\n", ivalue,ivalue2,icnt);
        if (flag == 1)
        {
            if (ivalue > 520)
            {
                TA2CCR2+=(int)0.01*(ivalue-520)^2;  //占空比80%
                P2DIR |= BIT5;    // P1.2 方向为输出
                P2SEL |= BIT5;   // P1.2端口为外设，定时器TA0.1
                __delay_cycles(0.25e4);

            }
            if (ivalue < 470)
            {
                TA2CCR2-=(int)0.01*(470-ivalue)^2;  //占空比80%
                P2DIR |= BIT5;    // P1.2 方向为输出
                P2SEL |= BIT5;   // P1.2端口为外设，定时器TA0.1
                __delay_cycles(0.25e4);

            }
//            printf("%d\t%d\n",ivalue,TA2CCR2);

        }

        if (ivalue <= 2400)
        {
            P8OUT |= BIT1;
        }
        else
        {
            P8OUT &= ~BIT1;
        }
        if (ivalue <= 1800)
        {
            P3OUT |= BIT7;
        }
        else
        {
            P3OUT &= ~BIT7;
        }
        if (ivalue <= 1200)
        {
            P7OUT |= BIT4;
        }
        else
        {
            P7OUT &= ~BIT4;
        }
        if (ivalue <= 800)
        {
            P6OUT |= BIT3;
        }
        else
        {
            P6OUT &= ~BIT3;
        }
        if (ivalue <= 600)
        {
            P6OUT |= BIT4;
        }
        else
        {
            P6OUT &= ~BIT4;
        }
        if (ivalue <= 400)
        {
            P3OUT |= BIT5;
        }
        else
        {
            P3OUT &= ~BIT5;
        }

    }

}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{

    icnt++;
    if (icnt == 2 * 200)
    {      //10s关灯
        TA2CCR2 = 0;  //关闭
        P2DIR |= BIT5;    // P1.2 方向为输出
        P2SEL |= BIT5;   // P1.2端口为外设，定时器TA0.1
        icnt = 0;
        flag = 0;
    }
}
