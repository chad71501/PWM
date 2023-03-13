/**
 * @file A4988_step_error.c
 * @author Chad (U06117127@o365.mcut.edt.tw)
 * @brief
 * @version 0.1
 * @date 2023-03-13
 *
 * @copyright Copyright (c) 2023
 *
 */

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
#define step 200
static float encoder_Angle = 0;
static float prev_encoder_Angle = 0;
uint16_t sin_count = 0;
int flag_cli = 2;
volatile uint16_t step_count = 0;
extern uint16_t sin_sampling[360];
char sample;
int Motor_turn = 0;
float error[step];
float actual_value[step];

int main() {
    sintable();
    uart_init();    // terminal picture
    SPI_MasterInit();
    Rotate_CW;
    // OCR2 = sin_sampling[0];
    TCNT2 = 0;
    pwm_A4988_init();    // about 675KHz
    Microstep(1);        // Microstep select 1 equit Full step ,2 equit Half,4 equit Quarter...
    step_count = 0;
    Enable;
    sei();
    while (1) {
        if (flag_cli == 1) {
            DisEnable;
            TIMSK &= ~(1 << OCIE2);
            if (step_count >= step) {
                for (int i = 0; i < step; i++) {
                    error[i] = ((float)1.8 * (i + 1)) - actual_value[i];
                }
                for (int i = 0; i < step; i++) {
                    printf(" %.3f\n", error[i]);
                }
            }
            flag_cli = 0;
            printf("%.2f\n", encoder_Angle);
            scanf("%s", &sample);
        }
        if ((sample == 'N') && ((TIFR >> TOV2) & 0x01)) {
            actual_value[step_count] = prev_encoder_Angle;
            step_count++;
            TIFR &= ~(1 << TOV2);
            printf("step_count %d\n", step_count);
        } else if (sample == 's') {
            // printf("start sample\n");
            TCNT2 = 0;
            Enable;
            DDRB |= (1 << Step_pin);
            TIMSK |= (1 << OCIE2);
            TIFR &= ~(1 << TOV2);
            sample = 'N';
        }
    }
}

ISR(TIMER2_COMP_vect) {
    encoder_Angle = readAngle();    // angle
    // encoder_Angle = readEncoder();  //count
    if ((prev_encoder_Angle >= (float)359.001) && (encoder_Angle >= (float)0.0001) &&
               (encoder_Angle <= (float)0.1)) {
        DDRB &= ~(1 << Step_pin);
        flag_cli = 1;
    } else if (step_count >= step) {
        DDRB &= ~(1 << Step_pin);
        flag_cli = 1;
    }
    if (step_count <= 0) {
        prev_encoder_Angle = encoder_Angle;
    } else if ((prev_encoder_Angle <= encoder_Angle) && step_count > 0) {
        prev_encoder_Angle = encoder_Angle;
    }
    // printf("%.2f\n", encoder_Angle);
    /*SPWM set*/
    // OCR2 = sin_sampling[sin_count++];    // extern sintable.h file
    // printf("encoder_Angle %d\n", encoder_Angle);
    // if (sin_count >= 360) {
    //     sin_count = 0;
    // }
}