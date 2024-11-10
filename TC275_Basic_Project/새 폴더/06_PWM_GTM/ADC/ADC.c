/*
 * ADC.c
 *
 *  Created on: 2024. 10. 25.
 *      Author: FM22
 */
#include "ADC.h"
#include "STM.h"
#include "GPIO.h"

void init_ADC_Group(void)
{
    IfxVadc_Adc_Config      adcConf;                        /* Define a configuration structure for the VADC module */
    IfxVadc_Adc_initModuleConfig(&adcConf, &MODULE_VADC);   /* adcConf 값을 디폴트 값(MODULE_VADC)오로 초기화 */
    IfxVadc_Adc_initModule(&Vadc, &adcConf);                /* Vadc를 adcConf 값으로 초기화 */

    IfxVadc_Adc_GroupConfig     adcGroupConf;               /* Define a configuration structure for the VADC group */
    IfxVadc_Adc_initGroupConfig(&adcGroupConf, &Vadc);      /* adc 그룹 구조체 초기화 및 Vadc 값 반영 */

    adcGroupConf.groupId = IfxVadc_GroupId_3;               /* Select the group 다른 아이디로는 그룹2, 그룹3으로 지정*/
    adcGroupConf.master = adcGroupConf.groupId;             /* Select the master group */

    adcGroupConf.arbiter.requestSlotScanEnabled = TRUE;     /* Enabled scan source 별도의 설정없이 ADC변환*/
    adcGroupConf.scanRequest.autoscanEnabled    = TRUE;     /* Enabled auto scan mode */

    adcGroupConf.scanRequest.triggerConfig.gatingMode = IfxVadc_GatingMode_always;  /* 특정 트리거 조건 없이 항상 변환 수행/인터럽트일 때는 다른 모드 */

    IfxVadc_Adc_initGroup(&adcGroup3, &adcGroupConf);       /* adc 그룹 설정 값 반영 */
}

void init_ADC_G3_SingleCh(uint8 Channel)
{
    IfxVadc_Adc_ChannelConfig   adcChannelConfigInfo;
    uint32 ulTemp = ((uint32)1u << Channel);

    IfxVadc_Adc_initChannelConfig(&adcChannelConfigInfo, &adcGroup3);           /* Fill it with default values */

    adcChannelConfigInfo.channelId      = (IfxVadc_ChannelId) Channel;          /* Select the channel ID */
    adcChannelConfigInfo.resultRegister = (IfxVadc_ChannelResult) (Channel);    /* Use dedicated result register */

    /* Initialize the channel */
    IfxVadc_Adc_initChannel(&adcG3Channel[Channel], &adcChannelConfigInfo);     /* 채널 초기화 */

    /* Add the channel to the scan sequence */
    IfxVadc_Adc_setScan(&adcGroup3, ulTemp, ulTemp);                            /* the background scan sequence */
}

void init_ADC_G3_Channel(void)
{
    init_ADC_G3_SingleCh(ADC_G3_CH0);   /* 각 채널 초기화 */
    init_ADC_G3_SingleCh(ADC_G3_CH1);   //litekit A0(가변저항)
    init_ADC_G3_SingleCh(ADC_G3_CH2);
    init_ADC_G3_SingleCh(ADC_G3_CH3);
    init_ADC_G3_SingleCh(ADC_G3_CH4);
    init_ADC_G3_SingleCh(ADC_G3_CH5);
    init_ADC_G3_SingleCh(ADC_G3_CH6);
    init_ADC_G3_SingleCh(ADC_G3_CH7);   //가변저항

    IfxVadc_Adc_startScan(&adcGroup3);  //아날로그값이 실제값으로 변환
    }

void ADC_G3_GetData(void)   //실제값을 디지털로 변환해서 가져오는 함수
{
    Ifx_VADC_RES    ADC_result;                                     /* 변환 결과 값 구조체 선언 */

    uint8 ch;
    for (ch = ADC_G3_CH0; ch < ADC_G3_MAX; ch++)
    {
        do{
            ADC_result = IfxVadc_Adc_getResult(&adcG3Channel[ch]);  /* 결과 값 가져오기 */
        }while(!ADC_result.B.VF);

        ADC_G3_RAWDATA[ch] = ADC_result.B.RESULT;                   /* 결과 값 저장 */
    }

    IfxVadc_Adc_startScan(&adcGroup3);
}

