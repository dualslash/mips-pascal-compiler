#ifndef _MOPERATOR_H
#define	_MOPERATOR_H


typedef enum mop 
{
  MOP_ENT			,	 MOP_END			,	 MOP_ALIGN		,	 MOP_ASCII		,	 MOP_ASCIIZ		,
  MOP_BYTE		,  MOP_DATA			,  MOP_DOUBLE		,  MOP_EXTERN		,  MOP_FLOAT		,
  MOP_GLOBL		,  MOP_HALF			,  MOP_KDATA		,  MOP_KTEXT		,  MOP_SPACE		,
  MOP_TEXT		,  MOP_WORD			,  MOP_ABS			,  MOP_ADD			,  MOP_ADDI			,
  MOP_ADDU		,  MOP_ADDIU		,  MOP_AND			,  MOP_ANDI			,  MOP_DIV2			,
  MOP_DIV2U		,  MOP_DIV			,  MOP_DIVU			,  MOP_MUL			,  MOP_MULO			,
  MOP_MULOU		,  MOP_MULT			,  MOP_MULTU		,  MOP_NEG			,  MOP_NEGU			,
  MOP_NOR			,  MOP_NOT			,  MOP_OR				,  MOP_ORI			,  MOP_REM			,
  MOP_REMU		,  MOP_ROL			,  MOP_ROR			,  MOP_SLL			,  MOP_SLLV			,
  MOP_SRA			,  MOP_SRL			,  MOP_SRLV			,  MOP_SUB			,  MOP_SUBU			,
  MOP_XOR			,  MOP_XORI			,  MOP_LI				,  MOP_LUI			,  MOP_SEQ			,
  MOP_SGE			,  MOP_SGEU			,  MOP_SGT			,  MOP_SGTU			,  MOP_SLE			,
  MOP_SLEU		,  MOP_SLT			,  MOP_SLTI			,  MOP_SLTU			,  MOP_SLTIU		,
  MOP_SNE			,  MOP_B				,  MOP_BCZT			,  MOP_BCZF			,  MOP_BEQ			,
  MOP_BEQZ		,  MOP_BGE			,  MOP_BGEU			,  MOP_BGEZ			,  MOP_BGEZAL		,
  MOP_BGT			,  MOP_BGTU			,  MOP_BGTZ			,  MOP_BLE			,  MOP_BLEU			,
  MOP_BLEZ		,  MOP_BLTZAL		,  MOP_BLT			,  MOP_BLTU			,  MOP_BLTZ			,
  MOP_BNE			,  MOP_BNEZ			,  MOP_J				,  MOP_JAL			,  MOP_JR				,
  MOP_LA			,  MOP_LB				,  MOP_LBU			,  MOP_LD				,  MOP_LH				,
  MOP_LHU			,  MOP_LW				,  MOP_LWCZ			,  MOP_LWL			,  MOP_LWR			,
  MOP_ULH			,  MOP_ULHU			,  MOP_ULW			,  MOP_SB				,  MOP_SD				,
  MOP_SH			,  MOP_SW				,  MOP_SWCZ			,  MOP_SWL			,  MOP_SWR			,
  MOP_USH			,  MOP_USW			,  MOP_MOVE			,  MOP_MFHI			,  MOP_MTLO			,
  MOP_MFC1		,  MOP_MFC1_D		,  MOP_MTC1			,  MOP_ABS_D		,  MOP_ABS_S		,
  MOP_ADD_D		,  MOP_ADD_S		,  MOP_C_EQ_D		,  MOP_C_EQ_S		,  MOP_C_LE_D		,
  MOP_C_LE_S	,  MOP_C_LT_D		,  MOP_C_LT_S		,  MOP_CVT_D_S	,  MOP_CVT_D_W	,
  MOP_CVT_S_D	,  MOP_CVT_S_W	,  MOP_CVT_W_D	,  MOP_CVT_W_S	,  MOP_DIV_D		,
  MOP_DIV_S		,  MOP_L_D			,  MOP_L_S			,  MOP_MOV_D		,  MOP_MOV_S		,
  MOP_MUL_D		,  MOP_MUL_S		,  MOP_NEG_D		,  MOP_NEG_S		,  MOP_S_D			,
  MOP_S_S			,  MOP_SUB_D		,  MOP_SUB_S		,  MOP_LI_S			,  MOP_RFE			,
  MOP_SYSCALL	,  MOP_BREAK		,  MOP_NOP			,  MOP_LABEL		,  MOP_NOPERATORS
} MOperator;


const char * lookup(MOperator op);


#endif
