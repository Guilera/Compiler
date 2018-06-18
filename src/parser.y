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
	bool debug = false;
%}
%error-verbose

%code requires {
    #include <string>
    #include "tree.hpp"

    struct NEWTYPE {
        int token;
        long long number;
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
%token LT LEQ GT GEQ ASS DIF EQ                     // relational operators
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

program             : declaration_list { program.declaration_list = *$1; if(debug){ std::cout << "program decs" << std::endl;} } // novo escopo
	                ;

declaration_list    : declaration_list declaration { $1->push_back($2); $$ = $1; if(debug){ std::cout << "push dec" << std::endl; }}
                    | declaration { $$ = std::make_shared<std::vector<std::shared_ptr<tree::Declaration>>>(); $$->push_back($1); if(debug){ std::cout << "reduce dec to dec_list" << std::endl; }}
	                ;

declaration         : var_declaration { $$ = $1; if(debug){ std::cout << "reduce var_dec to declaration" << std::endl; }}
	                | fun_declaration { $$ = $1; if(debug){ std::cout << "reduce fun_dec to declaration" << std::endl; }}
                    ;

var_declaration     : type_specifier ID SC { $$ = std::make_shared<tree::VariableDeclaration>($1, $2); if(debug){ std::cout << "var_dec " << $1 << " " << $2 << std::endl; }}
	                | type_specifier ID LBRACKET NUM RBRACKET SC { $$ = std::make_shared<tree::VariableDeclaration>($1, $2, $4); if(debug){ std::cout << "var_dec array" << std::endl; }}
	                ;

type_specifier      : INT { $$ = $1; if(debug){ std::cout << "type int" << std::endl; }}
	                | VOID { $$ = $1; if(debug){ std::cout << "type void" << std::endl; }}
	                ;

fun_declaration     : type_specifier ID LPAREN params RPAREN compound_stmt { $$ = std::make_shared<tree::FunctionDeclaration>($1, $2, *$4, $6); if(debug){ std::cout << "fun_dec " << $2 << std::endl; }}
	                ;

params              : param_list { $$ = $1; if(debug){ std::cout << "reduce param_list to params" << std::endl; }}
	                | VOID { $$ = std::make_shared<std::vector<std::shared_ptr<tree::Param>>>(); if(debug){ std::cout << "create param_list(void)" << std::endl; }}
	                ;

param_list          : param_list COMMA param { $1->push_back($3); $$ = $1; if(debug){ std::cout << "push param " << $3->id << std::endl; }}
	                | param { $$ = std::make_shared<std::vector<std::shared_ptr<tree::Param>>>(); $$->push_back($1); if(debug){ std::cout << "reduce param " << $1->id << " to param_list" << std::endl; }}
	                ;

param               : type_specifier ID { $$ = std::make_shared<tree::Param>($1, $2); if(debug){ std::cout << "param " << $1 << " " << $2 << std::endl; }}
	                | type_specifier ID LBRACKET RBRACKET { $$ = std::make_shared<tree::Param>($1, $2, true); if(debug){ std::cout << "array param " << $1 << " " << $2 << std::endl; }}
	                ;

compound_stmt       : LCBRT local_declarations statement_list RCBRT { $$ = std::make_shared<tree::CompoundStatement>(*$2, *$3); if(debug){ std::cout << "reduce local+stmt to compound" << std::endl; }} //novo escopo
	                ;

local_declarations  : local_declarations var_declaration { $1->push_back($2); $$ = $1; if(debug){ std::cout << "push var_declaration to local_declarations" << std::endl; }}
	                | %empty { $$ = std::make_shared<std::vector<std::shared_ptr<tree::VariableDeclaration>>>(); if(debug){ std::cout << "reduce empty to local_declarations" << std::endl; }}
	                ;
statement_list      : statement_list statement { $1->push_back($2); $$ = $1; if(debug){ std::cout << "push statement to statement_list" << std::endl; }}
	                | %empty { $$ = std::make_shared<std::vector<std::shared_ptr<tree::Statement>>>(); if(debug){ std::cout << "reduce empty to statement_list" << std::endl; }}
	                ;

statement           : expression_stmt { $$ = $1; if(debug){ std::cout << "reduce expression_stmt to statement" << std::endl; }}
	                | compound_stmt { $$ = $1; if(debug){ std::cout << "reduce compound_stmt to statement" << std::endl; }}
	                | iteration_stmt { $$ = $1; if(debug){ std::cout << "reduce iteration_stmt to statement" << std::endl; }}
	                | selection_stmt { $$ = $1; if(debug){ std::cout << "reduce selection_stmt to statement" << std::endl; }}
                    | return_stmt { $$ = $1; if(debug){ std::cout << "reduce return_stmt to statement" << std::endl; }}
                    ;
expression_stmt     : expression SC { $$ = $1; if(debug){ std::cout << "reduce expression to expression_stmt" << std::endl; }}
	                | SC { $$ = std::make_shared<tree::Expression>(); if(debug){ std::cout << "reduce empty expression to expression_stmt" << std::endl; }} //empty
	                ;

selection_stmt      : IF LPAREN expression RPAREN statement %prec TAIL { $$ = std::make_shared<tree::Selection>($3, $5); if(debug){ std::cout << "reduce single_if to selection_stmt" << std::endl; }}
                    | IF LPAREN expression RPAREN statement ELSE statement { $$ = std::make_shared<tree::Selection>($3, $5, $7); if(debug){ std::cout << "reduce if+else to selection_stmt" << std::endl; }}
                    ;

iteration_stmt      : WHILE LPAREN expression RPAREN statement { $$ = std::make_shared<tree::Iteration>($3, $5); if(debug){ std::cout << "reduce while to iteration_stmt" << std::endl; }}
	                ;

return_stmt         : RETURN SC { $$ = std::make_shared<tree::Return>(); if(debug){ std::cout << "reduce empty return to return_stmt" << std::endl; }}
	                | RETURN expression SC { $$ = std::make_shared<tree::Return>($2); if(debug){ std::cout << "reduce return+expression to return_stmt" << std::endl; }}
	                ;

expression          : var ASS expression { $$ = std::make_shared<tree::Assign>($1, $3); if(debug){ std::cout << "reduce assign to expr" << std::endl; }}
	                | simple_expression { $$ = $1; if(debug){ std::cout << "reduce simple_expr to expr" << std::endl; }}
	                ;

var                 : ID { $$ = std::make_shared<tree::Variable>($1); if(debug){ std::cout << "simple var " << $1 << std::endl; }}
	                | ID LBRACKET expression RBRACKET { $$ = std::make_shared<tree::Variable>($1, $3); if(debug){ std::cout << "array var " << $1; $3->print(std::cout); std::cout << std::endl; }}
	                ;

simple_expression   : additive_expression relop additive_expression { $$ = std::make_shared<tree::BinaryOperation>($1, $2, $3); }
                    | additive_expression { $$ = $1; if(debug){ std::cout << "reduce add_expr to simple_expr" << std::endl; }}
                    ;
relop               : LEQ { $$ = std::string("<="); }
	                | LT { $$ = std::string("<"); }
	                | GT { $$ = std::string(">"); }
	                | GEQ { $$ = std::string(">="); }
	                | EQ { $$ = std::string("=="); }
	                | DIF { $$ = std::string("!="); }
	                ;

additive_expression : additive_expression addop term { $$ = std::make_shared<tree::BinaryOperation>($1, $2, $3); }
	                | term { $$ = $1; if(debug){ std::cout << "reduce term to add_expr" << std::endl; }}
	                ;

addop               : PLUS { $$ = std::string("+"); }
	                | MINUS { $$ = std::string("-"); }
	                ;

term                : term mulop factor { $$ = std::make_shared<tree::BinaryOperation>($1, $2, $3); }
	                | factor { $$ = $1; if(debug){ std::cout << "reduce factor to term" << std::endl; }}
	                ;
mulop               : TIMES { $$ = std::string("*"); }
	                | DIV { $$ = std::string("/"); }
	                ;

factor              : LPAREN expression RPAREN { $$ = $2; }
	                | var { $$ = $1; if(debug){ std::cout << "reduce var " << $1->id << " to factor" << std::endl; }}
	                | call { $$ = $1; if(debug){ std::cout << "reduce call to factor" << std::endl; }}
	                | NUM { $$ = std::make_shared<tree::Number>($1); if(debug){ std::cout << "reduce num " << $1 << " to factor" << std::endl; }}
	                ;

call                : ID LPAREN args RPAREN { $$ = std::make_shared<tree::FunctionCall>($1, *$3); if(debug){ std::cout << "function call " << $1 << std::endl; }}
	                ;

args                : arg_list { $$ = $1; if(debug){ std::cout << "reduce arg_list to args" << std::endl; }}
	                | %empty { $$ = std::make_shared<std::vector<std::shared_ptr<tree::Expression>>>(); if(debug){ std::cout << "reduce empty to args" << std::endl; }}
	                ;

arg_list            : arg_list COMMA expression { $1->push_back($3); $$ = $1; if(debug){ std::cout << "push expression to arg_list" << std::endl; }}
	                | expression { $$ = std::make_shared<std::vector<std::shared_ptr<tree::Expression>>>(); $$->push_back($1); if(debug){ std::cout << "reduce expression to arg_list" << std::endl; }}
	                ;

%%

void yyerror(char const* msg) {
	std::cout << msg << " at line " << std::to_string(yylineno) << std::endl;
	exit(1);
}
