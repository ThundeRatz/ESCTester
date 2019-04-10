/*!
 * @file    led.c
 * @brief   ThundeRatz's ESC_Tester Project Firmware.
 *
 * @author  ThundeRatz Robotics Team - POLI-USP: http://thunderatz.org/
 *          Support email: contato@thunderatz.org
 *          Hama
 *
 * @date    11 March 2019
 */

#include <avr/io.h>

#include "led.h"

void led_init(){
    DDRB |= (1 << PB3);
}

void led_off(){
    PORTB &= ~(1 << PB3);
}

void led_on(){
    PORTB |= (1 << PB3);
}
