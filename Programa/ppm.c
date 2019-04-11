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
 * Public Functions Bodies Definitions
 *****************************************/

void ppm_init() {
    DDRB |= (1 << PB2);
    TCCR1A &= ~(1 << COM1A1);
    PPM_REG = 0;
}

void calibrate(ppm_mode_t mode) {
    timer_deinit();
    pwm_init(TIM_PPM_PERIOD);

    if ((mode == VAR_UNI) | (mode == FIXO_UNI)) {  // Calibrar
        PPM_REG = PPM_MAX;
        _delay_ms(PPM_CALIB_INTERVAL_MS);
        PPM_REG = PPM_MIN;
        _delay_ms(PPM_CALIB_INTERVAL_MS);
    }

    if ((mode == VAR_DOIS_BI) | (mode == VAR_UM_BI) | (mode == FIXO_BI)) {  // Calibrar para bidirecional
        PPM_REG = PPM_MAX;
        _delay_ms(PPM_CALIB_INTERVAL_MS);
        PPM_REG = PPM_MIN;
        _delay_ms(PPM_CALIB_INTERVAL_MS);
        PPM_REG = PPM_MID;
        _delay_ms(PPM_CALIB_INTERVAL_MS);
    }
    // Espera a calibracao da ESC
    _delay_ms(PPM_CALIB_POST_TIME_MS);
}

void ppm(uint8_t adc, ppm_mode_t mode) {
    static bool subida = true;

    uint16_t ppm_max_uni = PPM_MIN + 10 * adc;  // OCR1B vai ate 20000, entao a ppm deve ir de 1000 a 2000.
    uint16_t ppm_max_rev = PPM_MID + 5 * adc;
    uint16_t ppm_min_rev = PPM_MID - 5 * adc;

    if (subida) {
        led_on();
    } else {
        led_off();
    }

    switch (mode) {
        case NO_MODE: {
            PPM_REG = 0;
            break;
        }

        case VAR_UNI: {  // variavel, unidirecional
            if (PPM_REG >= ppm_max_uni) {
                subida = false;
                led_off();
            }

            else if (PPM_REG < PPM_MIN) {
                subida = true;
                led_on();
            }

            if (subida) {
                PPM_REG++;
            } else if (subida == 0) {
                PPM_REG--;
            }

            break;
        }

        case FIXO_UNI: {  // fixo, unidirecional
            if (PPM_REG < ppm_max_uni) {
                PPM_REG++;
            }

            break;
        }

        case VAR_DOIS_BI: {  // variavel, dois sentidos, bidirecional
            if (PPM_REG == ppm_max_rev) {
                subida = false;
            } else if (PPM_REG == ppm_min_rev) {
                subida = true;
            }

            if (subida) {
                PPM_REG++;
            } else {
                PPM_REG--;
            }

            break;
        }

        case VAR_UM_BI: {  // variavel, um sentido, bidirecional
            if (PPM_REG == ppm_max_rev) {
                subida = false;
            } else if (PPM_REG == PPM_MID) {
                subida = true;
            }

            if (subida) {
                PPM_REG++;
            } else {
                PPM_REG--;
            }

            break;
        }

        case FIXO_BI: {  // fixo, bidirecional
            if (PPM_REG < ppm_max_rev) {
                PPM_REG++;
            }

            break;
        }
    }

    _delay_ms(15);
}
