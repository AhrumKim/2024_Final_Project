/* DHT11.c
 *
 *  Created on: 2024. 11. 2.
 *      Author: 최종윤
 */


#include "Header_USER.h"




// 핀 모드 설정 (출력/입력)
static void set_pin_mode_output(void) {
    IfxPort_setPinModeOutput(DHT11_PIN, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
}

static void set_pin_mode_input(void) {
    IfxPort_setPinModeInput(DHT11_PIN, IfxPort_InputMode_pullDown);
}

// 핀 값 설정 및 읽기
static void set_pin_low(void) {
    IfxPort_setPinLow(DHT11_PIN);
}

static void set_pin_high(void) {
    IfxPort_setPinHigh(DHT11_PIN);
}

static int read_pin(void) {
    return IfxPort_getPinState(DHT11_PIN);
}

// 시간 지연 함수 (마이크로초 단위)
static void delay_us(uint32_t us) {
    for (volatile uint32_t i = 0; i < us * 100; ++i);
}

// 2초 대기 함수
void delay_ms(uint32_t ms) {
    for (volatile uint32_t i = 0; i < ms * 1000 * 100; ++i);
}

//void DHT11_init(void) {
//    set_pin_mode_output();
//    set_pin_high();  // 대기 상태 (High)
//}

int DHT11_read(int *temperature, int *humidity) {
    uint8_t data[5] = {0};

    // DHT11 시작 신호 보내기
    set_pin_mode_output();
    set_pin_low();
    IfxStm_waitTicks(STM0, IfxStm_getFrequency(STM0) / 1000 * 18); // 18ms
    set_pin_high();
    IfxStm_waitTicks(STM0, IfxStm_getFrequency(STM0) / 1000000 * 20); // 20us
    set_pin_mode_input();

    // 응답 신호 확인
    if (read_pin() == 1) return 0; // DHT11의 응답 신호 확인
    IfxStm_waitTicks(STM0, IfxStm_getFrequency(STM0) / 1000000 * 80); // 80us
    if (read_pin() == 0) return 0; // DHT11이 LOW 신호를 보내는지 확인
    IfxStm_waitTicks(STM0, IfxStm_getFrequency(STM0) / 1000000 * 80); // 80us

     //40 비트 데이터 수신
    for (int i = 0; i < 40; i++) {
        while (read_pin() == 0);  // 신호 시작 대기
        IfxStm_waitTicks(STM0, IfxStm_getFrequency(STM0) / 1000000 * 30); // 30us

        if (read_pin() == 1) {
            data[i / 8] |= (1 << (7 - (i % 8))); // 비트 설정
        }
        while (read_pin() == 1);  // 신호 끝날 때까지 대기
    }

    // 데이터 검증
    if ((uint8_t)(data[0] + data[1] + data[2] + data[3]) != data[4]) return 0;

    *humidity = data[0]; // 습도 데이터
    *temperature = data[2]; // 온도 데이터
    return 1; // 성공적으로 읽음
}


