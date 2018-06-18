#include "tree.hpp"
#include "parser.hpp"
#include <list>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

using namespace tree;
#define ss std::pair<std::string,std::string>
#define debug(x) std::cout << #x << " = " << (x) << std::endl;

//-----------------------------------------------------------------------------------

std::vector<std::vector<std::string> > func;
std::list<ss> scope;
bool isValid = true;
bool isArg = false;
bool isOp = false;
bool isVoid;
int funcID = -1, ind;

//-----------------------------------------------------------------------------------

void createScope();
void exitScope();
bool isInThisScope(std::string x);
bool isScopeGlobal();
void addVar(std::string x, std::string type);
std::string isDeclared(std::string x);
int idOfFunction(std::string x);
void printfunc(std::string x) {
	std::cout << "in function " << x << std::endl;
}

//-----------------------------------------------------------------------------------

void Node::semantic() {}

void Program::semantic() {
	//printfunc("Program");
  func.push_back(std::vector<std::string>());
  func.push_back(std::vector<std::string>());
  func[0].push_back("input");
  func[1].push_back("println");
  func[1].push_back("int");
  createScope();

  std::cout << "Scope Created in Program" << std::endl;
  for(auto dec: declaration_list) {
    dec->semantic();
  }
  exitScope();
  if(func.back().size() != 2 || func.back().front() != "main" || func.back()[1] != "void" || !isVoid) {
  	std::cout << "error in declaration of function main" << std::endl;
  	exit(0);
  }
}

void VariableDeclaration::semantic() {

	//printfunc("VariableDeclaration");
	if(idOfFunction(id) != -1) {
		std::cout << "id " << id << " was already decleared as a function" << std::endl;
		exit(0);
	}
  if(!isInThisScope(id)) {
    std::string tipo;
    if(type == INT)
      tipo = "int";
    if(num)
      tipo = "array";
    if(type == VOID)
      tipo = "void";

    if(isScopeGlobal() && type == VOID) {
      std::cout << "wrong void declaration globally" << std::endl;
      exit(0);
    }
    addVar(id,tipo);
    std::cout << id << " added" << " type " << tipo << std::endl;
  } else {
    std::cout << "Two variables with the same id in the same scope" << id << std::endl;
    exit(0);
  }
}

void Param::semantic() {
	//printfunc("Param");
  if(!isInThisScope(id)) {
    std::string tipo;
    if(type == INT)
      tipo = "int";
    if(is_array)
      tipo = "array";
    if(type == VOID)
      tipo = "void";
    addVar(id,tipo);
    std::cout << id << " added" << " which type is " << tipo << std::endl;
  } else {
    std::cout << "Two variables with the same id in the same scope" << id << std::endl;
    exit(0);
  }
}

void CompoundStatement::semantic() {

	//printfunc("CompoundStatement");
  for(auto local_dec : local_declarations) {
    if(local_dec->type == VOID) {
      std::cout << "wrong void declaration inside function" << std::endl;
      exit(0);
    }
    local_dec->semantic();
  }

  for(auto stmt : statement_list)
    stmt->semantic();
}

void FunctionDeclaration::semantic() {
	//printfunc("FunctionDeclaration");
  if(idOfFunction(id) != -1) {
  	std::cout << "function " << id << " was already decleared" << std::endl;
  	exit(0);
  }

  if(isDeclared(id) != "") {
  	std::cout << "id " << id << " was already decleared as a var" << std::endl;
  	exit(0);
  }
  createScope();
  std::cout << "Scope Created in Function " << id << std::endl;

  func.push_back(std::vector<std::string>());
  func.back().push_back(id);

  if (type == INT) {
   isVoid = false;
  }
  else if (type == VOID){
   isVoid = true;
  }

  if(param_list.size() == 0) {
  	func.back().push_back("void");
  }
  for(auto param : param_list) {
    if(param->type == VOID && (param->id > "&" || param_list.size() > 1)) {
      std::cout << "wrong void declaraion in parameter" << std::endl;
      exit(0);
    }
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
  std::cout << "Exit Scope in Function " << id << std::endl;
  exitScope();
}

void Selection::semantic() {
	//printfunc("Selection");
  expression->semantic();
  if_stmt->semantic();
  if(else_stmt)
    else_stmt->semantic();
}

void Iteration::semantic() {
	//printfunc("Iteration");
  expression->semantic();
  statement->semantic();
} 

void Return::semantic() {
	//printfunc("Return");
  //std::cout << isVoid << ' ' << (expression ? 1: 0) << std::endl;
  if(isVoid && expression) {
    std::cout << "error found in function return " << std::endl;
    exit(0);
  } else if(!isVoid && !expression) {
    std::cout << "error found in function return " << std::endl;
    exit(0);
  }
  if(expression) {
    expression->semantic();
  }
} 

void Variable::semantic() {
	//printfunc("Variable");
  std::string aux = isDeclared(id);
  if(aux == "") {
    std::cout << "variable " << id << " wasnt declared" << std::endl;
    exit(0);
  }  

  //debug(id);
  if(!expression && aux == "array" && !isArg) {
  	//if you comment this if statement array indexation will only work with number not expressions 
    std::cout << "array without index " << std::endl;
    exit(0);
  }

  if(funcID != -1) {
  	if(aux == "array" && expression)
  		aux = "int";
  	//debug(id);
  	//debug(aux);
  	//debug(func[funcID][ind]);
    if(func[funcID][ind++] != aux) {
      std::cout << "incompatible types in function" << std::endl;
  	  exit(0);
  	}  
  }
  
  aux = isDeclared(id);
  int saveID = funcID;
  if(aux == "array")  {
  	funcID = -1;
  }

  if(expression)
    expression->semantic();

  funcID = saveID;
} 


void Assign::semantic() {
	//printfunc("Assign");
  var->semantic();
  expression->semantic();
} 

void FunctionCall::semantic() {
	//printfunc("FunctionCall");

  if(idOfFunction(id) == -1) {
    std::cout << "function wasnt declared" << std::endl;
    exit(0);
    return;
  }
  //debug(id);
  funcID = idOfFunction(id);
  ind = 1;
  //std::cout << "funcID = " << funcID << std::endl;
  //std::cout << "args size " << args.size() << "       " << " fsize " <<  func[funcID].size()-1 << std::endl;
  if(args.size() != func[funcID].size()-1) {
  	std::cout << "qtd of args different from function" << std::endl;
    exit(0);
    funcID = -1;
    return;
  }
  isArg = true;
  for(auto &a : args)
    a->semantic();
  isArg = false;

  funcID = -1;
} 

void BinaryOperation::semantic() {
	//printfunc("BinaryOperation");
	isOp = true;
  lhs->semantic();
  rhs->semantic();
  if(funcID != -1) {
  	debug(func[funcID][ind]);
    if(func[funcID][ind++] != "int") {
      std::cout << "incompatible types in function" << std::endl;
  	  exit(0);
  	}  
  }
  isOp = false;
} 

void Number::semantic() {
	//printfunc("Number");
	if(funcID != -1 && !isOp) {
    if(func[funcID][ind++] != "int") {
      std::cout << "incompatible types in function" << std::endl;
  	  exit(0);
  	}  
  }
} 

// ---------------------------------------------------------------------------------------


void createScope() {
  scope.push_back(ss("$","$"));
}

void exitScope() {

  if(scope.size() == 0)
    return;

  auto it = scope.end();
  it--;
  while(it->first != "$") {
    std::cout << it->first << " removed" << std::endl;
    it = scope.erase(it);
    it--;
  }
  scope.erase(it);
}

bool isInThisScope(std::string x) {
  auto it = scope.rbegin();
  while(it->first != "$") {
    if(it->first == x)
      return true;
    it++;
  }
  return false;
}

bool isScopeGlobal() {
  int c = 0;
  for(auto it: scope) {
    if(it.first == "$")
      c++;
  }
  return (c==1);
}

void addVar(std::string x, std::string type) {
  scope.push_back(ss(x,type));
}

std::string isDeclared(std::string x) {
  for(auto it = scope.rbegin(); it != scope.rend(); it++) {
    if(it->first == x)
      return it->second;
  }
  return "";
}

int idOfFunction(std::string x) {
  for(int i = 0; i < func.size(); i++) {
  	//std::cout << func[i].front() << std::endl;
    if(func[i].front() == x) {
      return i;
    }
  }
  return -1;
}