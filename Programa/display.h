/*!
 * @file    display.h
 * @brief   ThundeRatz's ESC_Tester Project Firmware.
 *
 * @author  ThundeRatz Robotics Team - POLI-USP: http://thunderatz.org/
 *          Support email: contato@thunderatz.org
 *          Hama
 *
 * @date    11 March 2019
 */

#if !defined(__DISPLAY_H__)
#define __DISPLAY_H__

#include <stdint.h>


/**
 * @brief Initializes display pins.
 */
void display_init(void);

/**
 * @brief Display dozen at display 2 and units at display 1.
 * 
 * @param digit number to be displayed
 */
void display(uint8_t digit);
/**
 * @brief Disable both displays.
 */
void clear_display(void);

#endif  // __DISPLAY_H__
