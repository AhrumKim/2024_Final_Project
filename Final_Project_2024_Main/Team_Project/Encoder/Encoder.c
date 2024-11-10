/*
 * Encoder.c
 *
 *  Created on: 2024. 10. 28.
 *      Author: FM17
 */


#include "Encoder.h"
#include "GPIO.h"

float prev_input_low;
float prev_output_low;

float alpha_Encoder = 0.01;   // 저역 필터의 alpha 값 (컷오프 주파수에 따라 조정)


// LOW pass filter
float low_pass_filter(float input, float alpha) {
    float output = alpha * input + (1 - alpha) * prev_output_low;
    prev_output_low = output;  // 이전 출력 값 업데이트
    return output;
}


void Encoder(void){
    uint8 A = IfxPort_getPinState(PORT_ENCODER_A);
    uint8 B = IfxPort_getPinState(PORT_ENCODER_B);

    uint8 state = 0;

    if      (A==0 && B==0){state = 0;}
    else if (A==1 && B==0){state = 1;}
    else if (A==1 && B==1){state = 2;}
    else if (A==0 && B==1){state = 3;}

    if      (state-state_old==1 || state-state_old==-3) {encoderCNT++; encoderDir = 1;}
    else if (state-state_old==-1 || state-state_old==3) {encoderCNT--; encoderDir = -1;}

    //theta = encoderCNT*0.01*0.25*360;

    theta = (float)encoderCNT*360/48;

    state_old = state;

}



void radiantospeed(void)
{
    float32 deltaT = 0.001; // 0.001

    float Raw_Speed = theta/deltaT;
    //float Raw_Speed = theta;
    // low pass filter 적용
    float LPF_theta = low_pass_filter(Raw_Speed,alpha_Encoder);

    //velocity_rad = Filtered_speed;
    velocity_rad = LPF_theta;
    //velocity_rad = HPF_theta;

    //velocity_rad = theta / deltaT;
    //velocity_rpm = velocity_rad*9.5493;
    encoderCNT = 0;

   //  return velocity_rpm;
}
