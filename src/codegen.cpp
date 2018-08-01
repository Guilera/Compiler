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

void LOAD_IMMEDIATE(std::string reg, int value, std::ostream &os) {
	os << "li " << reg << " " << value << std::endl;
}
//-----------------------------------------------------------------------------------

struct ss {
	std::string id, typeOfV;
	bool isArgument;

	ss () {}

	ss(std::string id, std::string typeOfV, bool isArgument) : id(id), typeOfV(typeOfV), isArgument(isArgument) {}
};

struct variable {
	int size;
	std::string name;
	
	variable() {}
	variable(std::string name, int size) : name(name), size(size) {}
};

//-----------------------------------------------------------------------------------

std::vector<variable> localDec; // id of variables as local of current function and its size
std::vector<variable> paramDec; // id of variables as parameter of current function and its size 
std::vector<std::vector<std::string> > func;
std::list<ss> scope;
std::string nextBranch;
std::vector<variable> globalVar;
bool isValid = true;
bool isArg = false;
bool isOp = false;
bool next = false;
bool isVoid;
bool isInt = true;
bool isAssign = false;
bool cameFromFunc = false;
int funcID = -1, ind;
int if_counter = 0;
int while_counter = 0;
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
	
	// inicia escopo global
	createScope(false);

	// inicia o programa e chama a função main
	os << "main: " << std::endl;
  	os << "jal _main" << std::endl << std::endl;

	// finaliza o programa (10 é o codigo do sistema para finalizar  o programa)
  	os << "li $v0 10" << std::endl;
	os << "syscall" << std::endl << std::endl;

  	/*** IMPLEMENTAÇÃO DA FUNÇÃO INPUT ***/
  	// adiciona na lista de funções
  	func.emplace_back(std::initializer_list<std::string>{"int", "input", "void"});
  
  	// define o label
  	os << "_input:" << std::endl;

	// move o stack pointer para o frame pointer
  	os << "move $fp $sp" << std::endl;

  	// push return address
  	PUSH(RA, os);
  
  	// lê int (5 é o codigo system call para ler inteiros. O valor lido é armazenado em $v0)
  	LOAD_IMMEDIATE("$v0", 5, os); 
  	os << "syscall " << std::endl;
  
  	// coloca o valor lido no acumulador
  	os << "move $a0 $v0" << std::endl;

  	// pop return address
  	TOP(RA, os);
  	POP(os);

  	// pop frame pointer
  	TOP(FP, os);
  	POP(os);

  	// retorna para quem chamou(return addresss)
  	os << "jr $ra" << std::endl << std::endl;

  	/*** IMPLEMENTAÇÃO DA FUNÇÃO PRINTLN ***/
  	// adiciona na lista de funções
  	func.emplace_back(std::initializer_list<std::string>{"void", "println", "int"});

  	// define o label
  	os << "_println:" << std::endl;

  	// move o stack pointer para o frame pointer
  	os << "move  $fp  $sp" << std::endl;

  	// push return address
  	PUSH(RA, os);

  	// Adiciona o valor do paramêtro no acumulador
  	os << "lw $a0 4($fp)" << std::endl;

  	// imprime o valor do acumulador (1 é o codigo system call para imprimir inteiro armazenado no acumulador)
  	LOAD_IMMEDIATE("$v0", 1, os);
  	os << "syscall" << std::endl;

  	// imprime quebra de linha
  	os << "addi $a0, $0, 0xA" << std::endl; // 0xA é codigo ascii para '\n'
  	os << "addi $v0, $0, 0xB" << std::endl; // 0xB modifica a interpretação do acumulador como codigo ascii
  	os << "syscall" << std::endl;

  	// pop return address e paramêtro
  	TOP(RA, os);
  	nPOP(2, os);

  	// pop frame pointer
  	TOP(FP, os);
  	POP(os);
  
  	// retorna para quem chamou(return addresss)
  	os << "jr $ra" << std::endl << std::endl; 

  	// codegen das declarações globais(variaveis e funções)
  	for(auto dec: declaration_list) {
		dec->codegen(os);
  	}
  
  	// finaliza escopo global
  	exitScope(os,0);

  	// aloca todas as variaveis globais	
  	os << std::endl << ".data" << std::endl;
  	for(variable x: globalVar) {
		os << x.name << ":    .space " << x.size * 4 << std::endl;
	}
}

void VariableDeclaration::codegen(std::ostream &os) {
	
	// se não pertencer a esse escopo, significa que não foi declarada, então declara
	if(!isInThisScope(id)) {
		std::string tipo = (type == INT) ? "int" : "void";

		// se num for diferente de zero, significa que a variavel é um array de tamanho igual 'num', caso contrário é um inteiro
		int allocation_size = num ? num : 1;

		// adiciona a variavel no escopo atual
		addVar(id,tipo);

		// se o escopo for local reserva espaço na pilha,
		// caso contrário o tamanho será reservado no '.data'
		if(!isScopeGlobal()) {
			localDec.emplace_back(id, allocation_size);
			os << "addiu $sp $sp -" << allocation_size * 4 << std::endl;
		} else {
			// put in data
			globalVar.push_back(variable(id, allocation_size));
		}
	}
}

void Param::codegen(std::ostream &os) {
	
	// se não pertencer a esse escopo então adiciona
	if(!isInThisScope(id)) {
		std::string tipo;
		if(type == INT) {
			tipo = is_array ? "array" : "int";
			paramDec.emplace_back(id, 1);
		} else if(type == VOID) {
			tipo = "void";
		}
		addVar(id,tipo);
	}
}

void CompoundStatement::codegen(std::ostream &os) {

	createScope(next);
	next = false;

	// flag de aninhamento: guarda a informação se este compound está aninhado ou não
	bool saveCome = cameFromFunc;
	cameFromFunc = false;

	// codegen de todas as declarações de variaveis locais
	for(auto local_dec : local_declarations)
		local_dec->codegen(os);

	// codegen de todos os statements pertencentes a esse compound
	for(auto stmt : statement_list)
		stmt->codegen(os);

	// reseta a flag de aninhamento original
	cameFromFunc = saveCome;

	// zera o contador de declarações locais pendentes
	contaSizeLocalDec = 0;

	// finaliza escopo passando a flag de aninhamento
	exitScope(os, saveCome);
}

void FunctionDeclaration::codegen(std::ostream &os) {

	// define o label desta função a partir do seu id
	os << '_' << id << ':' << std::endl;

	// desloca o stack pointer para o frame pointer
	os << "move $fp $sp" << std::endl;

	// push return address
	PUSH(RA, os);

	// inicia escopo da função
	createScope(false);
	next = true;

	/*** adiciona na lista de funções ***/
	func.push_back(std::vector<std::string>());

	// define o tipo de retorno
	if (type == INT) {
		func.back().push_back("int");
		isVoid = false;
	} else if (type == VOID) {
		func.back().push_back("void");
		isVoid = true;
	}

	// define o seu nome
	func.back().push_back(id);

	// define o tipo de cada parametro
	if(param_list.size() == 0)
		func.back().push_back("void");

	for(auto param : param_list) {
		if(param->is_array)
			func.back().push_back("array");
		else if(param->type == VOID)
			func.back().push_back("void");
		else
			func.back().push_back("int");

		// codegen de cada parametro
		param->codegen(os);
	}

	// define flag de aninhamento
	cameFromFunc = true;

	// codegen do código da função
	compound_stmt->codegen(os);  
	cameFromFunc = false;

	// label de finalização da função
	os << "_end_function_" << id << ':' << std::endl;

	// pop variaveis locais
	nPOP(contaSizeLocalDec, os);
	
	// pop return address
	TOP(RA, os);
	POP(os);

	// reseta contador de declarações locais e finaliza o escopo da função
	contaSizeLocalDec = 0;
	exitScope(os,false);

	// pop frame pointer
	TOP(FP, os);
	POP(os);

	// retorna para o chamador
	os << "jr $ra" << std::endl << std::endl;
}

void Selection::codegen(std::ostream &os) {
	
	// cria escopo do if
	createScope(false);

	isInt = true;

	// pega o valor do contador de if's 
	int current_if = if_counter++;

	// codegen da expressão do if, o valor final da expressão estará no acumulador
	expression->codegen(os);

	/* compara o valor do acumulador com $0.
	 * if 0 then não entra
	 * else entra
	 */
	os << "bne $0 $a0 " << "_begin_if_" << current_if << std::endl;

	// executa o codegen do else, se houver, caso contrário encerra o if
	if(else_stmt)
	else_stmt->codegen(os);
	os << "j _end_if_" << current_if << std::endl;  

	// label de inicialização do if
	os << "_begin_if_" << current_if << ':' << std::endl;

	// codegen do if
	if_stmt->codegen(os);

	// label de finalização do if
	os << "_end_if_" << current_if << ':' << std::endl;
	
	// finaliza o escopo da função
	exitScope(os,false);
}

void Iteration::codegen(std::ostream &os) {
	
	// cria escopo para o while
	createScope(false);
	
	// pega o valor do contador de while's
	int current_while = while_counter++;

	// label de inicialização do while
	os << "_begin_while_" << current_while << ":" << std::endl;
	isInt = true;

	// codegen da expressão do while. O resultado da expressão estará no acumulador
	expression->codegen(os);

	/* compara o valor do acumulador com $0.
	 * if 0 then finaliza
	 * else continua
	 */
	os << "beq $0 $a0 " << "_end_while_" << current_while << std::endl;

	// codegen do bloco do while
	statement->codegen(os);

	// loop jump
	os << "j _start_while_" << current_while << std::endl;

	// label de finalização do while
	os << "_end_while_" << current_while << ':' << std::endl;

	// finaliza o escopo do while
	exitScope(os,false);
} 

void Return::codegen(std::ostream &os) {
	if(expression) {
		isInt = true;
		expression->codegen(os);
	}

	// jump para o label da ultima função adiconada na lista de funções
	os << "j _end_function_" << func.back()[1] << std::endl;
} 

void Variable::codegen(std::ostream &os) {

	std::string aux = isDeclared(id);
	bool globalScope = false;

	if(!isAssign && !isArg) {
		// pega o indice do parametro em ao relação frame pointer
		int parameter_index = indexFromFpParam(func.size() - 1, id);
		
		// verifica se é um index válido
		if(parameter_index != -1){

			// se não for um array
			if(!expression) {
				os << "lw $a0 " << parameter_index << "($fp)"  << std::endl;
			} else if(expression) {
				// se for array load a partir do primeiro endereço
				os << "addiu $a0 $fp " << parameter_index << std::endl;
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
			// pertence ao escopo global
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

			if(aux == "int")
				os << "lw $a0 " << indexFromFpLocal(id) << "($fp) " << std::endl;
			else if(aux == "array")				
				os << "addiu $a0 $fp " << indexFromFpLocal(id) << std::endl;

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
			if(!expression)
				os << "addiu $a0 " << "$fp " << indexFromFpLocal(id) << std::endl;
			else
				os << "addiu $a0 $fp " << indexFromFpLocal(id) << std::endl;
		} else {
			// global scope
			globalScope = true;
			if(!expression)
				os << "la $a0 " << id << std::endl;
			else
				os << "la $a0 " << id << std::endl;
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
			LOAD_IMMEDIATE(TEMP, 4, os);
		else
			LOAD_IMMEDIATE(TEMP, -4, os);
		
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
	
	// codegen da expresão (rhs)
	expression->codegen(os);
	
	// push acumulador
	PUSH(ACC, os);

	// seta flag de assignment
	isAssign = true;
	
	// codegen da variavel
	var->codegen(os);

	// reseta flag
	isAssign = false;

	// pop valor da expressão para temp
	TOP(TEMP, os);
	POP(os);

	// assingment
	os << "sw $t0 0($a0)" << std::endl;
	os << "addiu $a0 $t0 0" << std::endl;

	isInt = true;
} 

void FunctionCall::codegen(std::ostream &os) {

	funcID = idOfFunction(id);

	if(getType(funcID) == "void") {
		isInt = false;
	}

	// push frame pointer
	PUSH(FP, os);

	// TODO: explicar
	ind = 2;
	int sz = (func[funcID].size()-2 == 1 && func[funcID][2] == "void" ? 0 : func[funcID].size()-2);
	if(args.size() != sz) {
		funcID = -1;
		return;
	}

	// flags
	int oldIsInt = isInt;
	isArg = true;

	// push argumentos
	for(auto it = args.rbegin(); it != args.rend(); it++) {
		isInt = true;
		(*it)->codegen(os);
		PUSH(ACC, os);
	}

	// jump para a função
	os << "jal _" << id << std::endl;
	
	// flags
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

	// flags
	isOp = true;
	isInt = true;

	// codegen do lhs
	lhs->codegen(os);

	// push resultado(acumulador)
	PUSH(ACC, os);
	
	// flags
	isOp = true;
	isInt = true;

	// codegen rhs (resultado no acumulador)
	rhs->codegen(os);

	// pop o resultado do rhs do topo da pilha
	TOP(TEMP, os);
	POP(os);

	if(mapa.count(op)) {
		// operações aritimeticas
  		os << mapa[op] << " $a0  $t0  $a0" << std::endl;
	} else {
		if(op == "==") {
			// objetivo 
			// a0 = t0 - a0
			os << "sub $a0 $t0 $a0" << std::endl;
			
			// se a0 > 0 ou a0 < 0 então 0 < |a0| é verdadeiro, ou seja, a0 != 0;	a0 <- 1
			// caso contrario a0 == 0 então 0 < 0 é falso, ou seja, a0 == 0;		a0 <- 0
			os << "sltu $a0 $0 $a0" << std::endl;

			// transforma false em true
			// XOR 0 1 ou XOR 1 0 então 1 (true)
			// XOR 1 1 ou XOR 0 0 então 0 (false)
			os << "xori $a0 $a0 1" << std::endl;
		}else if(op == "<") {
			// se t0 < a0 então a0 = 1 senão a0 = 0
			os << "slt $a0 $t0 $a0" << std::endl;  		
		} else if(op == "<=") {
			// se a0 < t0 então t0 > a0 portanto a0 = 1
			// se a0 >= t0 então to
			os << "slt $a0 $a0 $t0" << std::endl;
			os << "xori $a0 $a0 1" << std::endl;
		} else if(op == ">") {
			os << "slt $a0 $a0 $t0" << std::endl;
		} else if(op == ">=") {
			os << "slt $a0 $t0 $a0" << std::endl;  		
			os << "xori $a0 $a0 1" << std::endl;
		} else if(op == "!=") {
			os << "sub $a0 $t0 $a0" << std::endl;
			os << "sltu $a0 $0 $a0" << std::endl;
		}
	}
  isOp = false;
} 

void Number::codegen(std::ostream &os) {
	// carrega o valor imediato no acumulador
	LOAD_IMMEDIATE(ACC, number, os);
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
				os << "addiu $sp $sp " << (*iterator).size*4 << std::endl;
			else 
				contaSizeLocalDec += (*iterator).size; 
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

int indexFromFpParam(int lastFunc, std::string variable_name) {
	int count = 4;
	for(auto param : paramDec) {
		if(param.name == variable_name)
			return count;
		count += 4;
	}

	return -1;  
}

int indexFromFpLocal(std::string var) {

	int count = 4;
	for(auto local : localDec) {
		count += local.size*4;
	}
	
	for(int i = localDec.size()-1; i >= 0; i--) {
		count -= localDec[i].size*4;
		if(localDec[i].name == var) 
			return -count;
	}

	return -1;
}

bool isVarGlobal(std::string id) {
	for(variable x: globalVar) {
		if(x.name == id)
			return true;
	}
	return false;
}