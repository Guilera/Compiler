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
std::vector<std::vector<std::string> > funcCGen;
std::list<ss> scopeCGen;
std::string nextBranch;
std::vector<variable> globalVar;
bool isArgCGen = false;
bool isOpCGen = false;
bool nextCGen = false;
bool isVoidCGen;
bool isIntCGen = true;
bool isAssignCGen = false;
bool cameFromFuncCGen = false;
int funcIDCGen = -1, indCGen;
int if_counter = 0;
int while_counter = 0;
int SizeLocalDec_counter = 0;

//-----------------------------------------------------------------------------------

void createScopeCGen(bool isArgument);
void exitScopeCGen(std::ostream &os, bool cameFromF);
bool isInThisScopeCGen(std::string x);
bool isScopeGlobalCGen();
void addVarCGen(std::string x, std::string type);
std::string isDeclaredCGen(std::string x);
int idOfFunctionCGen(std::string x);
std::string getTypeCGen(int id);
int indexFromFpParamCGen(int funcIDCGen, std::string var);
int indexFromFpLocalCGen(std::string var);

//-----------------------------------------------------------------------------------

void Node::codegen(std::ostream &os) {}

void Program::codegen(std::ostream &os) {

	os << ".text" << std::endl << std::endl;
	
	// inicia escopo global
	createScopeCGen(false);

	// inicia o programa e chama a função main
	os << "main: " << std::endl;
  	os << "jal _main" << std::endl << std::endl;

	// finaliza o programa (10 é o codigo do sistema para finalizar  o programa)
	os << "_end_program:" << std::endl;
  	os << "li $v0 10" << std::endl;
	os << "syscall" << std::endl << std::endl;

  	/*** IMPLEMENTAÇÃO DA FUNÇÃO INPUT ***/
  	// adiciona na lista de funções
  	funcCGen.emplace_back(std::initializer_list<std::string>{"int", "input", "void"});
  
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
  	funcCGen.emplace_back(std::initializer_list<std::string>{"void", "println", "int"});

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
  	exitScopeCGen(os,0);

  	// aloca todas as variaveis globais	
  	os << std::endl << ".data" << std::endl;
  	for(variable x: globalVar) {
		os << x.name << ":    .space " << x.size * 4 << std::endl;
	}
}

void VariableDeclaration::codegen(std::ostream &os) {
	
	// se não pertencer a esse escopo, significa que não foi declarada, então declara
	if(!isInThisScopeCGen(id)) {
		std::string tipo = (type == INT) ? (num ? "array" :"int") : "void";
		
		// se num for diferente de zero, significa que a variavel é um array de tamanho igual 'num', caso contrário é um inteiro
		int allocation_size = num ? num : 1;

		// adiciona a variavel no escopo atual
		addVarCGen(id,tipo);

		// se o escopo for local reserva espaço na pilha,
		// caso contrário o tamanho será reservado no '.data'
		if(!isScopeGlobalCGen()) {
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
	if(!isInThisScopeCGen(id)) {
		std::string tipo;
		if(type == INT) {
			tipo = is_array ? "array" : "int";
			paramDec.emplace_back(id, 1);
		} else if(type == VOID) {
			tipo = "void";
		}
		addVarCGen(id,tipo);
	}
}

void CompoundStatement::codegen(std::ostream &os) {

	createScopeCGen(nextCGen);
	nextCGen = false;

	// flag de aninhamento: guarda a informação se este compound está aninhado ou não
	bool saveCome = cameFromFuncCGen;
	cameFromFuncCGen = false;

	// codegen de todas as declarações de variaveis locais
	for(auto local_dec : local_declarations)
		local_dec->codegen(os);

	// codegen de todos os statements pertencentes a esse compound
	for(auto stmt : statement_list)
		stmt->codegen(os);

	// reseta a flag de aninhamento original
	cameFromFuncCGen = saveCome;

	// zera o contador de declarações locais pendentes
	SizeLocalDec_counter = 0;

	// finaliza escopo passando a flag de aninhamento
	exitScopeCGen(os, saveCome);
}

void FunctionDeclaration::codegen(std::ostream &os) {

	// define o label desta função a partir do seu id
	os << '_' << id << ':' << std::endl;

	// desloca o stack pointer para o frame pointer
	os << "move $fp $sp" << std::endl;

	// push return address
	PUSH(RA, os);

	// inicia escopo da função
	createScopeCGen(false);
	nextCGen = true;

	/*** adiciona na lista de funções ***/
	funcCGen.push_back(std::vector<std::string>());

	// define o tipo de retorno
	if (type == INT) {
		funcCGen.back().push_back("int");
		isVoidCGen = false;
	} else if (type == VOID) {
		funcCGen.back().push_back("void");
		isVoidCGen = true;
	}

	// define o seu nome
	funcCGen.back().push_back(id);

	// define o tipo de cada parametro
	if(param_list.size() == 0)
		funcCGen.back().push_back("void");

	for(auto param : param_list) {
		if(param->is_array)
			funcCGen.back().push_back("array");
		else if(param->type == VOID)
			funcCGen.back().push_back("void");
		else
			funcCGen.back().push_back("int");

		// codegen de cada parametro
		param->codegen(os);
	}

	// define flag de aninhamento
	cameFromFuncCGen = true;

	// codegen do código da função
	compound_stmt->codegen(os);  
	cameFromFuncCGen = false;

	// label de finalização da função
	os << "_end_function_" << id << ':' << std::endl;

	// pop variaveis locais
	nPOP(SizeLocalDec_counter, os);
	
	// pop return address
	TOP(RA, os);
	POP(os);

	// reseta contador de declarações locais e finaliza o escopo da função
	SizeLocalDec_counter = 0;
	exitScopeCGen(os,false);

	// pop frame pointer
	TOP(FP, os);
	POP(os);

	// retorna para o chamador
	os << "jr $ra" << std::endl << std::endl;
}

void Selection::codegen(std::ostream &os) {
	
	// cria escopo do if
	createScopeCGen(false);

	isIntCGen = true;

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
	exitScopeCGen(os,false);
}

void Iteration::codegen(std::ostream &os) {
	
	// cria escopo para o while
	createScopeCGen(false);
	
	// pega o valor do contador de while's
	int current_while = while_counter++;

	// label de inicialização do while
	os << "_begin_while_" << current_while << ":" << std::endl;
	isIntCGen = true;

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
	os << "j _begin_while_" << current_while << std::endl;

	// label de finalização do while
	os << "_end_while_" << current_while << ':' << std::endl;

	// finaliza o escopo do while
	exitScopeCGen(os,false);
} 

void Return::codegen(std::ostream &os) {
	if(expression) {
		isIntCGen = true;
		expression->codegen(os);
	}

	// jump para o label da ultima função adiconada na lista de funções
	os << "j _end_function_" << funcCGen.back()[1] << std::endl;
} 

void Variable::codegen(std::ostream &os) {

	std::string aux = isDeclaredCGen(id);
	bool globalScope = false;

	// CASO da variavel sendo acessada no rhs de um expressão
	if(!isAssignCGen && !isArgCGen) {
		// pega o indice do parametro em ao relação frame pointer
		int parameter_index = indexFromFpParamCGen(funcCGen.size() - 1, id);
		int local_index = indexFromFpLocalCGen(id);
		// verifica se é um index válido
		if(local_index != -1) {
			if(!expression) {
				os << "lw $a0 " << local_index << "($fp) " << std::endl;
			} else if(expression) {
				os << "addiu $a0 $fp" << local_index << std::endl;
			}
		} else if(parameter_index != -1){
			// se não for um array
			if(!expression) {
				os << "lw $a0 " << parameter_index << "($fp)"  << std::endl;
			} else if(expression) {
				// se for array load a partir do primeiro endereço
				os << "addiu $a0 $fp " << parameter_index << std::endl;
				os << "lw $a0 0($a0)" << std::endl;
			}
		}  else {
			// pertence ao escopo global
			globalScope = true;
		
			// carrega o endereço da variavel (int ou array[x])
			os << "la $a0 " << id << std::endl;

			if(aux == "int") {
				// se não for array então carrega o valor da variavel
				os << "lw $a0 0($a0)" << std::endl;
			}
		}
		
	// CASO da variavel sendo passada como argumento de alguma função 
	} else if(isArgCGen) {

		if(indexFromFpLocalCGen(id) != -1) {

			if(aux == "int") {
				// se esta no local e é inteiro recupera ele da pilha com index negativo
				os << "lw $a0 " << indexFromFpLocalCGen(id) << "($fp) " << std::endl;
			}
			else if(aux == "array")	{
				// se é um vetor pega o endereço de vetor[0] e depois avalia seu offset
				os << "addiu $a0 $fp " << indexFromFpLocalCGen(id) << std::endl;
			}

		} else if(indexFromFpParamCGen(funcCGen.size()-1, id) != -1){

			if(aux == "int"){
				// se for argumento e estiver nos parametros e for do tipo int entao carrega o valor presente nos parametros
				os << "lw $a0 " << indexFromFpParamCGen(funcCGen.size()-1, id) << "($fp) "  << std::endl;
			} else if(aux == "array") {
				// se for argumento e for do tipo array entao o valor correspodente lá sera o endereço e deve-se carregar ele e avaliá-lo depois
				os << "addiu $a0 $fp " << indexFromFpParamCGen(funcCGen.size()-1, id) << std::endl;
				os << "lw $a0 0($a0)" << std::endl;
			}

		} else {
			// global scope
			globalScope = true;
			
			// carrega o endereço da variavel (int ou array[x])
			os << "la $a0 " << id << std::endl;

			// se não tem expression e for do tipo int retornar o valor da variavel
			if(!expression && aux == "int") {
				// carrega o valor da variavel
				os << "lw $a0 0($a0)" << std::endl;
			}
		}

	// CASO da variavel sendo atribuida um valor, lhs de uma expressão
	} else if (isAssignCGen) {

		if(indexFromFpLocalCGen(id) != -1) {
			if(!expression)
				os << "addiu $a0 " << "$fp " << indexFromFpLocalCGen(id) << std::endl;
			else
				os << "addiu $a0 $fp " << indexFromFpLocalCGen(id) << std::endl;
		} else if(indexFromFpParamCGen(funcCGen.size()-1, id) != -1){

			if(!expression){
				// se esta nos parametros entao retorna o endereço da variavel nos parametros
				os << "addiu $a0 " << "$fp " << indexFromFpParamCGen(funcCGen.size()-1, id) << std::endl;
			}
			else if(expression) {
				// se é um vetor e esta nos parametros
				os << "addiu $a0 $fp " << indexFromFpParamCGen(funcCGen.size()-1, id) << std::endl;
				os << "lw $a0 0($a0)" << std::endl;
			}
		} else {
			// global scope
			// se é global então retorna o ponteiro
			globalScope = true;
			os << "la $a0 " << id << std::endl;
		}
		
	}

	// salva pra n se perder na recursão
	int saveID = funcIDCGen;
	if(aux == "array")  {
		funcIDCGen = -1;
	}

	if(expression) {
		// se é um vetor, entao avalia-se o offset
		isIntCGen = true;

		// push endereço do array
		PUSH(ACC, os);
		bool saveAssign = isAssignCGen, saveArg = isArgCGen;
		isAssignCGen = false; 
		isArgCGen = false;
		// avalia a expressao
		expression->codegen(os);

		// se o valor no acumulador for negativo (acesso de memoria invalida) finaliza a execução
		os << "bltz $a0, _end_program" << std::endl;
		isAssignCGen = saveAssign; 
		
		if(globalScope) {
			// se é global o offset é igual a posição * 4
			LOAD_IMMEDIATE(TEMP, 4, os);
		} else {
			// se é local o offset é igual a posição * -4
			LOAD_IMMEDIATE(TEMP, -4, os);
		}
		
		os << "mul $a0 $a0 $t0" << std::endl;
		TOP(TEMP, os);
		POP(os);
		// retorna o endereço da variável
		os << "add $a0 $a0 $t0" << std::endl;
		if(!isAssignCGen) {
			// se não é um caso de assign (vai armazenar no endereço depois) retorna o valor
			os << "lw $a0 0($a0)" << std::endl;
		}
	}

	funcIDCGen = saveID;
}

void Assign::codegen(std::ostream &os) {
	
	// codegen da expresão (rhs)
	expression->codegen(os);
	
	// push acumulador
	PUSH(ACC, os);

	// seta flag de assignment
	isAssignCGen = true;
	
	// codegen da variavel
	var->codegen(os);

	// reseta flag
	isAssignCGen = false;

	// pop valor da expressão para temp
	TOP(TEMP, os);
	POP(os);

	// assignment
	os << "sw $t0 0($a0)" << std::endl;
	os << "addiu $a0 $t0 0" << std::endl;

	isIntCGen = true;
} 

void FunctionCall::codegen(std::ostream &os) {

	funcIDCGen = idOfFunctionCGen(id);

	if(getTypeCGen(funcIDCGen) == "void") {
		isIntCGen = false;
	}

	// push frame pointer
	PUSH(FP, os);

	indCGen = 2;
	
	// flags
	int oldIsInt = isIntCGen;

	// push argumentos
	for(auto it = args.rbegin(); it != args.rend(); it++) {
		isArgCGen = true;
		isIntCGen = true;
		(*it)->codegen(os);
		PUSH(ACC, os);
	}

	// jump para a função
	os << "jal _" << id << std::endl;
	
	// flags
	isArgCGen = false;
	isIntCGen = oldIsInt;
	funcIDCGen = -1;
} 

void BinaryOperation::codegen(std::ostream &os) {

	std::map<std::string,std::string> mapa;
	mapa["+"] = "add";
	mapa["-"] = "sub";
	mapa["*"] = "mul";
	mapa["/"] = "div"; 

	// flags
	isOpCGen = true;
	isIntCGen = true;

	// codegen do lhs
	lhs->codegen(os);

	// push resultado(acumulador)
	PUSH(ACC, os);
	
	// flags
	isOpCGen = true;
	isIntCGen = true;

	// codegen rhs (resultado no acumulador)
	rhs->codegen(os);

	// pop o resultado do rhs do topo da pilha
	TOP(TEMP, os);
	POP(os);

	if(mapa.count(op)) {
		// operações aritimeticas
  		os << mapa[op] << " $a0  $t0  $a0" << std::endl;
	} else {
		// XOR x 1 nega o valor de x
		// XOR 0 1 -> 1 (true)
		// XOR 1 0 -> 1 (true)
		// XOR 1 1 -> 0 (false)
		
		if(op == "==") {
			// objetivo t0 == a0 ? true(a0 = 1) : false(a0 = 0)

			// a0 = t0 - a0
			os << "sub $a0 $t0 $a0" << std::endl;
			
			// se a0 > 0 ou a0 < 0 então 0 < |a0| -> true, ou seja, a0 != 0;	a0 <- 1
			// caso contrario a0 == 0 então 0 < 0 -> falso;						a0 <- 0
			os << "sltu $a0 $0 $a0" << std::endl;

			// inverte o valor de a0
			os << "xori $a0 $a0 1" << std::endl;

		}else if(op == "<") {
			// objetivo t0 < a0 ? true(a0 = 1) : false(a0 = 0)

			// se t0 < a0 então a0 = 1 senão a0 = 0
			os << "slt $a0 $t0 $a0" << std::endl;  		
		} else if(op == "<=") {
			// objetivo t0 <= a0 ? true(a0 = 1) : false(a0 = 0)

			// se a0 > t0 então -> a0 = 1(true)
			// se a0 >= t0 então to
			os << "slt $a0 $a0 $t0" << std::endl;
			os << "xori $a0 $a0 1" << std::endl;
		} else if(op == ">") {
			// inverso do <
			// retorna t0 > a0
			os << "slt $a0 $a0 $t0" << std::endl;
		} else if(op == ">=") {
			// se t0 < a0 -> a0 = 1, caso t0 >= a0 -> a0 = 0
			// o xori inverte os bits, ou seja, se a0 = 1 -> a0 = 0 e vice-versa
			os << "slt $a0 $t0 $a0" << std::endl;  		
			os << "xori $a0 $a0 1" << std::endl;
		} else if(op == "!=") {
			// objetivo 
			// a0 = t0 - a0
			os << "sub $a0 $t0 $a0" << std::endl;
			// se a0 > 0 ou a0 < 0 então 0 < |a0| é verdadeiro, ou seja, a0 != 0;	a0 <- 1
			// caso contrario a0 == 0 então 0 < 0 é falso, ou seja, a0 == 0;		a0 <- 0
			os << "sltu $a0 $0 $a0" << std::endl;
		}
	}
  isOpCGen = false;
} 

void Number::codegen(std::ostream &os) {
	// carrega o valor imediato no acumulador
	LOAD_IMMEDIATE(ACC, number, os);
} 

// ---------------------------------------------------------------------------------------


void createScopeCGen(bool isArgument) {

	scopeCGen.push_back(ss("$","$",isArgument));
}

void exitScopeCGen(std::ostream &os, bool cameFromF) {

	if(scopeCGen.size() == 0)
	return;

	auto it = scopeCGen.end();
	it--;
	while(it->id != "$") {
		std::string toDelete = it->id;
		it = scopeCGen.erase(it);
		it--;
		
		bool f = true;
		for(auto iterator = localDec.begin(); iterator != localDec.end(); iterator++) {
			if((*iterator).name == toDelete) {
				f = false;
			if(!cameFromF)
				os << "addiu $sp $sp " << (*iterator).size*4 << std::endl;
			else 
				SizeLocalDec_counter += (*iterator).size; 
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
	scopeCGen.erase(it);

}

bool isInThisScopeCGen(std::string x) {
	auto it = scopeCGen.rbegin();

	while(it->id != "$" || it->isArgument == true) {
		if(it->id == x)
			return true;
		it++;
	}
	return false;
}

bool isScopeGlobalCGen() {
	int c = 0;
	for(auto it: scopeCGen) {
	if(it.id == "$")
		c++;
	}
	return (c==1);
}

void addVarCGen(std::string x, std::string type) {
	scopeCGen.push_back(ss(x,type, false));
}

std::string isDeclaredCGen(std::string x) {
	for(auto it = scopeCGen.rbegin(); it != scopeCGen.rend(); it++) {
		if(it->id == x)
			return it->typeOfV;
	}
	return "";
}

int idOfFunctionCGen(std::string x) {
	for(int i = 0; i < funcCGen.size(); i++) {
	if(funcCGen[i][1] == x) {
		return i;
	}
	}
	return -1;
}

std::string getTypeCGen(int id) {
	if(funcCGen[id][0] == "void") {
		return "void";
	}
	return "int";
}

int indexFromFpParamCGen(int lastFunc, std::string variable_name) {
	int count = 4;
	for(auto param : paramDec) {
		if(param.name == variable_name)
			return count;
		count += 4;
	}

	return -1;  
}

int indexFromFpLocalCGen(std::string var) {

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
