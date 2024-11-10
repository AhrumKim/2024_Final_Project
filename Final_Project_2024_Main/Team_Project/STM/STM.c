/*
 * STM.c
 *
 *  Created on: 2024. 10. 28.
 *      Author: FM17
 */


#include "GPIO.h"
#include "STM.h"
#include "ADC.h"


uint32 counter1ms = 0;
uint32 Scheduler1msFlag = 0;
uint32 Scheduler10msFlag = 0;
uint32 Scheduler100msFlag = 0;
uint32 Scheduler1000msFlag = 0;

void init_STM(void){

    boolean ISR_State = IfxCpu_disableInterrupts();

    IfxStm_enableOcdsSuspend(STM0);
    IfxStm_initCompareConfig(&stmConfig);

    stmConfig.ticks             = 100000u;
    stmConfig.triggerPriority   = 100u;
    stmConfig.typeOfService     = IfxSrc_Tos_cpu0;

    IfxStm_initCompare(STM0, &stmConfig);

    IfxCpu_restoreInterrupts(ISR_State);

}

IFX_INTERRUPT(ISR_STM,0,100);
void ISR_STM(void){
    IfxCpu_enableInterrupts();
    IfxStm_clearCompareFlag(STM0, stmConfig.comparator);
    IfxStm_increaseCompare(STM0, stmConfig.comparator,100000u);
    //IfxStm_increaseCompare(STM0, stmConfig.comparator,count_STM); // Debug Mode

    counter1ms++;

    if((counter1ms % 1)==0) Scheduler1msFlag = 1;
    if((counter1ms % 10)==0) Scheduler10msFlag = 1;
    if((counter1ms % 100)==0) Scheduler100msFlag = 1;
    if((counter1ms % 1000)==0) Scheduler1000msFlag = 1;
    //if((counter1ms % ((int)ADC_G4_RAWDATA[6]/4))==0) SchedulerFlag = 1;

    //IfxPort_togglePin(PORT_102);
}
