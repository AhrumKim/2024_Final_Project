/*
 * PWM.c
 *
 *  Created on: 2024. 10. 25.
 *      Author: FM22
 */
#include "PWM.h"

void init_Tom(void)
{
   IfxGtm_Tom_Timer_Config timerConfig;
   IfxGtm_Tom_Timer_initConfig(&timerConfig, &MODULE_GTM);

   timerConfig.base.frequency       = 2000;                                          /* PWM 주기 한 주기 간격이 2kHz 중요 중요!*/
   timerConfig.base.isrPriority     = PRIORITY_GTM;                                  /* 인터럽트 우선순위 */
   timerConfig.base.isrProvider     = IfxSrc_Tos_cpu0;                               /* 인터럽트 처리 cpu 설정 */
   timerConfig.base.minResolution   = (1.0/timerConfig.base.frequency) / 1000;       /* 최소 분해능 설정 */
   timerConfig.clock                = IfxGtm_Tom_Ch_ClkSrc_cmuFxclk0;                /* Base clock (100MHz)에서 몇을 나누어 사용할지 */
   timerConfig.base.countDir        = IfxStdIf_Timer_CountDir_upAndDown;             /* 비교파 모양 설정 */

   timerConfig.tom                  = IfxGtm_Tom_0;                                  /* 몇 번째 TOM 사용할지 설정 */
   timerConfig.timerChannel         = IfxGtm_Tom_Ch_0;                               /* TOM 채널 설정 */
   timerConfig.triggerOut           = &IfxGtm_TOM0_0_TOUT77_P15_6_OUT;               /* trigger 출력 핀 설정 */

   timerConfig.base.trigger.enabled             = TRUE;                              /* trigger 활성화 */
   timerConfig.base.trigger.outputEnabled       = TRUE;                              /* trigger 출력 활성화 */
   timerConfig.base.trigger.triggerPoint        = 500;                               /* 이벤트 발생(ex: 1) 후 몇 틱(tick) 후에 이벤트를 끝낼지 (ex:0) */
   timerConfig.base.trigger.risingEdgeAtPeriod  = TRUE;                              /* 디폴트를 0으로할지 1로 할지 (ex: TRUE --> 디폴트 0, 이벤트 발생 시 1) */

   IfxGtm_Tom_Timer_init(&GtmPwmHl.timer, &timerConfig);                             /* 설정 값 반영 */

   init_PWM(&timerConfig);       /* PWM 초기 설정 */
}

IFX_INTERRUPT(ISR_PWM_GTM, 0, PRIORITY_GTM);
void ISR_PWM_GTM(void)
{
    IfxCpu_enableInterrupts();
    IfxGtm_Tom_Timer_acknowledgeTimerIrq(&GtmPwmHl.timer);          /**/
}

void init_PWM(IfxGtm_Tom_Timer_Config *timerConfig)
{
    IfxGtm_Tom_PwmHl_Config pwmHlConfig;         /* Hl (Hardware level) */  /* PWM 구조체 선언 */
    IfxGtm_Tom_PwmHl_initConfig(&pwmHlConfig);   /* 구조체 디폴트 값으로 초기화 */

    IfxGtm_Tom_ToutMapP ccx[2], coutx[2];
    ccx[0]   = &IfxGtm_TOM0_4_TOUT22_P33_0_OUT; /* PWM 출력 핀 설정 Ch.1 ccx */  /*ccx coutx는 정상과 역상*/
    coutx[0] = &IfxGtm_TOM0_3_TOUT105_P10_3_OUT;/* PWM 출력 핀 설정 Ch.1 coutx */ /*모터 드라이버 채널B PWM*/

    ccx[1]   = &IfxGtm_TOM0_5_TOUT23_P33_1_OUT; /* PWM 출력 핀 설정 Ch.2 ccx */
    coutx[1] = &IfxGtm_TOM0_2_TOUT107_P10_5_OUT;/* PWM 출력 핀 설정 Ch.2 coutx */

    pwmHlConfig.timer                   = &GtmPwmHl.timer;                          /* 타이머 객체 설정 */
    pwmHlConfig.tom                     = timerConfig ->tom;                        /* TOM 설정 */
    pwmHlConfig.base.deadtime           = 2e-6;                                     /* 데드 타임 설정 잘 설정해야 함*/
    pwmHlConfig.base.minPulse           = 1e-6;                                     /* 최소 펄스 시간 설정 */
    pwmHlConfig.base.channelCount       = 2;                                        /* PWM 채널 수 설정 */
    pwmHlConfig.base.emergencyEnabled   = FALSE;                                    /* 비상 기능 설정 */
    pwmHlConfig.base.outputMode         = IfxPort_OutputMode_none;                  /* 출력 모드 설정 */
    pwmHlConfig.base.outputDriver       = IfxPort_PadDriver_cmosAutomotiveSpeed1;   /* PWM 드라이버 타입 설정) */
    pwmHlConfig.base.ccxActiveState     = Ifx_ActiveState_high;                     /* 핀 활성 상태 설정 (Low or High일 때 활성 설정) */
    pwmHlConfig.base.coutxActiveState   = Ifx_ActiveState_high;                     /* 핀 활성 상태 설정 (Low or High일 때 활성 설정) */
    pwmHlConfig.ccx                     = ccx;                                      /* 핀 적용 (Compare capture x) */
    pwmHlConfig.coutx                   = coutx;                                    /* 핀 적용 (Compare output x) */

    IfxGtm_Tom_PwmHl_init(&GtmPwmHl.pwm, &pwmHlConfig);                             /* PWM 설정 값 적용 */

    IfxGtm_Tom_PwmHl_setMode(&GtmPwmHl.pwm, Ifx_Pwm_Mode_centerAligned);            /* PWM 생성 방식 설정 */

    GtmPwmHl.duty[0] = 0;    /* Ch.1 듀티 설정 */
    GtmPwmHl.duty[1] = 0;     /* Ch.2 듀티 설정 */
    PWM_dutyUpdate();           /* 듀티 설정 */

    IfxGtm_Tom_Timer_run(&GtmPwmHl.timer);  /* 타이머 및 PWM 시작 */
}

void PWM_dutyUpdate()
{
    GtmPwmHl.duty[0] += 0.1 * direction;
    if (GtmPwmHl.duty[0] >= 1.0) {
        GtmPwmHl.duty[0] = 1.0;
        direction = -1;
            }
    else if (GtmPwmHl.duty[0] <= 0.0) {
        GtmPwmHl.duty[0] = 0.0;
        direction = 1;
            }

    IfxGtm_Tom_PwmHl *pwmHl = &GtmPwmHl.pwm;
    IfxGtm_Tom_Timer *timer = &GtmPwmHl.timer;

    Ifx_TimerValue timerPeriod = IfxGtm_Tom_Timer_getPeriod(timer); /* = 타이머 한 주기 Tic 수 */
    Ifx_TimerValue Duty2Tic[2];

    Duty2Tic[0] = (uint32)(GtmPwmHl.duty[0]*timerPeriod);           /* 듀티 값을 Tic 수로 한산 */
    Duty2Tic[1] = (uint32)(GtmPwmHl.duty[0]*timerPeriod);;          /* 듀티 값을 Tic 수로 한산 */

    IfxGtm_Tom_Timer_disableUpdate(timer);                          /* 업데이트 비활성화 */
    IfxGtm_Tom_PwmHl_setOnTime(pwmHl, Duty2Tic);                    /* 듀티 값 변경 */
    IfxGtm_Tom_Timer_applyUpdate(timer);                            /* 듀티 변경 값 적용 */
}

void init_GTM(void)
{
    boolean interruptState = IfxCpu_disableInterrupts();

    Ifx_GTM *gtm = &MODULE_GTM;
    float32 gtmFreq = IfxGtm_Cmu_getModuleFrequency(gtm);           /* GTM 모듈 클럭 주파수 가져오기(100MHz) */
    IfxGtm_enable(gtm);

    IfxGtm_Cmu_setGclkFrequency(&MODULE_GTM, gtmFreq);              /* Global clock 주기 설정) */

    float32 gtmGclkFreq = IfxGtm_Cmu_getGclkFrequency(gtm);
    IfxGtm_Cmu_setClkFrequency(&MODULE_GTM, IfxGtm_Cmu_Clk_0, gtmGclkFreq); /* clk_0 클럭 주파수 설정) */

    init_Tom();         /* TOM 및 PWM 초기 설정 */

    IfxCpu_restoreInterrupts(interruptState);   /* enable interrupts again */
    IfxGtm_Cmu_enableClocks(gtm, IFXGTM_CMU_CLKEN_FXCLK | IFXGTM_CMU_CLKEN_CLK0);
}
