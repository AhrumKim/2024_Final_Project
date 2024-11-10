/*
 * SUB.h
 *
 *  Created on: 2024. 11. 3.
 *      Author: 최종윤
 */

#ifndef SUB_SUB_H_
#define SUB_SUB_H_

#include "Header_275.h"

#ifdef USE_GLOBAL_H
#define Global
#else
#define Global extern
#endif

Global void check_temperature_and_send_warning(void);

#endif /* SUB_SUB_H_ */
