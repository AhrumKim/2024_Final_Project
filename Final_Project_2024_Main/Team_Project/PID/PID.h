/*
 * PID.h
 *
 *  Created on: 2024. 11. 3.
 *      Author: FM17
 */

#ifndef PID_PID_H_
#define PID_PID_H_


#include "Header_275.h"

#ifdef USE_GLOBAL_H
#define Global
#else
#define Global extern
#endif


Global float32 ADC_variable;   // 가변저항 입력 펄스 값 [0~4095] -> [0~1] / ACC ON(속도 유지), ACC OFF(속도 변경 가능)
                        // RGB 점등 플레그 [1, 2, 3] -> 초록, 노랑, 빨강
                        // 최고 속도 일때 급발진 상황 -> 3초 이내 모터속도 0까지 감속

Global uint32 ultra_flag;     // 초음파 입력 플레그 [1, 2, 3]    -> 정지, 감속, 속도유지
Global uint32 encoder;        // 엔코더 입력[??]    -> PID 제어
Global uint32 switch1_flag;        // 스위치 입력 플레그 [0, 1] -> [ACC off, ACC on]
Global uint32 RGB_LED_flag;        // RGB 점등 플레그 [1, 2, 3] -> [초록, 노랑, 빨강]

void PID_motor_control(void);
void init_PID();

Global float Kp;
Global float Ki;
Global float Kd;

Global float32 previous_error;    // 이전 에러
Global float32 integral;      // 적분
Global float target_speed;  // 목표 속도 (예: ADC 입력을 통해 설정)
Global float32 current_speed;  // 목표 속도 (예: ADC 입력을 통해 설정)
Global float32 control;      // 제어 신호

#endif /* PID_PID_H_ */
