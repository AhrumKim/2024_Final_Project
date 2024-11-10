/*
 * Ultrasonic_241031_ver1.c
 *
 *  Created on: 2024. 10. 31.
 *      Author: FM15
 */


#include "Ultra.h"
#include "GPIO.h"
#include "STM.h"
#include "Header_USER.h"


float alpha_Ultra=0.2;

void init_Ultra(void)
{
    Ultra_flag = 0;         // 변수 초기화
    Ultra_select = 0;

    IfxPort_setPinLow(PORT_TRIG_MAIN);
    IfxPort_setPinLow(PORT_TRIG_SUB);
}

void init_Trigger(void)
{
    //IfxPort_setPinLow(trigger);     //
    //IfxStm_waitTicks(STM0, IfxStm_getFrequency(STM0) / 100000);
    IfxPort_setPinHigh(PORT_TRIG_MAIN);
    IfxStm_waitTicks(STM0, IfxStm_getFrequency(STM0) / 100000);
    IfxPort_setPinLow(PORT_TRIG_MAIN);

    IfxPort_setPinHigh(PORT_TRIG_SUB);
    IfxStm_waitTicks(STM0, IfxStm_getFrequency(STM0) / 100000);
    IfxPort_setPinLow(PORT_TRIG_SUB);
}

void measureDistance1(void)
{
    init_Trigger();

    float OutNum = 0;
    float errFlag1 = 0;
    while (IfxPort_getPinState(PORT_ECHO_MAIN) == 0)
    {
        OutNum += 0.01;
        if (OutNum > 10) {OutNum = 0; errFlag1 = 1; break;}
    }
    startTime = IfxStm_getLower(STM0);

    while (IfxPort_getPinState(PORT_ECHO_MAIN) == 1);
    endTime = IfxStm_getLower(STM0);

    distance1 = ((endTime - startTime) / (float)IfxStm_getFrequency(STM0)) * 34300 * 0.5;
    filtered_dist1 = alpha_Ultra * distance1 + (1 - alpha_Ultra) * filtered_dist1;
}

// OutNum, alpha 값 조정으로 튜닝 가능

/* 거리에 따른 함수*/
//    if (0<= filtered_theta1 && filtered_theta1<= 30)
//
//    if (30< filtered_theta1 && filtered_theta1<= 70)
//
//    if (filtered_theta1 > 70){errFlag == 1;}
//    if (errFlag == 1){distance = distance_prev;}


//    distance_prev = distance;

void measureDistance2(void)
{
    init_Trigger();

    float OutNum = 0;
    float errFlag2 = 0;
    while (IfxPort_getPinState(PORT_ECHO_SUB) == 0)
    {
        OutNum += 0.01;
        if (OutNum > 10) {OutNum = 0; errFlag2 = 1; break;}
    }
    startTime = IfxStm_getLower(STM0);

    while (IfxPort_getPinState(PORT_ECHO_SUB) == 1);
    endTime = IfxStm_getLower(STM0);

    distance2 = ((endTime - startTime) / (float)IfxStm_getFrequency(STM0)) * 34300 * 0.5;
    filtered_dist2 = alpha_Ultra * distance2 + (1 - alpha_Ultra) * filtered_dist2;
}

void obstacle_state_decision(void){
    if(Sudden_accel_flag == 0){
        if(Ultra_select == 0){
            measureDistance1();     // filtered_dist1
            if(filtered_dist1 <= 10){
                Ultra_flag = 1;
            }
            else if(filtered_dist1 > 10 && filtered_dist1 <= 30){
                Ultra_flag = 2;
            }
            else if(filtered_dist1 > 30 && filtered_dist1 <= 70){
                Ultra_flag = 3;
            }
            else if(filtered_dist1 > 70){
                Ultra_flag = 0;
                Ultra_select = 1;
            }
        }
        else{
            measureDistance2();
            if(filtered_dist2 <= 10){
                Ultra_flag = 1;
            }
            else if(filtered_dist2 > 10 && filtered_dist2 <= 30){
                Ultra_flag = 2;
            }
            else if(filtered_dist2 > 30 && filtered_dist2 <= 70){
                Ultra_flag = 3;
            }
            else if(filtered_dist2 > 70){
                Ultra_flag = 0;
                Ultra_select = 0;
            }
        }
    }
    else{
        // 급발진시 초음파 작동 X
    }
}
