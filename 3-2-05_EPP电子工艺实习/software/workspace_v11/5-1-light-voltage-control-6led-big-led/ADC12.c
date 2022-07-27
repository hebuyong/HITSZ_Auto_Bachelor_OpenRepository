/*
 * ad.c
 *
 *  Created on: 2018-2-10
 *      Author: Liu
 */
#include "ADC12.h"

//ADC 初始化
//void ADInit(char channel)
//{
//    ADC12CTL0 |= ADC12MSC;                                      //自动循环采样转换
//    ADC12CTL0 |= ADC12ON;                                       //启动ADC12模块
//    ADC12CTL1 |= ADC12CONSEQ1 ;                                 //选择单通道循环采样转换
//    ADC12CTL1 |= ADC12SHP;                                      //采样保持模式
//    switch (channel)
//    {
//            case 0:ADC12MCTL0 |= ADC12INCH_0;    break;         //选择通道0，P6.0
//            case 1:ADC12MCTL0 |= ADC12INCH_1;   break;          //选择通道1，P6.1
//            case 2:ADC12MCTL0 |= ADC12INCH_2;   break;          //选择通道2，P6.2
//            case 3:ADC12MCTL0 |= ADC12INCH_3;   break;          //选择通道3，P6.3
//            case 4:ADC12MCTL0 |= ADC12INCH_4;   break;          //选择通道4，P6.4
//            case 5:ADC12MCTL0 |= ADC12INCH_5;   break;          //选择通道5，P6.5  连接拨码电位器
//            case 6:ADC12MCTL0 |= ADC12INCH_6;   break;          //选择通道6，P6.6
//            case 12:ADC12MCTL0 |= ADC12INCH_12; break;          //选择通道12，P7.0
//            default: ;break;
//    }
//
//    ADC12CTL0 |= ADC12ENC;
//}
void InitAD()
{
ADC12CTL0 |= ADC12MSC;            //自动循环采样转换
ADC12CTL0 |= ADC12ON;               //启动ADC12模块
ADC12CTL1 |= ADC12CONSEQ_3 ;//选择序列通道多次循环采样转换
ADC12CTL1 |= ADC12SHP;             //采样保持模式
ADC12CTL1  |= ADC12CSTARTADD_0;
ADC12MCTL0 |=ADC12INCH_1;    //通道选择
ADC12MCTL1 |=ADC12INCH_2+ADC12EOS;
ADC12CTL0 |= ADC12ENC;
}

#define N_POINT 13
unsigned int  GetAD2()
{
    unsigned int temp = 0;          //设置变量
    ADC12CTL0 |= ADC12SC;           //开始采样转换
    temp= ADC12MEM1;                //把结果赋给变量
    return temp;
}

unsigned int Filter2( )
{
     char count,i,j;
     unsigned int value_buf[N_POINT];
     unsigned int temp=0;
     int sum=0;
      for (count=0;count<N_POINT;count++)
      {
            value_buf[count] = GetAD2();
      }
      for (j=0;j<N_POINT-1;j++)
      {
            for (i=0;i<N_POINT-j-1;i++)
           {
                if ( value_buf[i]>value_buf[i+1] )
              {
                   temp = value_buf[i];
                   value_buf[i] = value_buf[i+1];
                   value_buf[i+1] = temp;
               }
           }
    }
    for(count=1;count<N_POINT-1;count++)
    sum += value_buf[count];
    //如果为2的n次方等分，则可以用>>n的减少计算量  a=a*8;  可以为 a=a<<3;
    //b=b/8; 可以为b=b>>3;
    return (unsigned int)(sum/(N_POINT-2));
}

unsigned int  GetAD1()
{
    unsigned int temp = 0;          //设置变量
    ADC12CTL0 |= ADC12SC;           //开始采样转换
    temp= ADC12MEM0;                //把结果赋给变量
    return temp;
}

unsigned int Filter1( )
{
     char count,i,j;
     unsigned int value_buf[N_POINT];
     unsigned int temp=0;
     int sum=0;
      for (count=0;count<N_POINT;count++)
      {
            value_buf[count] = GetAD1();
      }
      for (j=0;j<N_POINT-1;j++)
      {
            for (i=0;i<N_POINT-j-1;i++)
           {
                if ( value_buf[i]>value_buf[i+1] )
              {
                   temp = value_buf[i];
                   value_buf[i] = value_buf[i+1];
                   value_buf[i+1] = temp;
               }
           }
    }
    for(count=1;count<N_POINT-1;count++)
    sum += value_buf[count];
    //如果为2的n次方等分，则可以用>>n的减少计算量  a=a*8;  可以为 a=a<<3;
    //b=b/8; 可以为b=b>>3;
    return (unsigned int)(sum/(N_POINT-2));
}

