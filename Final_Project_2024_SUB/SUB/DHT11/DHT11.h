/*
 * DHT11.h
 *
 *  Created on: 2024. 11. 2.
 *      Author: 최종윤
 */

#ifndef DHT11_DHT11_H_
#define DHT11_DHT11_H_

#include "Header_275.h"


#ifdef USE_GLOBAL_H
#define Global
#else
#define Global extern
#endif

#define DHT11_PIN &MODULE_P10, 4

Global int temperature;
Global int humidity;


// DHT11 센서 초기화
void DHT11_init(void);

// DHT11 센서로부터 온도 및 습도를 읽어오는 함수
int DHT11_read(int *temperature, int *humidity);



// 딜레이 함수 (2초 대기용)
void delay_ms(uint32_t ms);


#endif /* DHT11_DHT11_H_ */
