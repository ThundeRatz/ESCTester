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


    for (;;) {
        switch (current_state) {
            case INIT: {
                //Inicializa os pinos
                display_init();
                buzzer_init();
                adc_init();
                led_init();

                current_state = CHOOSE;

                break;
            }

            case CHOOSE: {
                adc = get_adc();
                display(adc);
                led_on();

                if (button() == 0) {
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

                    calibrate(mode);

                    led_on();
                    current_state = PPM;

                    pwm_init(TIM_PPM_PERIOD);

                    reset_timer();
                    timer_deinit();

                    pwm_init(TIM_PPM_PERIOD);
                } else if (button() != 0) {
                    mode = (mode % 5) + 1;
                    display(mode);
                    _delay_ms(500);

                    current_state = CHOOSE;
                    timer_deinit();
                }
                break;
            }

            case PPM: {
                if ((mode == VAR_UNI) | (mode == FIXO_UNI)){
                    atual = ppm (adc, mode, atual);
                }
                else {
                    atual_rev = ppm (adc, mode, atual_rev);
                }

                if (button() == 0) {
                    current_state = CHOOSE;
                    timer_deinit();
                }

                break;
            }
        }
    }
}
//     // modes_t mode = NO_MODE;
//     unsigned int p;

//     while (1) {
//         p = get_adc();
//         display(p);
//         led_on();
//         // botao =;

//         if (button() == 0) {  // Ao apertar o botão
//             pause_timer();
//             reset_timer();
//             start_timer();

//             while (button() == 0) {  // Medir quanto tempo o botão foi apertado
//                 p = get_adc();
//                 display(p);

//                 if (get_timer() > 18000) {  // Segurou por muito tempo
//                     break;
//                 }
//             }

//             pause_timer();

//             if (get_timer() > 15000) {  // Se estiver segurando
//                 clear_display();
//                 buzzer_beep(3);

//                 ppmOut(p, mode);  // inicia o sinal de PPM
//                 pause_timer();
//             } else {
//                 if (mode == 5)
//                     mode = 1;
//                 else
//                     mode++;
//                 display(mode);
//                 _delay_ms(500);
//                 pause_timer();
//             }
//         }
//     }
// }

// void _ppm(uint8_t p, mode_t mode) {
//     static int atual = 1000;
//     static int atualRev = 1460;
//     static bool subida = true;

//     int ppmMax = 1000 + 10 * p;  // OCR1B vai ate 20000, entao a ppm deve ir de 1000 a 2000.
//     int ppmMaxRev = 1460 + 5 * p;
//     int ppmMinRev = 1460 - 5 * p;

//     if (subida) {
//         led_on();
//     } else {
//         led_off();
//     }

//     switch (mode) {
//         case VAR_UNI:  // variavel, unidirecional

//             if (atual >= ppmMax) {
//                 subida = 0;
//                 led_off();
//             }

//             else if (atual < 1000) {
//                 subida = 1;
//                 led_on();
//             }
//             if (subida)
//                 atual++;
//             else if (subida == 0)
//                 atual--;
//             PPM_REG = atual;
//             _delay_ms(15);
//             break;
//         case FIXO_UNI:  // fixo, unidirecional
//             if (atual < ppmMax)
//                 atual++;
//             PPM_REG = atual;
//             _delay_ms(15);
//             break;
//         case VAR_DOIS_BI:  // variavel, dois sentidos, bidirecional
//             if (atualRev == ppmMaxRev)
//                 subida = 0;
//             else if (atualRev == ppmMinRev)
//                 subida = 1;
//             if (subida)
//                 atualRev++;
//             else
//                 atualRev--;
//             PPM_REG = atualRev;
//             _delay_ms(15);
//             break;
//         case VAR_UM_BI:  // variavel, um sentido, bidirecional
//             if (atualRev == ppmMaxRev)
//                 subida = 0;
//             else if (atualRev == 1460)
//                 subida = 1;
//             if (subida)
//                 atualRev++;
//             else
//                 atualRev--;
//             PPM_REG = atualRev;
//             _delay_ms(15);
//             break;
//         case FIXO_BI:  // fixo, bidirecional
//             if (atualRev < ppmMaxRev)
//                 atualRev++;
//             PPM_REG = atualRev;
//             _delay_ms(15);
//             break;
//         default:
//             PPM_REG = 0;
//             break;
//     }
// }

// void ppmOut(int p, modes_t mode) {
//     pwm_init(TIM_PPM_PERIOD);
//     int ppmMax = 1000 + 10 * p;  // OCR1B vai ate 20000, entao a ppm deve ir de 1000 a 2000.
//     int ppmMaxRev = 1460 + 5 * p;
//     int ppmMinRev = 1460 - 5 * p;
//     int atual = 1000;
//     int atualRev = 1460;
//     bool subida = 1;

//     if ((mode == 1) | (mode == 2)) {  // Calibrar
//         ppm = 2000;
//         _delay_ms(3000);
//         ppm = 1000;
//         _delay_ms(3000);
//     }

//     if ((mode == 3) | (mode == 4) | (mode == 5)) {  // Calibrar para bidirecional
//         ppm = 2000;
//         _delay_ms(3000);
//         ppm = 1000;
//         _delay_ms(3000);
//         ppm = 1460;
//         _delay_ms(3000);
//     }

//     // Espera o fim da calibração
//     _delay_ms(6000);

//     while (botao == 1) {  // Até apertar o botão novamente
//         if (subida) {
//             led_on();
//         } else {
//             led_off();
//         }

//         botao = PIND & (1 << PD2);
//         switch (mode) {
//             case VAR_UNI:  // variavel, unidirecional

//                 if (atual >= ppmMax) {
//                     subida = 0;
//                     led_off();
//                 }

//                 else if (atual < 1000) {
//                     subida = 1;
//                     led_on();
//                 }
//                 if (subida)
//                     atual++;
//                 else if (subida == 0)
//                     atual--;
//                 ppm = atual;
//                 _delay_ms(15);
//                 break;
//             case FIXO_UNI:  // fixo, unidirecional
//                 if (atual < ppmMax)
//                     atual++;
//                 ppm = atual;
//                 _delay_ms(15);
//                 break;
//             case VAR_DOIS_BI:  // variavel, dois sentidos, bidirecional
//                 if (atualRev == ppmMaxRev)
//                     subida = 0;
//                 else if (atualRev == ppmMinRev)
//                     subida = 1;
//                 if (subida)
//                     atualRev++;
//                 else
//                     atualRev--;
//                 ppm = atualRev;
//                 _delay_ms(15);
//                 break;
//             case VAR_UM_BI:  // variavel, um sentido, bidirecional
//                 if (atualRev == ppmMaxRev)
//                     subida = 0;
//                 else if (atualRev == 1460)
//                     subida = 1;
//                 if (subida)
//                     atualRev++;
//                 else
//                     atualRev--;
//                 ppm = atualRev;
//                 _delay_ms(15);
//                 break;
//             case FIXO_BI:  // fixo, bidirecional
//                 if (atualRev < ppmMaxRev)
//                     atualRev++;
//                 ppm = atualRev;
//                 _delay_ms(15);
//                 break;
//             default:
//                 ppm = 0;
//                 break;
//         }
//     }
    // Desativa a PWM, para o timer ficar livre
//     timer_deinit();
// }
