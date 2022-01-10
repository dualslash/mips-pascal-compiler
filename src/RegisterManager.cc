/*
 * RegisterManager.cc
 */
 
#include "RegisterManager.h"

#include <cstdlib>


extern bool IsGlobal(Symbol * sym);


//////////////////////////////////////
//    RegisterManager(--)           //
//  Initialize Register for target  //
//  StackFrame and Assembly Code    //
//////////////////////////////////////

RegisterManager::RegisterManager(StackFrameManager & stackframe, MIPS & mips)
	: rx(0), stackframe(stackframe), mips(mips), 
		int_register(), float_register() {}

RegisterManager::~RegisterManager() {}

//////////////////////////////////////
//    Search(---)                   //
//  Find index of target symbol in  //
//  target register type with datas //
//  length step size                //
//////////////////////////////////////

int RegisterManager::Search(Symbol * sym, Symbol * symt[], int length) 
{
  for (int i = 0; i < length; ++i) 
  	if(symt[i] != NULL)
    	if (symt[i]->GetName() == sym->GetName()) 
      	return i;
  
  return -1;
}

//////////////////////////////////////
//    Available(--)                 //
//  Find index of empty register of // 
//  target register type with data  //
//  length step size                //
//////////////////////////////////////

int RegisterManager::Available(Symbol * symt[], int length) 
{
  for (int i = 0; i < length; ++i) 
    if (symt[i] == NULL) 
      return i;
  
  return -1;
}

//////////////////////////////////////
//    WriteBack()                   //
//  Clears all non-empty registers  //
//  and writes back instances to    //
//  the memory                      //
//////////////////////////////////////

void RegisterManager::WriteBack() 
{
  for (int i = 0; i < int_register_size; i++) 
    if (int_register[i] != NULL) 
    {
	  	WriteInt(int_registers[i], int_register[i]);
			int_register[i] = NULL;
    }
      
  for (int i = 0; i < float_register_size; i++) 
    if (float_register[i] != NULL) 
    {
      WriteFloat(float_registers[i], float_register[i]);
  		float_register[i] = NULL;
    }
}

//////////////////////////////////////
//    Cache()                       //
//  Local registery cache that      //
//  cycles between four elements,   //
// returns using MRU architecture   //
//////////////////////////////////////

MRegisterType RegisterManager::Cache()
{
  rx = (rx + 1) % 4;
  return(cache[rx]);
}

//////////////////////////////////////
//    GetRegister(-)                //
//  Get float or integer type from  //
//  the register, default to int    //
//////////////////////////////////////

MRegisterType RegisterManager::Register(Symbol * sym) 
{
  if (sym->GetReturnType() == RT_REAL) 
    return FloatRegister(sym);
	else
  	return IntRegister(sym);
}

//////////////////////////////////////
//    IntRegister(-)                //
//  Find target symbol in integer   //
//  register, if symbol cannot be   //
//  found add it to unused register //
//////////////////////////////////////

MRegisterType RegisterManager::IntRegister(Symbol * sym) 
{
  int reg = Search(sym, int_register, int_register_size);
  
  if (reg != -1) 
    return int_registers[reg];
    
  reg = Available(int_register, int_register_size);
  if (reg == -1) 
  {
    reg = rand() % int_register_size;
    WriteInt(int_registers[reg], int_register[reg]);
  	int_register[reg] = NULL;
  }
  
  LoadInt(int_registers[reg], sym);
  int_register[reg] = sym;
  
  return int_registers[reg];
}

//////////////////////////////////////
//    FloatRegister(-)              //
//  Find target symbol in float     //
//  register, if symbol cannot be   //
//  found add it to unused register //
//////////////////////////////////////

MRegisterType RegisterManager::FloatRegister(Symbol * sym) 
{
  int reg = Search(sym, float_register, float_register_size);
  
  if (reg != -1) 
    return float_registers[reg];
  
  reg = Available(float_register, float_register_size);
  if (reg == -1) 
  {
    reg = rand() % float_register_size;
    WriteFloat(float_registers[reg], float_register[reg]);
  	float_register[reg] = NULL;
  }
  
  LoadFloat(float_registers[reg], sym);
  float_register[reg] = sym;
  
  return float_registers[reg];
}

//////////////////////////////////////
//    WriteInt(--)                  //
//  Write integer value from the    //
//  register to the memory          //
//////////////////////////////////////

void RegisterManager::WriteInt(MRegisterType reg, Symbol * sym) 
{
  if (IsGlobal(sym)) 
  {
    MOperand * op1 = new MOperand(MT_REGISTER, reg);
    MOperand * op2 = new MOperand(MT_LABEL, SYMBOL_PREFIX + sym->GetName());
    mips.Push(new MStatement(MOP_SW, op1, op2, "[Global Int Reg->Mem]"));
  } 
  	else 
  {
    MOperand * op1 = new MOperand(MT_REGISTER, reg);
    MOperand * op2 = new MOperand(MT_OFFSET, R_FP, sym->GetOffset());
    mips.Push(new MStatement(MOP_SW, op1, op2, "[Int Reg->Mem]"));
  }
}


//////////////////////////////////////
//    WriteFloat(--)                //
//  Write float value from the      //
//  register to the memory          //
//////////////////////////////////////

void RegisterManager::WriteFloat(MRegisterType reg, Symbol * sym)
{
  if (IsGlobal(sym)) 
  {
    MOperand * op1 = new MOperand(MT_REGISTER, reg);
    MOperand * op2 = new MOperand(MT_LABEL, SYMBOL_PREFIX + sym->GetName());
    mips.Push(new MStatement(MOP_S_S, op1, op2, "[Global Float Reg->Mem]"));
  } 
  	else 
  {
    MOperand * op1 = new MOperand(MT_REGISTER, reg);
    MOperand * op2 = new MOperand(MT_OFFSET, R_FP, sym->GetOffset());
    mips.Push(new MStatement(MOP_S_S, op1, op2, "[Float Reg->Mem]"));
  }
}

//////////////////////////////////////
//    LoadInt(--)                   //
//  Load integer value from the     //
//  memory to the register          //
//////////////////////////////////////

void RegisterManager::LoadInt(MRegisterType reg, Symbol * sym)
{
  if (IsGlobal(sym)) 
  {
    MOperand * op1 = new MOperand(MT_REGISTER, reg);
    MOperand * op2 = new MOperand(MT_LABEL, SYMBOL_PREFIX + sym->GetName());
    mips.Push(new MStatement(MOP_LW, op1, op2, "[Global Int Mem->Reg]"));
  } 
  	else 
  {
    MOperand * op1 = new MOperand(MT_REGISTER, reg);
    MOperand * op2 = new MOperand(MT_OFFSET, R_FP, sym->GetOffset());
    mips.Push(new MStatement(MOP_LW, op1, op2, "[Int Mem->Reg]"));
  }
}

//////////////////////////////////////
//    LoadFloat(--)                 //
//  Load float value from the       //
//  memory to the register          //
//////////////////////////////////////

void RegisterManager::LoadFloat(MRegisterType reg, Symbol * sym)
{
  if (IsGlobal(sym)) 
  {
    MOperand * op1 = new MOperand(MT_REGISTER, reg);
    MOperand * op2 = new MOperand(MT_LABEL, SYMBOL_PREFIX + sym->GetName());
    mips.Push(new MStatement(MOP_L_S, op1, op2, "[Global Float Mem->Reg]"));
  } 
  	else 
  {
    MOperand * op1 = new MOperand(MT_REGISTER, reg);
    MOperand * op2 = new MOperand(MT_OFFSET, R_FP, sym->GetOffset());
    mips.Push(new MStatement(MOP_L_S, op1, op2, "[Float Mem->Reg]"));
  }
}
