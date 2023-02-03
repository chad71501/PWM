/**
 * @file pwmtest.c
 * @author “ychad (U06117127@o365.mcut.edu.tw)
 * @brief 
 * @version 0.1
 * @date 2022-12-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <avr/io.h>
#include <math.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "Src/BIOS/pwm.h"
#include "Src/BIOS/uartdevice.h"
#define PI 3.1415926
#define STEP PI/180

uint8_t phase_A=0,phase_B=90,count=0;  //phase A & phase B  is ninety degrees out of phase
int16_t x[360]={0};
ISR(TIMER1_OVF_vect){
    if (count==10)
    {
        count=0;
        phase_A++;
        phase_B++;
        OCR1A=x[phase_A]*0.8+16384;  // 0.8 is Amplitude && wave shift to positive
        OCR1B=x[phase_B]*0.8+16384;
    }
   count++;
}


int main(){
    
    for (int i=0;i<360;i++){
        double wave=sin(STEP*i);
        if (wave>0)
        {
            x[i]=(int16_t)(wave*32767+0.5);   //wave value * int16_t become digital number & 0.5 is rounding
        }
        else
        {
            x[i]=(int16_t)(wave*32767-0.5);
        }
    }
    uart_init();
    pwm_init();
    sin();
}