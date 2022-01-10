#ifndef _STACKFRAMEMANAGER_H_
#define _STACKFRAMEMANAGER_H_


#include "parser/SymbolTable.h"
#include "mips/MCode.h"
#include "mips/MRegister.h"
#include "mips/MOperator.h"
#include "mips/MOperand.h"


class StackFrameManager 
{

  public:
  
    StackFrameManager(MIPS & mips);
    ~StackFrameManager();

    void AnalyzeSubprogram(SymbolTable * symtab, Symbol * subprogram);
    void GeneratePrologue(FILE * out);
    void GenerateEpilogue(FILE * out);
    void GenerateLocalAddress(FILE * out, Symbol * sym);


  private:

		int reg;
    int frame;
    int subframe;
    int frameoffset;

    Symbol * stack;
    MIPS & mips;
    
};


#endif
