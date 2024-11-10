/*
 * Scheduler.c
 *
 *  Created on: 2024. 10. 28.
 *      Author: FM17
 */


//#include "Scheduler.h"
//#include "STM.h"
//#include "GPIO.h"
//#include "PWM.h"
//#include "PID.h"
//#include "ADC.h"
//#include "UART.h"
//#include "Encoder.h"
#include "Header_USER.h"

extern uint32 Scheduler1msFlag;
extern uint32 Scheduler10msFlag;
extern uint32 Scheduler100msFlag;
extern uint32 Scheduler1000msFlag;


void AppScheduling(void){
    if(Scheduler1msFlag == 1){
        Scheduler1msFlag = 0;
        Task1ms();

        if(Scheduler10msFlag == 1){
            Scheduler10msFlag = 0;
            Task10ms();
        }
        if(Scheduler100msFlag == 1){
            Scheduler100msFlag = 0;
            Task100ms();
        }
        if(Scheduler1000msFlag == 1){
            Scheduler1000msFlag = 0;
            Task1000ms();
        }

    }
}

void Task1ms(void){
    //cnt1ms++;
    radiantospeed();        // 엔코더 값 변환 및 필터링
    target_speed_decision();    // 목표 속도 판단
    PID_motor_control();    // PID 제어
    PWM_dutyUpdate();       // PWM 업데이트
}

void Task10ms(void){
    //cnt10ms++;
    Mode_flag = GetState_SWITCH();
    ADC_G4_GetData();
}

void Task100ms(void){
    //cnt100ms++;
    obstacle_state_decision();  // 장애물 상태 판단

    out_UART_PC('c');   //  목표 값, 현재 모터 속도 값 전송
    out_UART_SUB(Uart_SUB_Output);  // 쿨러 작동 신호 전송

    redled_buzzer_cycle();
    rgb_led_color();
    blue_led_onoff();

}

void Task1000ms(void){
    cnt1000ms++;

}
