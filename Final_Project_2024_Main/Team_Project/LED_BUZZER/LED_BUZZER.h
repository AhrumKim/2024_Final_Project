/*
 * LED_BUZZER.h
 *
 *  Created on: 2024. 11. 3.
 *      Author: FM17
 */

#ifndef LED_BUZZER_LED_BUZZER_H_
#define LED_BUZZER_LED_BUZZER_H_

#include "Header_275.h"

#ifdef USE_GLOBAL_H
#define Global
#else
#define Global extern
#endif

Global void redled_buzzer_cycle(void);
Global void rgb_led_color(void);
Global void blue_led_onoff(void);

#endif /* LED_BUZZER_LED_BUZZER_H_ */
