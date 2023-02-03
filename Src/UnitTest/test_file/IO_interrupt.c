#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>

#include "uartdevice.h"
int flag = 0;
unsigned char sreg;
int main() {
    C4M_STDIO_init();
    DDRD |= (1 << PD1) | (1 << PD2);
    // EICRA |= (1 << ISC01);    // Trigger on falling edge
    EIMSK |= (1 << INT0);    // Enable external interrupt INT0
    // PORTD |= (1 << PD1);
    sei();    // Enable global interrupts
    printf(" %d %d\n", EIMSK, EICRA);
    while (1) {
        PORTD |= (1 << PD1);
        PORTD |= (0 << PD2);
        if (flag == 1) {
            PORTD |= (1 << PD2);
        }
        //sei();
        printf("123\n");
    }
    printf("123\n");
    return 0;
}

ISR(INT0_vect) {
    
    //sreg = SREG;
    flag = 1;
    PORTD &= (~(1 << PD1));
    //reti();
    __asm__ __volatile__("ret" ::: "memory");
    return;
    //SREG =sreg;
}