/*
 * MCode.cc - Implementation of the MIPS code repository
 */


#include "MCode.h"


extern int msglevel;


//////////////////////////////////////
//    MIPS()                        //
//  Initialize the mips repository  //
//////////////////////////////////////

MIPS::MIPS() 
	: mips(0) {}
MIPS::~MIPS() {}


//////////////////////////////////////
//    Count()                       //
//  Returns size of mips repository //
//////////////////////////////////////

int MIPS::Count() 
{
  return(mips.size());
}


//////////////////////////////////////
//    Push(-)                       //
//  Adds mips statement to the      //
//  repository                      //
//////////////////////////////////////

void MIPS::Push(MStatement * s) 
{
  mips.push_back(s);
}


//////////////////////////////////////
//    Output(-)                     //
//  Outputs the mips repository to  //
//  the specified output file       //
//////////////////////////////////////

void MIPS::Output(FILE *file) 
{
  msglevel = 100;
  
  for (int i = 0; i < Count(); ++i) 
  {
    MStatement * s = mips.at(i);
    string label = s->GetLabel();
    
    const char * h = "";
    const char * c = s->GetComment();
    const char * op = lookup(s->GetMOP());
    
    if (c == NULL) 
      c = "";
    else
    	h = "\t# ";

    if (s->GetMOP() == MOP_LABEL) 
    {
      pmesg(100, "[LABEL %s]\n", label.c_str());
      fprintf(file, "%s:\n", 
      				label.c_str());
      continue;
    }

    pmesg(100, "[STATEMENT %s]\n", op);
    if (s->GetOP1() == NULL)
    {
      fprintf(file, "%s\t%s\t%s%s\n", 
      				label.c_str(), op, h, c);
      continue;
    }

    string op1 = OutputOP(s->GetOP1());
    if (s->GetOP2() == NULL) 
    {
      fprintf(file, "%s\t%s\t%s\t%s%s\n", 
      				label.c_str(), op, op1.c_str(), h, c);
      continue;
    }

    string op2 = OutputOP(s->GetOP2());
    if (s->GetOP3() == NULL) 
    {
      fprintf(file, "%s\t%s\t%s, %s\t%s%s\n", 
      				label.c_str(), op, op1.c_str(), op2.c_str(), h, c);
      continue;
    }

    string op3 = OutputOP(s->GetOP3());
    fprintf(file, "%s\t%s\t%s, %s, %s\t%s%s\n", 
    				label.c_str(), op, op1.c_str(), op2.c_str(), op3.c_str(), h, c);
  }
}

//////////////////////////////////////
//    OutputOP(-)                   //
//  Outputs the mips statement      //
//  operands to the output stream   //
//////////////////////////////////////

string MIPS::OutputOP(MOperand * op) 
{
  stringstream ss;
  
  switch (op->GetOperandType()) 
  {
    case MT_INT:
    {
      pmesg(100, "\tOP_INT");
      ss << op->GetIntValue();
      break;
    }
    
    case MT_REAL:
    {
      pmesg(100, "\tOP_REAL");
      ss << showpoint << op->GetRealValue();
      break;
    }
    
    case MT_OFFSET:
    {
      pmesg(100, "\tOP_OFFSET");
      ss << op->GetOffset() << '(' 
      	 << reglookup(op->GetRegisterType()) << ')';
      break;

    }
    
    case MT_REGISTER:
    {
      pmesg(100, "\tOP_REGISTER");
      ss << reglookup(op->GetRegisterType());
      break;
    }
    
    case MT_ADDRESS:
    {
      pmesg(100, "\tOP_ADDRESS");
      ss << op->GetAddress();
      break;
    }
    
    case MT_LABEL:
    {
      pmesg(100, "\tOP_LABEL");
      ss << op->GetLabel();
      break;
    }
    
    default:
    {
    	pmesg(100,"WARNING: Unknown IOP");
    	break;
    }
  }
  
  pmesg(100, " - %s\n", ss.str().c_str());
  return (ss.str());
}

