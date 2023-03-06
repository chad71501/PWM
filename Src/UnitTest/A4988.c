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

#include "AS5X47.h"
#include "Overflow.h"
#include "RWFirFilter.h"
#include "SPI_set.h"
#include "pwm.h"
#include "uartdevice.h"
static float encoder_Angle;
int main() {
    uart_init();         // terminal picture
    pwm_A4988_init();    // about 675KHz
    // SPIDecoder(2);
    SPI_MasterInit();
    Overflower_lay(&Overflower_str);
    // RWFirFilter_LAY();
    // uint8_t countstep = 0;    // 200 step 等於 1圈
    // uint16_t lapcount = 0;    // 圈數
    sei();
    rotate_cw;
    while (1) {
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

        // Overflower_step(&Overflower_str);
        // printf("Encoder_Angle %f\n", encoder_Angle);
        // RWFirFilter_str.MTCountIn_p = Overflower_str.Count_p;
        // RWFirFilter_step(&RWFirFilter_str);
        // printf("RWFirFilter_str.MTCountOut_p %ld\n",*RWFirFilter_str.MTCountOut_p);

        // printf("Count  %d\n", *Overflower_str.Count_p);
        // printf("AccuOut  %ld\n", *Overflower_str.AccuOut_p);
    }
}
ISR(TIMER2_COMP_vect) {
    // encoder_Angle = readAngle();
    // printf("encoder_Angle %f\n",encoder_Angle);
}