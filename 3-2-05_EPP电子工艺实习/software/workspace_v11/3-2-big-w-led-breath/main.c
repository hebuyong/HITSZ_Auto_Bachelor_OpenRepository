/*
 * 大功率呼吸灯
 */
#include <msp430.h>

int main(void)
{
// stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
    P1DIR |= BIT5; //p8.1 output/L1
    P1OUT |= BIT5;
    P2DIR |= BIT4; //p8.1 output/L1
    P2OUT &= ~BIT4;
//    P2DIR|=BIT5; //p8.1 output/L1
//    P2OUT|=BIT5;

//ClockInit();
// 选择时钟ACLK, 清除 TAR，增计数
    TA2CTL = TASSEL_2 + TACLR + MC0;
    unsigned int period = 1e2;
    TA2CCR0 = period;   // PWM周期
    TA2CCTL2 = OUTMOD_7;   // 输出模式7
    while (1)
    {

        unsigned int i;
        for (i = 1; i <= period; i++)
        {

            TA2CCR2 = i;  //占空比80%
            P2DIR |= BIT5;    // P1.2 方向为输出
            P2SEL |= BIT5;   // P1.2端口为外设，定时器TA0.1
            __delay_cycles(0.25e4);
        }

        for (i = period; i >= 1; i--)
        {

            TA2CCR2 = i;  //占空比80%
            P2DIR |= BIT5;    // P1.2 方向为输出
            P2SEL |= BIT5;   // P1.2端口为外设，定时器TA0.1
            __delay_cycles(0.25e4);
        }

    }
}
