%defines

%{
	#pragma warning(disable: 4996)

	#include <iostream>
	#include <cmath>


	extern int yylex();
	extern int yyparse();
	extern FILE* yyin;

	extern void yyerror(char const* msg);
%}

%union
{
	int ival;
	float fval;
};

%token<ival> NUM

%token ADD MINUS TIMES DIV LT LEQ GT GEQ EQ DIF EQTO SC COMMA LBRACE RBRACE RBRACKET LBRACKET LCBRT RCBRT ELSE IF INT RETURN VOID WHILE ID
%type<ival>	expr
%type<ival>	term

%start program

%%


//program: /* empty */ 
//	| program expr '\n'		{ std::cout << $2 << std::endl; }  
//	;
//
//expr: term	{ $$ = $1; }
//	| expr '+' term { $$ = $1 + $3; }
//	| expr '-' term { $$ = $1 - $3; }
//	;
//
//term: LITERAL_DBL	{ $$ = $1; }
//	| term '*' LITERAL_DBL	{ $$ = $1 * $3 ; }
//	| term '/' LITERAL_DBL	{ $$ = $1 / $3 ; }
//	;

program : declaration_list
	;

declaration_list : declaration_list declaration 
	| declaration
	;

declaration : var_declaration 
	| fun_declaration

var_declaration : type_specifier ID SC 
	| type_specifier ID RBRACKET NUM LBRACKET SC
	;
type_specifier : INT 
	| VOID
	;

fun_declaration : type_specifier ID LBRACE params RBRACE compound_stmt
	;
params : param_list 
	| VOID
	;
param_list : param_list COMMA param 
	| param
	;
param : type_specifier ID 
	| type_specifier ID RBRACKET LBRACKET 
	;

compound_stmt : LCBRT local_declarations statement_list RCBRT
	;

local_declarations : local_declarations var_declaration 
	| empty
	;
statement_list : statement_list statement 
	| empty
	;

statement : expression_stmt 
	| compound_stmt 
	| selection_stmt 
	| iteration_stmt 
    | return_stmt
    ;
expression_stmt : expression SC 
	| ;

selection_stmt : IF LBRACE expression RBRACE statement            
    | IF LBRACE expression RBRACE statement ELSE statement
    ;

iteration_stmt : WHILE LBRACE expression RBRACE statement
	;

return_stmt : RETURN SC 
	| RETURN expression SC
	;	

expression : var = expression 
	| simple_expression
	;
var : ID 
	| ID RBRACKET expression LBRACKET
	;

simple_expression : additive_expression relop additive_expression 
    | additive_expression
    ;
relop : LEQ 
	| LT 
	| GT 
	| GEQ 
	| EQ
	| DIF
	;

additive_expression : additive_expression addop term 
	| term
	;
addop : ADD 
	| MINUS
	;
term : term mulop factor 
	| factor
	;
mulop : TIMES 
	| DIV
	;

factor : LBRACE expression RBRACE 
	| var 
	| call 
	| NUM
	;

call : ID LBRACE args RBRACE
	;
args : arg_list 
	| empty
	;
arg_list : arg_list COMMA expression 
	| expression
	;	

%%

void yyerror(char const* msg)
{
	std::cout<<"Syntax Error: " << msg << std::endl;
}
