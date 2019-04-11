/**
 * @file    display.c
 * @brief   ThundeRatz's ESC_Tester Project Firmware.
 *
 * @author Gustavo Hama <gustavo.hama@thunderatz.org>
 * @author Daniel Nery <daniel.nery@thunderatz.org>
 *
 * @date 04/2018
 */

#include <avr/io.h>
#include <util/delay.h>

#include "display.h"

/* _____________a____b____c____d____e____f____g__
 * DISPLAY 1 | PD5  PD6  PD4  PD3  PD1  PB7  PB6
 * DISPLAY 2 | PB7  PB6  PD1  PD3  PD4  PD5  PD6
 */

/*****************************************
 * Private Constant Definitions
 *****************************************/

// Pinos que não tem a ver com os LEDS ficam como estão, os outros zeram
#define D_RESET ((PORTD & 0b00000100) | 0b11111011)
#define B_RESET ((PORTB & 0b00111111) | 0b11000000)

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

/*****************************************
 * Private Function Prototypes
 *****************************************/

/**
 * @brief Shows a digit in one of the 7 segment displays
 *
 * @param display Which display to show digit
 *        Should be SD1 or SD2
 * @param digit   Digit to show (0 to 9)
 */
static void seven_seg_write(uint8_t display, uint8_t digit);

/**
 * @brief Like @ref seven_seg_write. Lower level.
 *
 * @note Doesn't need to be called outside seven_seg_write.
 */
static void set_display(uint8_t display, uint16_t pins);

/*****************************************
 * Public Functions Bodies Definitions
 *****************************************/

void display_init(void) {

}

void display(uint8_t digit) {

}

void clear_display(void) {

}

/*****************************************
 * Private Functions Bodies Definitions
 *****************************************/

// pins = PORTD << 8 | PORTB
void set_display(uint8_t display, uint16_t pins) {
    PORTD = D_RESET & ~(((pins >> 8) & 0xFF) | display);
    PORTB = B_RESET & ~(pins & 0xFF);
}

void seven_seg_write(uint8_t display, uint8_t digit) {
    switch (digit) {
        case 0: {
            if (display == 1) {
                set_display(SD1, A1 | B1 | C1 | D1 | E1 | F1);
            } else if (display == 2) {
                set_display(SD2, A2 | B2 | C2 | D2 | E2 | F2);
            }
            break;
        }

        case 1: {
            if (display == 1) {
                set_display(SD1, B1 | C1);
            } else if (display == 2) {
                set_display(SD2, B2 | C2);
            }
            break;
        }

        case 2: {
            if (display == 1) {
                set_display(SD1, A1 | B1 | D1 | E1 | G1);
            } else if (display == 2) {
                set_display(SD2, A2 | B2 | D2 | E2 | G2);
            }
            break;
        }

        case 3: {
            if (display == 1) {
                set_display(SD1, A1 | B1 | C1 | D1 | G1);
            } else if (display == 2) {
                set_display(SD2, A2 | B2 | C2 | D2 | G2);
            }
            break;
        }

        case 4: {
            if (display == 1) {
                set_display(SD1, B1 | C1 | F1 | G1);
            } else if (display == 2) {
                set_display(SD2, B2 | C2 | F2 | G2);
            }
            break;
        }

        case 5: {
            if (display == 1) {
                set_display(SD1, A1 | C1 | D1 | F1 | G1);
            } else if (display == 2) {
                set_display(SD2, A2 | C2 | D2 | F2 | G2);
            }
            break;
        }

        case 6: {
            if (display == 1) {
                set_display(SD1, A1 | C1 | D1 | E1 | F1 | G1);
            } else if (display == 2) {
                set_display(SD2, A2 | C2 | D2 | E2 | F2 | G2);
            }
            break;
        }

        case 7: {
            if (display == 1) {
                set_display(SD1, A1 | B1 | C1);
            } else if (display == 2) {
                set_display(SD2, A2 | B2 | C2);
            }
            break;
        }

        case 8: {
            if (display == 1) {
                set_display(SD1, A1 | B1 | C1 | D1 | E1 | F1 | G1);
            } else if (display == 2) {
                set_display(SD2, A2 | B2 | C2 | D2 | E2 | F2 | G2);
            }
            break;
        }

        case 9: {
            if (display == 1) {
                set_display(SD1, A1 | B1 | C1 | F1 | G1);
            } else if (display == 2) {
                set_display(SD2, A2 | B2 | C2 | F2 | G2);
            }
            break;
        }

        default: {
            set_display(SD1, 0);
            break;
        }
    }
}
