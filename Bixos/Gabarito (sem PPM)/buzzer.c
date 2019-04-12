/**
 * @file    buzzer.c
 * @brief   ThundeRatz's ESC_Tester Project Firmware.
 *
 * @author Gustavo Hama <gustavo.hama@thunderatz.org>
 * @author Daniel Nery <daniel.nery@thunderatz.org>
 *
 * @date 04/2018
 */

#include <avr/io.h>
#include <util/delay.h>

#include "buzzer.h"
#include "led.h"
#include "timer.h"

/*****************************************
 * Private Constant Definitions
 *****************************************/

#define TIM_BUZZER_PERIOD (2000)

/*****************************************
 * Public Functions Bodies Definitions
 *****************************************/

void buzzer_init(void) {
    BUZZER_DDR |= (1 << BUZZER_PIN);

    // Inicializacao da fast PWM, período regulado pelo ICR1
    TCCR1A = (1 << WGM11) | (1 << WGM10);
    TCCR1B = (1 << WGM12) | (1 << CS11);

    // Habilita
    TCCR1A |= (1 << COM1A1);

    // ICR1 = TIM_BUZZER_PERIOD;

    buzzer_off();
}

void buzzer_on(void) {
    BUZZER_PWM_REG = 1023;
}

void buzzer_off(void) {
    BUZZER_PWM_REG = 0;
}

void buzzer_beep(uint8_t beeps) {
    buzzer_init();

    while (beeps--) {
        led_on();
        buzzer_on();
        _delay_ms(BUZZER_BEEP_DELAY_MS);

        led_off();
        buzzer_off();
        _delay_ms(BUZZER_BEEP_DELAY_MS);
    }
}
