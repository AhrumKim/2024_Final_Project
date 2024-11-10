/*
 * STM.c
 *
 *  Created on: 2024. 10. 28.
 *      Author: 최종윤
 */

#include "Header_USER.h"

uint32 counter1ms = 0;
uint32 Scheduler1msFlag = 0;
uint32 Scheduler10msFlag = 0;
uint32 Scheduler100msFlag = 0;

void init_STM(void)
{
    boolean ISR_State = IfxCpu_disableInterrupts();

    IfxStm_enableOcdsSuspend(STM0);
    IfxStm_initCompareConfig(&stmConfig);

    stmConfig.ticks = 100u;     //100u
    stmConfig.triggerPriority = 3u;
    stmConfig.typeOfService = IfxSrc_Tos_cpu1;

    IfxStm_initCompare(STM0, &stmConfig);

    IfxCpu_restoreInterrupts(ISR_State);
}

void ISR_STM(void)
{
    IfxCpu_enableInterrupts();
    IfxStm_clearCompareFlag(STM0, stmConfig.comparator);
    IfxStm_increaseCompare(STM0, stmConfig.comparator, 100u); /***PERIOD***/


    //IfxPort_togglePin(DHT11_PIN);

    counter1ms++;
    //IfxPort_togglePin(PORT_102);

    if((counter1ms % 1) == 0)
    {
        Scheduler1msFlag = 1;
    }

    if((counter1ms % 100000) == 0)
        {
            Scheduler100msFlag = 1;
        }

}

IFX_INTERRUPT(ISR_STM,0,3);

