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
#include "Src/BIOS/SPI_set.h"
#include "AS5X47.h"

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
    
    // SS_LOW;    // SPI_set.h define
    // encoder.readData[1] = SPI_transmit_byte(Command[1]);    // send Command LSB 8bit
    // encoder.readData[0] = SPI_transmit_byte(Command[0]);    // send Command  MSB 8bit
    // SS_HIGH;
    // encoder.data= encoder.data & 0x3FFF;
    // Overflower_str.Count = encoder.data;
    
    DiffCount = Str_p->Count - Str_p->Count0;
    Str_p->AccuOut = Str_p->AccuOut + DiffCount;

    //printf("DiffCount %d\n",DiffCount);
    if (DiffCount > Str_p->HalfScale && Str_p->AccuOut > Str_p->FullScale) {
        Str_p->AccuOut = Str_p->AccuOut - Str_p->FullScale;
        printf("acw\n");
    }
    // printf("(Str_p->HalfScale) %d\n",(-Str_p->HalfScale));
    // printf("(Str_p->FullScale) %d\n",(Str_p->FullScale));

    if (DiffCount < (-Str_p->HalfScale)) {
        Str_p->AccuOut = Str_p->AccuOut + Str_p->FullScale;
        printf("cw\n");
    }

}
