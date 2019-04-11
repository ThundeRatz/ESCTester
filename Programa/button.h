/*!
 * @file    button.c
 * @brief   ThundeRatz's ESC_Tester Project Firmware.
 *
 * @author  ThundeRatz Robotics Team - POLI-USP: http://thunderatz.org/
 *          Support email: contato@thunderatz.org
 *          Hama
 *
 * @date    11 March 2019
 */

#if !defined(__BUTTON_H__)
#define __BUTTON_H__

/**
 * @brief Gets button reading.
 * 
 * @return Button value
 * @retval    0 pressed
 * @retval != 0 released
 */
uint8_t button(void);

#endif // __BUTTON_H__
