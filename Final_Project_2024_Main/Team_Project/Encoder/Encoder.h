/*
 * Encode.h
 *
 *  Created on: 2024. 10. 28.
 *      Author: FM17
 */

#ifndef ENCODER_ENCODER_H_
#define ENCODER_ENCODER_H_


#include "Header_275.h"

#ifdef USE_GLOBAL_H
#define Global
#else
#define Global extern
#endif

Global uint8    state_old;
Global int      encoderCNT;
Global int      encoderDir;
Global float    theta;

Global float theta_old;
Global float mul_dif;
Global float dif;

Global float pre_angle;
Global float cur_angle;
Global float velocity_rad;
Global float velocity_rpm;

Global void Encoder(void);
float low_pass_filter(float input, float alpha);
void radiantospeed(void);


#endif /* ENCODER_ENCODER_H_ */
