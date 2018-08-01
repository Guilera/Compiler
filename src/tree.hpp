//
// Created by Bruno Guilera on 01/06/18.
//

#ifndef TREE_H
#define TREE_H

#include <vector>
#include <string>
#include <ostream>
#include <memory>
#include <utility>
#include <list>
// #include "parser.hpp"

namespace tree {

class Node {
 public:
  virtual ~Node() = default;
  virtual void print(std::ostream &);
  virtual void semantic();
  virtual void codegen(std::ostream &);
};

class Declaration : public Node {
 public:
  int type;
  std::string id;

  Declaration(int, std::string &);
};

class Statement : public Node {};

class Expression : public Statement {
 public:
  void print(std::ostream &);
};

class Program : public Node {
 public:
	std::vector<std::shared_ptr<Declaration>> declaration_list;

  Program();
  void semantic() override;
  void codegen(std::ostream &) override;
  void print(std::ostream &) override;
};

class VariableDeclaration : public Declaration {
 public:
  int num; // size of array
  VariableDeclaration(int, std::string &);
  VariableDeclaration(int, std::string &, int);
  void semantic() override;
  void codegen(std::ostream &) override;
  void print(std::ostream &) override;
};

class Param : public Node {
 public:
  int type;
  std::string id;
  bool is_array;

  Param(int, std::string &);
  Param(int, std::string &, bool);
  void semantic() override;
  void codegen(std::ostream &) override;
  void print(std::ostream &) override;
};

class CompoundStatement : public Statement {

 //corpo do escopo
 public:
  std::vector<std::shared_ptr<VariableDeclaration>> local_declarations; // assignments
  std::vector<std::shared_ptr<Statement>> statement_list; // expressoes

  CompoundStatement(std::vector<std::shared_ptr<VariableDeclaration>> &, std::vector<std::shared_ptr<Statement>> &);
  void semantic() override;
  void codegen(std::ostream &) override;
  void print(std::ostream &) override;
};

class FunctionDeclaration : public Declaration {
 public:
  std::vector<std::shared_ptr<Param>> param_list;
  std::shared_ptr<CompoundStatement> compound_stmt;

  FunctionDeclaration(int, std::string &, std::shared_ptr<CompoundStatement>);
  FunctionDeclaration(int, std::string &, std::vector<std::shared_ptr<Param>> &, std::shared_ptr<CompoundStatement>);
  void semantic() override;
  void codegen(std::ostream &) override;
  void print(std::ostream &) override;
};

class Selection : public Statement {
 public:
  std::shared_ptr<Expression> expression;
  std::shared_ptr<Statement> if_stmt, else_stmt;

  Selection(std::shared_ptr<Expression>, std::shared_ptr<Statement>);
  Selection(std::shared_ptr<Expression>, std::shared_ptr<Statement>, std::shared_ptr<Statement>);
  void semantic() override;
  void codegen(std::ostream &) override;
  void print(std::ostream &) override;
};

class Iteration : public Statement {
 public:
  std::shared_ptr<Expression> expression;
  std::shared_ptr<Statement> statement;

  Iteration(std::shared_ptr<Expression>, std::shared_ptr<Statement>);
  void semantic() override;
  void codegen(std::ostream &) override;
  void print(std::ostream &) override;
};

class Return : public Statement {
 public:
  std::shared_ptr<Expression> expression;

  Return();
  Return(std::shared_ptr<Expression>);
  void semantic() override;
  void codegen(std::ostream &) override;
  void print(std::ostream &) override;
};

class Variable : public Expression {
 public:
  std::string id;
  std::shared_ptr<Expression> expression;

  Variable(std::string &);
  Variable(std::string &, std::shared_ptr<Expression>);
  void semantic() override;
  void codegen(std::ostream &) override;
  void print(std::ostream &) override;
};

class Assign : public Expression {
 public:
  std::shared_ptr<Variable> var;
  std::shared_ptr<Expression> expression;

  Assign(std::shared_ptr<Variable>, std::shared_ptr<Expression>);
  void semantic() override;
  void codegen(std::ostream &) override;
  void print(std::ostream &) override;
};

class FunctionCall : public Expression {
 public:
  std::string id;
  std::vector<std::shared_ptr<Expression>> args;

  FunctionCall(std::string &);
  FunctionCall(std::string &, std::vector<std::shared_ptr<Expression>> &);
  void semantic() override;
  void codegen(std::ostream &) override;
  void print(std::ostream &) override;
};

class BinaryOperation : public Expression {
 public:
  std::shared_ptr<Expression> lhs, rhs;
  std::string op;

  BinaryOperation(std::shared_ptr<Expression>, std::string &, std::shared_ptr<Expression>);
  void semantic() override;
  void codegen(std::ostream &) override;
  void print(std::ostream &) override;
};

class Number : public Expression {
 public:
  int number;

  Number(int);
  void semantic() override;
  void codegen(std::ostream &) override;
  void print(std::ostream &) override;
};
};

#endif //TREE_H