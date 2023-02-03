/**
 * @file PWM.c
 * @author “ychad (U06117127@o365.mcut.edu.tw)
 * @brief
 * @version 0.1
 * @date 2022-12-26
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "pwm.h"
#include <avr/io.h>
#include <stdio.h>


void pwm_init() {
    DDRB |= (1 << Steppin) | (1 << Dirpin);
    TCCR2 |= (1 << WGM21) | (1 << WGM20) | (1 << COM21) | (1 << CS21) |
             (1 << CS20);    // mode select fast pwm & Prescaler 64
    TCNT2 = 255;
    OCR2 = TCNT2 / 2;
}