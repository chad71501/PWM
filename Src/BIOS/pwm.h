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

#include <avr/interrupt.h>
#include <avr/io.h>
#include <math.h>
#include <stdio.h>
/**
 * @brief  use A4899 drive control motor
 */
#define Steppin PB7    // DDRB OCR2 footpin
#define Dirpin PD7     // DDRE Direction footpin
#define HIGH 1
#define LOW 0
#define rotate_cw PORTD |= (HIGH << Dirpin)
#define rotate_acw PORTD ^= (HIGH << Dirpin)

void pwm_A4988_init();
/**
 * @brief  two pwm is phase diff 90 phase , use drive drv8847
 */

void pwm_phase_init(void);

void sintable();
void spwm_init();

#endif