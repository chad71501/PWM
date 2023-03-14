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
#include <stdio.h>

/**
 * @brief  A4899 drive control motor
 */
#define HIGH 1
#define LOW 0
#define Step_pin PB7    // DDRB OCR2 footpin
#define Dir_pin PB6     // DDRE Direction footpin
#define Enable_pin PB5  // A4988 Enable pin
#define MS1 PD0    // Microstep pin
#define MS2 PD1    // Microstep pin
#define MS3 PD2    // Microstep pin
#define Enable PORTB &= ~(HIGH << Enable_pin)      // A4988 Enable
#define DisEnable PORTB |= (HIGH << Enable_pin)    // A4988 DisEnable
#define Rotate_CW PORTB |= (HIGH << Dir_pin)    // motor Forward/clockwise
#define Rotate_ACW PORTB &= ~(HIGH << Dir_pin)  // motor Reverse/counterclockwise
/*Microstep*/
void Microstep(uint8_t Num);
void pwm_A4988_init();


/**
 * @brief  DVR8847 drive control motor
 * @file PWM.c is stable with a duty cycle of 50%, and there are two PWM signals with a phase
 * difference of 25% in their duty cycles
 *
 * @file SPWM.c is a program that simulates a sinusoidal wave using PWM modulation. It includes two
 * PWM signals with a 90-degree phase difference in their duty cycles
 */

/*DVR8847_PWM.c*/
void pwm_phase_init(void);

/*DVR8847_SPWM.c*/
void spwm_init();

#endif