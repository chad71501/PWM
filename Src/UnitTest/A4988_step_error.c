/**
 * @file A4988_step_error.c
 * @author Chad (U06117127@o365.mcut.edt.tw)
 * @brief Microchip Atmega128A is used to control a step motor with an A4988 driver and an AS5047D
 * encoder. The motor step position error is measured
 * @version 0.1
 * @date 2023-03-13
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
#define step_set \
    2    // Select microsteps: 1 equals full step, 2 equals half step, and 4 equals quarter step..
#define _step(step_set) step_set * 200    // the number of microsteps per revolution of the motor
#define _ideal_value(step_set) (float)1.8 / step_set    //  ideal position of the motor step

static float encoder_Angle = 0;
static float prev_encoder_Angle = 0;
uint16_t sin_count = 0;
int flag_cli = 2;
volatile uint16_t step_count = 0;
extern uint16_t sin_sampling[360];
char sample;
float error[_step(step_set)];
float actual_value[_step(step_set)];

int main() {
    sintable();
    uart_init();
    SPI_MasterInit();
    Rotate_CW;    // motor clockwise/forward
    // OCR2 = sin_sampling[0];
    TCNT2 = 0;
    pwm_A4988_init();       // about 168Hz
    Microstep(step_set);    // Select microsteps: 1 equals full step, 2 equals half step, and 4
                            // equals quarter step..
    step_count = 0;
    Enable;    // A4988 Enable_pin
    sei();
    while (1) {
        /*interrupt close*/
        if (flag_cli == 1) {
            DisEnable;
            TIMSK &= ~(1 << OCIE2);
            if (step_count >= _step(step_set)) {
                for (int i = 0; i < _step(step_set); i++) {
                    error[i] = ((float)_ideal_value(step_set) * (i + 1)) - actual_value[i];
                }
                for (int i = 0; i < _step(step_set); i++) {
                    printf("%.3f\n", error[i]);
                }
            }
            flag_cli = 0;
            printf("step_count %d\n", step_count);
            printf("%.2f\n", encoder_Angle);
            printf("Sample by entering lowercase 's'\n");
            scanf("%s", &sample);
        }
        /*Open loop step*/
        if (sample == 's') {
            step_count = 0;
            TCNT2 = 0;
            TIMSK |= (1 << OCIE2);
            DDRB |= (1 << Step_pin);
            TIFR &= ~(1 << TOV2);
            Enable;
            sample = 'N';
        }
    }
}

ISR(TIMER2_COMP_vect) {
    encoder_Angle = readAngle();    // motor angle
    // encoder_Angle = readEncoder();   // encorder count
    if ((prev_encoder_Angle >= (float)359.001) && (encoder_Angle >= (float)0.0001) &&
        (encoder_Angle <= (float)0.1)) {
        DDRB &= ~(1 << Step_pin);
        flag_cli = 1;
    } else if (step_count >= _step(step_set)) {
        DDRB &= ~(1 << Step_pin);
        flag_cli = 1;
    }
    if (step_count <= 0) {
        prev_encoder_Angle = encoder_Angle;
    } else if ((prev_encoder_Angle <= encoder_Angle) && step_count > 0) {
        prev_encoder_Angle = encoder_Angle;
    }
    if (sample == 'N') {
        actual_value[step_count] = prev_encoder_Angle;
        step_count = step_count + 1;
    }

    /*SPWM set*/
    // OCR2 = sin_sampling[sin_count++];    // extern sintable.h file
    // printf("encoder_Angle %d\n", encoder_Angle);
    // if (sin_count >= 360) {
    //     sin_count = 0;
    // }
}