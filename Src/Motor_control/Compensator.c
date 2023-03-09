/*
Compensator.c
    use DynaSinTable to calculate four sinusoid components in misalignment error of magnetic encoder

*/
/*HW Interrupt Sharer Timer0*/
// #include "../BIOS2/M128Bios.h"
// #include "..\EXECSERVER\M128Executor.h"
#include "Compensator.h"

int16_t CompSinTable_S0_p[Comp_CHANNEL * 3] = {0};                    // F2.14
int16_t CompSinTable_S_p[Comp_CHANNEL * 3] = {0};                     // F2.14
int16_t CompSinTable_s_p[Comp_CHANNEL] = {0};                         // F2.14
int16_t CompSinTable_TwoCos_p[Comp_CHANNEL] = {0};                    // F3.13
uint16_t Compensator_A_p[Comp_CHANNEL] = {AMP1, AMP2, AMP3, AMP4};    // Fx.Expon
double CompSinTable_Theta_p[Comp_CHANNEL] = {THETA0, THETA1, THETA2, THETA3};

DynaSinTableStr_t CompSinTable_str = {.FullScale = Comp_FULL_SCALE,
                                      .CountPerPeri = Comp_ONE_PERIOD,
                                      .Channel = Comp_CHANNEL,
                                      .DiviShift = Comp_DIVISION_SHIFT};

CompensatorStr_t Compensator_str = {
    .A0 = AMP0, .Expon = EXPON, .Channel = Comp_CHANNEL, .Omega = OMEGA};

void Compensator_lay(CompensatorStr_t* Str_p, DynaSinTableStr_t* DynaStr_p, uint16_t* A_p,
                     int16_t* s_p, double* Theta_p);
uint8_t Compensator_step(void* void_p);

void Compensator_lay(CompensatorStr_t* Str_p, DynaSinTableStr_t* DynaStr_p, uint16_t* A_p,
                     int16_t* s_p, double* Theta_p) {
    Str_p->CountDiff_p = &Str_p->CountDiff;    // net output pointer
    Str_p->Count_p = &Str_p->Count;            // net output pointer
    Str_p->DynaStr_p = DynaStr_p;              // net internal structure
    Str_p->A_p = A_p;                          // net internal A array
    Str_p->s_p = s_p;                          // net s array
    Str_p->Theta_p = Theta_p;                  // net Theta array
    // net input of Str_p to input of DynaStr_p
    DynaStr_p->FullCountIn_p = Str_p->FullCountIn_p;
    // initialize S0_p[],TwoCos_p[]
    for (uint8_t c = 0; c < DynaStr_p->Channel; c++) {
        DynaStr_p->TwoCos_p[c] =
            (int16_t)((2 ^ 13) * 2 *
                      cos(c * Str_p->Omega));    // F3.13= (int16_t)(2^13*(double -2~2))
        for (uint8_t j = 0; j < 3; j++) {
            DynaStr_p->S0_p[c * 3 + j] =
                (int16_t)((2 ^ 14) *
                          sin(Str_p->Theta_p[c] +
                              (j - 1) * Str_p->Omega));    // F2.14=(int16_t)(2^14*(double -2~2))
        }
    }
}

uint8_t Compensator_step(void* void_p) {
    CompensatorStr_t* Str_p = (CompensatorStr_t*)void_p;
    DynaSinTable_step((void*)Str_p->DynaStr_p);
    int16_t Compen = Str_p->A0;    // Fx.Expon, x=16-Expon
    for (uint8_t i = 0; i < Str_p->Channel; i++) {
        Compen = Compen + Str_p->A_p[i] * Str_p->s_p[i];    // Fx.Expon=Fx.Expon+Fx.Expon
    }
    Str_p->Count = Str_p->DynaStr_p->n + (Compen >> Str_p->Expon);    // F16.0=F16.0+Fx.Expon>>Expon
    Str_p->CountDiff = *Str_p->FullCountGoad_p - *Str_p->FullCountIn_p +
                       (Compen >> Str_p->Expon);    // F8.0=F32.0-F32.0+Fx.Expon>>Rxpon
    return 0;
}
