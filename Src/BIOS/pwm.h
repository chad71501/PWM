/**
 * @file PWM.h
 * @author “ychad (U06117127@o365.mcut.edu.tw)
 * @brief
 * @version 0.1
 * @date 2022-12-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef PWM_H
#define PWM_H

#include <avr/io.h>
#include <stdio.h>
#include <math.h>
#include <avr/interrupt.h>

#define Steppin PIN7    // DDRB OCR2 footpin
#define Dirpin PIN0     // DDRB Direction footpin
#define HIGH 1
#define LOW 0
#define rotate_cw  PORTB |= (HIGH << Dirpin)
#define rotate_acw  PORTB |= (LOW << Dirpin)

void pwm_A4988_init();
void pwm_phase_init(void);

#define f 1    // frequency
#define Fs 90
#define shift_voltage 1    // -1~1 shift 1~2
#define narrow_down 2      // sine wave 0~1 voltage

void sintable();
void spwm_init();

#endif