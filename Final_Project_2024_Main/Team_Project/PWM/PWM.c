/*
 * PWM.c
 *
 *  Created on: 2024. 10. 29.
 *      Author: FM17
 */


#include "PWM.h"
#include "Header_USER.h"



void init_Tom(void){

    IfxGtm_Tom_Timer_Config timerConfig;
    IfxGtm_Tom_Timer_initConfig(&timerConfig, &MODULE_GTM);

    timerConfig.base.frequency          = 2000;
    timerConfig.base.isrPriority        = PRIORITY_GTM;
    timerConfig.base.isrPriority        = IfxSrc_Tos_cpu0;
    timerConfig.base.minResolution      = (1.0/timerConfig.base.frequency)/1000;
    timerConfig.clock                   = IfxGtm_Tom_Ch_ClkSrc_cmuFxclk0;
    timerConfig.base.countDir           = IfxStdIf_Timer_CountDir_upAndDown;

    timerConfig.tom                     = IfxGtm_Tom_0;
    timerConfig.timerChannel            = IfxGtm_Tom_Ch_0;
    timerConfig.triggerOut              = &IfxGtm_TOM0_0_TOUT77_P15_6_OUT;

    timerConfig.base.trigger.enabled                = TRUE;
    timerConfig.base.trigger.outputEnabled          = TRUE;
    timerConfig.base.trigger.triggerPoint           = 500;
    timerConfig.base.trigger.risingEdgeAtPeriod     = TRUE;

    IfxGtm_Tom_Timer_init(&GtmPwmHl.timer, &timerConfig);

    init_PWM(&timerConfig);

}

IFX_INTERRUPT(ISR_PWM_GTM, 0, PRIORITY_GTM);
void ISR_PWM_GTM(void){
    IfxCpu_enableInterrupts();
    IfxGtm_Tom_Timer_acknowledgeTimerIrq(&GtmPwmHl.timer);
}

void init_PWM(IfxGtm_Tom_Timer_Config *timerConfig){
   IfxGtm_Tom_PwmHl_Config pwmHlConfig;
   IfxGtm_Tom_PwmHl_initConfig(&pwmHlConfig);

   IfxGtm_Tom_ToutMapP     ccx[2], coutx[2];
   coutx[0]     = &IfxGtm_TOM0_4_TOUT22_P33_0_OUT;
   ccx[0]   = &IfxGtm_TOM0_3_TOUT105_P10_3_OUT;

   ccx[1]     = &IfxGtm_TOM0_5_TOUT23_P33_1_OUT;
   coutx[1]   = &IfxGtm_TOM0_2_TOUT107_P10_5_OUT;

   pwmHlConfig.timer                    = &GtmPwmHl.timer;
   pwmHlConfig.tom                      = timerConfig->tom;
   pwmHlConfig.base.deadtime            = 2e-6;
   pwmHlConfig.base.minPulse            = 1e-6;
   pwmHlConfig.base.channelCount        = 2;
   pwmHlConfig.base.emergencyEnabled    = FALSE;
   pwmHlConfig.base.outputMode          = IfxPort_OutputMode_none;
   pwmHlConfig.base.outputDriver        = IfxPort_PadDriver_cmosAutomotiveSpeed1;
   pwmHlConfig.base.ccxActiveState      = Ifx_ActiveState_high;
   pwmHlConfig.base.coutxActiveState    = Ifx_ActiveState_high;
   pwmHlConfig.ccx                      = ccx;
   pwmHlConfig.coutx                    = coutx;

   IfxGtm_Tom_PwmHl_init(&GtmPwmHl.pwm, &pwmHlConfig);

   IfxGtm_Tom_PwmHl_setMode(&GtmPwmHl.pwm, Ifx_Pwm_Mode_centerAligned);

   GtmPwmHl.duty[0] = 0.0;
   GtmPwmHl.duty[1] = 0.9;
   PWM_dutyUpdate();

   IfxGtm_Tom_Timer_run(&GtmPwmHl.timer);
}


void PWM_dutyUpdate(){
    IfxGtm_Tom_PwmHl    *pwmHl  = &GtmPwmHl.pwm;
    IfxGtm_Tom_Timer    *timer  = &GtmPwmHl.timer;

    Ifx_TimerValue timerPeriod = IfxGtm_Tom_Timer_getPeriod(timer);
    Ifx_TimerValue Duty2Tic[2];

    Duty2Tic[0] = (uint32)(GtmPwmHl.duty[0]*timerPeriod);
    Duty2Tic[1] = (uint32)(GtmPwmHl.duty[1]*timerPeriod);

    IfxGtm_Tom_Timer_disableUpdate(timer);
    IfxGtm_Tom_PwmHl_setOnTime(pwmHl, Duty2Tic);
    IfxGtm_Tom_Timer_applyUpdate(timer);
}

void init_GTM(void){

    boolean interruptState   = IfxCpu_disableInterrupts();

    Ifx_GTM  *gtm = &MODULE_GTM;
    float32 gtmFreq = IfxGtm_Cmu_getModuleFrequency(gtm);
    IfxGtm_enable(gtm);


    IfxGtm_Cmu_setGclkFrequency(&MODULE_GTM, gtmFreq);

    float32 gtmGclkFreq = IfxGtm_Cmu_getGclkFrequency(gtm);
    IfxGtm_Cmu_setClkFrequency(&MODULE_GTM, IfxGtm_Cmu_Clk_0, gtmGclkFreq);

    init_Tom();

    IfxCpu_restoreInterrupts(interruptState);

    IfxGtm_Cmu_enableClocks(gtm, IFXGTM_CMU_CLKEN_FXCLK | IFXGTM_CMU_CLKEN_CLK0);
}


void target_speed_decision(void){
    if(ADC_G4_RAWDATA[5] == 4095){
        Sudden_accel_flag = 1;
        Mode_flag = 0;
    }

    if(Sudden_accel_flag == 1){
        target_speed = target_speed - 0.01;
    }
    else{
        if(Mode_flag == 0){         // 속도 변환만 가능
            target_speed = (float32)ADC_G4_RAWDATA[5]/4095;
        }
        else if(Mode_flag == 1 && Ultra_flag == 1){     // 정지
            target_speed = 0;
        }
        else if(Mode_flag == 1 && Ultra_flag == 2){     // 감속
            target_speed = ((float32)ADC_G4_RAWDATA[5]/4095)/2;
        }
        else if(Mode_flag == 1 && Ultra_flag == 3){     // 유지
            target_speed = (float32)ADC_G4_RAWDATA[5]/4095;
        }
    }

}











