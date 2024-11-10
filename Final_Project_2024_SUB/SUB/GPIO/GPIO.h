/*
 * GPIO.h
 *
 *  Created on: 2024. 10. 25.
 *      Author: FM16
 */

#ifndef GPIO_GPIO_H_
#define GPIO_GPIO_H_

#include "Header_275.h"

#ifdef USE_GLOBAL_H
#define Global
#else
#define Global extern
#endif

/**********pin setting***********/
#define PORT_027 &MODULE_P02,7 /*ShieldBuddy P10.2  / D9 */
#define PORT_105 &MODULE_P10,5 /*ShieldBuddy P10.2  / D10 */
#define PORT_103 &MODULE_P10,3 /*ShieldBuddy P10.2  / D11 */
#define PORT_101 &MODULE_P10,1 /*ShieldBuddy P10.1  / D12 */
#define PORT_102 &MODULE_P10,2 /*ShieldBuddy P10.2  / D13 */

#define PORT_000 &MODULE_P00,0 /*ShieldBuddy P10.1  / A encoder */
#define PORT_001 &MODULE_P00,1 /*ShieldBuddy P10.2  / B encoder */

Global void init_GPIO(void);
Global int Delay_MS(int n);

Global int time;
Global float count;

#endif /* GPIO_GPIO_H_ */


