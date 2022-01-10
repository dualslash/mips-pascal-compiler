#ifndef _MCODE_H
#define	_MCODE_H


#define SYMBOL_PREFIX "id_"


#include "MStatement.h"
#include "../utils/debug.h"
#include "MRegister.h"

#include <sstream>
#include <cstdio>
#include <vector>
#include <string>


class MIPS 
{

  public:
  
    MIPS();
    ~MIPS();

    void Push(MStatement * s);
    void Output(FILE * file);


  private:
  
    vector<MStatement*> mips;
    
    int Count();
    string OutputOP(MOperand *operand);
    
};


#endif
