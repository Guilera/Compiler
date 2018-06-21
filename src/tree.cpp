//
// Created by Bruno Guilera on 01/06/18.
//

#include "tree.hpp"
#include "parser.hpp"

using namespace tree;

void Node::print(std::ostream &) {}

void Expression::print(std::ostream &os) {
  os << "[;]";
}

Program::Program() {}

void Program::print(std::ostream &os) {
  os << "[program" << std::endl;
  for(auto dec : declaration_list)
	dec->print(os);
  os << "]" << std::endl;
}

Declaration::Declaration(int type, std::string &id) : type(type), id(id) {}

VariableDeclaration::VariableDeclaration(int type, std::string &id, int num) : Declaration(type, id), num(num) {}

VariableDeclaration::VariableDeclaration(int type, std::string &id) : VariableDeclaration(type, id, 0) {}

void VariableDeclaration::print(std::ostream &os) {
  os << "[var-declaration [";
  if(type == INT)
    os << "int";
  if(type == VOID)
    os << "void";
  os << "] [" << id << "]";
  if(num)
    os << "[" << num << "]";
  os << "]" << std::endl;
}

Param::Param(int type, std::string &id) : type(type), id(id), is_array(false) {}

Param::Param(int type, std::string &id, bool) : type(type), id(id), is_array(true) {}

void Param::print(std::ostream &os) {
  os << "[param";
  os << " [";
  if(type == INT)
	os << "int";
  if(type == VOID)
	os << "void";
  os << "] " << "[" << id << "]";
  if(is_array)
    os << "[\\[\\]]";
  os << "]";
}

CompoundStatement::CompoundStatement(std::vector<std::shared_ptr<VariableDeclaration>> &local_declarations, std::vector<std::shared_ptr<Statement>> &statement_list) : local_declarations(local_declarations), statement_list(statement_list) {}

void CompoundStatement::print(std::ostream &os) {
  os << "[compound-stmt" << std::endl;
  for(auto local_dec : local_declarations)
    local_dec->print(os);
  for(auto stmt : statement_list)
    stmt->print(os);
  os << "]";
}

FunctionDeclaration::FunctionDeclaration(int type, std::string &id, std::shared_ptr<CompoundStatement> compound_stmt) : Declaration(type, id), compound_stmt(compound_stmt) {}

FunctionDeclaration::FunctionDeclaration(int type, std::string &id, std::vector<std::shared_ptr<Param>> &param_list, std::shared_ptr<CompoundStatement> compound_stmt) : Declaration(type, id), compound_stmt(compound_stmt), param_list(param_list) {}

void FunctionDeclaration::print(std::ostream &os) {
  os << "[fun-declaration" << std::endl;
  if (type == INT)
	os << "[int]";
  else if (type == VOID)
	os << "[void]";
  os << std::endl;
  os << "[" << id << "]" << std::endl;
  os << "[params";
  for (auto param : param_list) {
	os << std::endl;
	param->print(os);
  }
  os << "]" << std::endl;
  compound_stmt->print(os);
  os << std::endl << "]" << std::endl;
}

Selection::Selection(std::shared_ptr<Expression> expression, std::shared_ptr<Statement> if_stmt) : expression(expression), if_stmt(if_stmt) {}

Selection::Selection(std::shared_ptr<Expression> expression, std::shared_ptr<Statement> if_stmt, std::shared_ptr<Statement> else_stmt) : expression(expression), if_stmt(if_stmt), else_stmt(else_stmt) {}

void Selection::print(std::ostream &os) {
  os << "[selection-stmt" << std::endl;
  expression->print(os);
  os << std::endl;
  if_stmt->print(os);
  os << std::endl;
  if(else_stmt)
  	else_stmt->print(os);
  os << "]" << std::endl;
}

Iteration::Iteration(std::shared_ptr<Expression> expression, std::shared_ptr<Statement> statement) : expression(expression), statement(statement) {}

void Iteration::print(std::ostream &os) {
  os << "[iteration-stmt" << std::endl;
  expression->print(os);
  os << std::endl;
  statement->print(os);
  os << std::endl;
  os << "]" << std::endl;
}


Return::Return() : expression(nullptr) {}

Return::Return(std::shared_ptr<Expression> expression) : expression(expression) {}

void Return::print(std::ostream &os) {
  os << "[return-stmt ";
  if(expression)
  	expression->print(os);
  os << "]" << std::endl;
}

Variable::Variable(std::string &id) : id(id) {}

Variable::Variable(std::string &id, std::shared_ptr<Expression> expression) : id(id), expression(std::move(expression)) {}

void Variable::print(std::ostream &os) {
  os << "[var ";
  os << "[" << id << "]";
  if(expression) {
    os << " ";
    expression->print(os);
  }
  os << "]";
}

Assign::Assign(std::shared_ptr<Variable> variable, std::shared_ptr<Expression> expression) : var(variable), expression(expression) {}

void Assign::print(std::ostream &os) {
  os << "[= ";
  var->print(os);
  os << " ";
  expression->print(os);
  os << "]" << std::endl;
}

FunctionCall::FunctionCall(std::string &id) : id(id){}

FunctionCall::FunctionCall(std::string &id, std::vector<std::shared_ptr<Expression>> &args) : id(id), args(args){}

void FunctionCall::print(std::ostream &os) {
  os << "[call" << std::endl;
  os << "[" << id << "]" << std::endl;
  os << "[args "; //duvida: se não tiver argumentos deve-se escrever 'args' mesmo assim?
  for(auto &a : args)
    a->print(os);
  os << "]";
  os << "]" << std::endl;
}

BinaryOperation::BinaryOperation(std::shared_ptr<tree::Expression>lhs, std::string &op, std::shared_ptr<tree::Expression>rhs) : lhs(lhs), op(op), rhs(rhs) {}

void BinaryOperation::print(std::ostream &os) {
  os << "[" << op << " ";
  lhs->print(os);
  os << " ";
  rhs->print(os);
  os << "]" << std::endl;
}
Number::Number(int number) : number(number) {}

void Number::print(std::ostream &os) {
  os << "[" << number << "]";
}
