/**
 * @file    button.h
 * @brief   ThundeRatz's ESC_Tester Project Firmware.
 *
 * @author Gustavo Hama <gustavo.hama@thunderatz.org>
 * @author Daniel Nery <daniel.nery@thunderatz.org>
 *
 * @date 04/2018
 */

#if !defined(__BUTTON_H__)
#define __BUTTON_H__

#include <stdbool.h>

/*****************************************
 * Public Constant Definitions
 *****************************************/

#define BUTTON_DDR (DDRD)
#define BUTTON_PORT (PORTD)
#define BUTTON_PIN (PIND)
#define BUTTON_PINX (PD2)

/*****************************************
 * Public Function Prototypes
 *****************************************/

/**
 * @brief Gets button reading.
 *
 * @return Button value
 * @retval true pressed
 * @retval false released
 */
bool button_pressed(void);

#endif  // __BUTTON_H__
