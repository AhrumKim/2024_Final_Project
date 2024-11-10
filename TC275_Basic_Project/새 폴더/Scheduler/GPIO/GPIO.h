/*
 * GPIO.h
 *
 *  Created on: 2024. 10. 25.
 *      Author: FM22
 */

#ifndef GPIO_GPIO_H_
#define GPIO_GPIO_H_

#include "Header_275.h"

#ifdef USE_GLOBAL_H
#define Global
#else
#define Global extern
#endif



#define PORT_005    &MODULE_P00,5   /*ShieldBuddy P10.2(LED,D13) */  /* LiteKit P00.5(LED1, D8)    */
#define PORT_102    &MODULE_P10,2   //LED1
#define PORT_101    &MODULE_P10,1   //LED2
#define PORT_105    &MODULE_P10,5   //RGB G LED

Global void init_GPIO(void);

Global void Good_LED_toggle(void);
Global void LED_toggle(void);
Global float a;
Global float b;

#endif /* GPIO_GPIO_H_ */
