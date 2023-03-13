/**
 * @file Sintable.c
 * @author Chad (U06117127@o365.mcut.edt.tw)
 * @brief 
 * @version 0.1
 * @date 2023-03-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include "Sintable.h"
#include <stdio.h>

uint16_t sin_sampling[360];    // sinusoidal simulation
#define freq 1                 // frequency
#define Fs 360                 // Sampling rate
#define shift_voltage 1        // -1~1 shift 1~2
#define narrow_down 2          // sine wave 0~1 voltage
#define resolution_8bit 254
#define resolution_16bit 1023
void sintable() {
    int sample = 0;
    float tmp = 0;
    for (sample = 0; sample < 360; sample++) {
        tmp = ((sin((((2 * M_PI) * freq * sample) / Fs))) + shift_voltage) / narrow_down;
        sin_sampling[sample] = tmp * resolution_8bit;
        // printf("%d\n",sin_sampling[sample]);
    }
}