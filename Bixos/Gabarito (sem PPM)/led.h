/**
 * @file    led.h
 * @brief   ThundeRatz's ESC_Tester Project Firmware.
 *
 * @author Gustavo Hama <gustavo.hama@thunderatz.org>
 * @author Daniel Nery <daniel.nery@thunderatz.org>
 *
 * @date 04/2018
 */

#if !defined(__LED_H__)
#define __LED_H__

/*****************************************
 * Public Constant Definitions
 *****************************************/

#define LED_DDR (DDRB)
#define LED_PORT (PORTB)
#define LED_PIN (PINB)
#define LED_PINX (PB3)

/*****************************************
 * Public Function Prototypes
 *****************************************/

/**
 * @brief Initialize led pin.
 */
void led_init(void);

/**
 * @brief Turns LED off.
 */
void led_off(void);

/**
 * @brief Turns LED on.
 */
void led_on(void);

#endif  // __LED_H__
