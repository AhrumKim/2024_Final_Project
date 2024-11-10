/*
 * GPIO.h
 *
 *  Created on: 2024. 10. 25.
 *      Author: FM22
 */

#ifndef SCHEDULER_SCHEDULER_H_
#define SCHEDULER_SCHEDULER_H_

#include "Header_275.h"

#ifdef USE_GLOBAL_H
#define Global
#else
#define Global extern
#endif

Global void init_GPIO(void);

Global void AppScheduling(void);            //각 주기ㅏ다 아래 함수 실행
void Task1ms(void);
void Task10ms(void);
void Task100ms(void);

Global uint32 cnt1ms;                       //확인용 변수
Global uint32 cnt10ms;
Global uint32 cnt100ms;

#endif /* SCHEDULER_SCHEDULER_H_ */
