/*
Compensator.c
    use DynaSinTable to calculate four sinusoid components in misalignment error of magnetic encoder

*/

#include <math.h>

#define PI acos(-1)
/* copensator */
#define Comp_FULL_SCALE 1 << 14
#define Comp_ONE_PERIOD 1 << 9
#define Comp_CHANNEL 4
#define Comp_DIVISION_SHIFT 18
#define EXPON 3
//(uint16_t)(0.01*2^EXPON)
#define AMP0 0x0001
#define AMP1 0x0001
#define AMP2 0x0001
#define AMP3 0x0001
#define AMP4 0x0001
#define THETA0 0.01
#define THETA1 0.1
#define THETA2 0.1
#define THETA3 0.1
#define OMEGA 0.5

/* Space vector PWM */
#define Svpwm_FULL_SCALE 1 << 13
#define Svpwm_ONE_PERIOD 1 << 5
#define Svpwm_CHANNEL 2
#define Svpwm_DIVISION_SHIFT 10
// i_normal = i/I_fs maximum is 1 I_fs F16.0 maximum is 2^Bits
#define Svpwm_THETA0 0.1
#define Svpwm_THETA1 0.1
#define Svpwm_OMEGA 0.5

/* Lead-Lag FeedbackControled */
#define M_E_RATIAL 50
// FULL_SCALE/M_E_RATIAL/4: 2^14/50/4=81.92 81.92*2^9=41943 count in F7.9
#define MAX_LEAD_LAG_COUNT 41943
#define MAX_LEAD_LAG_EXPON 9
// lambda 0.95 F0.16 0.95*2^16=62259
#define LAMBDA_MANTISA 62259
#define LAMBDA_EXPON 16
// K_I 0~255 F0.9=F8.0>>9
#define LLK_I_MANTISA 127
#define LLK_I_EXPON 9

/* Current FeedbackControled */
// Maximun Current uint16_t F16.0
#define MAX_CURRENT 1023
// Minimun Current uint16_t F10.6 MIN_Current=MAX_Current/8
#define MIN_CURRENT 128
#define Curr_EXPON 0
// Satulate Count Error 8 count uint16_t F16.0
// I_max= K_p * Count_sat => K_p= 1024/8= 128
// Current K_p uint8_t F8.0 0~255
#define Curr_K_P 128
#define Curr_K_P_EXPON 0
// lambda=0.95 steady state error count=4
// steady state error integer count_acc= 4/(1-0.95)=8
// I_max= K_i * Count_acc => K_p= 1024/8= 128
// Current K_I 0~255 F0.9=F8.0>>9
#define Curr_K_I 128
#define Curr_K_I_EXPON 0

/* Overflower */
#define FULL_SCALE Comp_FULL_SCALE
#define HALF_SCALE (FULL_SCALE / 2)
#define ENCORDER_COUNT_REG_ID 1

/* RWFirFilter*/
#define FIR_TAP 8
#define DIVI_SHIFT 3

/* AVPBuffExec */
#define JERK_LIMIT 1
#define JERK_EXPON 1
#define ACCEL_LIMIT 1
#define ACCEL_EXPON 1
#define VELO_LIMIT 1
#define VELO_EXPON 1
#define POSI_LIMIT 1024
