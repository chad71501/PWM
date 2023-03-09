/*
DynaSinTable.c
Dynamic Sin wave Look up Table
        DynaSinTable_lay() :
                connect DynaSinTable structure, Table initial signal vector S0_p, Signal Table
matrix S_p, update parameter vector TwoCos_p and result signal vector Search for and initialize
Signal Table matrix S_p and Table section vector N[] DynaSinTable_step() : recursive update Dynamic
Signal talbe S_p[] and Table section vector N[] interpolation calculate signal vector s_p[] with
current S_p[] and N[]
*/
#define TO_COMPILE_DYNASINTABLE_C
/*HW Interrupt Sharer Timer0*/
// #include "../BIOS2/M128Bios.h"
// #include "..\EXECSERVER\M128Executor.h"
#include "DynaSinTable.h"
#include "CFG_Driver.h"

void DynaSinTable_lay(DynaSinTableStr_t* Str_p, int16_t* S0_p, int16_t* S_p, int16_t* TwoCos_p,
                      int16_t* s_p);
uint8_t DynaSinTable_step(void* void_p);

void DynaSinTable_lay(DynaSinTableStr_t* Str_p, int16_t* S0_p, int16_t* S_p, int16_t* TwoCos_p,
                      int16_t* s_p) {
    Str_p->S0_p = S0_p;
    Str_p->S_p = S_p;
    Str_p->TwoCos_p = TwoCos_p;
    Str_p->s_p = s_p;
    Str_p->n = *Str_p->FullCountIn_p %
               Str_p->FullScale;    // calculate initial onecycle count without compensate
    uint16_t PERIOD = Str_p->FullScale / Str_p->CountPerPeri;    // Total periods of one cycle
    uint16_t period = Str_p->n / Str_p->CountPerPeri;    // count is in which period of this cycle
    if (period < (PERIOD >> 1)) {			// half periods
        for (uint8_t i = 0; i < Str_p->Channel; i++) {
            Str_p->S_p[i * 3 + 0] = Str_p->S0_p[i * 3 + 1];  //iteration is three pooint
            Str_p->S_p[i * 3 + 1] = Str_p->S0_p[i * 3 + 2];
            Str_p->S_p[i * 3 + 2] =
                ((Str_p->TwoCos_p[i] * Str_p->S_p[i * 3 + 1]) >> 3) - Str_p->S_p[i * 3 + 0];
        }
        for (uint16_t p = 0; p <= period; p++) {
            for (uint8_t i = 0; i < Str_p->Channel; i++) {
                Str_p->S_p[i * 3 + 0] = Str_p->S_p[i * 3 + 1];
                Str_p->S_p[i * 3 + 1] = Str_p->S_p[i * 3 + 2];
                Str_p->S_p[i * 3 + 2] =
                   ((Str_p->TwoCos_p[i] * Str_p->S_p[i * 3 + 1]) >> 3 )- Str_p->S_p[i * 3 + 0];
            }
        }
        Str_p->N[0] = Str_p->CountPerPeri * period, Str_p->N[1] = Str_p->N[0] + Str_p->CountPerPeri,
        Str_p->N[2] = Str_p->N[0] + 2 * Str_p->CountPerPeri;
    } else {
        for (uint8_t i = 0; i < Str_p->Channel; i++) {
            Str_p->S_p[i * 3 + 2] = Str_p->S0_p[i * 3 + 1];
            Str_p->S_p[i * 3 + 1] = Str_p->S0_p[i * 3 + 0];
            Str_p->S_p[i * 3 + 0] =
                ((Str_p->TwoCos_p[i] * Str_p->S_p[i * 3 + 1]) >> 3 )- Str_p->S_p[i * 3 + 2];
        }
        for (uint16_t p = PERIOD - 1; p >= period; p--) {
            for (uint8_t i = 0; i < Str_p->Channel; i++) {
                Str_p->S_p[i * 3 + 2] = Str_p->S_p[i * 3 + 1];
                Str_p->S_p[i * 3 + 1] = Str_p->S_p[i * 3 + 0];
                Str_p->S_p[i * 3 + 0] =
                    ((Str_p->TwoCos_p[i] * Str_p->S_p[i * 3 + 1]) >> 3) - Str_p->S_p[i * 3 + 2];
            }
        }
        Str_p->N[2] = Str_p->CountPerPeri * period, Str_p->N[1] = Str_p->N[2] - Str_p->CountPerPeri,
        Str_p->N[0] = Str_p->N[2] - 2 * Str_p->CountPerPeri;
    }
    DynaSinTable_step((void*)Str_p);
}

uint8_t DynaSinTable_step(void* void_p) {
    DynaSinTableStr_t* Str_p = (DynaSinTableStr_t*)void_p;
    uint16_t PERIOD = Str_p->FullScale / Str_p->CountPerPeri;    // Total periods of one cycle
    uint16_t period = Str_p->n / Str_p->CountPerPeri;    // count is in which period of this cycle
    uint16_t R[3];                                       // F1.15 maximum is 1
    uint8_t Rexpon = 15;                                 //
    Str_p->n = *Str_p->FullCountIn_p % Str_p->FullScale;    // calculate onecycle count
    if (Str_p->n > Str_p->N[2] && Str_p->N[2] < Str_p->FullScale) { // count over right count
        for (uint8_t i = 0; i < Str_p->Channel; i++) {
            Str_p->S_p[i * 3 + 0] = Str_p->S0_p[i * 3 + 1];
            Str_p->S_p[i * 3 + 1] = Str_p->S0_p[i * 3 + 2];
            Str_p->S_p[i * 3 + 2] = ((Str_p->TwoCos_p[i] * Str_p->S_p[i * 3 + 1]) >>
                                    3 )- Str_p->S_p[i * 3 + 0];    // F2.14=(F3.14*F2.14)>>3 +F2.14
        }
        Str_p->N[0] = Str_p->N[1], Str_p->N[1] = Str_p->N[2], Str_p->N[2] = Str_p->N[2] + 32;
    } else if (Str_p->n < Str_p->N[0] && Str_p->N[2] == Str_p->FullScale) {
        for (uint8_t i = 0; i < Str_p->Channel; i++) {
            Str_p->S_p[i * 3 + 0] = Str_p->S0_p[i * 3 + 1];
            Str_p->S_p[i * 3 + 1] = Str_p->S0_p[i * 3 + 2];
            Str_p->S_p[i * 3 + 2] = ((Str_p->TwoCos_p[i] * Str_p->S_p[i * 3 + 1]) >>
                                    3) - Str_p->S_p[i * 3 + 0];    // F2.14=(F3.14*F2.14)>>3 +F2.14
        }
        Str_p->N[0] = 0, Str_p->N[1] = Str_p->CountPerPeri, Str_p->N[2] = 2 * Str_p->CountPerPeri;
    }
    if (Str_p->n < Str_p->N[0] && Str_p->N[0] != 0) {
        for (uint8_t i = 0; i < Str_p->Channel; i++) {
            Str_p->S_p[i * 3 + 2] = Str_p->S_p[i * 3 + 1];
            Str_p->S_p[i * 3 + 1] = Str_p->S_p[i * 3 + 0];
            Str_p->S_p[i * 3 + 0] =
                ((Str_p->TwoCos_p[i] * Str_p->S_p[i * 3 + 1]) >> 3) - Str_p->S_p[i * 3 + 2];
        }
        Str_p->N[2] = Str_p->CountPerPeri * period, Str_p->N[1] = Str_p->N[2] - Str_p->CountPerPeri,
        Str_p->N[0] = Str_p->N[2] - 2 * Str_p->CountPerPeri;
    } else if (Str_p->n > Str_p->N[2] && Str_p->N[0] == 0) {
        for (uint8_t i = 0; i < Str_p->Channel; i++) {
            Str_p->S_p[i * 3 + 2] = Str_p->S0_p[i * 3 + 1];
            Str_p->S_p[i * 3 + 1] = Str_p->S0_p[i * 3 + 0];
            Str_p->S_p[i * 3 + 0] =
                ((Str_p->TwoCos_p[i] * Str_p->S_p[i * 3 + 1]) >> 3) - Str_p->S_p[i * 3 + 2];
        }
        Str_p->N[2] = Str_p->FullScale, Str_p->N[1] = Str_p->FullScale - Str_p->CountPerPeri,
        Str_p->N[0] = Str_p->FullScale - 2 * Str_p->CountPerPeri;
    }
    // interpolation F1.15 = (F16.0*F16.0)<< 15/(F16.0*F16.0)
    R[0] = ((Str_p->n - Str_p->N[1]) * (Str_p->n - Str_p->N[2])) << (Rexpon - Str_p->DiviShift - 1);
    R[1] = (-(Str_p->n - Str_p->N[0]) * (Str_p->n - Str_p->N[2])) << (Rexpon - Str_p->DiviShift);
    R[2] = ((Str_p->n - Str_p->N[0]) * (Str_p->n - Str_p->N[1])) << (Rexpon - Str_p->DiviShift - 1);
    for (uint8_t i = 0; i < Str_p->Channel; i++){

        // F2.14=(F1.15*F2.14+F1.15*F2.14+F1.15*F2.14)>>1
        Str_p->s_p[i] = (R[0] * Str_p->S_p[i * 3 + 0] + R[1] * Str_p->S_p[i * 3 + 1] +
                         R[2] * Str_p->S_p[i * 3 + 2]) >>
                        1;
    }
    return 0;
}