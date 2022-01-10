/*
 * MBase.cc
 */
 

#include "CodeGenerator.h"


//////////////////////////////////////
//    MGenerator(----)              //
//  Converts target IOP to the MIPS //
//  equivalent from the code base   //
//////////////////////////////////////

void CodeGenerator::MGenerator(FILE *out, SymbolTable * symtab, IntermediateCode * inputCode, IStatement * iop)
{
  switch (iop->GetOperator()) 
  {
    case IOP_LABEL:
    {
  	  mips.Push(new MStatement(MOP_LABEL,
								string(iop->GetOperand1()->GetSymbol()->GetName().c_str()))); 
    	break;
    }
  
    case IOP_SUBPROG:
    {
      stackframe.AnalyzeSubprogram(symtab, iop->GetOperand1()->GetSymbol());
      stackframe.GeneratePrologue(out);
      break;
    }
    
    case IOP_GOTO:
    {
      magister.WriteBack();

      mips.Push(new MStatement(MOP_J, 
      					new MOperand(MT_LABEL, 
      					iop->GetOperand1()->GetSymbol()->GetName().c_str()),
      					"[Jump]"));
      break;
    }
    
    case IOP_PROCCALL:
    {
      magister.WriteBack();
      
      mips.Push(new MStatement(MOP_JAL,
              	new MOperand(MT_LABEL, 
              	string(SYMBOL_PREFIX) + 
              	iop->GetOperand1()->GetSymbol()->GetName().c_str()),
              	"[Jump And Link]"));
      break;
    }
    
    case IOP_FUNCCALL:
    {
      magister.WriteBack();

      mips.Push(new MStatement(MOP_JAL,
              	new MOperand(MT_LABEL, 
              	string(SYMBOL_PREFIX) + 
              	iop->GetOperand1()->GetSymbol()->GetName().c_str()),
              	"[Function Call]"));

      Symbol * symbol = iop->GetResult()->GetSymbol();
      
      if (symbol->GetReturnType() == RT_INT) 
      {
        mips.Push(new MStatement(MOP_MOVE,
                new MOperand(MT_REGISTER, magister.Register(symbol)),
                new MOperand(MT_REGISTER, R_V0),
                "[Move Integer Result]"));
      } 
      else 
      {
        mips.Push(new MStatement(MOP_MOV_S,
                new MOperand(MT_REGISTER, magister.Register(symbol)),
                new MOperand(MT_REGISTER, R_F0),
                "[Move Float Result]"));
      }
      break;
    }
    
    case IOP_RETURN:
    {
      magister.WriteBack();
      stackframe.GenerateEpilogue(out);
      break;
    }
    
    case IOP_RETURN_I:
    {
      magister.WriteBack();

      if (iop->GetOperand1()->GetOperandType() == OT_INT) 
      {
        mips.Push(new MStatement(MOP_ADDI,
	               	new MOperand(MT_REGISTER, R_V0),
	               	new MOperand(MT_REGISTER, R_ZERO),
	                new MOperand(MT_INT, iop->GetOperand1()->GetIntValue()),
	                "[Constant Integer Return]"));
      } 
      else 
      {
        MRegisterType reg = magister.Register(iop->GetOperand1()->GetSymbol());
        mips.Push(new MStatement(MOP_MOVE,
	                new MOperand(MT_REGISTER, R_V0),
	                new MOperand(MT_REGISTER, reg),
	                "[Integer Return]"));
      }

      stackframe.GenerateEpilogue(out);
      break;
    }
    
    case IOP_RETURN_R:
    {
      magister.WriteBack();
      
      if (iop->GetOperand1()->GetOperandType() == OT_REAL) 
      {
        mips.Push(new MStatement(MOP_LI_S,
                	new MOperand(MT_REGISTER, R_F0),
                	new MOperand(MT_REAL, iop->GetOperand1()->GetRealValue()),
                	"[Constant Float Return]"));
      } 
      	else 
      {
        MRegisterType reg = magister.Register(iop->GetOperand1()->GetSymbol());
        mips.Push(new MStatement(MOP_MOV_S,
                	new MOperand(MT_REGISTER, R_F0),
                	new MOperand(MT_REGISTER, reg),
                	"[Float Return]"));
      }

      stackframe.GenerateEpilogue(out);
      break;
    }
    
    case IOP_PARAM_I:
    {
      if (iop->GetOperand1()->GetOperandType() == OT_INT) 
      {
        mips.Push(new MStatement(MOP_ADDI,
                	new MOperand(MT_REGISTER, R_V1),
                	new MOperand(MT_REGISTER, R_ZERO),
                	new MOperand(MT_INT, iop->GetOperand1()->GetIntValue()),
                	"[Constant Integer Parameter]"));

      }
      	else
      {
        MRegisterType reg = magister.Register(iop->GetOperand1()->GetSymbol());
        
        mips.Push(new MStatement(MOP_MOVE,
                	new MOperand(MT_REGISTER, R_V1),
                	new MOperand(MT_REGISTER, reg),
                	"[Integer Parameter]"));
      }

      mips.Push(new MStatement(MOP_SW,
             		new MOperand(MT_REGISTER, R_V1),
             		new MOperand(MT_OFFSET, R_SP, 0)));

      mips.Push(Offset(-4));
      break;
    }
    
    case IOP_PARAM_R:
    {
      if (iop->GetOperand1()->GetOperandType() == OT_REAL) 
      {
        mips.Push(new MStatement(MOP_LI_S,
                	new MOperand(MT_REGISTER, R_F0),
                	new MOperand(MT_REAL, iop->GetOperand1()->GetRealValue()),
                	"[Constant Float Parameter]"));

      } 
      	else 
      {
        MRegisterType reg = magister.Register(iop->GetOperand1()->GetSymbol());
        mips.Push(new MStatement(MOP_MOV_S,
                	new MOperand(MT_REGISTER, R_F0),
                	new MOperand(MT_REGISTER, reg),
                	"[Float Parameter]"));
      }

      mips.Push(new MStatement(MOP_S_S,
              	new MOperand(MT_REGISTER, R_F0),
              	new MOperand(MT_OFFSET, R_SP, 0)));

      mips.Push(Offset(-4));
      break;
    }

    case IOP_ASSIGN_I:
    {
      MRegisterType reg = magister.Register(iop->GetResult()->GetSymbol());

      if (iop->GetOperand1()->GetOperandType() == OT_INT) 
      {
        mips.Push(new MStatement(MOP_ADDI,
                	new MOperand(MT_REGISTER, reg),
                	new MOperand(MT_REGISTER, R_ZERO),
                	new MOperand(MT_INT, iop->GetOperand1()->GetIntValue()),
                	"[Assign Constant Integer]"));
      } 
      else 
      {
        MRegisterType opreg = magister.Register(iop->GetOperand1()->GetSymbol());
        mips.Push(new MStatement(MOP_MOVE,
                	new MOperand(MT_REGISTER, reg),
                	new MOperand(MT_REGISTER, opreg),
                	"[Assign Integer]"));
      }
      
      magister.WriteBack();
      break;
    }
    
    case IOP_ASSIGN_R:
    {
      MRegisterType reg = magister.Register(iop->GetResult()->GetSymbol());

      if (iop->GetOperand1()->GetOperandType() == OT_REAL) 
      {
        mips.Push(new MStatement(MOP_LI_S,
                	new MOperand(MT_REGISTER, reg),
                	new MOperand(MT_REAL, iop->GetOperand1()->GetRealValue()),
                	"[Assign Constant Float]"));
      } 
      	else 
      {
        MRegisterType opreg = magister.Register(iop->GetOperand1()->GetSymbol());
        mips.Push(new MStatement(MOP_MOV_S,
                	new MOperand(MT_REGISTER, reg),
                	new MOperand(MT_REGISTER, opreg),
                	"[Assign Float]"));
      }
      
      magister.WriteBack();
      break;
    }
    
    case IOP_INT_TO_REAL:
    {
      MRegisterType reg = magister.Register(iop->GetResult()->GetSymbol());
      
      if (iop->GetOperand1()->GetOperandType() == OT_INT) 
      {
        float val = iop->GetOperand1()->GetIntValue();
        
        mips.Push(new MStatement(MOP_LI_S,
                	new MOperand(MT_REGISTER, reg),
                	new MOperand(MT_REAL, val),
                	"[Coerce Constant]"));
      } 
      	else 
      {
        MRegisterType creg = magister.Register(iop->GetOperand1()->GetSymbol());
        
        mips.Push(new MStatement(MOP_MTC1,
                	new MOperand(MT_REGISTER, creg),
                	new MOperand(MT_REGISTER, reg),
                	"[Coerce Variable]"));
                
        mips.Push(new MStatement(MOP_CVT_S_W,
                	new MOperand(MT_REGISTER, reg),
                	new MOperand(MT_REGISTER, reg)));
      }
      break;
    }

    case IOP_BEQ_I:
    {
      mips.Push(BranchOP(MOP_BEQ, iop,
      					"[Branch Equal]"));
      break;
    }
    
    case IOP_BEQ_R:
    {
      mips.Push(BranchROP(MOP_C_EQ_S, iop,
      					"[Branch Equal]"));
      mips.Push(new MStatement(MOP_BCZT,
              	new MOperand(MT_LABEL,
              	iop->GetResult()->GetSymbol()->GetName().c_str())));
      break;
    }
    
    case IOP_BNE_I:
    {
      mips.Push(BranchOP(MOP_BNE, iop,
      					"[Branch Not Equal]"));
      break;
    }
    
    case IOP_BNE_R:
    {
      mips.Push(BranchROP(MOP_C_EQ_S, iop,
      					"[Branch Not Equal]"));
      mips.Push(new MStatement(MOP_BCZF,
              	new MOperand(MT_LABEL,
              	iop->GetResult()->GetSymbol()->GetName().c_str())));
      break;
    }
    
    case IOP_BGT_I:
    {
      mips.Push(BranchOP(MOP_BGT, iop,
      					"[Branch Greater Than]"));
      break;
    }
    
    case IOP_BGT_R:
    {
      mips.Push(BranchROP(MOP_C_LT_S, iop,
      					"[Branch Greater Than]"));
      mips.Push(new MStatement(MOP_BCZT,
              	new MOperand(MT_LABEL,
              	iop->GetResult()->GetSymbol()->GetName().c_str())));
      break;
    }
    
    case IOP_BLT_I:
    {
      mips.Push(BranchOP(MOP_BLT, iop,
      					"[Branch Less Than]"));
      break;
    }
    
    case IOP_BLT_R:
    {
      mips.Push(BranchROP(MOP_C_LT_S, iop,
      					"[Branch Less Than]"));
      mips.Push(new MStatement(MOP_BCZT,
              	new MOperand(MT_LABEL,
              	iop->GetResult()->GetSymbol()->GetName().c_str())));
      break;
    }
    
    case IOP_BGE_I:
    {
      mips.Push(BranchOP(MOP_BGE, iop,
      					"[Branch Greater Equal]"));
      break;
    }
    
    case IOP_BGE_R:
    {
      mips.Push(BranchROP(MOP_C_LE_S, iop,
      					"[Branch Greater Equal]"));
      mips.Push(new MStatement(MOP_BCZF,
              	new MOperand(MT_LABEL,
              	iop->GetResult()->GetSymbol()->GetName().c_str())));
      break;
    }
    
    case IOP_BLE_I:
    {
      mips.Push(BranchOP(MOP_BLE, iop,
      					"[Branch Less Equal]"));
      break;
    }
    
    case IOP_BLE_R:
    {
      mips.Push(BranchROP(MOP_C_LE_S, iop,
      					"[Branch Less Equal]"));
      mips.Push(new MStatement(MOP_BCZT,
              	new MOperand(MT_LABEL,
              	iop->GetResult()->GetSymbol()->GetName().c_str())));
      break;
    }

    case IOP_ADD_I:
    {
      mips.Push(NumOP(MOP_ADD, 
      					iop, "[Integer Add]"));
      break;
    }
    
    case IOP_ADD_R:
    {
      mips.Push(NumOP(MOP_ADD_S, 
      					iop, "[Float Add]"));
      break;
    }
    
    case IOP_SUB_I:
    {
      mips.Push(NumOP(MOP_SUB, 
      					iop, "[Integer Sub]"));
      break;
    }
    
    case IOP_SUB_R:
    {
      mips.Push(NumOP(MOP_SUB_S,
      					iop, "[Float Sub]"));
      break;
    }
    
    case IOP_MUL_I:
    {
      mips.Push(NumOP(MOP_MUL,
      					iop, "[Integer Mult]"));
      break;
    }
    
    case IOP_MUL_R:
    {
      mips.Push(NumOP(MOP_MUL_S,
      					iop, "[Float Mult]"));
      break;
    }
    
    case IOP_DIV_I:
    {
      mips.Push(NumOP(MOP_DIV,
      					iop, "[Integer Div]"));
      break;
    }
    
    case IOP_DIV_R:
    {
      mips.Push(NumOP(MOP_DIV_S,
      					iop, "[Float Div]"));
      break;
    }
    
    case IOP_MOD:
    {
      mips.Push(NumOP(MOP_REM,
      					iop, "[Modulo]"));
      break;
    }
    
    case IOP_AND:
    {
      mips.Push(NumOP(MOP_AND,
      					iop, "[AND]"));
      break;
    }
    
    case IOP_OR:
    {
      mips.Push(NumOP(MOP_OR,
      					iop, "[OR]"));
      break;
    }

    case IOP_NOT:
    {
      mips.Push(NumUOP(MOP_NOT, 
      					iop, "[NOT]"));
      break;
    }
    
    case IOP_UNARY_MINUS_I:
    {
      mips.Push(NumUOP(MOP_NEG, 
      					iop, "[Integer Negation]"));
      break;
    }
    
    case IOP_UNARY_MINUS_R:
    {
      mips.Push(NumUOP(MOP_NEG_S, 
      					iop, "[Float Negation]"));
      break;
    }
    
    default:
    {
    	pmesg(100,"WARNING: Unknown IOP");
    	break;
    }
  }
}
