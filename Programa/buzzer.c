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
 * Public Functions Bodies Definitions
 *****************************************/

void buzzer_init(void) {
    BUZZER_DDR |= (1 << BUZZER_PIN);
    buzzer_off();
}

void buzzer_on(void) {
    BUZZER_PWM_REG = TIM_BUZZER_PERIOD;
    TCCR1A &= ~(1 << COM1B1);
}

void buzzer_off(void) {
    BUZZER_PWM_REG = 0;
}

void buzzer_beep(uint8_t beeps) {
    pwm_init(TIM_BUZZER_PERIOD);

    while (beeps--) {
        led_on();
        buzzer_on();
        _delay_ms(BUZZER_BEEP_DELAY_MS);

        led_off();
        buzzer_off();
        _delay_ms(BUZZER_BEEP_DELAY_MS);
    }
}
