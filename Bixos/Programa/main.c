/**
 * @file    main.c
 * @brief   ThundeRatz's ESC_Tester Project Firmware.
 *
 * @author Gustavo Hama <gustavo.hama@thunderatz.org>
 * @author Daniel Nery <daniel.nery@thunderatz.org>
 *
 * @date 04/2018
 */

#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>

#include "adc.h"
#include "button.h"
#include "buzzer.h"
#include "display.h"
#include "led.h"
#include "ppm.h"
#include "timer.h"

/*****************************************
 * Private Constant Definitions
 *****************************************/

#define BEEPS (3)
#define BUTTON_TIME (15000)

/*****************************************
 * Private types
 *****************************************/

/**
 * @brief FSM states
 */
typedef enum state {
    INIT,        /**< Initial state */
    CHOOSE,      /**< Mode choosing state */
    WAIT_BUTTON, /**< Wait button release */
    PPM,         /**< Actual testing */
} state_t;

/*****************************************
 * Private Variables
 *****************************************/

static state_t current_state = INIT;

/*****************************************
 * Main Function
 *****************************************/

int main() {
    static uint8_t adc = 0;
    static ppm_mode_t mode = NO_MODE;
    static bool calibrated = false;

    for (;;) {
        switch (current_state) {
            case INIT: {
                // Inicializa os pinos
                display_init();
                adc_init();
                led_init();
                current_state = CHOOSE;

                break;
            }

            case CHOOSE: {
                adc = get_adc();
                display(adc);
                led_on();

                if (button_pressed()) {  // Ao apertar o botao
                    timer_deinit();
                    reset_timer();
                    start_timer();

                    current_state = WAIT_BUTTON;
                }

                break;
            }

            case WAIT_BUTTON: {
                adc = get_adc();
                display(adc);

                if (get_timer() > BUTTON_TIME) {
                    timer_deinit();
                    clear_display();
                    buzzer_beep(BEEPS);

                    led_off();
                    // Calibra apenas uma vez
                    if (calibrated == false) {
                        calibrate(mode);
                        calibrated = true;
                    }

                    led_on();
                    current_state = PPM;

                    reset_timer();

                    // Configura a ppm em 50Hz
                    ppm_init();
                } else if (!button_pressed()) {
                    mode = (mode % 5) + 1;  // Modos de 1 a 5
                    display(mode);
                    _delay_ms(500);

                    current_state = CHOOSE;
                    timer_deinit();
                }
                break;
            }

            case PPM: {
                ppm(adc, mode);

                if (button_pressed()) {  // Ao apertar o botao, ele volta ao modo de seleção
                    current_state = CHOOSE;
                    timer_deinit();
                }

                break;
            }
        }
    }
}
