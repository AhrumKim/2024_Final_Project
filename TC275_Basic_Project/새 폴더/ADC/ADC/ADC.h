/*
 * GPIO.h
 *
 *  Created on: 2024. 10. 25.
 *      Author: FM22
 */

#ifndef ADC_ADC_H_
#define ADC_ADC_H_

#include "Header_275.h"

#ifdef USE_GLOBAL_H
#define Global
#else
#define Global extern
#endif

typedef enum
{
    ADC_G3_CH0 = 0u, //0   각 채널 할당
    ADC_G3_CH1,      //1
    ADC_G3_CH2,      //2
    ADC_G3_CH3,      //3
    ADC_G3_CH4,      //4
    ADC_G3_CH5,      //5
    ADC_G3_CH6,      //6
    ADC_G3_CH7,      //7
    ADC_G3_MAX,      //8

}ADC4;

Global IfxVadc_Adc          Vadc;                       //ADC 구조체 선언
Global IfxVadc_Adc_Group    adcGroup3;                  //ADC Group 구조체 선언
Global IfxVadc_Adc_Channel  adcG3Channel[ADC_G3_MAX];   //ADC Channel 구조체 선언

Global uint16 ADC_G3_RAWDATA[ADC_G3_MAX];               // 변환 값을 저장할 배열 선언

Global void init_ADC_Group(void);                       // ADC Group 초기 세팅 함수

void init_ADC_G3_SingleCh(uint8 Channel);               // ADC 단일 채널 초기 세팅 함수

Global void init_ADC_G3_Channel(void);                  // ADC 채널 초기 세팅 함수

void ADC_G3_GetData(void);                              // ADC 변환 값 가져오는 함수

#endif /* ADC_ADC_H_ */
