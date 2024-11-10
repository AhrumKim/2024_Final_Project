/*
 * GPIO.c
 *
 *  Created on: 2024. 10. 25.
 *      Author: FM16
 */

#include "Header_USER.h"


void init_GPIO(void)
{
    IfxPort_setPinModeOutput(PORT_101, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(PORT_102, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(PORT_027, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(PORT_105, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinModeOutput(PORT_103, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);


    IfxPort_setPinModeInput(PORT_000, IfxPort_InputMode_pullDown);
    IfxPort_setPinModeInput(PORT_001, IfxPort_InputMode_pullDown);
}


int Delay_MS(int n)
{
    int num = n*22222*3;
    for(int i=0;i<=num;i++)
      {
          if(i==num)
          {
              break;
          }
      }
    return 0;
}
