/*
 * UART.h
 *
 *  Created on: 2024. 10. 29.
 *      Author: FM17
 */

#ifndef UART_UART_H_
#define UART_UART_H_


#include "Header_275.h"

#ifdef USE_GLOBAL_H
#define Global
#else
#define Global extern
#endif


typedef enum{
    byte0 = 0u,  // 0
    byte1,       // 1
    byte2,       // 2
    byteEnd      // 5
};


Global char Uart_SUB_Output;
Global char Uart_PC_Output;


//----------------- Main <-> PC -----------------//
Global float RXcnt_PC;
Global uint8 RXDATA_PC[byte2];

void init_UART_PC(void);
void out_UART_PC(uint8 data); // uart 송신 함수
void read_UART_PC(void);  // uart 수신 함수



//----------------- Main <-> Sub -----------------//
Global float RXcnt_SUB;
Global uint8 RXDATA_SUB[byteEnd];

void init_UART_SUB(void);
void out_UART_SUB(const unsigned char chr); // uart 송신 함수
void read_UART_SUB(void);  // uart 수신 함수

#endif /* UART_UART_H_ */
