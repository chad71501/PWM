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
#include <util/delay.h>

#include "AS5X47.h"
#include "Overflow.h"
#include "RWFirFilter.h"
#include "SPI_set.h"
#include "Sintable.h"
#include "pwm.h"
#include "uartdevice.h"




int main() {
    sintable();
    uart_init();    // terminal picture
    SPI_MasterInit();
    // SPIDecoder(2);
    Overflower_lay(&Overflower_str);
    RWFirFilter_LAY();
    Microstep(1);    // Microstep select 1 equit Full step ,2 equit Half,4 equit Quarter...
    pwm_A4988_init();    // about 675Hz
    Rotate_CW;
    Enable;
    while (1) {

        // readEncoder();
        // printf("encoder_Angle %f\n",encoder_Angle);
        // Overflower_step(&Overflower_str);
        // printf("Encoder_Angle %f\n", encoder_Angle);
        // RWFirFilter_str.MTCountIn_p = Overflower_str.Count_p;
        // RWFirFilter_step(&RWFirFilter_str);
        // printf("RWFirFilter_str.MTCountOut_p %ld\n",*RWFirFilter_str.MTCountOut_p);
        // printf("Count  %d\n", *Overflower_str.Count_p);
        // printf("AccuOut  %ld\n", *Overflower_str.AccuOut_p);
    }
}

