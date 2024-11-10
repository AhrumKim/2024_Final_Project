/*
 * GPIO.h
 *
 *  Created on: 2024. 10. 25.
 *      Author: FM22
 */

#ifndef ENCODER_ENCODER_H_
#define ENCODER_ENCODER_H_

#include "Header_275.h"

#ifdef USE_GLOBAL_H
#define Global
#else
#define Global extern
#endif

Global uint8 state_old;     /* 현재 스테이트 */
Global int encoderCNT;      /* 펄스 카운트 */
Global int encoderDir;      /* 회전 방향 */
Global float theta;         /* 현재 회전 각도 */

Global void Encoder(void);

#endif /* ENCODER_ENCODER_H_ */
