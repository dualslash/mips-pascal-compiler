/*
 * IOperator.h
 */

#ifndef _IOPERATOR_H_
#define _IOPERATOR_H_

typedef enum __ioperator {
  /* Meta */
  IOP_UNKNOWN,             // [---] (yet) Unknown operation
  
  /* Subprogram entry
     operand1  should refer to the corresponding Symbol_Subprogram object */
  IOP_SUBPROG,             // [1--] Subprogram
   
  /* Subprogram return
     operand1  should contain the value that has to be returned */
  IOP_RETURN,              // [---] Procedure return
  IOP_RETURN_I,            // [1--] Integer function return
  IOP_RETURN_R,            // [1--] Real function return
  
  /* Parameter passing (caller side)
     operand1  actual parameter value or Symbol object */
  IOP_PARAM_I,             // [1--] Integer parameter
  IOP_PARAM_R,             // [1--] Real parameter
  
  /* Subprogram call
     operand1  should refer to the corresponding Symbol object
     result    receives the result of a function call */
  IOP_PROCCALL,            // [1--] Procedure call
  IOP_FUNCCALL,            // [1-r] Function call
  
  /* Label
     operand1  should refer to the corresponding Symbol object */
  IOP_LABEL,               // [1--] Label
  
  /* Goto
     operand1  should refer to the corresponding Symbol object; note that
               the Symbol pointed to should be of type ST_LABEL */
  IOP_GOTO,                // [1--] Goto a label
  
  /* Variable assignment (copy value)
     operand1  the source operand
     result    the destination operand (pointer to a Symbol object) */
  IOP_ASSIGN_I,            // [1-r] Integer assignment
  IOP_ASSIGN_R,            // [1-r] Real assignment
  
  /* Branching
     operand1  the first source operand
     operand2  the second source operand
     result    should refer to the target Symbol object; note that
               the Symbol pointed to must be of type ST_LABEL */
  IOP_BEQ_I,               // [12r] = operator for integers
  IOP_BLT_I,               // [12r] < operator for integers
  IOP_BGT_I,               // [12r] > operator for integers
  IOP_BLE_I,               // [12r] <= operator for integers
  IOP_BGE_I,               // [12r] >= operator for integers
  IOP_BNE_I,               // [12r] <> operator for integers
  IOP_BEQ_R,               // [12r] = operator for reals
  IOP_BLT_R,               // [12r] < operator for reals
  IOP_BGT_R,               // [12r] > operator for reals
  IOP_BLE_R,               // [12r] <= operator for reals
  IOP_BGE_R,               // [12r] >= operator for reals
  IOP_BNE_R,               // [12r] <> operator for reals
  
  /* Binary arithmetic operators
     operand1  the first source operand
     operand2  the second source operand
     result    the destination operand (refers to a Symbol object) */
  IOP_ADD_I,               // [12r] Integer addition
  IOP_ADD_R,               // [12r] Real addition
  IOP_SUB_I,               // [12r] Integer subtraction
  IOP_SUB_R,               // [12r] Real subtraction
  IOP_MUL_I,               // [12r] Integer multiplication
  IOP_MUL_R,               // [12r] Real multiplication
  IOP_DIV_I,               // [12r] Integer division
  IOP_DIV_R,               // [12r] Real division
  IOP_MOD,                 // [12r] Modulo
  IOP_AND,                 // [12r] AND operation
  IOP_OR,                  // [12r] OR operation
  
  /* Unary arithmetic operators
     operand1  the source operand
     result    the destination operand (refers to a Symbol object) */
  IOP_NOT,                 // [1-r] NOT operation
  IOP_UNARY_MINUS_I,       // [1-r] Unary integer minus
  IOP_UNARY_MINUS_R,       // [1-r] Unary real minus
  
  /* Coercion
     operand1  the source operand
     result    the destination operand (refers to a Symbol object) */
  IOP_INT_TO_REAL          // [1-r] Int to Real coercion
} IOperator;


const char *IOperatorToString(IOperator op);


#endif
