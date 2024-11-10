/*
 * STM.c
 *
 *  Created on: 2024. 10. 25.
 *      Author: FM22
 */
#include "STM.h"
#include "GPIO.h"
#include "ADC.h"

uint32 counter1ms = 0;
uint32 Scheduler1msFlag = 0;
uint32 Scheduler10msFlag = 0;
uint32 Scheduler100msFlag = 0;

void init_STM(void)
{
    boolean ISR_State = IfxCpu_disableInterrupts();     // 진행 중인 인터럽트를 반환 및 인터럽트 중지

    IfxStm_enableOcdsSuspend(STM0);                     //OCDS: on chip debugging system [디버깅 시,cpu 중단하면 타이머도 같이 중단되도록 설정(시스템 상태분석 용이)]
    IfxStm_initCompareConfig(&stmConfig);                // 비교기능 구조체 초기화 (초기값 정의)

    stmConfig.ticks           = 100000u;             // 주기 (비교 값) 설정 1밀리초 뒤 시작
    stmConfig.triggerPriority = 100u;                   // STM 모듈에서 발생한 인터럽트 우선순위 설정 100번째 함수
    stmConfig.typeOfService   = IfxSrc_Tos_cpu0;        // STM에서 발생한 인터럽트를 cpu0에서 처리하도록 설정

    IfxStm_initCompare(STM0, &stmConfig);               // STM0의 비교기 초기화 및 설정 값 적용 (stmConfig로 바꿈)

    IfxCpu_restoreInterrupts(ISR_State);                // 진행 중이던 인터럽트 상태 복원
}


IFX_INTERRUPT(ISR_STM,0,100);                           // 인터럽트 등록 명령어 (실행할 함수, 벡터 테이블 번호, 우선순위)

void ISR_STM(void)
{
    IfxCpu_enableInterrupts();
    IfxStm_clearCompareFlag(STM0, stmConfig.comparator);                // 비교 flag 초기화 (완료 표시 초기화)
    IfxStm_increaseCompare(STM0, stmConfig.comparator, 100000u);     // 비교 값 업데이트 (100000u >> 100000/100M = 0.001 = 1ms)

    counter1ms++;

    if ((counter1ms % 1) == 0){Scheduler1msFlag = 1;}           //1밀리초에 한번 flag가 1로 올라감 1초에 실행되는 scheduler 실행
    if ((counter1ms % 10) == 0){Scheduler10msFlag = 1;}         //
    if ((counter1ms % 100) == 0){Scheduler100msFlag = 1;}       //1000000u >> 10ms, 10ms&100 = 1s

}

/* 실습 1 */
//IFX_INTERRUPT(ISR_STM,0,100);
//void ISR_STM(void)
//{
//
//    IfxCpu_enableInterrupts();
//    IfxStm_clearCompareFlag(STM0, stmConfig.comparator);
//    IfxStm_increaseCompare(STM0, stmConfig.comparator, 10000*ADC_G3_RAWDATA[1]);     // 비교 값 업데이트 (10000000u를 바꾸면 주기가 바뀜)
//
//    IfxPort_togglePin(PORT_102);
//}

