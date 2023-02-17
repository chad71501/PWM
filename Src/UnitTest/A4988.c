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

#include "SPI_set.h"
#include "Overflow.h"
#include "pwm.h"
#include "uartdevice.h"
#include "RWFirFilter.h"



int main() {
    uart_init();    // terminal picture
    pwm_init();     // about 675KHz
    SPIDecoder(2);
    SPI_MasterInit();
    Overflower_lay(&Overflower_str);
    RWFirFilter_LAY();
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

        
        Overflower_step(&Overflower_str);
        RWFirFilter_str.MTCountIn_p = Overflower_str.Count_p;
        RWFirFilter_step(&RWFirFilter_str);
        //printf("RWFirFilter_str.MTCountOut_p %ld\n",*RWFirFilter_str.MTCountOut_p);

        // printf("Count  %d\n", *Overflower_str.Count_p);
        // printf("AccuOut  %ld\n", *Overflower_str.AccuOut_p);

    }
}