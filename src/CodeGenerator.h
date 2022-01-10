#ifndef _CODEGENERATOR_H_
#define _CODEGENERATOR_H_


#include "parser/SymbolTable.h"
#include "icode/IntermediateCode.h"
#include "icode/IStatement.h"
#include "mips/MCode.h"
#include "mips/MStatement.h"
#include "mips/MRegister.h"
#include "utils/debug.h"

#include "StackFrameManager.h"
#include "RegisterManager.h"


class CodeGenerator 
{

	public:
	
		CodeGenerator();
		~CodeGenerator();

		void GenerateHeader(FILE * out);
		void GenerateGlobalDecls(FILE * out, SymbolTable * symtab, IntermediateCode * inputCode);
		void GenerateCode(FILE * out, SymbolTable * symtab, IntermediateCode * inputCode);
		void GenerateTrailer(FILE * out);
		void Write(FILE * out);
		

	private:
	
		MIPS mips;
		StackFrameManager stackframe;
		RegisterManager magister;
		
		////////////////////////////////////////////////////
		// Function set of the MIPS specific architecture //
		////////////////////////////////////////////////////
		
		void MGenerator(FILE *out, SymbolTable * symtab, 
										IntermediateCode * inputCode, IStatement * iop);
										
		MOperand 	 * Convert(IOperand * iop);
		MStatement * Offset(int val);
		
		MStatement * NumOP(MOperator op, IStatement * s, const char * str = NULL);
		MStatement * NumUOP(MOperator op, IStatement * s, const char * str = NULL);
		MStatement * BranchOP(MOperator op, IStatement * s, const char * str = NULL);
		MStatement * BranchROP(MOperator op, IStatement * s, const char * str = NULL);

};


#endif
