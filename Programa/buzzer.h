/*!
 * @file    buzzer.h
 * @brief   ThundeRatz's ESC_Tester Project Firmware.
 *
 * @author  ThundeRatz Robotics Team - POLI-USP: http://thunderatz.org/
 *          Support email: contato@thunderatz.org
 *          Hama
 *
 * @date    11 March 2019
 */

#if !defined(__BUZZER_H__)
#define __BUZZER_H__

#define BUZZER_DDR DDRB
#define BUZZER_PIN PB1
#define BUZZER_PWM_REG OCR1A
#define BUZZER_BEEP_DELAY_MS 500

/**
 * @brief Initializes buzzer pin and PWM timer.
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
 * @param beeps Number of beeps.
 */
void buzzer_beep(uint8_t beeps);

#endif  // __BUZZER_H__
