/*
Overflower.c
    use DynaSinTable to calculate four sinusoid components in misalignment error of magnetic encoder

*/
#ifndef Overflower_H_INCLUDED
#define Overflower_H_INCLUDED
#include <stdint.h>
#include "CFG_Driver.h"

typedef struct Overflower {
    uint16_t FullScale;  // F16.0 full scale of one turn encoder
    uint16_t HalfScale;  // F16.0 half scale of one ture of encoder
    uint8_t RegId;       // F8.0 Register id number of the count in encoder
    uint8_t Bytes;       // F8.0 bytes of the count in encoder
    uint16_t Count;      // F16.0 newly readed count of encder
    uint16_t Count0;     // F16.0 old count of encoder
    uint32_t AccuOut;    // F32 accumulated multiturn count of encoder
    // output pointers
    volatile uint16_t* Count_p;    // F16.0 address of newly readed count of encder
    volatile uint32_t* AccuOut_p;  // F32 address of accumulated multiturn count of encoder
    // Structure pointer
    // CardSetStr_t* CardStr_p;  // CardSetStr_t type stucture
} OverflowerStr_t;


extern OverflowerStr_t Overflower_str;
void Overflower_step(void* void_p);
void Overflower_lay(OverflowerStr_t* Str_p);
#endif  // TO_COMPILE_OVERFLOWER_C

