/*
 * GPIO.h
 *
 *  Created on: 2024. 10. 25.
 *      Author: FM22
 */

#ifndef PWM_PWM_H_
#define PWM_PWM_H_

#include "Header_275.h"

#ifdef USE_GLOBAL_H
#define Global
#else
#define Global extern
#endif

#define PRIORITY_GTM    200u                        /* 인터럽트 우선순위 설정 변수 */

typedef struct
{
    IfxGtm_Tom_Timer    timer;                      /* 타이머 선언 */
    IfxGtm_Tom_PwmHl    pwm;                        /* pwm 선언 */
    float32             duty[2];                    /* duty 구조체 선언 */
}st_GtmTomPwmHl;

Global st_GtmTomPwmHl GtmPwmHl;

void init_Tom(void);                                /* TOM 초기화 함수 선언 */
void init_PWM(IfxGtm_Tom_Timer_Config *timerConfig);/* PWM 초기화 함수 선언 */
Global void init_GTM(void);                         /* GTM 초기화 함수 선언 */
Global void PWM_dutyUpdate();                       /* PWM duty 업데이트 함수 선언 */

Global int direction;

#endif /* PWM_PWM_H_ */
