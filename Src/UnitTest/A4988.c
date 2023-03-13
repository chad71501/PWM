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

static float encoder_Angle = 0;
static float prev_encoder_Angle = 0;
uint16_t sin_count = 0;
volatile int flag_cli = 2;
volatile uint16_t step_count = 0;
extern uint16_t sin_sampling[360];
char sample;
int Motor_turn = 0;

int main() {
    sintable();
    uart_init();    // terminal picture
    SPI_MasterInit();

    // SPIDecoder(2);
    // Overflower_lay(&Overflower_str);
    // RWFirFilter_LAY();

    Rotate_CW;
    // OCR2 = sin_sampling[0];
    TCNT2 = 0;
    pwm_A4988_init();    // about 675KHz
    // Microstep(1);    // Microstep select 1 equit Full step ,2 equit Half,4 equit Quarter...
    step_count = 0;
    Enable;
    sei();
    while (1) {
        if ((sample == 'N') && ((TIFR >> TOV2) & 0x01)) {
            printf("step_count %d\n", step_count);
            step_count++;
        } else if (sample == 's') {
            printf("start sample\n");
            TCNT2 = 0;
            step_count = 0;
            DDRB |= (1 << Step_pin);
            Enable;
            TIMSK |= (1 << OCIE2);
            sample = 'N';
        }
        if (flag_cli == 1) {
            TIMSK &= ~(1 << OCIE2);
            DisEnable;
            printf("in_step_count %d\n", step_count);
            printf("encoder_Angle %f\n", encoder_Angle);
            flag_cli = 0;
            scanf("%s", &sample);
        }

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
    encoder_Angle = readAngle();    // angle
    // encoder_Angle = readEncoder();  //count
    if ((prev_encoder_Angle <= (float)359.999999) && (prev_encoder_Angle >= (float)359.599) &&
        (encoder_Angle >= (float)0.1)) {
        DisEnable;
        DDRB &= ~(1 << Step_pin);
        flag_cli = 1;
    } else if (step_count >= 200) {
        DisEnable;
        DDRB &= ~(1 << Step_pin);
        flag_cli = 1;
    }
    printf(" %f\n", encoder_Angle);
    prev_encoder_Angle = encoder_Angle;

    /*SPWM set*/
    // OCR2 = sin_sampling[sin_count++];    // extern sintable.h file
    // printf("encoder_Angle %d\n", encoder_Angle);
    // if (sin_count >= 360) {
    //     sin_count = 0;
    // }
}