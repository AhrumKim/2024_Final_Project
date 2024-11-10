/*
 * Scheduler.h
 *
 *  Created on: 2024. 10. 28.
 *      Author: FM17
 */

#ifndef SCHEDULER_SCHEDULER_H_
#define SCHEDULER_SCHEDULER_H_


#include "Header_275.h"

#ifdef USE_GLOBAL_H
#define Global
#else
#define Global extern
#endif

Global void AppScheduling(void);
void Task1ms(void);
void Task10ms(void);
void Task100ms(void);
void Task1000ms(void);

Global uint32 cnt1ms;
Global uint32 cnt10ms;
Global uint32 cnt100ms;
Global uint32 cnt1000ms;

#endif /* SCHEDULER_SCHEDULER_H_ */
