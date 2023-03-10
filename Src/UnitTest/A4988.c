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
#include "pwm.h"
#include "uartdevice.h"
static float encoder_Angle;
extern uint16_t sin_sampling[360];
int count=0;
int main() {
    sintable();
    uart_init();         // terminal picture
    SPI_MasterInit();
    // SPIDecoder(2);
    // Overflower_lay(&Overflower_str);
    // RWFirFilter_LAY();
    // uint8_t countstep = 0;    // 200 step 等於 1圈
    // uint16_t lapcount = 0;    // 圈數
    rotate_cw;
    pwm_A4988_init();    // about 675KHz
    sei();
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

ISR(TIMER2_COMP_vect) {
    encoder_Angle = readAngle();
    printf("encoder_Angle %d\t %d\n",(uint8_t)encoder_Angle,count);
    // if(!(uint8_t)encoder_Angle){
    //      DDRB &= ~(1 << Steppin) ;
    //      cli();
    // }
    OCR2=sin_sampling[count++];
    if(count >=360){
        count=0;
    }  
}