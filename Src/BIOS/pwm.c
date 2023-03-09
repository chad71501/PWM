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
    DDRB |= (1 << Steppin) ;
    DDRD |= (1 << Dirpin);
    TCCR2 |= (1 << WGM21) | (1 << WGM20) | (1 << COM21) | (1 << CS22);    // mode select fast pwm & Prescaler 64
    OCR2 = 255/ 2;
    TIMSK |= (1 << TOIE2) | (1 << OCIE2);

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

uint16_t sin_sampling[360];  // sinusoidal simulation
#define freq 1    // frequency
#define Fs 360  //Sampling rate
#define shift_voltage 1    // -1~1 shift 1~2
#define narrow_down 2      // sine wave 0~1 voltage
void sintable() {
    int sample = 0;
    float tmp = 0;
    for (sample = 0; sample < 360; sample++) {
        tmp = ((sin((((2 * M_PI) * freq * sample) / Fs))) + shift_voltage) / narrow_down;
        sin_sampling[sample] = tmp * 1023;
        //printf("%d\n",sin_sampling[sample]);
    }
}

void spwm_init() {
    // PWM set Fast PWM Mode
    TCCR1A |=  (1 << WGM11)|(1 << COM1A1)|(1 << COM1B1);   //COMnx1  需要設置為 Clear OCnA/OCnB/OCnC on compare match
    TCCR1B |= (1 << WGM12) |(1 << WGM13) | (1 << CS12);
    TIMSK |= (1 << TOIE1);
    ICR1 = 1024;

    // Set output pins as output
    DDRB |= (1 << PB5) | (1 << PB6);
    DDRE |= (1 << PE3);
}