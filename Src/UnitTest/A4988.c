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
#include "Compensator.h"
#include "Overflow.h"
#include "RWFirFilter.h"
#include "SPI_set.h"
#include "Sintable.h"
#include "pwm.h"
#include "uartdevice.h"

double A[4] = {THETA0, THETA1, THETA2, THETA3};
int main() {
    uart_init();    // terminal picture


    // Microstep(1);    // Microstep select 1 equit Full step ,2 equit Half,4 equit Quarter...
    // pwm_A4988_init();    // about 675Hz
    // Rotate_CW;
    // Enable;
    // SPIDecoder(2);
    // SPI_MasterInit();
    // Overflower_lay(&Overflower_str);
    // RWFirFilter_LAY();
    Compensator_LAY();
    // for (uint8_t c = 0; c < 4; c++) {
    //     printf("TwoCos_p[%d]=%d\n", c,CompSinTable_str.TwoCos_p[c]);
    //     printf("TwoCos %d\n", (int16_t)((1 << 13) * 2 * cos(c * 0.5)));
    // }
    /*self*/

    // for (uint8_t c = 0; c < DynaStr_p->Channel; c++) {
    //     TwoCos[c] = 2 * cos(c * 0.5);    // F3.13= (int16_t)(2^13*(double -2~2))
    //     for (uint8_t j = 0; j < 3; j++) {
    //         S0[c * 3 + j] = sin(Theta[c] + (j - 1) * 0.5);    // F2.14=(int16_t)(2^14*(double
    //         -1~1))
    //     }
    // }
    /*self*/

    // for (uint8_t j = 0; j < 3; j++) {
    //     printf(" S0[%d]= %f\tS0_p[%d]= %d\n", c, S0[c * 3 + j], c * 3 + j,
    //            DynaStr_p->S0_p[c * 3 + j]);
    // }

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
