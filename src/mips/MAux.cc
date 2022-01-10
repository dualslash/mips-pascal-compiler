/*
 * MBase.cc
 */
 

#include "CodeGenerator.h"


//////////////////////////////////////
//    Convert(-)                    //
//  Convert from register symbol to //
//  cache element                   //
//////////////////////////////////////

MOperand * CodeGenerator::Convert(IOperand * iop) 
{
  MOperand * op;
  MRegisterType cache;
  
  if(iop->GetOperandType() == OT_SYMBOL)
  {
    op = new MOperand(MT_REGISTER, magister.Register(iop->GetSymbol()));
  }
  else if(iop->GetOperandType() == OT_INT)
  {
    cache = magister.Cache();
    mips.Push(new MStatement(MOP_ADDI,
            	new MOperand(MT_REGISTER, cache),
            	new MOperand(MT_REGISTER, R_ZERO),
            	new MOperand(MT_INT, iop->GetIntValue()),
            	"[Add From Cache]"));

    op = new MOperand(MT_REGISTER, cache);
  }
  else if(iop->GetOperandType() == OT_REAL)
  {
    cache = magister.Cache();
    mips.Push(new MStatement(MOP_LI_S,
            	new MOperand(MT_REGISTER, cache),
            	new MOperand(MT_REAL, iop->GetRealValue()),
            	"[Load From Cache]"));

    op = new MOperand(MT_REGISTER, cache);
  }
  else
  	op = NULL;
    
  return (op);
}

//////////////////////////////////////
//    Offset(--)                    //
//  Offset the stack pointer        //
//////////////////////////////////////

MStatement * CodeGenerator::Offset(int val)
{  
  return (new MStatement(MOP_ADDI, 
					new MOperand(MT_REGISTER, R_SP), 
					new MOperand(MT_REGISTER, R_SP), 
				  new MOperand(MT_INT, val),
				  "[Stack Offset]"));
}

//////////////////////////////////////
//    NumOP(---)                    //
//  Template for numeric operators  //
//////////////////////////////////////

MStatement * CodeGenerator::NumOP(MOperator op, IStatement * s, const char * str) 
{
  return (new MStatement(op, 
  				Convert(s->GetResult()), 
  				Convert(s->GetOperand1()), 
  				Convert(s->GetOperand2()), 
  				str));
}

//////////////////////////////////////
//    NumUOP(---)                   //
//  Template for unary numeric      //
//  operators                       //
//////////////////////////////////////

MStatement * CodeGenerator::NumUOP(MOperator op, IStatement * s, const char * str)
{
  return (new MStatement(op, 
  				Convert(s->GetResult()), 
  				Convert(s->GetOperand1()), 
  				str));
}

//////////////////////////////////////
//    BranchOP(----)                //
//  Template for integer branch     // 
//  instructions                    //
//////////////////////////////////////

MStatement * CodeGenerator::BranchOP(MOperator op, IStatement * s, const char * str)
{
  magister.WriteBack();

  return (new MStatement(op, 
  				Convert(s->GetOperand1()), 
  				Convert(s->GetOperand2()), 
  				new MOperand(MT_LABEL, s->GetResult()->GetSymbol()->GetName()), 
  				str));
}

//////////////////////////////////////
//    BranchROP(----)               //
//  Template for float branch       //
//  instruction on the flag of the  //
//  float co-processor              //
//////////////////////////////////////

MStatement * CodeGenerator::BranchROP(MOperator op, IStatement * s, const char * str)
{  
  return (new MStatement(op,
  				Convert(s->GetOperand1()),
  				Convert(s->GetOperand2()),
  				str));
}
