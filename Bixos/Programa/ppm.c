/**
 * @file    ppm.h
 * @brief   ThundeRatz's ESC_Tester Project Firmware.
 *
 * @author Gustavo Hama <gustavo.hama@thunderatz.org>
 * @author Daniel Nery <daniel.nery@thunderatz.org>
 *
 * @date 04/2018
 */

#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>

#include "led.h"
#include "ppm.h"
#include "timer.h"

#define PPM_REG OCR1B
#define PPM_CALIB_INTERVAL_MS 3000
#define PPM_CALIB_POST_TIME_MS 6000

/*****************************************
 * Public Variables
 *****************************************/

extern uint16_t ppm_reset[] = {
    0,
    PPM_MIN,
    PPM_MIN,
    PPM_MID,
    PPM_MID,
    PPM_MID,
};

/*****************************************
 * Public Functions Bodies Definitions
 *****************************************/

void ppm_init() {

}

void calibrate(ppm_mode_t mode) {

}

void ppm(uint8_t adc, ppm_mode_t mode) {
    switch (mode) {
        case NO_MODE: {

            break;
        }

        case VAR_UNI: {  // variavel, unidirecional

            break;
        }

        case FIXO_UNI: {  // fixo, unidirecional


            break;
        }
    }

    _delay_ms(15);
}
