/*
 * SWITCH.h
 *
 *  Created on: 2024. 10. 30.
 *      Author: 최종윤
 */

#ifndef SWITCH_SWITCH_H_
#define SWITCH_SWITCH_H_

#include "Header_275.h"

#ifdef USE_GLOBAL_H
#define Global
#else
#define Global extern
#endif

//Global int switchState; // ACC 모드 on/off 설정시 switchState 이름 사용하면 됨
Global int Mode_flag;

//void init_SWITCH(void);
int GetState_SWITCH(void);


#endif /* SWITCH_SWITCH_H_ */
