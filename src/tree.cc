//
// Created by Bruno Guilera on 01/06/18.
//

#include "tree.h"
#include <utility>
using namespace tree;

void Node::print(std::ostream &) {}

void Statement::print(std::ostream &) {}

void Expression::print(std::ostream &) {}

Program::Program() {}

void Program::print(std::ostream &os) {
  os << "[program" << std::endl;
  for(auto dec : declaration_list)
	dec.print(os);
  os << std::endl;
  os << "]" << std::endl;
}

Declaration::Declaration(int type, std::string &id) : type(type), id(id) {}

VariableDeclaration::VariableDeclaration(int type, std::string &id) : Declaration(type, id) {}

VariableDeclaration::VariableDeclaration(int type, std::string &id, int num) : Declaration(type, id), num(num) {}

void VariableDeclaration::print(std::ostream &os) {
  os << "[var-declaration [int] [" << id << "]";
  if(num)
    os << "[" << num << "]";
}

Param::Param(int type, std::string &id) : type(type), id(id) {}

void Param::print(std::ostream &os) {
  os << "[param";
  os << " [int] " << "[" << id << "]";
}

CompoundStatement::CompoundStatement(std::vector<VariableDeclaration> &local_declarations, std::vector<Statement> &statement_list) : local_declarations(local_declarations), statement_list(statement_list) {}
void CompoundStatement::print(std::ostream &os) {
  for(auto local_dec : local_declarations)
    local_dec.print(os);
  for(auto stmt : statement_list)
    stmt.print(os);
}

FunctionDeclaration::FunctionDeclaration(int type, std::string &id, CompoundStatement &compound_stmt) : Declaration(type, id), compound_stmt(compound_stmt) {}
FunctionDeclaration::FunctionDeclaration(int type, std::string &id, std::vector<Param> &param_list, tree::CompoundStatement &compound_stmt) : FunctionDeclaration(type, id, compound_stmt), param_list(param_list) {}
void FunctionDeclaration::print(std::ostream &os) {
  os << "[fun-declaration" << std::endl;
  if(type == INT)
  	os << "[int]";
  else if(type == VOID)
    os << "[void]";
  os << std::endl;
  os << "[" << id << "]" << std::endl;
  os << "[params";
  for(auto param : param_list)
    os << std::endl << param.print(os);
  os << "]" << std::endl;
}

Selection::Selection(Expression &expression, Statement &if_stmt) : expression(expression), if_stmt(if_stmt) {}
Selection::Selection(Expression &expression, Statement &if_stmt, Statement &else_stmt) : Selection(expression, if_stmt), else_stmt(else_stmt) {}
void Selection::print(std::ostream &os) {
  os << "[selection-stmt" << std::endl;
  expression.print(os);
  os << std::endl;
  if_stmt.print(os);
  os << std::endl;
  else_stmt.print(os);
  os << "]" << std::endl;
}

Iteration::Iteration(Expression &expression, Statement &statement) : expression(expression), statement(statement) {}
void Iteration::print(std::ostream &os) {
  os << "[iteration-stmt" << std::endl;
  expression.print(os);
  os << std::endl;
  statement.print(os);
  os << std::endl;
  os << "]" << std::endl;
}

Return::Return() : Expression() {}
Return::Return(Expression &expression) : expression(expression) {}
void Return::print(std::ostream &os) {
  os << "[return-stmt";
  expression.print(os);
  os << "]" << std::endl;
}

Variable::Variable(std::string &id) : id(id) {}
Variable::Variable(std::string &id, Expression &expression) : Variable(id), expression(expression) {}
void Variable::print(std::ostream &os) {
	os << "[" << id << "]";
	os << " ";
	expression.print(os);
	os << std::endl;
}

Assing::Assing(Variable &variable, Expression &expression) : var(variable), expression(expression) {}
void Assing::print(std::ostream &os) {
  os << "[= ";
  var.print(os);
  os << " ";
  expression.print(os);
  os << "]" << std::endl;
}

SimpleExpression::SimpleExpression(AdditiveExpression &exp) : lhs(exp) {
  relop = nullptr;
  rhs = nullptr;
}
SimpleExpression::SimpleExpression(AdditiveExpression &lhs, int relop, AdditiveExpression &rhs) : lhs(lhs), relop(relop), rhs(rhs) {}
