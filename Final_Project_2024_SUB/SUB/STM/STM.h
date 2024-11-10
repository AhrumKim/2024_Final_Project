
/*
 * STM.h
 *
 *  Created on: 2024. 10. 28.
 *      Author: 최종윤
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


#endif /* STM_STM_H_ */
