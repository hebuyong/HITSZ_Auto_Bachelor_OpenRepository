/*
 * ad.h
 *
 *  Created on: 2018-2-10
 *      Author: peter Liu
 */

#ifndef ADC12_H_
#define ADC12_H_
#include <msp430.h>



void InitAD();
extern unsigned int  GetAD1();//返回AD采集数据，
extern unsigned int Filter1( );  //AD采集数据软件滤波，中位值平均滤波法
extern unsigned int  GetAD2();//返回AD采集数据，
extern unsigned int Filter2( );  //AD采集数据软件滤波，中位值平均滤波法

#endif /* ADC12_H_ */
