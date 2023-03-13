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
void Microstep(uint8_t Num) {
    DDRD |= (1 << MS1) | (1 << MS2) | (1 << MS3);
    switch (Num) {
        case 1:
            Num = 0;
            break;
        case 2:
            Num = 1;
            break;
        case 4:
            Num = 2;
            break;
        case 8:
            Num = 3;
            break;
        case 16:
            Num = 7;
            break;
        default:
            Num = 0;
            break;
    }
    PORTD |= Num & 0x0C;
}

void pwm_A4988_init() {
    DDRB |= (1 << Step_pin) | (1 << Dir_pin) | (1 << Enable_pin);
    TCCR2 |= (1 << WGM21) | (1 << WGM20) | (1 << COM21) |
             (1 << CS22);    // mode select fast pwm & Prescaler 64
    OCR2 = 255 / 2;
    TIMSK |= (1 << OCIE2);
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

void spwm_init() {
    // PWM set Fast PWM Mode
    TCCR1A |= (1 << WGM11) | (1 << COM1A1) |
              (1 << COM1B1);    // COMnx1  需要設置為 Clear OCnA/OCnB/OCnC on compare match
    TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS12);
    TIMSK |= (1 << TOIE1);
    ICR1 = 1024;

    // Set output pins as output
    DDRB |= (1 << PB5) | (1 << PB6);
    DDRE |= (1 << PE3);
}