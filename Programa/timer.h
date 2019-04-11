/**
 * @file    timer.h
 * @brief   ThundeRatz's ESC_Tester Project Firmware.
 *
 * @author Gustavo Hama <gustavo.hama@thunderatz.org>
 * @author Daniel Nery <daniel.nery@thunderatz.org>
 *
 * @date 04/2018
 */

#if !defined(__TIMER_H__)
#define __TIMER_H__

/*****************************************
 * Public Macros
 *****************************************/

#define get_timer() (TCNT1)
#define start_timer() (TCCR1B = (1 << CS12))
#define pause_timer() (TCCR1B = 0)
#define reset_timer() (TCNT1 = 0)

/*****************************************
 * Public Function Prototypes
 *****************************************/

/**
 * @brief Initializes timer as PWM
 */
void pwm_init(uint16_t);

/**
 * @brief Clears timers registers.
 */
void timer_deinit(void);

#endif  // __TIMER_H__
