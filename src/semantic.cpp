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
std::string getType(int id);

//-----------------------------------------------------------------------------------

void Node::semantic() {}

void Program::semantic() {
  func.push_back(std::vector<std::string>());
  func.push_back(std::vector<std::string>());
  func[0].push_back("int");
  func[0].push_back("input");
  func[0].push_back("void");
  func[1].push_back("void");
  func[1].push_back("println");
  func[1].push_back("int");
  createScope(false);

  for(auto dec: declaration_list) {
    dec->semantic();
  }
  exitScope();
  if(func.back().size() != 3 || func.back()[1] != "main" || func.back()[2] != "void" || !isVoid) {
  	std::cout << "Error in declaration of function main" << std::endl;
  	exit(0);
  }
}

void VariableDeclaration::semantic() {

  if(idOfFunction(id) != -1 && isScopeGlobal()) {
    std::cout << "Id " << id << " was already decleared as a function" << std::endl;  
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
      std::cout << "Wrong void declaration globally" << std::endl;
      exit(0);
    }
    addVar(id,tipo);
  } else {
    std::cout << "Two variables with the same id in the same scope: " << id << std::endl;
    exit(0);
  }
}

void Param::semantic() {

  if(!isInThisScope(id)) {
    std::string tipo;
    if(type == INT)
      tipo = "int";
    if(is_array)
      tipo = "array";
    if(type == VOID)
      tipo = "void";
    addVar(id,tipo);
  } else {
    std::cout << "Two variables with the same id in the same scope: " << id << std::endl;
    exit(0);
  }
}

void CompoundStatement::semantic() {

	createScope(next);
  next = false;

  for(auto local_dec : local_declarations) {
    if(local_dec->type == VOID) {
      std::cout << "Wrong void declaration inside function" << std::endl;
      exit(0);
    }
    local_dec->semantic();
  }

  for(auto stmt : statement_list)
    stmt->semantic();

  exitScope();
}

void FunctionDeclaration::semantic() {

  if(idOfFunction(id) != -1) {
  	std::cout << "Function " << id << " was already decleared" << std::endl;
  	exit(0);
  }

  if(isDeclared(id) != "") {
  	std::cout << "Id " << id << " was already decleared as a var" << std::endl;
  	exit(0);
  }
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
    if(param->type == VOID && (param->id > "&" || param_list.size() > 1)) {
      std::cout << "Wrong void declaraion in parameter" << std::endl;
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
  
  exitScope();
}

void Selection::semantic() {

	createScope(false);

  isInt = true;
  expression->semantic();
  if(!isInt) {
  	std::cout << "Is not an int expression" << std::endl;
  	exit(0);
  }
  if_stmt->semantic();
  if(else_stmt)
    else_stmt->semantic();

  exitScope();
}

void Iteration::semantic() {

	createScope(false);
  isInt = true;
  expression->semantic();
  if(!isInt) {
  	std::cout << "Is not an int expression" << std::endl;
  	exit(0);
  }
  statement->semantic();
  exitScope();
} 

void Return::semantic() {

  if(isVoid && expression) {
    std::cout << "Error found in function return " << std::endl;
    exit(0);
  } else if(!isVoid && !expression) {
    std::cout << "Error found in function return " << std::endl;
    exit(0);
  }
  if(expression) {
    isInt = true;
	  expression->semantic();
	  if(!isInt) {
	  	std::cout << "Is not an int expression" << std::endl;
	  	exit(0);
	  }
  }
} 

void Variable::semantic() {

  std::string aux = isDeclared(id);
  if(aux == "") {
    std::cout << "Variable " << id << " wasnt declared" << std::endl;
    exit(0);
  }  

  if(expression && aux == "int") {
    std::cout << "Int declared as array" << std::endl;
    exit(0);
  }

  if(!expression && aux == "array" && !isArg) {
    std::cout << "Array without index " << std::endl;
    exit(0);
  }

  if(funcID != -1 && !isOp) {
  	if(aux == "array" && expression)
  		aux = "int";
    if(func[funcID][ind++] != aux) {
      std::cout << "Incompatible types in function" << std::endl;
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
			std::cout << "Is not an int expression" << std::endl;
			exit(0);
		}
  }

  funcID = saveID;
} 


void Assign::semantic() {

  var->semantic();
	isInt = true;
	expression->semantic();
	if(!isInt) {
		std::cout << "Is not an int expression" << std::endl;
		exit(0);
	}
} 

void FunctionCall::semantic() {

  if(idOfFunction(id) == -1) {
    std::cout << "Function wasnt declared" << std::endl;
    exit(0);
    return;
  }

  funcID = idOfFunction(id);

  if(getType(funcID) == "void") {
  	isInt = false;
  }

  ind = 2;
  int sz = (func[funcID].size()-2 == 1 && func[funcID][2] == "void" ? 0 : func[funcID].size()-2);
  if(args.size() != sz) {
  	std::cout << "Qtd of args different from function" << std::endl;
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
  if(funcID != -1 && !isOp) {
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