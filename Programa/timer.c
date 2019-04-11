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

void timer_deinit() {
    reset_timer();
    TCCR1A = 0;
    TCCR1B = 0;
}
