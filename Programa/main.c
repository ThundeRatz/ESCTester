/*!
 * @file	main.c
 * @brief	ThundeRatz's ESC_Tester Project Firmware.
 *
 * @author	ThundeRatz Robotics Team - POLI-USP: http://thunderatz.org/ \n
 *			Support email: contato@thunderatz.org
 *
 * @date	11 March 2019
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

typedef enum modes {
    NO_MODE,
    VAR_UNI,
    FIXO_UNI,
    VAR_DOIS_BI,
    VAR_UM_BI,
    FIXO_BI,
} modes_t; 

#define ONES_COUNT		25000	

 /* _____________a____b____c____d____e____f____g__
 * DISPLAY 1 | PD5  PD6  PD4  PD3  PD1  PB7  PB6
 * DISPLAY 2 | PB7  PB6  PD1  PD3  PD4  PD5  PD6
 */

// Pinos que não tem a ver com os LEDS ficam como estão, os outros zeram
#define D_RESET (PORTD & 0b00000100)
#define B_RESET (PORTB & 0b00111111)

#define A1 ((1 << PD5) << 8)
#define B1 ((1 << PD6) << 8)
#define C1 ((1 << PD4) << 8)
#define D1 ((1 << PD3) << 8)
#define E1 ((1 << PD1) << 8)
#define F1 (1 << PB7)
#define G1 (1 << PB6)

#define A2 (1 << PB7)
#define B2 (1 << PB6)
#define C2 ((1 << PD1) << 8)
#define D2 ((1 << PD3) << 8)
#define E2 ((1 << PD4) << 8)
#define F2 ((1 << PD5) << 8)
#define G2 ((1 << PD6) << 8)

#define SD1 (1 << PD0)
#define SD2 (1 << PD7)

#define timerCount		TCNT1
#define startTimer()	TCCR1B |= (1<<CS12)
#define pauseTimer()	TCCR1B = 0
#define resetTimer()	TCNT1 = 0

#define ppm OCR1A
#define botao PD2 

#define ledOff()	PORTB &= ~(1<<PB3)
#define ledOn()		PORTB |= (1<<PB3)
#define ledToggle()	PORTB ^= (1<<PB3)

void ppmOut(int, modes_t);
void sevenSegWrite(uint8_t display, uint8_t digit);
void display(unsigned int);
void buzzer(int);
int adcMeas(void);
void set_display(uint8_t , uint16_t );

int main(){
    //Pinos de saída
    DDRB |= (1<<PB1) | (1<<PB2) | (1<<PB3) | (1<<PB6) | (1<<PB7);
    DDRD |= ~(1<<PD2);

    //Inicializacao do ADC
    ADMUX |= (1<<REFS0);
    ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);

    //Inicializacao da PWM
    TCCR1A |= (1 << WGM11) | (1<<COM1A1) | (1<<COM1B1);
    TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1<<CS11);

    modes_t mode = NO_MODE;
    unsigned int p;

    while (1)
    {
        p = adcMeas();
        display(p);
        if (~botao)
        {   
        	resetTimer();
	        startTimer();
            while (~botao){}
            if (timerCount > ONES_COUNT) //Se estiver segurando
            {
                buzzer(166);
                _delay_ms(500);
                buzzer(209);
                _delay_ms(500);
                buzzer(249);
                _delay_ms(1000);
                ppmOut(p, mode);
            }
            else //Mudar o modo
            {
                if (mode == 5) 
                    mode = 1;
                else mode++;
                display(mode);
                while (timerCount < ONES_COUNT){}    
            }
        }
    }
}

void ppmOut(int p, modes_t mode){
    int ppmMax = 1000 + 1000 * p; // OC1A vai ate 20000, entao a ppm deve ir de 1000 a 2000.
    int ppmMaxRev = 1460 + 500 * p;
    int ppmMinRev = 1460 - 500 * p;
    int atual = 1000;
    int atualRev = 1460;
    bool subida = 1;
    
    ICR1 = 20000; //Para a frequencia ser 50 Hz

    while (botao)
    {    
        switch (mode)
        {
            case VAR_UNI: //variavel, unidirecional
                
                if (atual == ppmMax){
                    subida = 0;
                } 
                    
                else if (atual == 1000){
                    subida = 1;
                } 
                if (subida)
                    atual++;
                else atual--;
                ppm = atual;
                _delay_ms(50);
                break;
            case FIXO_UNI: // fixo, unidirecional
                if (atual < ppmMax)
                    atual++;
                ppm = atual;
                _delay_ms(50);
                break;
            case VAR_DOIS_BI: // variavel, dois sentidos, bidirecional
                if (atualRev == ppmMaxRev)
                    subida = 0;
                else if (atualRev == ppmMinRev)
                    subida = 1;
                if (subida) atualRev++;
                else atualRev--;
                ppm = atualRev;
                _delay_ms(50);
                break;
            case VAR_UM_BI: // variavel, um sentido, bidirecional
                if (atualRev == ppmMaxRev) subida = 0;
                else if (atualRev == 1460) subida = 1;
                if (subida) atualRev++;
                else atualRev--;
                ppm = atualRev;
                _delay_ms(50);
            case FIXO_BI: // fixo, bidirecional
                if (atualRev < ppmMaxRev) atual++;
                ppm = atualRev;
                _delay_ms(50);
            default:
                ppm = 0;
                break;
        }
    }
}

// pins = PORTD << 8 | PORTB
void set_display(uint8_t display, uint16_t pins) {
    PORTD = D_RESET | ((pins >> 8) & 0xFF) | display;
    PORTB = B_RESET | (pins & 0xFF);
}

void sevenSegWrite(uint8_t display, uint8_t digit){
	switch (digit) {
		case 0:
            if (display == 1) {
                set_display(SD1, A1 | B1 | C1 | D1 | E1 | F1);
            }
            else if (display == 2){
                set_display(SD2, A2 | B2 | C2 | D2 | E2 | F2);
            }
            break;
		case 1:
            if (display == 1){
                set_display(SD1, B1 | C1);
            }
            else if (display == 2){
                set_display(SD2, B2 | C2);            
            }
            break;
		case 2:
            if (display == 1) {
			    set_display(SD1, A1 | B1 | D1 | E1 | G1);
            } else if (display == 2) {
                set_display(SD2, A2 | B2 | D2 | E2 | G2);
			} 
            break;
		case 3:
            if (display == 1) {
			    set_display(SD1, A1 | B1 | C1 | D1 | G1);
            } else if (display == 2) {
                set_display(SD2, A2 | B2 | C2 | D2 | G2);
            } 
            break;
		case 4:
            if (display == 1) {
        	    set_display(SD1, B1 | C1 | F1 | G1);
            } else if (display == 2) {
                set_display(SD2, B2 | C2 | F2 | G2);
            } 
            break;
		case 5:
			if (display == 1) {
                set_display(SD1, A1 | C1 | D1 | F1 | G1);
            } else if (display == 2) {
                set_display(SD2, A2 | C2 | D2 | F2 | G2);
            } 
            break;
		case 6:
            if (display == 1) {
			    set_display(SD1, A1 | C1 | D1 | E1 | F1 | G1);
            } else if (display == 2) {
                set_display(SD2, A2 | C2 | D2 | E2 | F2 | G2);
            } 
            break;
		case 7:
            if (display == 1) {
			    set_display(SD1, A1 | B1 | C1);
            } else if (display == 2) {
                set_display(SD2, A2 | B2 | C2);
            } 
            break;
		case 8:
            if (display == 1) {
			    set_display(SD1, A1 | B1 | C1 | D1 | E1 | F1 | G1);
            } else if (display == 2) {
                set_display(SD2, A2 | B2 | C2 | D2 | E2 | F2 | G2);
            } 
            break;
		case 9:
			if (display == 1) {
                set_display(SD1, A1 | B1 | C1 | F1 | G1);
            } else if (display == 2) {
                set_display(SD2, A2 | B2 | C2 | F2 | G2);
            } 
            break;
		default:
		    set_display(SD1, 0);
	}
}

void display(unsigned int digit) {
	int u, d;
    
    //Dezena e unidade
    d = digit / 10;
    u = digit % 10;

    sevenSegWrite(1, u);
	_delay_ms(2);

	sevenSegWrite(2, d);
	_delay_ms(2);
}

int adcMeas(){
    double p;
    //Inicia a conversao
    ADCSRA |= (1 << ADSC);

    //Ate terminar a conversao
    while (ADCSRA & (1 << ADSC));
	
    p = (double) (100 * ADC) / 1024;

    return p;
}

void buzzer(int freq){
    ICR1 = (double) (1 / freq) * 1000000;
    OCR1B = ICR1 / 2;
}