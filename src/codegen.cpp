#include "tree.hpp"
#include "parser.hpp"
#include <string>
#include <list>
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>


int DEBUG = 0;

using namespace tree;
#define debug(x) os << "# " << #x << " = " << (x) << std::endl;

std::string ACC = "$a0"; // Accumulator
std::string TEMP = "$t0"; // Temporary
std::string SP = "$sp"; // Stack Pointer
std::string FP = "$fp"; // Frame Pointer
std::string RA = "$ra"; // Return Address

void PUSH(std::string reg, std::ostream &os) {
  os << "sw " << reg << " 0($sp)" << std::endl; // put the value of reg in top of the stack
  os << "addiu $sp $sp -4" << std::endl;		// deslocate stack pointer to the next empty slot
}

void POP(std::ostream &os) {
  os << "addiu $sp $sp 4" << std::endl;
}

void nPOP(int times, std::ostream &os) {
  os << "addiu $sp $sp " << times*4 << std::endl;
}

void TOP(std::string reg, std::ostream &os) {
  os << "lw " << reg << " 4($sp)" << std::endl;
}

void LOAD(std::string reg, int value, std::ostream &os) {
  os << "li " << reg << " " << value << std::endl;
}
//-----------------------------------------------------------------------------------

struct ss {
  std::string id, typeOfV;
  bool isArgument;

  ss () {}

  ss(std::string id, std::string typeOfV, bool isArgument) : id(id), typeOfV(typeOfV), isArgument(isArgument) {}
};

struct str {
  int sz;
  std::string name;
  
  str() {}
  str(std::string name, int sz) : name(name), sz(sz) {}
};

//-----------------------------------------------------------------------------------

std::vector<str> localDec; // id of variables as local of current function and its size
std::vector<str> paramDec; // id of variables as parameter of current function and its size 
std::vector<std::vector<std::string> > func;
std::list<ss> scope;
std::string nextBranch;
std::vector<str> globalVar;
bool isValid = true;
bool isArg = false;
bool isOp = false;
bool next = false;
bool isVoid;
bool isInt = true;
bool isAssign = false;
bool thereIsRelop = false;
bool cameFromFunc = false;
int funcID = -1, ind;
int contaIf = 0;
int contaWhile = 0;
int contaSizeLocalDec = 0;

//-----------------------------------------------------------------------------------

void createScope(bool isArgument);
void exitScope(std::ostream &os, bool cameFromF);
bool isInThisScope(std::string x);
bool isScopeGlobal();
void addVar(std::string x, std::string type);
std::string isDeclared(std::string x);
int idOfFunction(std::string x);
void printfunc(std::string x) {
	if(DEBUG)
		std::cout << "in function " << x << std::endl;
}
std::string getType(int id);
int indexFromFpParam(int funcID, std::string var);
int indexFromFpLocal(std::string var);
bool isVarGlobal(std::string id);

//-----------------------------------------------------------------------------------

void Node::codegen(std::ostream &os) {}

void Program::codegen(std::ostream &os) {

  os << ".text" << std::endl << std::endl;
	printfunc("Program");
  func.push_back(std::vector<std::string>());
  func.push_back(std::vector<std::string>());
  func[0].push_back("int");
  func[0].push_back("input");
  func[0].push_back("void");
  func[1].push_back("void");
  func[1].push_back("println");
  func[1].push_back("int");
  createScope(false);

  os << "main: " << std::endl;
  os << "j _main" << std::endl << std::endl;

  // function input
  os << "_input:" << std::endl;
  os << "move $fp $sp" << std::endl;
  PUSH(RA, os);

  LOAD("$v0", 5, os);
  os << "syscall " << std::endl;

  os << "move $a0 $v0" << std::endl;

  TOP(RA, os);
  nPOP(2, os);
  os << "lw $fp 0($sp)" << std::endl;
  os << "jr $ra" << std::endl << std::endl;

  // function println
  os << "_println:" << std::endl;
  os << "move  $fp  $sp" << std::endl;
  PUSH(RA, os);

  LOAD("$v0", 1, os);
  os << "lw $a0 4($fp)" << std::endl;
  os << "syscall" << std::endl;
  os << "addi $a0, $0, 0xA" << std::endl;
  os << "addi $v0, $0, 0xB" << std::endl;
  os << "syscall" << std::endl;

  TOP(RA, os);
  nPOP(3, os);
  os << "lw $fp 0($sp)" << std::endl;
  os << "jr $ra" << std::endl << std::endl; 

  // os << "Scope Created in Program" << std::endl;
  for(auto dec: declaration_list) {
    dec->codegen(os);
  }
  
  exitScope(os,0);
  

  os << std::endl << ".data" << std::endl;
  for(str x: globalVar) {
    os << x.name << ":    .space " << x.sz*4 << std::endl;
  }

}

void VariableDeclaration::codegen(std::ostream &os) {

	printfunc("VariableDeclaration");

  if(!isInThisScope(id)) {
    std::string tipo;
    if(type == INT)
      tipo = "int";
    if(num) {
      tipo = "array";
    }
    if(type == VOID)
      tipo = "void";

    addVar(id,tipo);
    if(!isScopeGlobal()) {
      int auxiliar = 1;
      if(num) {
        auxiliar = num;
        localDec.push_back(str(id, num));
      }
      else {
        localDec.push_back(str(id, 1));
      }
      os << "addiu $sp $sp -" << auxiliar*4 << std::endl;
    } else {
      // put in data
      int auxiliar = 1;
      if(num) {
        auxiliar = num;
        globalVar.push_back(str(id, num));
      }
      else {
        globalVar.push_back(str(id, 1));
      }
    }
  }
}

void Param::codegen(std::ostream &os) {
	printfunc("Param");
  if(!isInThisScope(id)) {
    std::string tipo;
    if(type == INT) {
      tipo = "int";
    	paramDec.push_back(str(id, 1));
    }
    else if(is_array) {
    	paramDec.push_back(str(id, 1));
      tipo = "array";
    }
    if(type == VOID)
      tipo = "void";
    addVar(id,tipo);

    //os << id << " added" << " which type is " << tipo << std::endl;
  } 
}

void CompoundStatement::codegen(std::ostream &os) {

	printfunc("CompoundStatement");
	createScope(next);
	next = false;
  // debug(cameFromFunc);
  bool saveCome = cameFromFunc;  
  cameFromFunc = false;

  for(auto local_dec : local_declarations)
    local_dec->codegen(os);

  for(auto stmt : statement_list)
    stmt->codegen(os);

  cameFromFunc = saveCome;

  contaSizeLocalDec = 0;
  debug(saveCome);
  exitScope(os, saveCome);
}

void FunctionDeclaration::codegen(std::ostream &os) {
	printfunc("FunctionDeclaration");
  os << '_' << id << ':' << std::endl;
  os << "move  $fp  $sp" << std::endl;
  PUSH(RA, os);

  createScope(false);
  next = true;

  func.push_back(std::vector<std::string>());
  if (type == INT) {
   func.back().push_back("int");
   isVoid = false;
  } else if (type == VOID) {
   func.back().push_back("void");
   isVoid = true;
  }

  func.back().push_back(id);

  if(param_list.size() == 0)
    func.back().push_back("void");
  
  for(auto param : param_list) {
    if(param->is_array)
      func.back().push_back("array");
    else if(param->type == VOID)
      func.back().push_back("void");
    else
      func.back().push_back("int");
    
    param->codegen(os);
  }

  cameFromFunc = true;
  compound_stmt->codegen(os);  
  cameFromFunc = false;

  os << "_end_function_" << id << ':' << std::endl;
  os << "addiu $sp $sp " << contaSizeLocalDec << std::endl;
  int paramSz = param_list.size();
  TOP(RA, os);
  os << "addiu $sp $sp " << 8 << std::endl;
  contaSizeLocalDec = 0;
  exitScope(os,0);

  if(id != "main") {
    os << "lw  $fp  0($sp)" << std::endl;
    os << "jr $ra" << std::endl << std::endl;
  } else {
    os << "li $v0 10" << std::endl;
    os << "syscall" << std::endl << std::endl;
  }
  //os << "Exit Scope in Function " << id << std::endl;
}

void Selection::codegen(std::ostream &os) {
	printfunc("Selection");
	createScope(false);
	// os << "Scope Created in Selection" << std::endl;

  isInt = true;
  int saveContaIf = contaIf;
  nextBranch = "_true_branch_" + std::to_string(saveContaIf);
  thereIsRelop = false;
  expression->codegen(os);
  if(!thereIsRelop) {
    os << "li $t0 0" << std::endl;
    LOAD(TEMP, 0, os);
    os << "bne $t0 $a0 " << "_true_branch_" << saveContaIf << std::endl;
  }
  thereIsRelop = false;

  os << "_false_branch_" << saveContaIf << ':' << std::endl;
  if(else_stmt) {
    contaIf++;
    else_stmt->codegen(os);
  }

  os << "j _end_if_" << saveContaIf << std::endl;  
  os << "_true_branch_" << saveContaIf << ':' << std::endl;
  contaIf++;
  if_stmt->codegen(os);

  os << "_end_if_" << saveContaIf << ':' << std::endl;
  exitScope(os,0);
}

void Iteration::codegen(std::ostream &os) {
	printfunc("Iteration");
  createScope(false);
  // os << "Scope Created in if statement" << std::endl;

  int saveContaWhile = contaWhile;
  nextBranch = "_start_while_" + std::to_string(saveContaWhile);
  os << "_while_" << saveContaWhile << ":" << std::endl; 
  isInt = true;
  thereIsRelop = false;
  expression->codegen(os);
  if(!thereIsRelop) {
    LOAD(TEMP, 0, os);
    os << "bne $t0 $a0 " << "_start_while_" << saveContaWhile << std::endl;
  }

  thereIsRelop = false;
  os << "j _end_while_" << saveContaWhile << std::endl; 
  os << "_start_while_" << saveContaWhile << ":" << std::endl; 

  contaWhile++;
  statement->codegen(os);

  os << "j _while_" << saveContaWhile << std::endl;
  os << "_end_while_" << saveContaWhile << ':' << std::endl;
  exitScope(os,0);

} 

void Return::codegen(std::ostream &os) {
	printfunc("Return");
  if(expression) {
    isInt = true;
	  expression->codegen(os);
  }
  os << "j _end_function_" << func.back()[1] << std::endl;
} 

void Variable::codegen(std::ostream &os) {
	printfunc("Variable");

  std::string aux = isDeclared(id);
  bool globalScope = false;
  debug(id);
  if(!isAssign && !isArg) {
    if(indexFromFpParam(func.size()-1, id) != -1){

      if(!expression){
        os << "lw $a0 " << indexFromFpParam(func.size()-1, id) << "($fp) "  << std::endl;
      }
      else if(expression) {
        
        os << "addiu $a0 $fp " << indexFromFpParam(func.size()-1, id) << std::endl;
        os << "lw $a0 0($a0)" << std::endl;

      }
    } else if(indexFromFpLocal(id) != -1) {
      if(!expression) {
        os << "lw $a0 " << indexFromFpLocal(id) << "($fp) " << std::endl;
      }
      else if(expression) {
        
        os << "addiu $a0 $fp" << indexFromFpLocal(id) << std::endl;
        
      }
    }  else {
    	// global scope
      globalScope = true;

      if(!expression) {
        os << "la $a0 " << id << std::endl;
        os << "lw $a0 0($a0)" << std::endl;
      } else {
        os << "la $a0 " << id << std::endl;
      }
    }

  } else if(isArg) {

    if(indexFromFpParam(func.size()-1, id) != -1){

      if(aux == "int"){
        os << "lw $a0 " << indexFromFpParam(func.size()-1, id) << "($fp) "  << std::endl;
      }
      else if(aux == "array") {

        os << "addiu $a0 $fp " << indexFromFpParam(func.size()-1, id) << std::endl;
        os << "lw $a0 0($a0)" << std::endl;
        if(!expression) {
          PUSH(ACC, os);       
        }
      }

    } else if(indexFromFpLocal(id) != -1) {

      if(aux == "int") {
        os << "lw $a0 " << indexFromFpLocal(id) << "($fp) " << std::endl;
      }
      else if(aux == "array") {
        
        os << "addiu $a0 $fp " << indexFromFpLocal(id) << std::endl;
        
      } 
    } else {

      // global scope
      globalScope = true;
      if(!expression) {
        os << "la $a0 " << id << std::endl;
        os << "lw $a0 0($a0)" << std::endl;
      } else {
        os << "la $a0 " << id << std::endl;
      }
    }

  } else if (isAssign) {

    if(indexFromFpParam(func.size()-1, id) != -1){

      if(!expression){
        os << "addiu $a0 " << "$fp " << indexFromFpParam(func.size()-1, id) << std::endl;
      }
      else if(expression) {
        os << "addiu $a0 $fp " << indexFromFpParam(func.size()-1, id) << std::endl;
        os << "lw $a0 0($a0)" << std::endl;
      }
    } else if(indexFromFpLocal(id) != -1) {
      if(!expression)  {
        os << "addiu $a0 " << "$fp " << indexFromFpLocal(id) << std::endl;
      }
      else if(expression)  {
        os << "addiu $a0 $fp " << indexFromFpLocal(id) << std::endl;
      }
    } else {
      // global scope
      globalScope = true;
      if(!expression) {
        os << "la $a0 " << id << std::endl;
      } else {
        os << "la $a0 " << id << std::endl;
    	}
    }
    
  }


  if(funcID != -1 && !isOp) {
    if(aux == "array" && expression)
      aux = "int";
  }
  
  aux = isDeclared(id);
  int saveID = funcID;
  if(aux == "array")  {
    funcID = -1;
  }

  if(expression) {
    isInt = true;
    PUSH(ACC, os);
    bool saveAss = isAssign, saveArg = isArg;
    isAssign = false; 
    isArg = false;
    expression->codegen(os);
    isAssign = saveAss; 
    isArg = saveArg;
    
    if(globalScope)
      LOAD(TEMP, 4, os);
    else
      LOAD(TEMP, -4, os);
    
    os << "mul $a0 $a0 $t0" << std::endl;
    TOP(TEMP, os);
    POP(os);
    os << "add $a0 $a0 $t0" << std::endl;
    if(!isAssign) {
      os << "lw $a0 0($a0)" << std::endl;
    }
  }

  funcID = saveID;

}

void Assign::codegen(std::ostream &os) {
  printfunc("Assign");
  expression->codegen(os);
  
  PUSH(ACC, os);

  isAssign = true;
  
  var->codegen(os);

  isAssign = false;
  TOP(TEMP, os);
  POP(os);
  os << "sw $t0 0($a0)" << std::endl;
  os << "addiu $a0 $t0 0" << std::endl;

  isInt = true;
} 

void FunctionCall::codegen(std::ostream &os) {
	printfunc("FunctionCall");

  funcID = idOfFunction(id);

  if(getType(funcID) == "void") {
  	isInt = false;
  }

  PUSH(FP, os);

  ind = 2;
  int sz = (func[funcID].size()-2 == 1 && func[funcID][2] == "void" ? 0 : func[funcID].size()-2);
  if(args.size() != sz) {
    funcID = -1;
    return;
  }

  int oldIsInt = isInt;
  isArg = true;
  for(auto it = args.rbegin(); it != args.rend(); it++) {
    auto a = *it;
    isInt = true;
	  a->codegen(os);
    PUSH(ACC, os);
  }
  os << "jal _" << id << std::endl;
  isArg = false;

  isInt = oldIsInt;
  funcID = -1;
} 

void BinaryOperation::codegen(std::ostream &os) {

	std::map<std::string,std::string> mapa;
	mapa["+"] = "add";
	mapa["-"] = "sub";
	mapa["*"] = "mul";
	mapa["/"] = "div"; 

  printfunc("BinaryOperation");
  if(funcID != -1 && !isOp) {
    if(func[funcID][ind++] != "int") {
  	}  
  }
  isOp = true;
  isInt = true;
  lhs->codegen(os);

  PUSH(ACC, os);
  
  isOp = true;
  isInt = true;
  rhs->codegen(os);
  TOP(TEMP, os);
  POP(os);

  if(mapa.count(op)) {
  	os << mapa[op] << " $a0  $t0  $a0" << std::endl;
  } else {

  	mapa["=="] = "beq";
  	mapa["<="] = "ble";
  	mapa["<"] = "blt";
  	mapa[">"] = "bgt";
  	mapa[">="] = "bge";
  	mapa["!="] = "bne";

    thereIsRelop = true;
  	os << mapa[op] << " $t0 $a0 " << nextBranch << std::endl;   
  }
  isOp = false;
} 

void Number::codegen(std::ostream &os) {
	printfunc("Number");
  LOAD(ACC, number, os);

	if(funcID != -1 && !isOp) {
    if(func[funcID][ind++] != "int") {
  	}  
  }
} 

// ---------------------------------------------------------------------------------------


void createScope(bool isArgument) {
  scope.push_back(ss("$","$",isArgument));
}

void exitScope(std::ostream &os, bool cameFromF) {

  if(scope.size() == 0)
    return;

  auto it = scope.end();
  it--;
  while(it->id != "$") {
    os << "# " << it->id << " removed" << std::endl;
    std::string toDelete = it->id;
    it = scope.erase(it);
    it--;
    
    bool f = true;
    for(auto iterator = localDec.begin(); iterator != localDec.end(); iterator++) {
    	if((*iterator).name == toDelete) {
    		f = false;
        if(!cameFromF)
    		  os << "addiu $sp $sp " << (*iterator).sz*4 << std::endl;
        else 
          contaSizeLocalDec += (*iterator).sz*4; 
      	localDec.erase(iterator);
      	break;
      }
    }

    for(auto iterator = paramDec.begin(); iterator != paramDec.end() && f; iterator++) {
    	if((*iterator).name == toDelete) {
    		os << "addiu $sp $sp " << 4 << std::endl;
      	paramDec.erase(iterator);
      	break;
      }
    }

  }
  scope.erase(it);

}

bool isInThisScope(std::string x) {
  auto it = scope.rbegin();

  while(it->id != "$" || it->isArgument == true) {
    if(it->id == x)
      return true;
    it++;
  }
  return false;
}

bool isScopeGlobal() {
  int c = 0;
  for(auto it: scope) {
    if(it.id == "$")
      c++;
  }
  return (c==1);
}

void addVar(std::string x, std::string type) {
  scope.push_back(ss(x,type, false));
}

std::string isDeclared(std::string x) {
  for(auto it = scope.rbegin(); it != scope.rend(); it++) {
    if(it->id == x)
      return it->typeOfV;
  }
  return "";
}

int idOfFunction(std::string x) {
  for(int i = 0; i < func.size(); i++) {
    if(func[i][1] == x) {
      return i;
    }
  }
  return -1;
}

std::string getType(int id) {
	if(func[id][0] == "void") {
		return "void";
	}
	return "int";
}

int indexFromFpParam(int lastFunc, std::string var) {
  int ident = lastFunc;
  int cont = 4;
  for(int i = 0; i < paramDec.size(); i++, cont += 4) {
    if(paramDec[i].name == var)
      return cont;
  }

  return -1;  
}

int indexFromFpLocal(std::string var) {

  int cont = 4;

  for(int i = 0; i < localDec.size(); i++) {
    cont += localDec[i].sz*4;
  }
  
  for(int i = localDec.size()-1; i >= 0; i--) {
    cont -= localDec[i].sz*4;
    if(localDec[i].name == var) 
      return -cont;
  }

  return -1;
}

bool isVarGlobal(std::string id) {
	for(str x: globalVar) {
		if(x.name == id)
			return true;
	}
	return false;
}