%{
	#include <iostream>
	#include <cmath>
	#include <stdlib.h>
	#include <cstdio>
    #include <string>
    #include "tree.hpp"

	void yyerror(const char* s);

	extern int yylex();
	extern int yyparse();
	extern FILE* yyin;
	extern int yylineno;
	tree::Program program;
%}
  
%code requires {
    #include <string>
    #include "tree.hpp"

    struct NEWTYPE {
        int token, number;
        std::string id, op;
        std::shared_ptr<std::vector<std::shared_ptr<tree::Declaration>>> declaration_list;
        std::shared_ptr<tree::Declaration> declaration;
        std::shared_ptr<tree::VariableDeclaration> var_declaration;
        std::shared_ptr<tree::FunctionDeclaration> fun_declaration;
        std::shared_ptr<std::vector<std::shared_ptr<tree::Param>>> params;
        std::shared_ptr<tree::Param> param;
        std::shared_ptr<tree::CompoundStatement> compound_stmt;
        std::shared_ptr<std::vector<std::shared_ptr<tree::VariableDeclaration>>> local_declarations;
        std::shared_ptr<std::vector<std::shared_ptr<tree::Statement>>> statement_list;
        std::shared_ptr<tree::Statement> statement;
        std::shared_ptr<tree::Variable> variable;
        std::shared_ptr<tree::Expression> expression;
        std::shared_ptr<std::vector<std::shared_ptr<tree::Expression>>> expressions;
    };

    #define YYSTYPE NEWTYPE
}

%token<token> INT VOID                              // type specifier
%token<number> NUM                                  // integer value
%token<id> ID                                       // string
%token ELSE IF RETURN WHILE                         // keywords
%token LT LEQ GT GEQ EQ DIF EQTO                    // relational operators
%token SC COMMA                                     // punctuation symbols
%token LPAREN RPAREN RBRACKET LBRACKET LCBRT RCBRT  // scopes symbols
%token PLUS MINUS                                   // addition and subtraction operators
%token TIMES DIV                                    // multiplication and division operators

%type<declaration_list> declaration_list
%type<declaration> declaration
%type<var_declaration> var_declaration
%type<token> type_specifier
%type<fun_declaration> fun_declaration
%type<params> params param_list
%type<param> param
%type<compound_stmt> compound_stmt
%type<local_declarations> local_declarations
%type<statement_list> statement_list
%type<statement> statement expression_stmt selection_stmt iteration_stmt return_stmt
%type<variable> var
%type<expression> expression call simple_expression additive_expression term factor
%type<op> relop addop mulop
%type<expressions> args arg_list

%start program

%precedence TAIL
%precedence ELSE

%%

program             : declaration_list { program.declaration_list = *$1; } // novo escopo
	                ;

declaration_list    : declaration_list declaration { $1->push_back($2); }
                    | declaration { $$ = std::make_shared<std::vector<std::shared_ptr<tree::Declaration>>>(); $$->push_back($1); }
	                ;

declaration         : var_declaration { $$ = $1; }
	                | fun_declaration { $$ = $1; }
                    ;

var_declaration     : type_specifier ID SC { $$ = std::make_shared<tree::VariableDeclaration>($1, $2); }
	                | type_specifier ID RBRACKET NUM LBRACKET SC { $$ = std::make_shared<tree::VariableDeclaration>($1, $2, $4); }
	                ;

type_specifier      : INT { $$ = $1; }
	                | VOID { $$ = $1; }
	                ;

fun_declaration     : type_specifier ID LPAREN params RPAREN compound_stmt { $$ = std::make_shared<tree::FunctionDeclaration>($1, $2, *$4, $6); }
	                ;

params              : param_list { $$ = $1; }
	                | VOID { $$ = std::make_shared<std::vector<std::shared_ptr<tree::Param>>>(); }
	                ;

param_list          : param_list COMMA param { $1->push_back($3); $$ = $1; }
	                | param { $$ = std::make_shared<std::vector<std::shared_ptr<tree::Param>>>(); $$->push_back($1); }
	                ;

param               : type_specifier ID { $$ = std::make_shared<tree::Param>($1, $2); }
	                | type_specifier ID RBRACKET LBRACKET { $$ = std::make_shared<tree::Param>($1, $2, true); }
	                ;

compound_stmt       : LCBRT local_declarations statement_list RCBRT { $$ = std::make_shared<tree::CompoundStatement>(*$2, *$3); } //novo escopo
	                ;

local_declarations  : local_declarations var_declaration { $1->push_back($2); $$ = $1; }
	                | %empty { $$ = std::make_shared<std::vector<std::shared_ptr<tree::VariableDeclaration>>>(); }
	                ;
statement_list      : statement_list statement { $1->push_back($2); $$ = $1; }
	                | %empty { std::make_shared<std::vector<std::shared_ptr<tree::Statement>>>(); }
	                ;

statement           : expression_stmt { $$ = $1; }
	                | compound_stmt { $$ = $1; }
	                | selection_stmt { $$ = $1; }
	                | iteration_stmt { $$ = $1; }
                    | return_stmt { $$ = $1; }
                    ;
expression_stmt     : expression SC { $$ = $1;}
	                | SC { $$ = std::make_shared<tree::Expression>(); } //empty
	                ;

selection_stmt      : IF LPAREN expression RPAREN statement %prec TAIL { $$ = std::make_shared<tree::Selection>($3, $5); }
                    | IF LPAREN expression RPAREN statement ELSE statement { std::make_shared<tree::Selection>($3, $5, $7); }
                    ;

iteration_stmt      : WHILE LPAREN expression RPAREN statement { $$ = std::make_shared<tree::Iteration>($3, $5); }
	                ;

return_stmt         : RETURN SC { std::make_shared<tree::Return>(); }
	                | RETURN expression SC { std::make_shared<tree::Return>($2); }
	                ;

expression          : var EQ expression { $$ = std::make_shared<tree::Assign>($1, $3); }
	                | simple_expression { $$ = $1; }
	                ;

var                 : ID { $$ = std::make_shared<tree::Variable>($1); }
	                | ID LBRACKET expression RBRACKET { $$ = std::make_shared<tree::Variable>($1, $3); }
	                ;

simple_expression   : additive_expression relop additive_expression { $$ = std::make_shared<tree::BinaryOperation>($1, $2, $3); }
                    | additive_expression { $$ = $1; }
                    ;
relop               : LEQ { $$ = std::string("<="); }
	                | LT { $$ = std::string("<"); }
	                | GT { $$ = std::string(">"); }
	                | GEQ { $$ = std::string(">="); }
	                | EQTO { $$ = std::string("=="); }
	                | DIF { $$ = std::string("!="); }
	                ;

additive_expression : additive_expression addop term { $$ = std::make_shared<tree::BinaryOperation>($1, $2, $3); }
	                | term { $$ = $1; }
	                ;

addop               : PLUS { $$ = std::string("+"); }
	                | MINUS { $$ = std::string("-"); }
	                ;

term                : term mulop factor { $$ = std::make_shared<tree::BinaryOperation>($1, $2, $3); }
	                | factor { $$ = $1; }
	                ;
mulop               : TIMES { $$ = std::string("*"); }
	                | DIV { $$ = std::string("/"); }
	                ;

factor              : LPAREN expression RPAREN { $$ = $2; }
	                | var { $$ = $1; }
	                | call { $$ = $1; }
	                | NUM { $$ = std::make_shared<tree::Number>($1); }
	                ;

call                : ID LPAREN args RPAREN { $$ = std::make_shared<tree::FunctionCall>($1, *$3); }
	                ;

args                : arg_list { $$ = $1; }
	                | %empty { $$ = std::make_shared<std::vector<std::shared_ptr<tree::Expression>>>(); }
	                ;

arg_list            : arg_list COMMA expression { $1->push_back($3); $$ = $1; }
	                | expression { $$ = std::make_shared<std::vector<std::shared_ptr<tree::Expression>>>(); $$->push_back($1); }
	                ;

%%

void yyerror(char const* msg) {
	std::cout << "Syntax Error: " << msg << " at line " << std::to_string(yylineno) << std::endl;
	exit(1);
}
