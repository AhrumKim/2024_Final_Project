/*
 * ADC.c
 *
 *  Created on: 2024. 10. 25.
 *      Author: FM22
 */
#include "GPIO.h"
#include "Encoder.h"

void Encoder(void)
{
   uint8 A = IfxPort_getPinState(PORT_023);
   uint8 B = IfxPort_getPinState(PORT_024);

   uint8 state = 0;

   if       (A == 0 && B == 0) {state = 0;}
   else if  (A == 1 && B == 0) {state = 1;}
   else if  (A == 1 && B == 1) {state = 2;}
   else if  (A == 0 && B == 1) {state = 3;}

   if       (state-state_old==1 || state-state_old==-3) {encoderCNT++; encoderDir = 1;}
   else if  (state-state_old==-1 || state-state_old==3) {encoderCNT--; encoderDir = -1;}

   theta = encoderCNT*1/16*0.25*360;    //한바퀴 1/16

   state_old = state;
}

