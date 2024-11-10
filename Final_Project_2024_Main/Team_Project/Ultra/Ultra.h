/*
 * Ultra.h
 *
 *  Created on: 2024. 11. 2.
 *      Author: FM17
 */

#ifndef ULTRA_ULTRA_H_
#define ULTRA_ULTRA_H_

#include "Header_275.h"

#ifdef USE_GLOBAL_H
#define Global
#else
#define Global extern
#endif

Global float distance1;
Global float distance2;
Global float filtered_dist1;
Global float filtered_dist2;
Global float distance_prev;
Global uint32 startTime;
Global uint32 endTime;


Global int Ultra_flag;
Global int Ultra_select;

Global void init_Ultra(void);
Global void init_Trigger(void);
Global void measureDistance1(void);
Global void measureDistance2(void);
Global void obstacle_state_decision(void);



#endif /* ULTRA_ULTRA_H_ */
