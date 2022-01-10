/*
 * MRegister.cc
 */


#include "MRegister.h"


//////////////////////////////////////
//    int_registers[-]     		      //
//  The mips integer registers      //
//  storing single word data        //
//////////////////////////////////////

MRegisterType int_registers[int_register_size] = 
{
  R_T0,  R_T1,  R_T2,  R_T3,  R_T4,
  R_T5,  R_T6,  R_T7,  R_S0,  R_S1,
  R_S2,  R_S3,  R_S4,  R_S5,  R_S6,
  R_S7,  R_T8,  R_T9
};

//////////////////////////////////////
//    float_registers[-]     		    //
//  The mips float registers        //
//  storing double word data        //
//////////////////////////////////////

MRegisterType float_registers[float_register_size] = 
{
  R_F2 ,  R_F4 ,  R_F6 ,  R_F8 ,  R_F10,
  R_F12,  R_F14,  R_F16,  R_F18,  R_F20,
  R_F22,  R_F24,  R_F26,  R_F28,  R_F30
};

//////////////////////////////////////
//    cache[-]     		              //
//  A four word cyclic cache for    //
//  fast storing and loading of     //
//  temporary working data          //
//////////////////////////////////////

MRegisterType cache[cache_register_size] = 
{
  R_A0,  R_A1,  R_A2,  R_A3
};

//////////////////////////////////////
//    reglookup(-)                  //
//  Looks up target register in the //
//  register database for the mips  //
//  language                        //
//////////////////////////////////////

const char * reglookup(MRegisterType op)
{
  const char * register_type[] = 
  {
    "$0"	,    "$at"	,    "$v0"	,    "$v1"	,    "$a0"	,
    "$a1"	,    "$a2"	,    "$a3"	,    "$t0"	,    "$t1"	,
    "$t2"	,    "$t3"	,    "$t4"	,    "$t5"	,    "$t6"	,
    "$t7"	,    "$s0"	,    "$s1"	,    "$s2"	,    "$s3"	,
    "$s4"	,    "$s5"	,    "$s6"	,    "$s7"	,    "$t8"	,
    "$t9"	,    "$k0"	,    "$k1"	,    "$gp"	,    "$sp"	,
    "$fp"	,    "$ra"	,    "$f0"	,    "$f1"	,    "$f2"	,
    "$f3"	,    "$f4"	,    "$f5"	,    "$f6"	,    "$f7"	,
    "$f8"	,    "$f9"	,    "$f10"	,    "$f11"	,    "$f12"	,
    "$f13",    "$f14"	,    "$f15"	,    "$f16"	,    "$f17"	,
    "$f18",    "$f19"	,    "$f20"	,    "$f21"	,    "$f22"	,
    "$f23",    "$f24"	,    "$f25"	,    "$f26"	,    "$f27"	,
    "$f28",    "$f29"	,    "$f30"	,    "$f31"
  };
  
  return register_type[op];
}
