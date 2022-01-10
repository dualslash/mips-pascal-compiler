/*
 * StackFrameManager.cc
 */
 

#include "StackFrameManager.h"

#include <cstdio>


//////////////////////////////////////
//    StackFrameManager(-)          //
//  Initialize stackframe manager   //
//  for target Assembly Code        //
//////////////////////////////////////

StackFrameManager::StackFrameManager(MIPS & mips)
	: reg(12), frame(reg), subframe(reg), frameoffset(4),
		stack(NULL), mips(mips) {}

StackFrameManager::~StackFrameManager() {}

//////////////////////////////////////
//    AnalyzeSubprogram(--)         //
//  Analyzes a subprogram and       //
// computes the stack frame layout  //
//////////////////////////////////////

void StackFrameManager::AnalyzeSubprogram(SymbolTable * symtab, Symbol * subprogram) 
{
	frame = reg;
  subframe = frame;
  stack = subprogram;
  
  int offset = frameoffset;
  subprogram->SetOffset(-2 * frameoffset);

  if(!(subprogram->GetSymbolType() == ST_PROGRAM)) 
  {
    for(int i = 0; i < (int)subprogram->GetParameterCount(); i++) 
    {
      subprogram->GetParameter(i)->SetOffset(offset);
      offset += frameoffset;
      frame += frameoffset;
    }
    
    Scope * scope = symtab->GetScope(subprogram->GetName());
    offset = -3 * frameoffset;
    
    for(int i = 0; i < (int)scope->GetNumberOfSymbols(); i++) 
    {
      Symbol * sym = scope->GetSymbol(i);
      
      if (sym->GetSymbolType() == ST_VARIABLE ||
      		sym->GetSymbolType() == ST_TEMPVAR) 
      {
        sym->SetOffset(offset);
        offset -= frameoffset;
        frame += frameoffset;
        subframe += frameoffset;
      }
    }
  }
  	else 
  {
    Scope * scope = symtab->GetScope(subprogram->GetName());
    offset = -3 * frameoffset;
    
    for(int i = 0; i < (int)scope->GetNumberOfSymbols(); i++) 
    {
      Symbol * sym = scope->GetSymbol(i);
      
      if(sym->GetSymbolType() == ST_TEMPVAR) 
      {
        sym->SetOffset(offset);
        offset -= frameoffset;
        frame += frameoffset;
        subframe += frameoffset;
      }
    }
  }

}

//////////////////////////////////////
//    GeneratePrologue(-)           //
// Generates the code that sets up  //
// the stack frame at the entry     //
// point of a subprogram            //
//////////////////////////////////////

void StackFrameManager::GeneratePrologue(FILE *) 
{
  mips.Push(new MStatement(MOP_ENT,
  					new MOperand(MT_LABEL,
  					string(SYMBOL_PREFIX) + stack->GetName())));
  
  mips.Push(new MStatement(MOP_LABEL,
  					string(SYMBOL_PREFIX) + stack->GetName()));
  
  mips.Push(new MStatement(MOP_SW,
  					new MOperand(MT_REGISTER, R_RA), 
  					new MOperand(MT_OFFSET, R_SP, 0),
  					"[Construct Stack Frame]"));
    
  mips.Push(new MStatement(MOP_SW,
						new MOperand(MT_REGISTER, R_FP),
						new MOperand(MT_OFFSET, R_SP, -4)));
  
  mips.Push(new MStatement(MOP_MOVE,
  					new MOperand(MT_REGISTER, R_FP),
  					new MOperand(MT_REGISTER, R_SP)));
  
  mips.Push(new MStatement(MOP_ADDI,
  					new MOperand(MT_REGISTER, R_SP),
  					new MOperand(MT_REGISTER, R_SP),
  					new MOperand(MT_INT, -subframe),
  					"[Function Body]"));
}

//////////////////////////////////////
//    GenerateEpilogue(-)           //
// Generates the code that discards //
// the stack frame at the leaving   //
// point of a subprogram            //
//////////////////////////////////////

void StackFrameManager::GenerateEpilogue(FILE *) 
{
  mips.Push(new MStatement(MOP_LW, 
						new MOperand(MT_REGISTER, R_RA), 
						new MOperand(MT_OFFSET, R_FP, 0),
						"[Deconstruct Stack Frame]"));
											 
  mips.Push(new MStatement(MOP_LW, 
  					new MOperand(MT_REGISTER, R_FP), 
  					new MOperand(MT_OFFSET, R_FP, -4)));
  										 
  mips.Push(new MStatement(MOP_ADDI,
  					new MOperand(MT_REGISTER, R_SP), 
  					new MOperand(MT_REGISTER, R_SP), 
  					new MOperand(MT_INT, frame)));
  
  mips.Push(new MStatement(MOP_JR, 
  					new MOperand(MT_REGISTER, R_RA),
  					"[Function Return]"));
  
  mips.Push(new MStatement(MOP_END, 
  					new MOperand(MT_LABEL, 
  					string(SYMBOL_PREFIX) + stack->GetName())));
}

//////////////////////////////////////
//    GenerateLocalAddress(--)      //
// Generates a $fp-relative address //
// for local variable or parameter  //
//////////////////////////////////////

void StackFrameManager::GenerateLocalAddress(FILE * out, Symbol * sym) 
{
  fprintf(out, "%d($fp)", sym->GetOffset());
}
