/**
 * @file    display.h
 * @brief   ThundeRatz's ESC_Tester Project Firmware.
 *
 * @author Gustavo Hama <gustavo.hama@thunderatz.org>
 * @author Daniel Nery <daniel.nery@thunderatz.org>
 *
 * @date 04/2018
 */

#if !defined(__DISPLAY_H__)
#define __DISPLAY_H__

#include <stdint.h>

/*****************************************
 * Public Function Prototypes
 *****************************************/

/**
 * @brief Initializes display pins.
 */
void display_init(void);

/**
 * @brief Display dozen at display 2 and units at display 1.
 *
 * @note Time between show display 1 and display 2
 *
 * @param digit number to be displayed
 */
void display(uint8_t digit);

/**
 * @brief Disable both displays.
 */
void clear_display(void);

#endif  // __DISPLAY_H__
