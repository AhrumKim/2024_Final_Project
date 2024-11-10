/*
 * STM.c
 *
 *  Created on: 2024. 10. 25.
 *      Author: FM22
 */
#include <Scheduler/Scheduler.h>

#include "Scheduler.h"
#include "GPIO.h"
#include "ADC.h"

extern uint32 Scheduler1msFlag;
extern uint32 Scheduler10msFlag;
extern uint32 Scheduler100msFlag;

//IfxStm_CompareConfig     stmConfig;
void AppScheduling(void)
{
    if (Scheduler1msFlag == 1)
    {
        Scheduler1msFlag = 0;
        Task1ms();

        if (Scheduler10msFlag == 1)
        {
            Scheduler10msFlag = 0;
            Task10ms();
        }
        if (Scheduler100msFlag == 1)
        {
            Scheduler100msFlag = 0;
            Task100ms();
        }
    }
}


void Task1ms(void)
{
       cnt1ms++;
}
void Task10ms(void)
{
    CAN_TX();
    cnt10ms++;
}
void Task100ms(void)
{
    cnt100ms++;
}

