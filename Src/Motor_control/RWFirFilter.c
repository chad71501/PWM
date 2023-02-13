/*
RWFirFilter.c
    use DynaSinTable to calculate four sinusoid components in misalignment error of magnetic encoder

*/
#define TO_COMPILE_RWFIRFILTER_C
/*HW Interrupt Sharer Timer0*/
#include "RWFirFilter.h"

RWFirFilterStr_t RWFirFilter_str = {.Tap = FIR_TAP, .DiviShift = DIVI_SHIFT};

uint32_t RWFirFilter_Buffer_p[FIR_TAP] = {0};

void RWFirFilter_lay(RWFirFilterStr_t* Str_p, uint32_t* Buffer_p) {
    Str_p->MTCountOut_p = &Str_p->MTCountOut;
    Str_p->Buffer_p = Buffer_p;
    for (uint8_t i = 0; i < Str_p->Tap; i++) RWFirFilter_step((void*)Str_p);
}

uint8_t RWFirFilter_step(void* void_p) {
    RWFirFilterStr_t* Str_p = (RWFirFilterStr_t*)void_p;
    Str_p->MTCountAcc = Str_p->MTCountAcc + *Str_p->MTCountIn_p - Str_p->Buffer_p[Str_p->Index];
    Str_p->Buffer_p[Str_p->Index] = *Str_p->MTCountIn_p;   //Encoder 數值輸入
    Str_p->Index++;
    if (Str_p->Index == Str_p->Tap) Str_p->Index = 0;
    Str_p->MTCountOut = Str_p->MTCountAcc >> Str_p->DiviShift;  // 可以+4，來做4捨5入，這裡是做除法，將總數平均
    return 0;
}
