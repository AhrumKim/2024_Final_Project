/*
 * SUB.c
 *
 *  Created on: 2024. 11. 3.
 *      Author: 최종윤
 */

#include "Header_USER.h"

void check_temperature_and_send_warning(void) {

    // DHT11에서 온도 읽기

        if (temperature > 30) {
            out_UART_SUB(0);  // "EH" 송신
        }
    }


