/**
 * @file    button.c
 * @brief   ThundeRatz's ESC_Tester Project Firmware.
 *
 * @author  ThundeRatz Robotics Team - POLI-USP: http://thunderatz.org/
 *          Support email: contato@thunderatz.org
 *          Hama
 *
 * @date    11 March 2019
 */

#include <avr/io.h>

#include "button.h"

uint8_t button(void) {
    //Retorna a leitura do botao
    return PIND & (1 << PD2);
}
