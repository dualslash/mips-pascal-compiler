#ifndef REGISTERMANAGER_H
#define REGISTERMANAGER_H


#include "StackFrameManager.h"
#include "parser/Symbol.h"
#include "parser/types.h"
#include "mips/MCode.h"
#include "mips/MRegister.h"
#include "utils/debug.h"


class RegisterManager 
{

	public:

		RegisterManager(StackFrameManager & stackframe, MIPS & mips);
		~RegisterManager();
		
		int Search(Symbol * sym, Symbol * symt[], int length);
		int Available(Symbol * symt[], int length);
		void WriteBack();
		
		MRegisterType Register(Symbol * sym);
		MRegisterType Cache();

		
	private:

		int rx;

		StackFrameManager & stackframe;
		MIPS & mips;
		
		Symbol * int_register[int_register_size]; 
		Symbol * float_register[float_register_size];
		
		MRegisterType IntRegister(Symbol * sym);
		MRegisterType FloatRegister(Symbol * sym);
		
		void WriteInt(MRegisterType reg, Symbol * sym);
		void WriteFloat(MRegisterType reg, Symbol * sym);
		void LoadInt(MRegisterType reg, Symbol * sym);
		void LoadFloat(MRegisterType reg, Symbol * sym);
  
};


#endif
