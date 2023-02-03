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


#define Steppin PIN7    // OCR2 footpin
#define Dirpin PIN0     // Direction footpin
#define HIGH 1
#define LOW 0
#define rotate_cw  PORTB |= (HIGH << Dirpin)
#define rotate_acw  PORTB |= (LOW << Dirpin)

void pwm_init(void);


#endif