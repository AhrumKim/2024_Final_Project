/*
 * PID.c
 *
 *  Created on: 2024. 10. 30.
 *      Author: FM17
 */


#include "PWM.h"
#include "Encoder.h"
#include "PID.h"

float alpha_PID = 0.01;

void init_PID(void){
    Kp = 5;
    Ki = 0.007;
    //Kd = 0.015;

    current_speed = 0.0;

    previous_error = 0.0;    // 이전 에러
    integral = 0.0;      // 적분
    control = 0.0;      // 제어 신호
    cur_angle = 0.0;

}

void PID_motor_control(void){
    float32 error, derivative;

    // PID 제어 계산
    current_speed = velocity_rad;
    //target_speed = (float)((int)(target_speed*100))/100;
    //target_speed = low_pass_filter(target_speed,alpha_PID);
    error = target_speed*34000 - current_speed;  // 현재 속도는 센서나 피드백 값에서 얻어옴
    integral += error;                     // 누적 오차
    derivative = error - previous_error;   // 오차 변화율

    control = (Kp * error) + (Ki * integral) + (Kd * derivative);

    previous_error = error;



    if (GtmPwmHl.duty[0] > 1) {
        GtmPwmHl.duty[0] = 1;
    }
    else if (GtmPwmHl.duty[0] < 0) {
        GtmPwmHl.duty[0] = 0;
    }
    else{
        GtmPwmHl.duty[0] = control/34000;
    }

}
