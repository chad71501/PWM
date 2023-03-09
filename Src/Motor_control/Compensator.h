/*
Compensator.c
    use DynaSinTable to calculate four sinusoid components in misalignment error of magnetic encoder

*/

#ifndef Compensator_H_INCLUDED
#define Compensator_H_INCLUDED
#include <stdint.h>
#include "CFG_Driver.h"
#include "DynaSinTable.h"

typedef struct Compensator {
    int16_t A0;         // Fx.Expon DC offset
    uint8_t Expon;      // F8.0  exponent of offset and sinusoid wave bias
    uint8_t Channel;    // F8.0
    double Omega;
    uint16_t Count;                  // F16.0 encoder count after compensation
    int8_t CountDiff;                // F8.0 difference of goad count and sensed count
    volatile uint16_t* Count_p;      // F16.0 compensated single cycle encoder count
    volatile int8_t* CountDiff_p;    // F8.0 difference of goad and sensed encoder count
    volatile uint16_t* A_p;          // Fx.Expon Amplitude of 0 to 4 mode
    volatile int16_t* s_p;           // F2.14 sin values of all channels at the input count
    volatile double* Theta_p;        //
    volatile uint32_t*
        FullCountIn_p;    // F32.0 address of multi cycle encoder count before compensated
    volatile uint32_t*
        FullCountGoad_p;    // F32.0 address of position goad of multi cycle encoder count
    volatile DynaSinTableStr_t* DynaStr_p;
} CompensatorStr_t;


extern int16_t CompSinTable_S0_p[Comp_CHANNEL * 3];                    // F2.14
extern int16_t CompSinTable_S_p[Comp_CHANNEL * 3] ;                     // F2.14
extern int16_t CompSinTable_s_p[Comp_CHANNEL] ;                         // F2.14
extern int16_t CompSinTable_TwoCos_p[Comp_CHANNEL] ;                    // F3.13
extern uint16_t Compensator_A_p[Comp_CHANNEL] ;    // Fx.Expon
extern double CompSinTable_Theta_p[Comp_CHANNEL] ;

extern DynaSinTableStr_t CompSinTable_str;
extern CompensatorStr_t Compensator_str;


void Compensator_lay(CompensatorStr_t* Str_p, DynaSinTableStr_t* DynaStr_p, uint16_t* A_p,
                     int16_t* s_p, double* Theta_p);
uint8_t Compensator_step(void* void_p);
#define Compensator_LAY()                                                                       \
    {                                                                                           \
        Compensator_lay(&Compensator_str, &CompSinTable_str, Compensator_A_p, CompSinTable_s_p, \
                        CompSinTable_Theta_p);                                                  \
        DynaSinTable_lay(&CompSinTable_str, CompSinTable_S0_p, CompSinTable_S_p,                \
                         CompSinTable_TwoCos_p, CompSinTable_s_p);                              \
    }
#endif
