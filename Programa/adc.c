/*!
 * @file    adc.c
 * @brief   ThundeRatz's ESC_Tester Project Firmware.
 *
 * @author  ThundeRatz Robotics Team - POLI-USP: http://thunderatz.org/
 *          Support email: contato@thunderatz.org
 *          Hama
 *
 * @date    11 March 2019
 */

#include <avr/io.h>

#include "adc.h"

// Inicializacao do ADC
void adc_init() {
    ADMUX |= (1 << REFS0);
    ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint8_t get_adc() {
    uint8_t measure;
    // Inicia a conversao
    ADCSRA |= (1 << ADSC);

    // Ate terminar a conversao
    while (ADCSRA & (1 << ADSC))
        ;

    measure = 100 * (float) ADC / 1023.0;  // Porcentagem

    return measure;
}
