#ifndef _MREGISTER_H
#define	_MREGISTER_H


typedef enum registername 
{
  R_ZERO,  R_AT	,  R_V0	,  R_V1	,  R_A0	,
  R_A1	,  R_A2	,  R_A3	,  R_T0	,  R_T1	,
  R_T2	,  R_T3	,  R_T4	,  R_T5	,  R_T6	,
  R_T7	,  R_S0	,  R_S1	,  R_S2	,  R_S3	,
  R_S4	,  R_S5	,  R_S6	,  R_S7	,  R_T8	,
  R_T9	,  R_K0	,  R_K1	,  R_GP	,  R_SP	,
  R_FP	,  R_RA	,  R_F0	,  R_F1	,  R_F2	,
  R_F3	,  R_F4	,  R_F5	,  R_F6	,  R_F7	,
  R_F8	,  R_F9	,  R_F10,  R_F11,  R_F12,
  R_F13	,  R_F14,  R_F15,  R_F16,  R_F17,
  R_F18	,  R_F19,  R_F20,  R_F21,  R_F22,
  R_F23	,  R_F24,  R_F25,  R_F26,  R_F27,
  R_F28	,  R_F29,  R_F30,  R_F31
} MRegisterType;


static const int int_register_size = 18;
static const int float_register_size = 15;
static const int cache_register_size = 4;

extern MRegisterType int_registers[int_register_size];
extern MRegisterType float_registers[float_register_size];
extern MRegisterType cache[cache_register_size];

const char * reglookup(MRegisterType op);


#endif
