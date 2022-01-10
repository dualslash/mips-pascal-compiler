/*
 * MStatement.cc
 */


#include "MStatement.h"


//////////////////////////////////////
//    MStatement(---)               //
//  Initialize the mips statement   //
//  type                            //
//////////////////////////////////////

MStatement::MStatement(MOperator op, const char * str) 
{
  mop = op;
  op1 = NULL;
  op2 = NULL;
  op3 = NULL;
  c = str;
}

MStatement::MStatement(MOperator op, MOperand * o1, const char * str) 
{
  mop = op;
  op1 = o1;
  op2 = NULL;
  op3 = NULL;
  c = str;
}

MStatement::MStatement(MOperator op, MOperand * o1,  MOperand * o2, const char * str) 
{
  mop = op;
  op1 = o1;
  op2 = o2;
  op3 = NULL;
  c = str;
}

MStatement::MStatement(MOperator op, MOperand * o1, MOperand * o2, MOperand * o3, const char * str) 
{
  mop = op;
  op1 = o1;
  op2 = o2;
  op3 = o3;
  c = str;
}

MStatement::MStatement(MOperator op, string str) 
{
  mop = op;
  op1 = NULL;
  op2 = NULL;
  op3 = NULL;
  label = str;
}

MStatement::~MStatement() 
{
  delete c;
}

//////////////////////////////////////
//    GetMOP()                      //
//  Returns the statement operator  //
//////////////////////////////////////

MOperator MStatement::GetMOP() 
{
  return mop;
}

//////////////////////////////////////
//    GetOP1()                      //
//  Returns statement operand one   //
//////////////////////////////////////

MOperand *MStatement::GetOP1() 
{
  return op1;
}

//////////////////////////////////////
//    GetOP2()                      //
//  Returns statement operand two   //
//////////////////////////////////////

MOperand *MStatement::GetOP2() 
{
  return op2;
}

//////////////////////////////////////
//    GetOP3()                      //
//  Returns statement operand three //
//////////////////////////////////////

MOperand *MStatement::GetOP3() 
{
  return op3;
}

//////////////////////////////////////
//    GetComment()                  //
//  Returns statement descriptor    //
//////////////////////////////////////

const char * MStatement::GetComment() 
{
  return c;
}

//////////////////////////////////////
//    GetLabel()                    //
//  Returns statement label         //
//////////////////////////////////////

string MStatement::GetLabel() 
{
  return label;
}

