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


#define PORT_SW1 &MODULE_P02,0 /*ShieldBuddy P02.0  / D2 SW1 */

#define PORT_BUZZER &MODULE_P02,3 /*ShieldBuddy P02.3  / D5 BUZZER */

#define PORT_R_LED &MODULE_P02,4 /*ShieldBuddy P02.4  / D6 R_LED */
#define PORT_B_LED &MODULE_P02,5 /*ShieldBuddy P02.5  / D7 B_LED */

#define PORT_R_RGB &MODULE_P02,7 /*ShieldBuddy P02.7  / D9 RGB(R) */
#define PORT_G_RGB &MODULE_P10,5 /*ShieldBuddy P10.5  / D10 RGB(G) */
#define PORT_B_RGB &MODULE_P00,4 /*ShieldBuddy P00.4  / D33 RGB(B) */

//#define PORT_PWM &MODULE_P10,3 /*ShieldBuddy P10.3  / D11 PWM */
#define PORT_DIR &MODULE_P10,2 /*ShieldBuddy P10.2  / D13 B_DIR */

#define PORT_ENCODER_A &MODULE_P00,0 /*ShieldBuddy P10.1  / D25 A encoder */
#define PORT_ENCODER_B &MODULE_P00,1 /*ShieldBuddy P10.2  / D27 B encoder */

#define PORT_TRIG_MAIN &MODULE_P15,6 /*ShieldBuddy P15.6  / D24 Trig Main*/
#define PORT_ECHO_MAIN &MODULE_P00,8 /*ShieldBuddy P00.8  / D26 Echo Main*/

#define PORT_TRIG_SUB &MODULE_P11,6 /*ShieldBuddy P11.6  / D47 Trig Sub*/
#define PORT_ECHO_SUB &MODULE_P11,2 /*ShieldBuddy P11.2  / D45 Echo Sub*/

Global void init_GPIO(void);
Global float count;

#endif /* GPIO_GPIO_H_ */


