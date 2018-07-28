#include "tree.hpp"
#include "parser.hpp"
#include <list>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>

int DEBUG = 0;

using namespace tree;
#define debug(x) std::cout << #x << " = " << (x) << std::endl;

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
int funcID = -1, ind;
int contaIf = 0;
int contaWhile = 0;

//-----------------------------------------------------------------------------------

void createScope(bool isArgument);
void exitScope();
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

void Node::semantic() {}

void Program::semantic() {

  std::cout << ".text" << std::endl << std::endl;
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

  std::cout << "j _main" << std::endl << std::endl;

  // function input
  std::cout << '_' << "input" << ':' << std::endl;
  std::cout << "move  $fp  $sp" << std::endl;
  std::cout << "sw  $ra  0($sp)" << std::endl;
  std::cout << "addiu  $sp  $sp  -4" << std::endl;

  std::cout << "li $v0 5" << std::endl;
  std::cout << "syscall " << std::endl;

  std::cout << "move $a0 $v0" << std::endl;

  std::cout << "lw  $ra  4($sp)" << std::endl;
  std::cout << "addiu  $sp  $sp  " << 8 << std::endl;
  std::cout << "lw  $fp  0($sp)" << std::endl;
  std::cout << "jr $ra" << std::endl << std::endl;

  // function println
  std::cout << '_' << "println" << ':' << std::endl;
  std::cout << "move  $fp  $sp" << std::endl;
  std::cout << "sw  $ra  0($sp)" << std::endl;
  std::cout << "addiu  $sp  $sp  -4" << std::endl;

  std::cout << "li $v0 1" << std::endl;
  std::cout << "lw $a0 4($fp)" << std::endl;
  std::cout << "syscall" << std::endl;
  std::cout << "addi $a0, $0, 0xA" << std::endl;
  std::cout << "addi $v0, $0, 0xB" << std::endl;
  std::cout << "syscall" << std::endl;

  std::cout << "lw  $ra  4($sp)" << std::endl;
  std::cout << "addiu  $sp  $sp  " << 12  << std::endl;
  std::cout << "lw  $fp  0($sp)" << std::endl;
  std::cout << "jr $ra" << std::endl << std::endl; 

  // std::cout << "Scope Created in Program" << std::endl;
  for(auto dec: declaration_list) {
    dec->semantic();
  }
  exitScope();
  

  std::cout << std::endl << ".data" << std::endl;
  for(str x: globalVar) {
    std::cout << x.name << ":    .space " << x.sz*4 << std::endl;
  }

}

void VariableDeclaration::semantic() {

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

    if(isScopeGlobal() && type == VOID) {
      //std::cout << "wrong void declaration globally" << std::endl;
      //exit(0);
    }

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
      //debug(id);
      std::cout << "addiu $sp $sp -" << auxiliar*4 << std::endl;
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
    //std::cout << id << " added" << " type " << tipo << std::endl;
  } 
}

void Param::semantic() {
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

    //std::cout << id << " added" << " which type is " << tipo << std::endl;
  } 
}

void CompoundStatement::semantic() {

	printfunc("CompoundStatement");
	createScope(next);
  	next = false;
	// std::cout << "Scope Created in CompoundStatement" << std::endl;

  for(auto local_dec : local_declarations) {
    
    local_dec->semantic();
  }

  for(auto stmt : statement_list)
    stmt->semantic();

  exitScope();
}

void FunctionDeclaration::semantic() {
	printfunc("FunctionDeclaration");
  std::cout << '_' << id << ':' << std::endl;
  std::cout << "move  $fp  $sp" << std::endl;
  std::cout << "sw  $ra  0($sp)" << std::endl;
  std::cout << "addiu  $sp  $sp  -4" << std::endl;

  createScope(false);
  next = true;

  func.push_back(std::vector<std::string>());
  if (type == INT) {
   func.back().push_back("int");
   isVoid = false;
  }
  else if (type == VOID){
   func.back().push_back("void");
   isVoid = true;
  }
  func.back().push_back(id);


  if(param_list.size() == 0) {
  	func.back().push_back("void");
  }
  for(auto param : param_list) {

    if(param->is_array) {
      func.back().push_back("array");
    } else if(param->type == VOID) {
      func.back().push_back("void");
    } else {
      func.back().push_back("int");
    }
    param->semantic();
  }

  compound_stmt->semantic();  

  int paramSz = param_list.size();
  std::cout << "lw  $ra  4($sp)" << std::endl;
  std::cout << "addiu  $sp  $sp  " << 8 << std::endl;
  exitScope();

  if(id != "main") {
    std::cout << "lw  $fp  0($sp)" << std::endl;
    std::cout << "jr $ra" << std::endl << std::endl;
  } else {
    std::cout << "li $v0 10" << std::endl;
    std::cout << "syscall" << std::endl << std::endl;
  }
  //std::cout << "Exit Scope in Function " << id << std::endl;
}

void Selection::semantic() {
	printfunc("Selection");
	createScope(false);
	// std::cout << "Scope Created in Selection" << std::endl;

  isInt = true;
  int saveContaIf = contaIf;
  nextBranch = "_true_branch_" + std::to_string(saveContaIf);
  thereIsRelop = false;
  expression->semantic();
  if(!thereIsRelop) {
    std::cout << "li $t0 0" << std::endl;
    std::cout << "bne $t0 $a0 " << "_true_branch_" << saveContaIf << std::endl;
  }
  thereIsRelop = false;

  std::cout << "_false_branch_" << saveContaIf << ':' << std::endl;
  if(else_stmt) {
    contaIf++;
    else_stmt->semantic();
  }
  std::cout << "j _end_if_" << saveContaIf << std::endl;  
  std::cout << "_true_branch_" << saveContaIf << ':' << std::endl;
  contaIf++;
  if_stmt->semantic();

  std::cout << "_end_if_" << saveContaIf << ':' << std::endl;
  exitScope();
}

void Iteration::semantic() {
	printfunc("Iteration");
  createScope(false);
  // std::cout << "Scope Created in if statement" << std::endl;

  int saveContaWhile = contaWhile;
  nextBranch = "_start_while_" + std::to_string(saveContaWhile);
  std::cout << "_while_" << saveContaWhile << ":" << std::endl; 
  isInt = true;
  thereIsRelop = false;
  expression->semantic();
  if(!thereIsRelop) {
    std::cout << "li $t0 0" << std::endl;
    std::cout << "bne $t0 $a0 " << "_start_while_" << saveContaWhile << std::endl;
  }
  thereIsRelop = false;
  std::cout << "j _end_while_" << saveContaWhile << std::endl; 
  std::cout << "_start_while_" << saveContaWhile << ":" << std::endl; 

  contaWhile++;
  statement->semantic();

  std::cout << "j _while_" << saveContaWhile << std::endl;
  std::cout << "_end_while_" << saveContaWhile << ':' << std::endl;
  exitScope();

} 

void Return::semantic() {
	printfunc("Return");
  if(expression) {
    isInt = true;
	  expression->semantic();
  }
} 

void Variable::semantic() {
	printfunc("Variable");


  std::string aux = isDeclared(id);
  bool globalScope = false;
  std::cout << "# ";
  debug(id);
  if(!isAssign && !isArg) {
    if(indexFromFpParam(func.size()-1, id) != -1){

      if(!expression){
        std::cout << "lw $a0 " << indexFromFpParam(func.size()-1, id) << "($fp) "  << std::endl;
      }
      else if(expression) {
        
        std::cout << "addiu $a0 $fp " << indexFromFpParam(func.size()-1, id) << std::endl;
        std::cout << "lw $a0 0($a0)" << std::endl;

      }
    } else if(indexFromFpLocal(id) != -1) {
      if(!expression) {
        std::cout << "lw $a0 " << indexFromFpLocal(id) << "($fp) " << std::endl;
      }
      else if(expression) {
        
        std::cout << "addiu $a0 $fp" << indexFromFpLocal(id) << std::endl;
        
      }
    }  else {
    	// global scope
      globalScope = true;

      if(!expression) {
        std::cout << "la $a0 " << id << std::endl;
        std::cout << "lw $a0 0($a0)" << std::endl;
      } else {
        std::cout << "la $a0 " << id << std::endl;
      }
    }

  } else if(isArg) {

    if(indexFromFpParam(func.size()-1, id) != -1){

      if(aux == "int"){
        std::cout << "lw $a0 " << indexFromFpParam(func.size()-1, id) << "($fp) "  << std::endl;
      }
      else if(aux == "array") {

        std::cout << "addiu $a0 $fp " << indexFromFpParam(func.size()-1, id) << std::endl;
        std::cout << "lw $a0 0($a0)" << std::endl;
        if(!expression) {
          std::cout << "sw $a0 0($sp)" << std::endl;
          std::cout << "addiu $sp $sp -4" << std::endl;
        }
      }

    } else if(indexFromFpLocal(id) != -1) {

      if(aux == "int") {
        std::cout << "lw $a0 " << indexFromFpLocal(id) << "($fp) " << std::endl;
      }
      else if(aux == "array") {
        
        std::cout << "addiu $a0 $fp " << indexFromFpLocal(id) << std::endl;
        
      } 
    } else {

      // global scope
      globalScope = true;
      if(!expression) {
        std::cout << "la $a0 " << id << std::endl;
        std::cout << "lw $a0 0($a0)" << std::endl;
      } else {
        std::cout << "la $a0 " << id << std::endl;
      }
    }

  } else if (isAssign) {

    if(indexFromFpParam(func.size()-1, id) != -1){

      if(!expression){
        std::cout << "addiu $a0 " << "$fp " << indexFromFpParam(func.size()-1, id) << std::endl;
      }
      else if(expression) {
        std::cout << "addiu $a0 $fp " << indexFromFpParam(func.size()-1, id) << std::endl;
        std::cout << "lw $a0 0($a0)" << std::endl;
      }
    } else if(indexFromFpLocal(id) != -1) {
      if(!expression)  {
        std::cout << "addiu $a0 " << "$fp " << indexFromFpLocal(id) << std::endl;
      }
      else if(expression)  {
        std::cout << "addiu $a0 $fp " << indexFromFpLocal(id) << std::endl;
      }
    } else {
      // global scope
      globalScope = true;
      if(!expression) {
        std::cout << "la $a0 " << id << std::endl;
      } else {
        std::cout << "la $a0 " << id << std::endl;
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
    std::cout << "sw $a0 0($sp)" << std::endl;
    std::cout << "addiu $sp $sp -4" << std::endl;
    bool saveAss = isAssign, saveArg = isArg;
    isAssign = false, isArg = false;
    expression->semantic();
    isAssign = saveAss, isArg = saveArg;
    if(globalScope) {
    	std::cout << "li $t0 4" << std::endl;
    } else {
    	std::cout << "li $t0 -4" << std::endl;
    }
    std::cout << "mul $a0 $a0 $t0" << std::endl;
    std::cout << "lw $t0 4($sp)" << std::endl;
    std::cout << "addiu $sp $sp 4" << std::endl;
    std::cout << "add $a0 $a0 $t0" << std::endl;
    if(!isAssign) {
      std::cout << "lw $a0 0($a0)" << std::endl;
    }
  }

  funcID = saveID;

} 


void Assign::semantic() {
  printfunc("Assign");
  expression->semantic();
  
	std::cout << "sw $a0 0($sp)" << std::endl;
  std::cout << "addiu  $sp  $sp  -4" << std::endl;

  isAssign = true;
  var->semantic();
  isAssign = false;
  std::cout << "lw $t0 4($sp)" << std::endl;
  std::cout << "addiu  $sp  $sp  4" << std::endl;
  std::cout << "sw $t0 0($a0)" << std::endl;
  std::cout << "addiu $a0 $t0 0" << std::endl;

  isInt = true;
} 

void FunctionCall::semantic() {
	printfunc("FunctionCall");

  funcID = idOfFunction(id);

  if(getType(funcID) == "void") {
  	isInt = false;
  }

  std::cout << "sw  $fp  0($sp)" << std::endl;
  std::cout << "addiu  $sp  $sp  -4" << std::endl;

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
	  a->semantic();
    std::cout << "sw  $a0  0($sp)" << std::endl;
    std::cout << "addiu  $sp  $sp  -4" << std::endl;
  }
  std::cout << "jal _" << id << std::endl;
  isArg = false;

  isInt = oldIsInt;
  funcID = -1;
} 

void BinaryOperation::semantic() {

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
  lhs->semantic();

  std::cout << "sw $a0 0($sp)" << std::endl;
  std::cout << "addiu  $sp  $sp  -4" << std::endl;
  isOp = true;
  isInt = true;
  rhs->semantic();
  std::cout << "lw $t0 4($sp)" << std::endl;
  std::cout << "addiu  $sp  $sp  4" << std::endl;
  if(mapa.count(op)) {
  	std::cout << mapa[op] << "   $a0  $t0  $a0" << std::endl;
  } else {

  	mapa["=="] = "beq";
  	mapa["<="] = "ble";
  	mapa["<"] = "blt";
  	mapa[">"] = "bgt";
  	mapa[">="] = "bge";
  	mapa["!="] = "bne";

    thereIsRelop = true;
  	std::cout << mapa[op] << " $t0 $a0 " << nextBranch << std::endl;   
  }
  isOp = false;
} 

void Number::semantic() {
	printfunc("Number");
	std::cout << "li $a0 " << number << std::endl;
	if(funcID != -1 && !isOp) {
    if(func[funcID][ind++] != "int") {
  	}  
  }
} 

// ---------------------------------------------------------------------------------------


void createScope(bool isArgument) {
  scope.push_back(ss("$","$",isArgument));
}

void exitScope() {

  if(scope.size() == 0)
    return;

  auto it = scope.end();
  it--;
  while(it->id != "$") {
    std::cout << "# " << it->id << " removed" << std::endl;
    std::string toDelete = it->id;
    it = scope.erase(it);
    it--;
    
    bool f = true;
    for(auto iterator = localDec.begin(); iterator != localDec.end(); iterator++) {
    	if((*iterator).name == toDelete) {
    		f = false;
    		std::cout << "addiu $sp $sp " << (*iterator).sz*4 << std::endl;
      	localDec.erase(iterator);
      	break;
      }
    }

    for(auto iterator = paramDec.begin(); iterator != paramDec.end() && f; iterator++) {
    	if((*iterator).name == toDelete) {
    		std::cout << "addiu $sp $sp " << (*iterator).sz*4 << std::endl;
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