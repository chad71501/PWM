
/*
DynaSinTable.h
Dynamic Sin wave Look up Table
        DynaSinTable_lay() :
                connect DynaSinTable structure, Table initial signal vector S0_p, Signal Table
matrix S_p, update parameter vector TwoCos_p and result signal vector Search for and initialize
Signal Table matrix S_p and Table section vector N[] DynaSinTable_step() : recursive update Dynamic
Signal talbe S_p[] and Table section vector N[] interpolation calculate signal vector s_p[] with
current S_p[] and N[]
*/

#ifndef DynaSinTable_H_INCLUDED
#define DynaSinTable_H_INCLUDED
#include <avr/io.h>
#include <stdint.h>

typedef struct DynaSinTable {
    uint16_t FullScale;                  // F16.0 Total counts of one cycle
    uint16_t n;                          // F16.0 count at this cycle
    uint16_t CountPerPeri;               // F16.0 count per period
    uint8_t Channel;                     // F8.0 channel number of sinusoid waves F8.0
    uint8_t DiviShift;                   // F8.0 shift for division
    uint16_t N[3];                       // F16.0 dynamic sin table current count vector
    volatile uint32_t* FullCountIn_p;    // F32.0 address of the input count variable
    volatile int16_t* S0_p;              // F2.14 dynamic sin table initial sin value matrix
    int16_t *TwoCos_p;          // F3.13 dynamic iteration update parameter vector
    volatile int16_t* S_p;               // F2.14 dynamic sin table current sin value matrix
    volatile int16_t* s_p;               // F2.14 sin values of all channels at the input count
} DynaSinTableStr_t;


void DynaSinTable_lay(DynaSinTableStr_t* Str_p, int16_t* S0_p, int16_t* S_p, int16_t* TwoCos_p,
                      int16_t* s_p);
uint8_t DynaSinTable_step(void* void_p);

#endif