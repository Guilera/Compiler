//
// Created by Bruno Guilera on 01/06/18.
//

#ifndef TREE_H
#define TREE_H

#include <vector>
#include <string>
#include <ostream>

namespace tree {

class Node {
 public:
  virtual void print(std::ostream &);
};

class Declaration : public Node {
 public:
  int type;
  std::string id;

  Declaration(int, std::string &);
};

class Statement : public Node {
 public:
  void print(std::ostream &);
};

class Expression : public Statement {
 public:
  void print(std::ostream &);
};

class Program : public Node {
 public:
  std::vector<Declaration> declaration_list;

  Program();
  void print(std::ostream &) override;
};

class VariableDeclaration : public Declaration {
 public:
  int num;
  VariableDeclaration(int, std::string &);
  VariableDeclaration(int, std::string &, int);
  void print(std::ostream &) override;
};

class Param : public Node {
 public:
  int type;
  std::string id;

  Param(int, std::string &);
  void print(std::ostream &) override;
};

class CompoundStatement : public Statement {
 public:
  std::vector<VariableDeclaration> local_declarations;
  std::vector<Statement> statement_list;

  CompoundStatement(std::vector<VariableDeclaration> &, std::vector<Statement> &);
  void print(std::ostream &) override;
};

class FunctionDeclaration : public Declaration {
 public:
  std::vector<Param> param_list;
  CompoundStatement compound_stmt;

  FunctionDeclaration(int, std::string &, CompoundStatement &);
  FunctionDeclaration(int, std::string &, std::vector<Param> &, CompoundStatement &);
  void print(std::ostream &) override;
};

class Selection : Statement {
 public:
  Expression expression;
  Statement if_stmt, else_stmt;

  Selection(Expression &, Statement &);
  Selection(Expression &, Statement &, Statement &);
  void print(std::ostream &) override;
};

class Iteration : Statement {
 public:
  Expression expression;
  Statement statement;

  Iteration(Expression &, Statement &);
  void print(std::ostream &) override;
};

class Return : Statement {
 public:
  Expression expression;

  Return();
  Return(Expression &);
  void print(std::ostream &) override;
};

class Variable : Expression {
 public:
  std::string id;
  Expression expression;

  Variable(std::string &);
  Variable(std::string &, Expression &);
  void print(std::ostream &) override;
};

class Assing : Expression {
 public:
  Variable var;
  Expression expression;

  Assing(Variable &, Expression &);
  void print(std::ostream &) override;
};

class FunctionCall : Expression {
  std::string id;
  std::vector<Expression> args;

  FunctionCall(std::string);
  FunctionCall(std::string, std::vector<Expression>);
  void print(std::ostream &) override;
};

class Factor : Expression {
  Expression expression;
  Variable var;
  FunctionCall function_call;

  Factor(Expression);
  Factor(Variable);
  Factor(FunctionCall);
  void print(std::ostream &) override;
};

class Term : Expression {
  Term lhs;
  int mulop;
  Factor rhs;

  Term(Term, int, Factor);
  Term(Factor);
  void print(std::ostream &) override;
};

class AdditiveExpression : Expression {
  AdditiveExpression lhs;
  int addop;
  Term rhs;

  AdditiveExpression(AdditiveExpression, int, Term);
  AdditiveExpression(Term);
  void print(std::ostream &) override;
};

class SimpleExpression : Expression {
 public:
  AdditiveExpression lhs, rhs;
  int relop;

  SimpleExpression(AdditiveExpression &);
  SimpleExpression(AdditiveExpression &, int, AdditiveExpression &);
  void print(std::ostream &) override;
};
};

#endif //TREE_H