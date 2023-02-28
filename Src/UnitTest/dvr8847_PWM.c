#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "uartdevice.h"



void pwma_init() {
    // Set T/C 1 to PWM mode, with TOP value of 255
    // TCCR1A |= (1 << COM1A0) | (1 << COM1B0) | (1 << COM1A1) | (1 << COM1B1);
    TCCR1A |= (1 << COM1A1) | (1 << WGM11);
    TCCR1B |= (1 << WGM13) | (1 << CS10);
    ICR1 = 254;

    TCCR3A |= (1 << COM3A1) | (1 << WGM31);
    TCCR3B |= (1 << WGM33) | (1 << CS30);
    ICR3 = 254;

    // TCCR1A |= (1 << COM1A1) | (1 << WGM11);
    // TCCR1B |= (1 << WGM13) | (1 << CS11);
    // Set T/C 3 to PWM mode, with TOP value of 255
    // TCCR3A |= (1 << COM3A1) | (1 << WGM31);
    //  TCR3 = 255;
    TCNT3 = TCNT1 + 126;
    OCR1A = 127;
    OCR3A = 127;

    // Set output pins as output
    DDRB |= (1 << PB5) | (1 << PB6);
    DDRE |= (1 << PE3);
}

int main() {
    uart_init();    // terminal picture
    pwma_init();
    printf("123");
    // OCR1A = 64;
    // OCR1B = 127;
    while (1) {
    }
}