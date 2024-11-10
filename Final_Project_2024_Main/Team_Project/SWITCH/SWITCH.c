/*
 * SWITCH.c
 *
 *  Created on: 2024. 10. 30.
 *      Author: 최종윤
 */

#include "SWITCH.h"
#include "GPIO.h"


//void init_SWITCH(void)
//{
//    IfxPort_setPinModeInput(PORT_002, IfxPort_InputMode_pullUp); // SW1 핀을 입력으로 설정
//} // 초기화 함수

int GetState_SWITCH(void)
{
    static int state = 0;  // 현재 반환할 상태 (0 또는 1)
    static int lastSwitchState = 1;  // 이전 스위치 상태를 추적
    int currentSwitchState = IfxPort_getPinState(PORT_SW1);

    // SW1을 눌렀다 떼는 동작이 발생할 때 상태를 변경
    if (currentSwitchState == 1 && lastSwitchState == 0)  // 눌렀다 떼면
    {
        state = !state;  // 상태를 반전
    }

    // 현재 스위치 상태를 기록
    lastSwitchState = currentSwitchState;


    // 현재 상태 반환
    return state;
} // SW1을 눌렀다 떼면 1과 0을 번갈아 반환하는 함수
