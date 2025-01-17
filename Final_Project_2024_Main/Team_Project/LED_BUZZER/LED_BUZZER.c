/*
 * LED_BUZZER.c
 *
 *  Created on: 2024. 11. 3.
 *      Author: FM17
 */
#include "LED_BUZZER.h"
#include "GPIO.h"
#include "Header_USER.h"

static uint32 led_buzzerCounter = 0;  // LED 부저 깜빡임 카운터

void redled_buzzer_cycle(void){
    if(Mode_flag == 1 && Ultra_flag == 1 && Ultra_select == 0 ){
        led_buzzerCounter++;
        if (led_buzzerCounter >= 2)  // 100ms * 2 = 200ms
        {
            IfxPort_togglePin(PORT_R_LED);
            IfxPort_togglePin(PORT_BUZZER);
            led_buzzerCounter = 0;
        }
    }
    else if(Mode_flag == 1 && Ultra_flag == 2 && Ultra_select == 0 ){
        led_buzzerCounter++;
        if (led_buzzerCounter >= 5)  // 100ms * 5 = 500ms
        {
            IfxPort_togglePin(PORT_R_LED);
            IfxPort_togglePin(PORT_BUZZER);
            led_buzzerCounter = 0;
        }
    }
    else if(Mode_flag == 1 && Ultra_flag == 3 && Ultra_select == 0 ){
        IfxPort_setPinLow(PORT_R_LED);
        IfxPort_setPinLow(PORT_BUZZER);
    }
    else if(Mode_flag == 1 && Ultra_select == 1){
        led_buzzerCounter++;
        if (led_buzzerCounter >= 10)  // 100ms * 10 = 1000ms
        {
            IfxPort_togglePin(PORT_R_LED);
            IfxPort_togglePin(PORT_BUZZER);
            led_buzzerCounter = 0;
        }
    }
    else if(Mode_flag == 0 || Sudden_accel_flag == 1){
        IfxPort_setPinLow(PORT_R_LED);
        IfxPort_setPinLow(PORT_BUZZER);
    }
}

void rgb_led_color(void){
    if(GtmPwmHl.duty[0] >= 0 && GtmPwmHl.duty[0] <= 0.3){    // 0~30 초록
        IfxPort_setPinLow(PORT_R_RGB);
        IfxPort_setPinHigh(PORT_G_RGB);
        IfxPort_setPinLow(PORT_B_RGB);
    }
    else if(GtmPwmHl.duty[0] > 0.3 && GtmPwmHl.duty[0] <= 0.6){   // 31~60 노랑
        IfxPort_setPinHigh(PORT_R_RGB);
        IfxPort_setPinHigh(PORT_G_RGB);
        IfxPort_setPinLow(PORT_B_RGB);
    }
    else if(GtmPwmHl.duty[0] > 0.6 && GtmPwmHl.duty[0] <= 1){     // 61~100 파랑
        IfxPort_setPinLow(PORT_R_RGB);
        IfxPort_setPinLow(PORT_G_RGB);
        IfxPort_setPinHigh(PORT_B_RGB);
    }
}

void blue_led_onoff(void){
    if(Mode_flag == 0 || Sudden_accel_flag == 1){IfxPort_setPinLow(PORT_B_LED);}
    else if(Mode_flag == 1){IfxPort_setPinHigh(PORT_B_LED);}
}
