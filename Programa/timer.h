/*!
 * @file    timer.h
 * @brief   ThundeRatz's ESC_Tester Project Firmware.
 *
 * @author  ThundeRatz Robotics Team - POLI-USP: http://thunderatz.org/
 *          Support email: contato@thunderatz.org
 *          Hama
 *
 * @date    11 March 2019
 */

#if !defined(__TIMER_H__)
#define __TIMER_H__

#define TIM_PPM_PERIOD 16965
#define TIM_BUZZER_PERIOD 2000

#define get_timer() (TCNT1)
#define start_timer() (TCCR1B = (1 << CS12))
#define pause_timer() (TCCR1B = 0)
#define reset_timer() (TCNT1 = 0)

void pwm_init(uint16_t);
void timer_deinit(void);

#endif  // __TIMER_H__
