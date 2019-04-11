/**
 * @file    ppm.h
 * @brief   ThundeRatz's ESC_Tester Project Firmware.
 *
 * @author Gustavo Hama <gustavo.hama@thunderatz.org>
 * @author Daniel Nery <daniel.nery@thunderatz.org>
 *
 * @date 04/2018
 */

#if !defined(__PPM_H__)
#define __PPM_H__

/*****************************************
 * Public Constant Definitions
 *****************************************/

#define PPM_REG OCR1B

#define PPM_MIN (1000)
#define PPM_MID (1460)
#define PPM_MAX (2000)

#define TIM_PPM_PERIOD (16965)

/*****************************************
 * Public Types Definitions
 *****************************************/

/**
 * @brief PPM modes
 */
typedef enum ppm_mode {
    NO_MODE,     /**< No mode */
    VAR_UNI,     /**< Variable unidirectional */
    FIXO_UNI,    /**< Fixed unidirectional */
    VAR_DOIS_BI, /**< Variable bidirectional */
    VAR_UM_BI,   /**< Fixed bidirectional */
    FIXO_BI,     /**< Fixed bidirectional */
} ppm_mode_t;

/*****************************************
 * Public Variables
 *****************************************/

extern uint16_t ppm_reset[];

/*****************************************
 * Public Function Prototypes
 *****************************************/

/**
 * @brief Initializes timer for PPM.
 *
 * @note This function disables buzzer PWM.
 */
void ppm_init(void);

/**
 * @brief Calibrates ESC.
 *
 * @param mode PPM mode.
 */
void calibrate(ppm_mode_t mode);

/**
 * @brief
 *
 * @param adc  ADC reading percentage.
 * @param mode PPM mode.
 */
void ppm(uint8_t adc, ppm_mode_t mode);

#endif  // __PPM_H__
