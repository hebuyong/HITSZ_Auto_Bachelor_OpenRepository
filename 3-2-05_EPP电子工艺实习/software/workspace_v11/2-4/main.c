#include <msp430.h>
int main(void)
{
// stop watchdog timer
WDTCTL = WDTPW | WDTHOLD;

// 选择时钟ACLK, 清除 TAR，增计数
TA0CTL = TASSEL_2 + TACLR + MC0;

TA0CCR0 = 512;   // PWM周期

TA0CCTL1 = OUTMOD_7 ;// 输出模式7
TA0CCR1 = 410;  //占空比80%

TA0CCTL2 = OUTMOD_7; // 输出模式7;
TA0CCR2 = 51;  //占空比10%

P1DIR |= BIT2;    // P1.2 方向为输出
P1SEL |= BIT2;   // P1.2端口为外设，定时器TA0.1
P1DIR |= BIT3;    // P1.3 方向为输出
P1SEL |= BIT3;   // P1.3端口为外设，定时器TA0.2
}
