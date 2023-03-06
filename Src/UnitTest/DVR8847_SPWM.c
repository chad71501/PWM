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
int count_A = 0;
int count_B = 90;
int main() {
    uart_init();    // terminal picture
    sintable();
    spwm_init();
    OCR1A = sin_sampling[count_A];
    OCR1B = sin_sampling[count_B];
    //printf("OCR1A %d\n OCR1B %d\n",OCR1A,OCR1B);
    sei();
    while (1) {

        if (TIFR & (1<<TOV1)) {
        printf("OCR1A %d\tOCR1B %d\n",OCR1A,OCR1B);
        }
    }
}

ISR(TIMER1_OVF_vect) {
    OCR1A = sin_sampling[count_A];
    OCR1B = sin_sampling[count_B];
    if (count_A >= 180) {
        count_A = 0;
    }
    if (count_B >= 180) {
        count_B = 0;
    }
    count_A++;
    count_B++;
}