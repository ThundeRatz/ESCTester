/*!
 * @file    buzzer.c
 * @brief   ThundeRatz's ESC_Tester Project Firmware.
 *
 * @author  ThundeRatz Robotics Team - POLI-USP: http://thunderatz.org/
 *          Support email: contato@thunderatz.org
 *          Hama
 *
 * @date    11 March 2019
 */

#include <avr/io.h>
#include <util/delay.h>

#include "buzzer.h"
#include "timer.h"

#define led_off() PORTB &= ~(1 << PB3)
#define led_on() PORTB |= (1 << PB3)

void buzzer_on(void) {
    BUZZER_PWM_REG = TIM_BUZZER_PERIOD;
}

void buzzer_off(void) {
    BUZZER_PWM_REG = 0;
}

void buzzer_init(void) {
    BUZZER_DDR |= (1 << BUZZER_PIN);
    buzzer_off();
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