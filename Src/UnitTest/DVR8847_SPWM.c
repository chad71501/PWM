/**
 * @file DVR8847_SPWM.c
 * @author Chad (U06117127@o365.mcut.edt.tw)
 * @brief
 * @version 0.1
 * @date 2023-03-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>

#include "pwm.h"
#include "uartdevice.h"

extern uint16_t sin_sampling[180];

int main() {
    uart_init();    // terminal picture
    sintable();
    spwm_init();
    OCR1A = sin_sampling[0];
    OCR1B = sin_sampling[90];
    printf("OCR1A %d\n OCR1B %d\n",OCR1A,OCR1B);
    sei();
    while (1) {
        //PORTE &= ~(HIGH << PIN3);
        //printf(" TCNT %x\n", TCNT1);
        if (TIFR & (1<<TOV1)) {
            printf("123\n");
            PORTE &= ~(HIGH << PIN3);
        }
    }
}

ISR(TIMER1_OVF_vect) {
    PORTE |= (HIGH << PIN3);
    //printf("123\n");
    static int count = 1;
    OCR1A = sin_sampling[count];
    OCR1B = sin_sampling[count + 90];
    if (count == 90) {
        count = 0;
    }
    count++;
    TCNT1 = 0;
}