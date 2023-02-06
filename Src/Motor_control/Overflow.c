/*
Overflower.c
    use DynaSinTable to calculate four sinusoid components in misalignment error of magnetic encoder

*/

/*HW Interrupt Sharer Timer0*/
// #include "../BIOS2/M128Bios.h"
//  #include "..\EXECSERVER\M128Executor.h"
#include "Overflow.h"
#include <avr/io.h>
#include <stdio.h>
OverflowerStr_t Overflower_str = {.FullScale = FULL_SCALE,
                                  .HalfScale = HALF_SCALE,
                                  .RegId = ENCORDER_COUNT_REG_ID,
                                  .Bytes = 2,
                                  .Count = 0,
                                  .AccuOut = 0};

uint16_t DiffCount = 0;
void Overflower_lay(OverflowerStr_t* Str_p) {
    Str_p->Count_p = &Str_p->Count;
    Str_p->AccuOut_p = &Str_p->AccuOut;
}

void Overflower_step(void* void_p) {
    OverflowerStr_t* Str_p = (OverflowerStr_t*)void_p;
    Str_p->Count0 = Str_p->Count;    // update old count
    DiffCount = Str_p->Count - Str_p->Count0;
    Str_p->AccuOut = Str_p->AccuOut + DiffCount;
    if (DiffCount > Str_p->HalfScale && Str_p->AccuOut > Str_p->FullScale) {
        Str_p->AccuOut = Str_p->AccuOut - Str_p->FullScale;
        printf("acw\n");
    }

    if (DiffCount < (-Str_p->HalfScale)) {
        Str_p->AccuOut = Str_p->AccuOut + Str_p->FullScale;
        printf("cw\n");
    }

}
