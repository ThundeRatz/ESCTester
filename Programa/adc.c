/**
 * @file    adc.c
 * @brief   ThundeRatz's ESC_Tester Project Firmware.
 *
 * @author Gustavo Hama <gustavo.hama@thunderatz.org>
 * @author Daniel Nery <daniel.nery@thunderatz.org>
 *
 * @date 04/2018
 */

#include <avr/io.h>

#include "adc.h"

/*****************************************
 * Public Functions Bodies Definitions
 *****************************************/

void adc_init(void) {
    ADMUX |= (1 << REFS0);
    ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint8_t get_adc(void) {
    uint8_t measure;

    // Inicia a conversao
    ADCSRA |= (1 << ADSC);

    // Ate terminar a conversao
    while (ADCSRA & (1 << ADSC))
        ;

    measure = (100 * ADC) >> 10;  // Porcentagem 100 * ADC / 1024 (2 ^ 10)

    return measure;
}
