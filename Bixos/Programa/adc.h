/**
 * @file    adc.h
 * @brief   ThundeRatz's ESC_Tester Project Firmware.
 *
 * @author Gustavo Hama <gustavo.hama@thunderatz.org>
 * @author Daniel Nery <daniel.nery@thunderatz.org>
 *
 * @date 04/2018
 */

#if !defined(__ADC_H__)
#define __ADC_H__

#include <stdint.h>

/*****************************************
 * Public Function Prototypes
 *****************************************/

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
