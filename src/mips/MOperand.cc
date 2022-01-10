/*
 * MOperand.cc
 */
 
 
#include "MOperand.h"


//////////////////////////////////////
//    MOperand(---)                 //
//  Initialize the mips operand     //
//  type                            //
//////////////////////////////////////

MOperand::MOperand(MOperandType t, int value) 
{
  type = t;
  intval = value;
  SetOffset(INT_MIN);
}

MOperand::MOperand(MOperandType t, float value) 
{
  type = t;
  floatval = value;
  SetOffset(INT_MIN);
}

MOperand::MOperand(MOperandType t, MRegisterType reg) 
{
  type = t;
  regnum = (int)reg;
  SetOffset(INT_MIN);
}

MOperand::MOperand(MOperandType t, string str) 
{
  type = t;
  label = str;
  SetOffset(INT_MIN);
}

MOperand::MOperand(MOperandType t, MRegisterType reg, int offset) 
{
  type = t;
  regnum = (int)reg;
  SetOffset(offset);
}

//////////////////////////////////////
//    GetOperandType()              //
//  Returns the operand type        //
//////////////////////////////////////

MOperandType MOperand::GetOperandType() 
{
  return (type);
}

//////////////////////////////////////
//    GetIntValue()                 //
//  Returns integer value           //
//////////////////////////////////////

int MOperand::GetIntValue() 
{
  return (intval);
}

//////////////////////////////////////
//    GetRealValue()                //
//  Returns float value             //
//////////////////////////////////////

float MOperand::GetRealValue() 
{
  return (floatval);
}

//////////////////////////////////////
//    GetRegisterType()             //
//  Returns the register type       //
//////////////////////////////////////

MRegisterType MOperand::GetRegisterType() 
{
  return ((MRegisterType) regnum);
}

//////////////////////////////////////
//    SetOffset(-)                  //
//  Sets the operand stack offset   //
//////////////////////////////////////

void MOperand::SetOffset(int value) 
{
  offset = value;
}

//////////////////////////////////////
//    GetOffset()                   //
//  Returns the operand stack       //
//  offset                          //
//////////////////////////////////////

int MOperand::GetOffset() 
{
  return (offset);
}

//////////////////////////////////////
//    SetAddress(-)                 //
//  Sets the operand address        //
//////////////////////////////////////

void MOperand::SetAddress(int reg) 
{
  address = reg;
}

void MOperand::SetAddress(MRegisterType reg) 
{
  address = (int)reg;
}

//////////////////////////////////////
//    GetAddress()                  //
//  Returns the operand address     //
//////////////////////////////////////

int MOperand::GetAddress() 
{
  return (address);
}

//////////////////////////////////////
//    SetLabel(-)                   //
//  Sets the operand label          //
//////////////////////////////////////

void MOperand::SetLabel(string str) 
{
  label = str;
}

//////////////////////////////////////
//    GetLabel()                    //
//  Returns the operand label       //
//////////////////////////////////////

string MOperand::GetLabel() 
{
  return (label);
}


