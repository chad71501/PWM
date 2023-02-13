/*
RWFirFilter.c
    use DynaSinTable to calculate four sinusoid components in misalignment error of magnetic encoder

*/
#ifndef RWFirFilter_H_INCLUDED
  #define RWFirFilter_H_INCLUDED
#include "CFG_Driver.h"
#include <stdint.h>

typedef struct RWFirFilter {
    uint8_t Tap; //F8.0 Tap of FIR filter
    uint8_t DiviShift; //F8.0 shift to replace division 
    uint8_t Index; //F8.0 Index to Signal Buffer 
    uint32_t MTCountAcc; //F32.0 multi turn encoder count accumulated value 
    uint32_t MTCountOut; //F32.0 multi turn encoder count 
    //output pointers  
    volatile uint32_t* MTCountOut_p;//F32  address of multi turn encoder count output 
    //input pointers
    volatile uint16_t* MTCountIn_p; //F16.0 address of multi turn encoder count iput 
    //Buffer array pointer
    volatile uint32_t* Buffer_p; //F16.0 address of signal buffer array
}RWFirFilterStr_t; 

extern RWFirFilterStr_t RWFirFilter_str;
extern uint32_t RWFirFilter_Buffer_p[FIR_TAP];
void RWFirFilter_lay(RWFirFilterStr_t* Str_p, uint32_t* Buffer_p);
uint8_t RWFirFilter_step(void* void_p);

#define RWFirFilter_LAY(){\
	RWFirFilter_lay(&RWFirFilter_str,RWFirFilter_Buffer_p);\
}

#endif

