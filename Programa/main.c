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
#include "buzzer.h"
#include "display.h"
#include "timer.h"

#define ONES_COUNT 18000

#define ppm OCR1B  // PB2

#define led_off() PORTB &= ~(1 << PB3)
#define led_on() PORTB |= (1 << PB3)
#define led_toggle() PORTB ^= (1 << PB3)

#define button() (PIND & (1 << PD2))

typedef enum modes {
    NO_MODE,
    VAR_UNI,
    FIXO_UNI,
    VAR_DOIS_BI,
    VAR_UM_BI,
    FIXO_BI,
} modes_t;

void ppmOut(int, modes_t);
void _ppm(uint8_t p, modes_t mode);

static bool botao;
static unsigned mode = 0;

typedef enum state {
    INIT,
    CHOOSE,
    WAIT_BUTTON,
    INCREMENT_MODE,
    CALIBRATE,
    PPM,
} state_t;

state_t current_state = INIT;

int main() {
    uint8_t adc = 0;

    for (;;) {
        switch (current_state) {
            case INIT: {
                // Pinos de saída
                DDRB |= (1 << PB2) | (1 << PB3);

                display_init();
                buzzer_init();
                adc_init();

                DDRD &= ~(1 << PD2);

                current_state = CHOOSE;

                break;
            }

            case CHOOSE: {
                adc = get_adc();
                display(adc);
                led_on();

                if (button() == 0) {
                    // timer_deinit();
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

                if (get_timer() > 15000) {
                    timer_deinit();
                    clear_display();
                    buzzer_beep(3);

                    current_state = CALIBRATE;

                    reset_timer();
                    timer_deinit();

                    timer_init(TIM_PPM_PERIOD);
                } else if (button() != 0) {
                    current_state = INCREMENT_MODE;
                    reset_timer();
                    timer_deinit();
                }

                break;
            }

            case INCREMENT_MODE: {
                mode = (mode % 5) + 1;
                display(mode);
                _delay_ms(500);

                current_state = CHOOSE;

                break;
            }

            case CALIBRATE: {
                led_off();

                if ((mode == 1) | (mode == 2)) {  // Calibrar
                    ppm = 2000;
                    _delay_ms(3000);
                    ppm = 1000;
                    _delay_ms(3000);
                }

                if ((mode == 3) | (mode == 4) | (mode == 5)) {  // Calibrar para bidirecional
                    ppm = 2000;
                    _delay_ms(3000);
                    ppm = 1000;
                    _delay_ms(3000);
                    ppm = 1460;
                    _delay_ms(3000);
                }

                _delay_ms(6000);
                led_on();
                current_state = CHOOSE;

                // timer_init(TIM_PPM_PERIOD);

                break;
            }

            case PPM: {
                _ppm(adc, mode);

                if (button() == 0) {
                    current_state = CHOOSE;
                    timer_deinit();
                }

                break;
            }
        }
    }

    // modes_t mode = NO_MODE;
    unsigned int p;

    while (1) {
        p = get_adc();
        display(p);
        led_on();
        // botao =;

        if (button() == 0) {  // Ao apertar o botão
            pause_timer();
            reset_timer();
            start_timer();

            while (button() == 0) {  // Medir quanto tempo o botão foi apertado
                p = get_adc();
                display(p);

                if (get_timer() > 18000) {  // Segurou por muito tempo
                    break;
                }
            }

            pause_timer();

            if (get_timer() > 15000) {  // Se estiver segurando
                clear_display();
                buzzer_beep(3);

                ppmOut(p, mode);  // inicia o sinal de PPM
                pause_timer();
            } else {
                if (mode == 5)
                    mode = 1;
                else
                    mode++;
                display(mode);
                _delay_ms(500);
                pause_timer();
            }
        }
    }
}

void _ppm(uint8_t p, modes_t mode) {
    static int atual = 1000;
    static int atualRev = 1460;
    static bool subida = true;

    int ppmMax = 1000 + 10 * p;  // OCR1B vai ate 20000, entao a ppm deve ir de 1000 a 2000.
    int ppmMaxRev = 1460 + 5 * p;
    int ppmMinRev = 1460 - 5 * p;

    if (subida) {
        led_on();
    } else {
        led_off();
    }

    switch (mode) {
        case VAR_UNI:  // variavel, unidirecional

            if (atual >= ppmMax) {
                subida = 0;
                led_off();
            }

            else if (atual < 1000) {
                subida = 1;
                led_on();
            }
            if (subida)
                atual++;
            else if (subida == 0)
                atual--;
            ppm = atual;
            _delay_ms(15);
            break;
        case FIXO_UNI:  // fixo, unidirecional
            if (atual < ppmMax)
                atual++;
            ppm = atual;
            _delay_ms(15);
            break;
        case VAR_DOIS_BI:  // variavel, dois sentidos, bidirecional
            if (atualRev == ppmMaxRev)
                subida = 0;
            else if (atualRev == ppmMinRev)
                subida = 1;
            if (subida)
                atualRev++;
            else
                atualRev--;
            ppm = atualRev;
            _delay_ms(15);
            break;
        case VAR_UM_BI:  // variavel, um sentido, bidirecional
            if (atualRev == ppmMaxRev)
                subida = 0;
            else if (atualRev == 1460)
                subida = 1;
            if (subida)
                atualRev++;
            else
                atualRev--;
            ppm = atualRev;
            _delay_ms(15);
            break;
        case FIXO_BI:  // fixo, bidirecional
            if (atualRev < ppmMaxRev)
                atualRev++;
            ppm = atualRev;
            _delay_ms(15);
            break;
        default:
            ppm = 0;
            break;
    }
}

void ppmOut(int p, modes_t mode) {
    timer_init(TIM_PPM_PERIOD);
    int ppmMax = 1000 + 10 * p;  // OCR1B vai ate 20000, entao a ppm deve ir de 1000 a 2000.
    int ppmMaxRev = 1460 + 5 * p;
    int ppmMinRev = 1460 - 5 * p;
    int atual = 1000;
    int atualRev = 1460;
    bool subida = 1;

    botao = PIND & (1 << PD2);
    // som = 0;

    if ((mode == 1) | (mode == 2)) {  // Calibrar
        ppm = 2000;
        _delay_ms(3000);
        ppm = 1000;
        _delay_ms(3000);
    }

    if ((mode == 3) | (mode == 4) | (mode == 5)) {  // Calibrar para bidirecional
        ppm = 2000;
        _delay_ms(3000);
        ppm = 1000;
        _delay_ms(3000);
        ppm = 1460;
        _delay_ms(3000);
    }

    // Espera o fim da calibração
    _delay_ms(6000);

    while (botao == 1) {  // Até apertar o botão novamente
        if (subida) {
            led_on();
        } else {
            led_off();
        }

        botao = PIND & (1 << PD2);
        switch (mode) {
            case VAR_UNI:  // variavel, unidirecional

                if (atual >= ppmMax) {
                    subida = 0;
                    led_off();
                }

                else if (atual < 1000) {
                    subida = 1;
                    led_on();
                }
                if (subida)
                    atual++;
                else if (subida == 0)
                    atual--;
                ppm = atual;
                _delay_ms(15);
                break;
            case FIXO_UNI:  // fixo, unidirecional
                if (atual < ppmMax)
                    atual++;
                ppm = atual;
                _delay_ms(15);
                break;
            case VAR_DOIS_BI:  // variavel, dois sentidos, bidirecional
                if (atualRev == ppmMaxRev)
                    subida = 0;
                else if (atualRev == ppmMinRev)
                    subida = 1;
                if (subida)
                    atualRev++;
                else
                    atualRev--;
                ppm = atualRev;
                _delay_ms(15);
                break;
            case VAR_UM_BI:  // variavel, um sentido, bidirecional
                if (atualRev == ppmMaxRev)
                    subida = 0;
                else if (atualRev == 1460)
                    subida = 1;
                if (subida)
                    atualRev++;
                else
                    atualRev--;
                ppm = atualRev;
                _delay_ms(15);
                break;
            case FIXO_BI:  // fixo, bidirecional
                if (atualRev < ppmMaxRev)
                    atualRev++;
                ppm = atualRev;
                _delay_ms(15);
                break;
            default:
                ppm = 0;
                break;
        }
    }
    // Desativa a PWM, para o timer ficar livre
    timer_deinit();
}
