/**
 * @file    timer.c
 * @brief   ThundeRatz's ESC_Tester Project Firmware.
 *
 * @author Gustavo Hama <gustavo.hama@thunderatz.org>
 * @author Daniel Nery <daniel.nery@thunderatz.org>
 *
 * @date 04/2018
 */

#include <avr/io.h>

#include "timer.h"

/*****************************************
 * Public Functions Bodies Definitions
 *****************************************/

void pwm_init(uint16_t period) {
    // Inicializacao da fast PWM, período regulado pelo ICR1
    TCCR1A |= (1 << WGM11);
    TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS11);

    // Habilita
    TCCR1A |= (1 << COM1B1);
    TCCR1A |= (1 << COM1A1);

    ICR1 = period;  // Para a frequencia ser 50 Hz
}

void timer_deinit() {
    reset_timer();
    TCCR1A = 0;
    TCCR1B = 0;
}
