/*
 * GPIO.c
 *
 *  Created on: 2024. 10. 25.
 *      Author: FM22
 */
#include "GPIO.h"



void init_GPIO(void)
{
    IfxPort_setPinModeOutput(PORT_005, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(PORT_102, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(PORT_101, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(PORT_105, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(PORT_206, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinLow(PORT_206); /*CAN 트랜시버 활성화를 위해 LOW로 설정*/
}


void LED_toggle(void){
    int i = 0;
    int j = 0; /*10^7*/
    for (i = 0; i < 10^8; i++){
        IfxPort_setPinHigh(PORT_005);
    }
    for (j = 0; j < 10^8; j++){
        IfxPort_setPinLow(PORT_005);
    }
}

void Good_LED_toggle(void){
    if(a>10){
        a = 0;
        IfxPort_togglePin(PORT_005);
    }
    a += 0.0001;    /*(0.0001*10^5 = 10)*/
}


