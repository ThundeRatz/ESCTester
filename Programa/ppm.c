/*!
 * @file    ppm.c
 * @brief   ThundeRatz's ESC_Tester Project Firmware.
 *
 * @author  ThundeRatz Robotics Team - POLI-USP: http://thunderatz.org/
 *          Support email: contato@thunderatz.org
 *          Hama
 *
 * @date    11 March 2019
 */

#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>

#include "ppm.h"
#include "led.h"

void ppm_init(){
    DDRB |= (1 << PB2);
}

void calibrate(mode_t mode){
    if ((mode == 1) | (mode == 2)) {  // Calibrar
        PPM_REG = PPM_MAX;
        _delay_ms(3000);
        PPM_REG = PPM_MIN;
        _delay_ms(3000);
    }

    if ((mode == 3) | (mode == 4) | (mode == 5)) {  // Calibrar para bidirecional
        PPM_REG = PPM_MAX;
        _delay_ms(3000);
        PPM_REG = PPM_MIN;
        _delay_ms(3000);
        PPM_REG = PPM_MID;
        _delay_ms(3000);
    }

    _delay_ms(6000);
}

uint16_t ppm(uint8_t adc, mode_t mode, uint16_t atual) {
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
        case VAR_UNI:  // variavel, unidirecional

            if (atual >= ppm_max_uni) {
                subida = 0;
                led_off();
            }

            else if (atual < PPM_MIN) {
                subida = 1;
                led_on();
            }
            if (subida)
                atual++;
            else if (subida == 0)
                atual--;
            PPM_REG = atual;
            _delay_ms(15);
            break;
        case FIXO_UNI:  // fixo, unidirecional
            if (atual < ppm_max_uni)
                atual++;
            PPM_REG = atual;
            _delay_ms(15);
            break;
        case VAR_DOIS_BI:  // variavel, dois sentidos, bidirecional
            if (atual == ppm_max_rev)
                subida = 0;
            else if (atual == ppm_min_rev)
                subida = 1;
            if (subida)
                atual++;
            else
                atual--;
            PPM_REG = atual;
            _delay_ms(15);
            break;
        case VAR_UM_BI:  // variavel, um sentido, bidirecional
            if (atual == ppm_max_rev)
                subida = 0;
            else if (atual == PPM_MID)
                subida = 1;
            if (subida)
                atual++;
            else
                atual--;
            PPM_REG = atual;
            _delay_ms(15);
            break;
        case FIXO_BI:  // fixo, bidirecional
            if (atual < ppm_max_rev)
                atual++;
            PPM_REG = atual;
            _delay_ms(15);
            break;
        default:
            PPM_REG = 0;
            break;
    }
    return atual;
}
