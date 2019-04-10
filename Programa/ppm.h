/*!
 * @file    ppm.h
 * @brief   ThundeRatz's ESC_Tester Project Firmware.
 *
 * @author  ThundeRatz Robotics Team - POLI-USP: http://thunderatz.org/
 *          Support email: contato@thunderatz.org
 *          Hama
 *
 * @date    11 March 2019
 */

#if !defined(__PPM_H__)
#define __PPM_H__

#define PPM_REG OCR1B  // PB2
#define PPM_MIN 1000
#define PPM_MID 1460
#define PPM_MAX 2000

typedef enum mode {
    NO_MODE,
    VAR_UNI,
    FIXO_UNI,
    VAR_DOIS_BI,
    VAR_UM_BI,
    FIXO_BI,
} mode_t;

void ppm_init(void);
void calibrate(mode_t);
uint16_t ppm(uint8_t adc, mode_t mode, uint16_t atual);

#endif // __PPM_H__
