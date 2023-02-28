#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#include "uartdevice.h"

// Lookup table for sine wave values
const uint16_t sineTable[] = {0,    402,  788,  1145, 1452, 1699, 1879, 1986, 2019, 1978, 1864,
                              1681, 1436, 1137, 793,  413,  15,   383,  765,  1122, 1440, 1701,
                              1899, 2029, 2090, 2081, 2004, 1860, 1655, 1395, 1089, 745,  377};

volatile uint8_t pwmIndex = 0;

ISR(TIMER1_COMPA_vect) {
    OCR3A = sineTable[pwmIndex];
    pwmIndex = (pwmIndex + 1) % 32;
}

ISR(TIMER3_COMPA_vect) { OCR1A = sineTable[(pwmIndex + 8) % 32]; }

int main(void) {
    // Initialize Timer/Counter1 for PWM generation
    TCCR1A = (1 << COM1A1) | (1 << WGM11);
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS10);
    ICR1 = 399;

    // Initialize Timer/Counter3 for PWM generation with 90-degree phase shift
    TCCR3A = (1 << COM3A1) | (1 << WGM31);
    TCCR3B = (1 << WGM33) | (1 << WGM32) | (1 << CS30);
    ICR3 = 399;

    // Enable Timer/Counter1 and Timer/Counter3 interrupts
    TIMSK = (1 << OCIE1A);
    TIMSK = (1 << OCIE3A);
        DDRB |= (1 << PB5) | (1 << PB6);
        DDRE |= (1 << PE3);
    // Enable global interrupts
    sei();
    while (1) {
    }
}

// void pwma_init() {
//     // Set T/C 1 to PWM mode, with TOP value of 255
//     // TCCR1A |= (1 << COM1A0) | (1 << COM1B0) | (1 << COM1A1) | (1 << COM1B1);
//     TCCR1A |= (1 << COM1A1) | (1 << WGM11);
//     TCCR1B |= (1 << WGM13) | (1 << CS11);
//     ICR1 = 0xFF;

//     TCCR3A |= (1 << COM3A1) | (1 << WGM31);
//     TCCR3B |= (1 << WGM33) | (1 << CS30);
//     ICR3 = 0xFF;

//     // TCCR1A |= (1 << COM1A1) | (1 << WGM11);
//     // TCCR1B |= (1 << WGM13) | (1 << CS11);
//     // Set T/C 3 to PWM mode, with TOP value of 255
//     // TCCR3A |= (1 << COM3A1) | (1 << WGM31);
//     //  TCR3 = 255;
//     OCR1A = ICR1 / 2;
//     OCR3A = ICR3 / 2;
//     // Set output pins as output
//     DDRB |= (1 << PB5) | (1 << PB6);
//     DDRE |= (1 << PE3);
// }

// int main() {
//     uart_init();    // terminal picture
//     pwma_init();
//     printf("123");
//     // OCR1A = 64;
//     // OCR1B = 127;
//     while (1) {
//         // Set A PWM duty cycle to 50%

//         // printf("TOV1 %d\n ",(TIFR >>TOV1));

//         // if (((TIFR >> ICF1) & 0x01) == 1) {
//         //     // printf("ICF1 %d\t ",TIFR);

//         //     OCR1A = 127;
//         //     OCR1B = 64;
//         //     // printf("ICF1 %d\n ",TIFR);

//         //     TIFR &= ~(TIFR >> TOV1);
//         // }
//         // if (((TIFR >> TOV1) & 0x01) == 1) {
//         //     // printf("TOV1 %d\n ",(TIFR >>TOV1));
//         //     OCR1A = 64;
//         //     OCR1B = 127;
//         //     TIFR &= ~(TIFR >> ICF1);
//         //     // printf("TOV1 %d\n ",TIFR);
//         // }

//         // Wait for a short delay
//         // Set B PWM duty cycle to 50%
//         // OCR1A = 127;
//         // OCR3A = 127;

//         // Wait for a short delay
//     }
// }
