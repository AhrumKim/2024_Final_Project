/*
 * GPIO.h
 *
 *  Created on: 2024. 10. 25.
 *      Author: FM22
 */

#ifndef UART_UART_H_
#define UART_UART_H_

#include "Header_275.h"

#ifdef USE_GLOBAL_H
#define Global
#else
#define Global extern
#endif


Global uint8 RXDATA;
Global float RXcnt;

void init_UART(void);                                /* UART 초기화 함수 선언 */

void out_UART0(const unsigned char chr);            /* UART 송신 함수 */


#endif /* UART_H_ */
