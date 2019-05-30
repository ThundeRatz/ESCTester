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

#define PPM_CALIB_INTERVAL_MS 3000
#define PPM_CALIB_POST_TIME_MS 6000

/*****************************************
 * Public Variables
 *****************************************/

uint16_t ppm_reset[] = {
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
    DDRB |= (1 << PB2);

    // Inicializacao da fast PWM, período regulado pelo ICR1
    TCCR1A = (1 << WGM11);
    TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS11);

    // Habilita
    TCCR1A |= (1 << COM1B1);

    ICR1 = TIM_PPM_PERIOD;  // Para a frequencia ser 50 Hz

}

void calibrate(ppm_mode_t mode) {
    ppm_init();

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
            }

            else if (PPM_REG <= PPM_MIN) {
                subida = true;
            }

            if (subida) {
                PPM_REG++;
            } else {
                PPM_REG--;
            }

            break;
        }

        case FIXO_UNI: {  // fixo, unidirecional
            if (PPM_REG < ppm_max_uni) {
                PPM_REG++;
            } else if (PPM_REG > ppm_max_uni){
                PPM_REG--;
            }

            break;
        }

        case VAR_DOIS_BI: {  // variavel, dois sentidos, bidirecional
            if (PPM_REG >= ppm_max_rev) {
                subida = false;
            } else if (PPM_REG <= ppm_min_rev) {
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
            if (PPM_REG >= ppm_max_rev) {
                subida = false;
            } else if (PPM_REG <= PPM_MID) {
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
            if (PPM_REG = ppm_max_rev) {
                PPM_REG++;
            } else if (PPM_REG > ppm_max_rev) {
                PPM_REG--;
            }

            break;
        }
    }

    _delay_ms(15);
}
