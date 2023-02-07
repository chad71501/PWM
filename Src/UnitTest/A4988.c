/**
 * @file A4988.c
 * @author “ychad (U06117127@o365.mcut.edu.tw)
 * @brief  Use pwm drive motor
 * @version 0.1
 * @date 2023-02-01
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

#include "Src/BIOS/SPI_set.h"
#include "Src/BIOS/pwm.h"
#include "Src/BIOS/uartdevice.h"
#include "Src/Motor_control/Overflow.h"



int main() {
    uart_init();    // terminal picture
    pwm_init();     // about 675KHz
    SPI_MasterInit();
    Overflower_lay(&Overflower_str);
    uint8_t countstep = 0;                // 200 step 等於 1圈
    uint16_t lapcount = 0;                // 圈數
    
    
    while (1) {
        rotate_cw;
        // if (countstep == 200) {
        //     countstep = 0;
        //     lapcount++;
        // }
        // if (TCNT2 == 254) {
        //     countstep++;
        // }
        // if (lapcount == 100) {
        //     TCCR2 &= ~(1 << CS20);
        //     DDRB |= (1 << Steppin) | (1 << Dirpin);
        // }


        //_delay_us(10);
        // SS_LOW;    // SPI_set.h define

        // = SPI_transmit_byte(0);    // send Command  MSB 8bit
        // = SPI_transmit_byte(0);    // send Command LSB 8bit
        // SS_HIGH;


        Overflower_step(&Overflower_str);
        // printf("Count  %d\n", *Overflower_str.Count_p);
        // printf("AccuOut  %ld\n", *Overflower_str.AccuOut_p);

    }
}