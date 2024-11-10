/*
 * GPIO.c
 *
 *  Created on: 2024. 10. 25.
 *      Author: FM22
 */
#include "GPIO.h"



void init_GPIO(void)
{
    IfxPort_setPinModeInput(PORT_023, IfxPort_InputMode_pullDown);
    IfxPort_setPinModeInput(PORT_024, IfxPort_InputMode_pullDown);
}



