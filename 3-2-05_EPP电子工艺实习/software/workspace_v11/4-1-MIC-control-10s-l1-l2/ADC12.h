/*
 * ad.h
 *
 *  Created on: 2018-2-10
 *      Author: peter Liu
 */

#ifndef ADC12_H_
#define ADC12_H_
#include <msp430.h>



extern void  ADInit(char channel);  //初始化ADC ，channel——AD采集通道  通道0，P6.0；通道1，P6.1；通道2，P6.2；通道3，P6.3；通道4，P6.4；通道5，P6.5；通道12，P7.0
extern unsigned int  GetAD();//返回AD采集数据，
extern unsigned int Filter( );  //AD采集数据软件滤波，中位值平均滤波法


#endif /* ADC12_H_ */
