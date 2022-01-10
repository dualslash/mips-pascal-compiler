#ifndef _MSTATEMENT_H
#define	_MSTATEMENT_H


#include "../parser/Symbol.h"
#include "MOperator.h"
#include "MOperand.h"

#include <string>


class MStatement 
{

	public:

		MStatement(MOperator op, const char * str = NULL);
		MStatement(MOperator op, MOperand * o1, const char * str = NULL);
		MStatement(MOperator op, MOperand * o1, MOperand * o2, const char * str = NULL);
		MStatement(MOperator op, MOperand * o1, MOperand * o2, MOperand * o3, const char * str = NULL);
		MStatement(MOperator op, string str);
		~MStatement();

		MOperator GetMOP();
		MOperand * GetOP1();
		MOperand * GetOP2();
		MOperand * GetOP3();
		const char * GetComment();
		string GetLabel();


	private:

		MOperator mop;
		MOperand * op1;
		MOperand * op2;
		MOperand * op3;
		const char * c;
		string label;
  
};


#endif
