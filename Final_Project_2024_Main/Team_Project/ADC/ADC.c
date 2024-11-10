/*
 * ADC.c
 *
 *  Created on: 2024. 10. 28.
 *      Author: FM17
 */


#include "ADC.h"

void init_ADC_Group(void){
    IfxVadc_Adc_Config  adcConf;
    IfxVadc_Adc_initModuleConfig(&adcConf, &MODULE_VADC);
    IfxVadc_Adc_initModule(&Vadc, &adcConf);

    IfxVadc_Adc_GroupConfig  adcGroupConf;
    IfxVadc_Adc_initGroupConfig(&adcGroupConf, &Vadc);

    adcGroupConf.groupId = IfxVadc_GroupId_4;
    adcGroupConf.master = adcGroupConf.groupId;

    adcGroupConf.arbiter.requestSlotScanEnabled = TRUE;
    adcGroupConf.scanRequest.autoscanEnabled = TRUE;

    adcGroupConf.scanRequest.triggerConfig.gatingMode = IfxVadc_GatingMode_always;

    IfxVadc_Adc_initGroup(&adcGroup4, &adcGroupConf);
}

void init_ADC_G4_SingleCh(uint8 Channel){
    IfxVadc_Adc_ChannelConfig   adcChannelConfigInfo;
    uint32 ulTemp = ((uint32)1u << Channel);

    IfxVadc_Adc_initChannelConfig(&adcChannelConfigInfo, &adcGroup4);

    adcChannelConfigInfo.channelId       = (IfxVadc_ChannelId) Channel;
    adcChannelConfigInfo.resultRegister  = (IfxVadc_ChannelResult)Channel;

    IfxVadc_Adc_initChannel(&adcG4Channel[Channel], &adcChannelConfigInfo);

    IfxVadc_Adc_setScan(&adcGroup4, ulTemp, ulTemp);
}

void init_ADC_G4_Channel(void){
    init_ADC_G4_SingleCh(ADC_G4_CH0);
    init_ADC_G4_SingleCh(ADC_G4_CH1);
    init_ADC_G4_SingleCh(ADC_G4_CH2);
    init_ADC_G4_SingleCh(ADC_G4_CH3);
    init_ADC_G4_SingleCh(ADC_G4_CH4);
    init_ADC_G4_SingleCh(ADC_G4_CH5);
    init_ADC_G4_SingleCh(ADC_G4_CH6);
    init_ADC_G4_SingleCh(ADC_G4_CH7);

    IfxVadc_Adc_startScan(&adcGroup4);
}

void ADC_G4_GetData(void){
    Ifx_VADC_RES        ADC_result;

    uint8 ch;
    for(ch = ADC_G4_CH0; ch<ADC_G4_MAX; ch++){
        do{
            ADC_result = IfxVadc_Adc_getResult(&adcG4Channel[ch]);
        }while(!ADC_result.B.VF);

        ADC_G4_RAWDATA[ch] = ADC_result.B.RESULT;
    }

    IfxVadc_Adc_startScan(&adcGroup4);
}


