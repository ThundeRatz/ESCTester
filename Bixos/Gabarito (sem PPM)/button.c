/**
 * @file    button.c
 * @brief   ThundeRatz's ESC_Tester Project Firmware.
 *
 * @author Gustavo Hama <gustavo.hama@thunderatz.org>
 * @author Daniel Nery <daniel.nery@thunderatz.org>
 *
 * @date 04/2018
 */

#include <avr/io.h>

#include "button.h"

/*****************************************
 * Public Functions Bodies Definitions
 *****************************************/

bool button_pressed(void) {
    return (BUTTON_PIN & (1 << BUTTON_PINX)) == 0;
}
