/*
 * ADC.h
 *
 *  Created on: 2024. 10. 28.
 *      Author: FM17
 */

#ifndef ADC_ADC_H_
#define ADC_ADC_H_

#include "Header_275.h"

#ifdef USE_GLOBAL_H
#define Global
#else
#define Global extern
#endif

typedef enum{
    ADC_G4_CH0 = 0u,    // 0
    ADC_G4_CH1,    // 1
    ADC_G4_CH2,    // 2
    ADC_G4_CH3,    // 3
    ADC_G4_CH4,    // 4
    ADC_G4_CH5,    // 5
    ADC_G4_CH6,    // 6
    ADC_G4_CH7,    // 7
    ADC_G4_MAX,    // 8
}ADC4;

Global IfxVadc_Adc            Vadc;
Global IfxVadc_Adc_Group      adcGroup4;
Global IfxVadc_Adc_Channel    adcG4Channel[ADC_G4_MAX];

Global uint16 ADC_G4_RAWDATA[ADC_G4_MAX];

Global void init_ADC_Group(void);

void init_ADC_G4_SingleCh(uint8 Channel);

Global void init_ADC_G4_Channel(void);

void ADC_G4_GetData(void);

#endif /* ADC_ADC_H_ */
