/*
 * GPIO.c
 *
 *  Created on: 2024. 10. 25.
 *      Author: FM16
 */

#include "GPIO.h"

void init_GPIO(void)
{
    IfxPort_setPinModeOutput(PORT_R_LED, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(PORT_B_LED, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(PORT_R_RGB, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(PORT_G_RGB, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(PORT_B_RGB, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    //IfxPort_setPinModeOutput(PORT_PWM, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);

    IfxPort_setPinModeOutput(PORT_BUZZER, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(PORT_DIR, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);

    IfxPort_setPinModeOutput(PORT_TRIG_MAIN, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(PORT_TRIG_SUB, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);


    IfxPort_setPinModeInput(PORT_SW1, IfxPort_InputMode_pullUp);
    IfxPort_setPinModeInput(PORT_ENCODER_A, IfxPort_InputMode_pullDown);
    IfxPort_setPinModeInput(PORT_ENCODER_B, IfxPort_InputMode_pullDown);
    IfxPort_setPinModeInput(PORT_ECHO_MAIN, IfxPort_InputMode_pullDown);
    IfxPort_setPinModeInput(PORT_ECHO_SUB, IfxPort_InputMode_pullDown);
}
