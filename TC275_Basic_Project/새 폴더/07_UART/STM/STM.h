/*
 * GPIO.h
 *
 *  Created on: 2024. 10. 25.
 *      Author: FM22
 */

#ifndef STM_STM_H_
#define STM_STM_H_

#include "Header_275.h"

#ifdef USE_GLOBAL_H
#define Global
#else
#define Global extern
#endif


#define STM0    &MODULE_STM0

Global IfxStm_CompareConfig     stmConfig;

Global void init_STM(void);

Global float t;

#endif /* STM_STM_H_ */
