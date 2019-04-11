/**
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

/**
 * @brief Initializes ADC registers.
 * 
 * @note Uses AVCC as reference and 128 prescaler.
 */
void adc_init(void);

/**
 * @brief Gets ADC value.
 * 
 * @return ADC value.
 * @retval 0-99 percentage of max ADC value (1023).
 */
uint8_t get_adc(void);

#endif  // __ADC_H__
