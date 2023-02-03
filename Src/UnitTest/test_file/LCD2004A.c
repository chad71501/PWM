/**
 * @file LCD2004A.c
 * @author Chad_Guo (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-06-11
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include "stdio.h"
#include <avr/io.h>

#define RS_on 0x01
#define RS_off 0x00
#define E_on 0x20
#define E_off 0x20

int main() {
    C4M_STDIO_init();  
    _delay_ms(1000);

    DDRD = 0XFF;
    PORTD = 0x30;
    _delay_ms(200);
    PORTD = 0x30;
    _delay_ms(200);
    PORTD = 0x30;

    PORTD = 0x20;
    _delay_ms(200);

    PORTD = 0x20;  // function set
    PORTD = 0x80;
    _delay_ms(200);
    PORTD = 0x00;  // display off
    PORTD = 0x80;
    _delay_ms(200);
    PORTD = 0x00;  // display clear
    PORTD = 0x10;
    _delay_ms(200);
    while (1) {
        PORTD = 0x00;  // display clear
        PORTD = 0x30;
    }
}
