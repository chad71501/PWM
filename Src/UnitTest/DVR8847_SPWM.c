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
#include "Sintable.h"

extern uint16_t sin_sampling[360];
uint16_t count_A = 0;
uint16_t count_B = 90;
int main() {
    uart_init();    // terminal picture
    sintable();
    spwm_init();
    OCR1A = sin_sampling[count_A];
    OCR1B = sin_sampling[count_B];
    //printf("OCR1A %d\n OCR1B %d\n",OCR1A,OCR1B);
    sei();
    while (1) {

    }
}

ISR(TIMER1_OVF_vect) {
    OCR1A = sin_sampling[count_A];
    OCR1B = sin_sampling[count_B];
    if (count_A >= 360) {
        count_A = 0;
    }
    if (count_B >= 360) {
        count_B = 0;
    }
    count_A++;
    count_B++;
}