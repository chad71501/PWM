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

#include "AS5X47.h"
#include "Src/BIOS/SPI_set.h"

OverflowerStr_t Overflower_str = {.FullScale = FULL_SCALE,
                                  .HalfScale = HALF_SCALE,
                                  .RegId = ENCORDER_COUNT_REG_ID,
                                  .Bytes = 2,
                                  .Count = 0,
                                  .AccuOut = 0};
float Encoder_Angle;
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
    Str_p->Count =readEncoder();
    Encoder_Angle = Str_p->Count/16384.*360.;
    // printf("Encoder_Angle %.3f\n", Encoder_Angle);
    printf("Encoder_count %d\n", Str_p->Count);

    DiffCount = Str_p->Count - Str_p->Count0;       //new count - old count
    Str_p->AccuOut = Str_p->AccuOut + DiffCount;

    if (DiffCount > Str_p->HalfScale && Str_p->AccuOut > Str_p->FullScale) {
        Str_p->AccuOut = Str_p->AccuOut - Str_p->FullScale;
    }

    if (DiffCount < (-Str_p->HalfScale)) {
        Str_p->AccuOut = Str_p->AccuOut + Str_p->FullScale;
    }
}
