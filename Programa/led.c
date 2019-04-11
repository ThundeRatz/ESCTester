/**
 * @file    led.c
 * @brief   ThundeRatz's ESC_Tester Project Firmware.
 *
 * @author Gustavo Hama <gustavo.hama@thunderatz.org>
 * @author Daniel Nery <daniel.nery@thunderatz.org>
 *
 * @date 04/2018
 */

#include <avr/io.h>

#include "led.h"

/*****************************************
 * Public Functions Bodies Definitions
 *****************************************/

void led_init(void) {
    LED_DDR |= (1 << LED_PINX);
}

void led_off(void) {
    LED_PORT &= ~(1 << LED_PINX);
}

void led_on(void) {
    LED_PORT |= (1 << LED_PINX);
}
