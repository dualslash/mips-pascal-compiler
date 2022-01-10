/*
 * MOperator.cc
 */
 

#include "MOperator.h"


//////////////////////////////////////
//    mips_op[-]     		            //
//  The complete mips operator      //
//  database                        //
//////////////////////////////////////

static const char * const mips_op[MOP_NOPERATORS] = 
{
  "\n\t.ent"	,  ".end"				,  ".align"			,  ".ascii"			,  ".asciiz"		,
  ".byte"			,  "\n\t.data"	,  ".double"		,  ".extern"		,  ".float"			,
  ".globl"		,  ".half"			,  "\n\t.kdata"	,  "\n\t.ktext"	,  ".space"			,
  "\n\t.text"	,  ".word"			,  "abs"				,  "add"				,  "addi"				,
  "addu"			,	 "addiu"			,  "and"				,  "andi"				,  "div2"				,
  "div2u"			,  "div"				,  "divu"				,  "mul"				,  "mulo"				,
  "mulou"			,  "mult"				,  "multu"			,  "neg"				,  "negu"				,
  "nor"				,  "not"				,  "or"					,  "ori"				,  "rem"				,
  "remu"			,  "rol"				,  "ror"				,  "sll"				,  "sllv"				,
  "sra"				,  "srl"				,  "srlv"				,  "sub"				,  "subu"				,
  "xor"				,  "xori"				,  "li"					,  "lui"				,  "seq"				,
  "sge"				,  "sgeu"				,  "sgt"				,  "sgtu"				,  "sle"				,
  "sleu"			,  "slt"				,  "slti"				,  "sltu"				,  "sltiu"			,
  "sne"				,  "b"					,  "bc1t"				,  "bc1f"				,  "beq"				,
  "beqz"			,  "bge"				,  "bgeu"				,  "bgez"				,  "bgezal"			,
  "bgt"				,  "bgtu"				,  "bgtz"				,  "ble"				,  "bleu"				,
  "blez"			,  "bltzal"			,  "blt"				,  "bltu"				,  "bltz"				,
  "bne"				,  "bnez"				,  "j"					,  "jal"				,  "jr"					,
  "la"				,  "lb"					,  "lbu"				,  "ld"					,  "lh"					,
  "lhu"				,  "lw"					,  "lwcz"				,  "lwl"				,  "lwr"				,
  "ulh"				,  "ulhu"				,  "ulw"				,  "sb"					,  "sd"					,
  "sh"				,  "sw"					,  "swcz"				,  "swl"				,  "swr"				,
  "ush"				,  "usw"				,  "move"				,  "mfhi"				,  "mtlo"				,
  "mfc1"			,  "mfc1.d"			,  "mtc1"				,  "abs.d"			,  "abs.s"			,
  "add.d"			,  "add.s"			,  "c.eq.d"			,  "c.eq.s"			,  "c.le.d"			,
  "c.le.s"		,  "c.lt.d"			,  "c.lt.s"			,  "cvt.d.s"		,  "cvt.d.w"		,
  "cvt.s.d"		,  "cvt.s.w"		,  "cvt.w.d"		,  "cvt.w.s"		,  "div.d"			,
  "div.s"			,  "l.d"				,  "l.s"				,  "mov.d"			,  "mov.s"			,
  "mul.d"			,  "mul.s"			,  "neg.d"			,  "neg.s"			,  "s.d"				,
  "s.s"				,  "sub.d"			,  "sub.s"			,  "li.s"				,  "rfe"				,
  "syscall"		,  "break"			,  "nop"
};

//////////////////////////////////////
//    lookup(-)     		            //
//  Looks up target operator in the //
//  operator database for the mips  //
//  language                        //
//////////////////////////////////////

const char * lookup(MOperator op) 
{
  return mips_op[op];
}
