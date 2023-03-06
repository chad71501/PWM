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

void pwm_A4988_init() {
    DDRB |= (1 << Steppin) | (1 << Dirpin);
    TCCR2 |= (1 << WGM21) | (1 << WGM20) | (1 << COM21) | (1 << CS21) |
             (1 << CS20);    // mode select fast pwm & Prescaler 64
    TCNT2 = 255;
    OCR2 = TCNT2 / 2;
}

void pwm_phase_init() {
    TCCR1A |= (1 << COM1A1) | (1 << WGM11);
    TCCR1B |= (1 << WGM13) | (1 << CS11) | (1 << CS10);
    ICR1 = 0XFFF;

    TCCR3A |= (1 << COM3A1) | (1 << WGM31);
    TCCR3B |= (1 << WGM33) | (1 << CS31) | (1 << CS30);
    ICR3 = 0xFFF;

    // 90 degrees out of phase
    TCNT3 = TCNT1 + ICR1 / 2;
    OCR1A = ICR1 / 2;
    OCR3A = ICR3 / 2;

    // Set output pins as output
    DDRB |= (1 << PB5);
    DDRE |= (1 << PE3);
}

uint16_t sin_sampling[180];

void sintable() {
    int sample = 0;
    float tmp = 0;
    for (sample = 0; sample < 90; sample++) {
        tmp = ((sin((((2 * M_PI) * f * sample) / Fs))) + shift_voltage) / narrow_down;
        sin_sampling[sample] = tmp * 1023;
    }
}

void spwm_init() {
    // PWM set
    TCCR1A |= (1 << WGM10) | (1 << WGM11)|(1 << COM1A0);
    TCCR1B |= (1 << WGM12) | (1 << CS12);
    TIMSK |= (1 << TOIE1);
    ICR1 = 0xFF;

    // Set output pins as output
    DDRB |= (1 << PB5) | (1 << PB6);
    DDRE |= (1 << PE3);
}