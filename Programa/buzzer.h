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

void buzzer_init(void);

void buzzer_on(void);
void buzzer_off(void);
void buzzer_beep(uint8_t beeps);

#endif  // __BUZZER_H__
