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

/**
 * @brief Free running timer.
 *
 * @note timer should be deinitialized before using
 *       these macros.
 */
#define get_timer() (TCNT1)
#define start_timer() (TCCR1B = (1 << CS12))
#define pause_timer() (TCCR1B = 0)
#define reset_timer() (TCNT1 = 0)

/*****************************************
 * Public Function Prototypes
 *****************************************/

/**
 * @brief Clears timers registers.
 *
 * @note TCNT1 is set to 0
 * @note PPM and Buzzer PWM settings are erased.
 */
void timer_deinit(void);

#endif  // __TIMER_H__
