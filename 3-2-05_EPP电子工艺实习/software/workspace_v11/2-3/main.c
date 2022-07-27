/*
 * 5s定时器
 */

#include <msp430.h>
#include "key.h"
StrKeyFlag KeyFlag;
void delay(uint16 t)
{
    uint16 i,j,k;

    for(j=t;j>0;j--)
        for(i=250;i>0;i--)
            k=0;
}


unsigned int i=0;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    IO_Init();

    //时钟为SMCLK,比较模式，开始时清零计数器
    TA0CTL |= MC_1 + TASSEL_2 + TACLR;
    TA0CCTL0 = CCIE;                //比较器中断使能
    TA0CCR0  = 50000;               //比较值设为50000，相当于50ms的时间间隔
    while(1)
    {
        ScanKey();                          //扫描按键动作
          if(KeyFlag.S1==1)
          {
              KeyFlag.S1=0;
              P8OUT |= BIT1;          //形成闪灯效果
              P3OUT |= BIT6;      //形成鸣叫效果
              i=0;
                __disable_interrupt();
          }
          else{
              __enable_interrupt();
          }
//          if(KeyFlag.S2==1)
//        {
//            KeyFlag.S2=0;
//
//
//        }
    }
}
/************************定时器中断函数********************************/
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    i++;
    if(i==100)
   {
        P8OUT &= ~BIT1;          //关闭闪灯效果
        P3OUT &= ~BIT6;      //关闭蜂鸣器
        i=0;
   }
}
/************************IO口初始化********************************/
void IO_Init(void)
{
    P8DIR |= BIT1;              // 设置P8.1口为输出模式  控制LED灯
    P8OUT |= BIT1;  // 选中P8.1为输出方式

    P3DIR |= BIT6;              // 设置P3.6口为输出模式  控制蜂鸣器
    P3OUT |= BIT6;  // 选中P3.6为输出方式

    P2DIR |= BIT2;
    P2OUT &=~ BIT2;

    P1DIR &=~( BIT3+BIT2);
    P1REN = BIT3+BIT2;
    P1OUT |= BIT3+BIT2;

    P2DIR &= ~(BIT3+BIT6);
    P2REN |= BIT3+BIT6;
    P2OUT |= BIT3+BIT6;
}

void ScanKey(void)
{
    if((P1IN&BIT2)!=BIT2)//通过IO口值得出按键按下信息
   {
        delay(50);  //延时去抖
        if((P1IN&BIT2)!=BIT2)   //通过IO口值得出按键按下信息
        {
    KeyFlag.S1=1;
        }
   }
   if((P1IN&BIT3)!=BIT3)//通过IO口值得出按键按下信息
   {
        delay(50);   //延时去抖
        if((P1IN&BIT3)!=BIT3) //通过IO口值得出按键按下信息
        {
                KeyFlag.S2=1;
        }
   }
   if((P2IN&BIT3)!=BIT3) //通过IO口值得出按键按下信息
  {
        delay(50);   //延时去抖
        if((P2IN&BIT3)!=BIT3)           //通过IO口值得出按键按下信息
        {
                KeyFlag.S3=1;
        }
  }
  if((P2IN&BIT6)!=BIT6) //通过IO口值得出按键按下信息
  {
         delay(50);//延时去抖
         if((P2IN&BIT6)!=BIT6)          //通过IO口值得出按键按下信息
         {
               KeyFlag.S4=1;
         }
   }
}

