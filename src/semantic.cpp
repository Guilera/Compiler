#include "tree.hpp"
#include "parser.hpp"
#include <list>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

using namespace tree;
#define debug(x) std::cout << #x << " = " << (x) << std::endl;

//-----------------------------------------------------------------------------------

struct ss {
  std::string first, second;
  bool isArgument;

  ss () {}

  ss(std::string first, std::string second, bool isArgument) : first(first), second(second), isArgument(isArgument) {}
};

//-----------------------------------------------------------------------------------

std::vector<std::vector<std::string> > func;
std::list<ss> scope;
bool isValid = true;
bool isArg = false;
bool isOp = false;
bool next = false;
bool isVoid;
bool isInt = true;
int funcID = -1, ind;

//-----------------------------------------------------------------------------------

void createScope(bool isArgument);
void exitScope();
bool isInThisScope(std::string x);
bool isScopeGlobal();
void addVar(std::string x, std::string type);
std::string isDeclared(std::string x);
int idOfFunction(std::string x);
void printfunc(std::string x) {
	std::cout << "in function " << x << std::endl;
}
std::string getType(int id);

//-----------------------------------------------------------------------------------

void Node::semantic() {}

void Program::semantic() {
	//printfunc("Program");
  func.push_back(std::vector<std::string>());
  func.push_back(std::vector<std::string>());
  func[0].push_back("int");
  func[0].push_back("input");
  func[0].push_back("void");
  func[1].push_back("void");
  func[1].push_back("println");
  func[1].push_back("int");
  createScope(false);

  std::cout << "Scope Created in Program" << std::endl;
  for(auto dec: declaration_list) {
    dec->semantic();
  }
  exitScope();
  if(func.back().size() != 3 || func.back()[1] != "main" || func.back()[2] != "void" || !isVoid) {
  	std::cout << "error in declaration of function main" << std::endl;
  	exit(0);
  }
}

void VariableDeclaration::semantic() {

	//printfunc("VariableDeclaration");
  if(idOfFunction(id) != -1 && isScopeGlobal()) {
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
    std::cout << "Two variables with the same id in the same scope: " << id << std::endl;
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
	createScope(next);
  next = false;
	std::cout << "Scope Created in CompoundStatement" << std::endl;

  for(auto local_dec : local_declarations) {
    if(local_dec->type == VOID) {
      std::cout << "wrong void declaration inside function" << std::endl;
      exit(0);
    }
    local_dec->semantic();
  }

  for(auto stmt : statement_list)
    stmt->semantic();

  exitScope();
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
  createScope(false);
  next = true;
  std::cout << "Scope Created in Function " << id << std::endl;

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
	createScope(false);
	std::cout << "Scope Created in Selection" << std::endl;

  isInt = true;
  expression->semantic();
  if(!isInt) {
  	std::cout << "is not an int expression" << std::endl;
  	exit(0);
  }
  if_stmt->semantic();
  if(else_stmt)
    else_stmt->semantic();

  exitScope();
}

void Iteration::semantic() {
	//printfunc("Iteration");
	createScope(false);
	std::cout << "Scope Created in if statement" << std::endl;
  isInt = true;
  expression->semantic();
  if(!isInt) {
  	std::cout << "is not an int expression" << std::endl;
  	exit(0);
  }
  statement->semantic();
  exitScope();
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
    isInt = true;
	  expression->semantic();
	  if(!isInt) {
	  	std::cout << "is not an int expression" << std::endl;
	  	exit(0);
	  }
  }
} 

void Variable::semantic() {
	//printfunc("Variable");

  std::string aux = isDeclared(id);
  if(aux == "") {
    std::cout << "variable " << id << " wasnt declared" << std::endl;
    exit(0);
  }  

  if(expression && aux == "int") {
    std::cout << "int declared as array" << std::endl;
    exit(0);
  }

  //debug(id);
  if(!expression && aux == "array" && !isArg) {
    std::cout << "array without index " << std::endl;
    exit(0);
  }

  if(funcID != -1 && !isOp) {
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

  if(expression) {
    isInt = true;
		expression->semantic();
		if(!isInt) {
			std::cout << "is not an int expression" << std::endl;
			exit(0);
		}
  }

  funcID = saveID;
} 


void Assign::semantic() {
	//printfunc("Assign");
  var->semantic();
	isInt = true;
	expression->semantic();
	if(!isInt) {
		std::cout << "is not an int expression" << std::endl;
		exit(0);
	}
} 

void FunctionCall::semantic() {
	//printfunc("FunctionCall");

  if(idOfFunction(id) == -1) {
    std::cout << "function wasnt declared" << std::endl;
    exit(0);
    return;
  }

  funcID = idOfFunction(id);

  if(getType(funcID) == "void") {
  	isInt = false;
  }

  ind = 2;
  //std::cout << "funcID = " << funcID << std::endl;
  //std::cout << "args size " << args.size() << "       " << " fsize " <<  func[funcID].size()-1 << std::endl;
  int sz = (func[funcID].size()-2 == 1 && func[funcID][2] == "void" ? 0 : func[funcID].size()-2);
  if(args.size() != sz) {
  	std::cout << "qtd of args different from function" << std::endl;
    exit(0);
    funcID = -1;
    return;
  }

  int oldIsInt = isInt;
  isArg = true;
  for(auto &a : args) {
    isInt = true;
	  a->semantic();
	  if(!isInt) {
	    std::cout << "is not an int expression" << std::endl;
	    exit(0);
	  }
  }
  isArg = false;

  isInt = oldIsInt;
  funcID = -1;
} 

void BinaryOperation::semantic() {
  //printfunc("BinaryOperation");
  if(funcID != -1 && !isOp) {
  	//debug(func[funcID][ind]);
  	//debug(ind);
    if(func[funcID][ind++] != "int") {
      std::cout << "incompatible types in function" << std::endl;
  	  exit(0);
  	}  
  }
  isOp = true;
  isInt = true;
  lhs->semantic();
  if(!isInt) {
    std::cout << "is not an int expression" << std::endl;
    exit(0);
  }
  isOp = true;
  isInt = true;
  rhs->semantic();
  if(!isInt) {
    std::cout << "is not an int expression" << std::endl;
    exit(0);
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


void createScope(bool isArgument) {
  scope.push_back(ss("$","$",isArgument));
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

  while(it->first != "$" || it->isArgument == true) {
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
  scope.push_back(ss(x,type, false));
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