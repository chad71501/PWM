/**
 * @file DVR8847_PWM.c
 * @author Chad (U06117127@o365.mcut.edt.tw)
 * @brief 
 * @version 0.1
 * @date 2023-03-01
 * @
 * @copyright Copyright (c) 2023
 * 
 */
#include <avr/io.h>
#include <stdio.h>
#include "pwm.h"
#include "uartdevice.h"


int main() {
    //uart_init();    // terminal picture
    pwm_phase_init();
    while (1) {
    }
}