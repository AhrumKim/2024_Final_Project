/*
 * PWM.h
 *
 *  Created on: 2024. 10. 29.
 *      Author: FM17
 */

#ifndef PWM_PWM_H_
#define PWM_PWM_H_


#include "Header_275.h"

#ifdef USE_GLOBAL_H
#define Global
#else
#define Global extern
#endif

#define PRIORITY_GTM       200u

typedef struct{
        IfxGtm_Tom_Timer        timer;
        IfxGtm_Tom_PwmHl        pwm;
        float32                 duty[2];
}st_GtmTomPwmHl;

Global st_GtmTomPwmHl   GtmPwmHl;

Global int Sudden_accel_flag;

void init_Tom(void);
void init_PWM(IfxGtm_Tom_Timer_Config *timerConfig);

Global void init_GTM(void);
Global void PWM_dutyUpdate();
Global void target_speed_decision(void);

#endif /* PWM_PWM_H_ */
