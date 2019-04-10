/*!
 * @file    adc.h
 * @brief   ThundeRatz's ESC_Tester Project Firmware.
 *
 * @author  ThundeRatz Robotics Team - POLI-USP: http://thunderatz.org/
 *          Support email: contato@thunderatz.org
 *          Hama
 *
 * @date    11 March 2019
 */

#if !defined(__ADC_H__)
#define __ADC_H__

#include <stdint.h>

void adc_init();
uint8_t get_adc();

#endif // __ADC_H__
