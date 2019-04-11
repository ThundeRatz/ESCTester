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
 * @retval    0 pressed
 * @retval != 0 released
 */
uint8_t button(void);

#endif  // __BUTTON_H__
