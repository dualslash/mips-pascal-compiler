#ifndef _MOPERAND_H
#define	_MOPERAND_H


#include <cstdio>
#include "../icode/IOperand.h"
#include "MRegister.h"
#include <string>
#include <climits>


typedef enum mips_type 
{
  MT_INT,
  MT_REAL,
  MT_LABEL,
  MT_REGISTER,
  MT_ADDRESS,
  MT_OFFSET,
  MT_UNKNOWN
} MOperandType;

class MOperand 
{

   public:
   
    MOperand(MOperandType t, int value);
    MOperand(MOperandType t, float value);
    MOperand(MOperandType t, MRegisterType reg);
    MOperand(MOperandType t, string str);
    MOperand(MOperandType t, MRegisterType reg, int offset);
    ~MOperand();

    MOperandType GetOperandType();
    int GetIntValue();
    float GetRealValue();
    int GetRegisterNumber();
    MRegisterType GetRegisterType();
    void SetOffset(int value);
    int GetOffset();
    void SetAddress(int value);
    void SetAddress(MRegisterType value);
    int GetAddress();
    void SetLabel(string str);
    string GetLabel();


  private:
  
    int intval;
    float floatval;
    int regnum;
    int offset;
    int address;
    
    string label;
    MOperandType type;
    
 };
 

#endif
