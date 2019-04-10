/*!
 * @file    main.c
 * @brief   ThundeRatz's ESC_Tester Project Firmware.
 *
 * @author  ThundeRatz Robotics Team - POLI-USP: http://thunderatz.org/
 *          Support email: contato@thunderatz.org
 *          Hama
 *
 * @date    11 March 2019
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

#include "adc.h"
#include "button.h"
#include "buzzer.h"
#include "display.h"
#include "led.h"
#include "ppm.h"
#include "timer.h"

#define BEEPS 3
#define BUTTON_TIME 15000

typedef enum state {
    INIT,
    CHOOSE,
    WAIT_BUTTON,
    PPM,
} state_t;

state_t current_state = INIT;

int main() {
    uint8_t adc = 0;
    mode_t mode = NO_MODE;
    uint16_t atual = PPM_MIN;
    uint16_t atual_rev = PPM_MID;
    bool calibrado = false;

    for (;;) {
        switch (current_state) {
            case INIT: {
                //Inicializa os pinos
                display_init();
                buzzer_init();
                adc_init();
                led_init();
                ppm_init();
                current_state = CHOOSE;

                break;
            }

            case CHOOSE: {
                adc = get_adc();
                display(adc);
                led_on();

                if (button() == 0) {    //Ao apertar o botao
                    timer_deinit();
                    pause_timer();
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
                    //Calibra apenas uma vez
                    if (calibrado == false) {
                        calibrate(mode);
                        calibrado = true;
                    }

                    led_on();
                    current_state = PPM;

                    reset_timer();
                    timer_deinit();

                    //Configura a ppm em 50Hz
                    pwm_init(TIM_PPM_PERIOD);
                } else if (button() != 0) {
                    mode = (mode % 5) + 1; //Modos de 1 a 5
                    display(mode);
                    _delay_ms(500);

                    current_state = CHOOSE;
                    timer_deinit();
                }
                break;
            }

            case PPM: {
                if ((mode == VAR_UNI) | (mode == FIXO_UNI)){    //Modos unidirecionais
                    atual = ppm(adc, mode, atual);
                }else { //Modos bidirecionais
                    atual_rev = ppm(adc, mode, atual_rev);
                }

                if (button() == 0) { //Ao apertar o botao, ele volta ao modo de seleção
                    current_state = CHOOSE;
                    timer_deinit();
                }

                break;
            }
        }
    }
}
