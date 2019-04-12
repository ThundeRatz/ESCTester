/**
 * @file    buzzer.h
 * @brief   ThundeRatz's ESC_Tester Project Firmware.
 *
 * @author Gustavo Hama <gustavo.hama@thunderatz.org>
 * @author Daniel Nery <daniel.nery@thunderatz.org>
 *
 * @date 04/2018
 */

#if !defined(__BUZZER_H__)
#define __BUZZER_H__

/*****************************************
 * Public Constant Definitions
 *****************************************/

#define BUZZER_DDR (DDRB)
#define BUZZER_PIN (PB1)
#define BUZZER_PWM_REG (OCR1A)
#define BUZZER_BEEP_DELAY_MS (500)


/*****************************************
 * Public Function Prototypes
 *****************************************/

/**
 * @brief Initializes timer for PWM and buzzer pins.
 *
 * @note This function disables PPM.
 */
void buzzer_init(void);

/**
 * @brief Turns buzzer on.
 *
 * @note Buzzer needs PWM on its pin.
 */
void buzzer_on(void);

/**
 * @brief Turns buzzer off.
 */
void buzzer_off(void);

/**
 * @brief Beeps the buzzer.
 *
 * @note This function calls buzzer_init()
 *
 * @param beeps Number of beeps.
 */
void buzzer_beep(uint8_t beeps);

#endif  // __BUZZER_H__
