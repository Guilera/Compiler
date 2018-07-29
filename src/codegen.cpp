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
using namespace std;
#define debug(x) os << #x << " = " << (x) << endl;

string ACC = "$a0"; // Accumulator
string TEMP = "$t0"; // Temporary
string SP = "$sp"; // Stack Pointer
string FP = "$fp"; // Frame Pointer
string RA = "$ra"; // Return Address

void PUSH(string reg, ostream &os) {
  os << "sw " << reg << " 0($sp)" << endl; // put the value of reg in top of the stack
  os << "addiu $sp $sp -4" << endl;		// deslocate stack pointer to the next empty slot
}

void POP(ostream &os) {
  os << "addiu $sp $sp 4" << endl;
}

void nPOP(int times, ostream &os) {
  os << "addiu $sp $sp " << times*4 << endl;
}

void TOP(string reg, ostream &os) {
  os << "lw " << reg << " 4($sp)" << endl;
}

void LOAD(string reg, int value, ostream &os) {
  os << "li " << reg << " " << value << endl;
}
//-----------------------------------------------------------------------------------

struct ss {
  string id, typeOfV;
  bool isArgument;

  ss () {}

  ss(string id, string typeOfV, bool isArgument) : id(id), typeOfV(typeOfV), isArgument(isArgument) {}
};

struct str {
  int sz;
  string name;
  
  str() {}
  str(string name, int sz) : name(name), sz(sz) {}
};

//-----------------------------------------------------------------------------------

vector<str> localDec; // id of variables as local of current function and its size
vector<str> paramDec; // id of variables as parameter of current function and its size 
vector<vector<string> > func;
list<ss> scope;
string nextBranch;
vector<str> globalVar;
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
bool isInThisScope(string x);
bool isScopeGlobal();
void addVar(string x, string type);
string isDeclared(string x);
int idOfFunction(string x);
void printfunc(string x) {
	if(DEBUG)
		os << "in function " << x << endl;
}
string getType(int id);
int indexFromFpParam(int funcID, string var);
int indexFromFpLocal(string var);
bool isVarGlobal(string id);

//-----------------------------------------------------------------------------------

void Node::codegen(ostream &os) {}

void Program::codegen(ostream &os) {

  os << ".text" << endl << endl;
	printfunc("Program");
  func.push_back(vector<string>());
  func.push_back(vector<string>());
  func[0].push_back("int");
  func[0].push_back("input");
  func[0].push_back("void");
  func[1].push_back("void");
  func[1].push_back("println");
  func[1].push_back("int");
  createScope(false);

  os << "j _main" << endl << endl;

  // function input
  os << "_input:" << endl;
  os << "move $fp $sp" << endl;
  PUSH(RA, os);

  LOAD("$v0", 5, os)
  os << "syscall " << endl;

  os << "move $a0 $v0" << endl;

  TOP(RA, os);
  nPOP(2, os);
  os << "lw $fp 0($sp)" << endl;
  os << "jr $ra" << endl << endl;

  // function println
  os << "_println:" << endl;
  os << "move  $fp  $sp" << endl;
  PUSH(RA, os);

  LOAD("$v0", 1, os)
  os << "lw $a0 4($fp)" << endl;
  os << "syscall" << endl;
  os << "addi $a0, $0, 0xA" << endl;
  os << "addi $v0, $0, 0xB" << endl;
  os << "syscall" << endl;

  TOP(RA, os);
  nPOP(3, os);
  os << "lw $fp 0($sp)" << endl;
  os << "jr $ra" << endl << endl; 

  // os << "Scope Created in Program" << endl;
  for(auto dec: declaration_list) {
    dec->codegen(os);
  }
  exitScope();
  

  os << endl << ".data" << endl;
  for(str x: globalVar) {
    os << x.name << ":    .space " << x.sz*4 << endl;
  }

}

void VariableDeclaration::codegen(ostream &os) {

	printfunc("VariableDeclaration");

  if(!isInThisScope(id)) {
    string tipo;
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
      os << "addiu $sp $sp -" << auxiliar*4 << endl;
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

void Param::codegen(ostream &os) {
	printfunc("Param");
  if(!isInThisScope(id)) {
    string tipo;
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

    //os << id << " added" << " which type is " << tipo << endl;
  } 
}

void CompoundStatement::codegen(ostream &os) {

	printfunc("CompoundStatement");
	createScope(next);
  	next = false;

  for(auto local_dec : local_declarations)
    local_dec->codegen(os);

  for(auto stmt : statement_list)
    stmt->codegen(os);

  exitScope();
}

void FunctionDeclaration::codegen(ostream &os) {
	printfunc("FunctionDeclaration");
  os << '_' << id << ':' << endl;
  os << "move  $fp  $sp" << endl;
  PUSH(RA, os);

  createScope(false);
  next = true;

  func.push_back(vector<string>());
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

  compound_stmt->codegen(os);  

  int paramSz = param_list.size();
  TOP(RA, os);
  os << "addiu $sp $sp " << paramSz*4 + 8 << endl;
  exitScope();

  if(id != "main") {
    os << "lw  $fp  0($sp)" << endl;
    os << "jr $ra" << endl << endl;
  } else {
    os << "li $v0 10" << endl;
    os << "syscall" << endl << endl;
  }
  //os << "Exit Scope in Function " << id << endl;
}

void Selection::codegen(ostream &os) {
	printfunc("Selection");
	createScope(false);
	// os << "Scope Created in Selection" << endl;

  isInt = true;
  int saveContaIf = contaIf;
  nextBranch = "_true_branch_" + to_string(saveContaIf);
  thereIsRelop = false;
  expression->codegen(os);
  if(!thereIsRelop) {
    os << "li $t0 0" << endl;
    LOAD(TEMP, 0, os)
    os << "bne $t0 $a0 " << "_true_branch_" << saveContaIf << endl;
  }
  thereIsRelop = false;

  os << "_false_branch_" << saveContaIf << ':' << endl;
  if(else_stmt) {
    contaIf++;
    else_stmt->codegen(os);
  }

  os << "j _end_if_" << saveContaIf << endl;  
  os << "_true_branch_" << saveContaIf << ':' << endl;
  contaIf++;
  if_stmt->codegen(os);

  os << "_end_if_" << saveContaIf << ':' << endl;
  exitScope();
}

void Iteration::codegen(ostream &os) {
	printfunc("Iteration");
  createScope(false);
  // os << "Scope Created in if statement" << endl;

  int saveContaWhile = contaWhile;
  nextBranch = "_start_while_" + to_string(saveContaWhile);
  os << "_while_" << saveContaWhile << ":" << endl; 
  isInt = true;
  thereIsRelop = false;
  expression->codegen(os);
  if(!thereIsRelop) {
    LOAD(TEMP, 0, os);
    os << "bne $t0 $a0 " << "_start_while_" << saveContaWhile << endl;
  }

  thereIsRelop = false;
  os << "j _end_while_" << saveContaWhile << endl; 
  os << "_start_while_" << saveContaWhile << ":" << endl; 

  contaWhile++;
  statement->codegen(os);

  os << "j _while_" << saveContaWhile << endl;
  os << "_end_while_" << saveContaWhile << ':' << endl;
  exitScope();

} 

void Return::codegen(ostream &os) {
	printfunc("Return");
  if(expression) {
    isInt = true;
	  expression->codegen(os);
  }
} 

void Variable::codegen(ostream &os) {
	printfunc("Variable");

  string aux = isDeclared(id);
  bool globalScope = false;
  os << "# ";
  debug(id);
  if(!isAssign && !isArg) {
    if(indexFromFpParam(func.size()-1, id) != -1){

      if(!expression){
        os << "lw $a0 " << indexFromFpParam(func.size()-1, id) << "($fp) "  << endl;
      }
      else if(expression) {
        
        os << "addiu $a0 $fp " << indexFromFpParam(func.size()-1, id) << endl;
        os << "lw $a0 0($a0)" << endl;

      }
    } else if(indexFromFpLocal(id) != -1) {
      if(!expression) {
        os << "lw $a0 " << indexFromFpLocal(id) << "($fp) " << endl;
      }
      else if(expression) {
        
        os << "addiu $a0 $fp" << indexFromFpLocal(id) << endl;
        
      }
    }  else {
    	// global scope
      globalScope = true;

      if(!expression) {
        os << "la $a0 " << id << endl;
        os << "lw $a0 0($a0)" << endl;
      } else {
        os << "la $a0 " << id << endl;
      }
    }

  } else if(isArg) {

    if(indexFromFpParam(func.size()-1, id) != -1){

      if(aux == "int"){
        os << "lw $a0 " << indexFromFpParam(func.size()-1, id) << "($fp) "  << endl;
      }
      else if(aux == "array") {

        os << "addiu $a0 $fp " << indexFromFpParam(func.size()-1, id) << endl;
        os << "lw $a0 0($a0)" << endl;
        if(!expression) {
          PUSH(ACC, os);       
        }
      }

    } else if(indexFromFpLocal(id) != -1) {

      if(aux == "int") {
        os << "lw $a0 " << indexFromFpLocal(id) << "($fp) " << endl;
      }
      else if(aux == "array") {
        
        os << "addiu $a0 $fp " << indexFromFpLocal(id) << endl;
        
      } 
    } else {

      // global scope
      globalScope = true;
      if(!expression) {
        os << "la $a0 " << id << endl;
        os << "lw $a0 0($a0)" << endl;
      } else {
        os << "la $a0 " << id << endl;
      }
    }

  } else if (isAssign) {

    if(indexFromFpParam(func.size()-1, id) != -1){

      if(!expression){
        os << "addiu $a0 " << "$fp " << indexFromFpParam(func.size()-1, id) << endl;
      }
      else if(expression) {
        os << "addiu $a0 $fp " << indexFromFpParam(func.size()-1, id) << endl;
        os << "lw $a0 0($a0)" << endl;
      }
    } else if(indexFromFpLocal(id) != -1) {
      if(!expression)  {
        os << "addiu $a0 " << "$fp " << indexFromFpLocal(id) << endl;
      }
      else if(expression)  {
        os << "addiu $a0 $fp " << indexFromFpLocal(id) << endl;
      }
    } else {
      // global scope
      globalScope = true;
      if(!expression) {
        os << "la $a0 " << id << endl;
      } else {
        os << "la $a0 " << id << endl;
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
    
    os << "mul $a0 $a0 $t0" << endl;
    TOP(TEMP, os);
    POP(os);
    os << "add $a0 $a0 $t0" << endl;
    if(!isAssign) {
      os << "lw $a0 0($a0)" << endl;
    }
  }

  funcID = saveID;

}

void Assign::codegen(ostream &os) {
  printfunc("Assign");
  expression->codegen(os);
  
  PUSH(ACC, os);

  isAssign = true;
  
  var->codegen(os);

  isAssign = false;
  TOP(TEMP, os);
  POP(os);
  os << "sw $t0 0($a0)" << endl;
  os << "addiu $a0 $t0 0" << endl;

  isInt = true;
} 

void FunctionCall::codegen(ostream &os) {
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
  os << "jal _" << id << endl;
  isArg = false;

  isInt = oldIsInt;
  funcID = -1;
} 

void BinaryOperation::codegen(ostream &os) {

	map<string,string> mapa;
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
  	os << mapa[op] << " $a0  $t0  $a0" << endl;
  } else {

  	mapa["=="] = "beq";
  	mapa["<="] = "ble";
  	mapa["<"] = "blt";
  	mapa[">"] = "bgt";
  	mapa[">="] = "bge";
  	mapa["!="] = "bne";

    thereIsRelop = true;
  	os << mapa[op] << " $t0 $a0 " << nextBranch << endl;   
  }
  isOp = false;
} 

void Number::codegen(ostream &os) {
	printfunc("Number");
  LOAD(ACC, number);
  
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
    os << "# " << it->id << " removed" << endl;
    string toDelete = it->id;
    it = scope.erase(it);
    it--;
    
    bool f = true;
    for(auto iterator = localDec.begin(); iterator != localDec.end(); iterator++) {
    	if((*iterator).name == toDelete) {
    		f = false;
    		os << "addiu $sp $sp " << (*iterator).sz*4 << endl;
      	localDec.erase(iterator);
      	break;
      }
    }

    for(auto iterator = paramDec.begin(); iterator != paramDec.end() && f; iterator++) {
    	if((*iterator).name == toDelete) {
    		os << "addiu $sp $sp " << (*iterator).sz*4 << endl;
      	paramDec.erase(iterator);
      	break;
      }
    }

  }
  scope.erase(it);

}

bool isInThisScope(string x) {
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

void addVar(string x, string type) {
  scope.push_back(ss(x,type, false));
}

string isDeclared(string x) {
  for(auto it = scope.rbegin(); it != scope.rend(); it++) {
    if(it->id == x)
      return it->typeOfV;
  }
  return "";
}

int idOfFunction(string x) {
  for(int i = 0; i < func.size(); i++) {
    if(func[i][1] == x) {
      return i;
    }
  }
  return -1;
}

string getType(int id) {
	if(func[id][0] == "void") {
		return "void";
	}
	return "int";
}

int indexFromFpParam(int lastFunc, string var) {
  int ident = lastFunc;
  int cont = 4;
  for(int i = 0; i < paramDec.size(); i++, cont += 4) {
    if(paramDec[i].name == var)
      return cont;
  }

  return -1;  
}

int indexFromFpLocal(string var) {

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

bool isVarGlobal(string id) {
	for(str x: globalVar) {
		if(x.name == id)
			return true;
	}
	return false;
}
