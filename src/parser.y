%defines

%{
	#pragma warning(disable: 4996)

	#include <iostream>
	#include <cmath>
	#include <stdlib.h>
	#include <cstdio>
	void yyerror(const char* s);

	extern int yylex();
	extern int yyparse();
	extern FILE* yyin;

%}
  
%union
{
	int ival;
	float fval;
};

%token<ival> NUM

%token ADD MINUS TIMES DIV LT LEQ GT GEQ EQ DIF EQTO SC COMMA LPAREN RPAREN RBRACKET LBRACKET LCBRT RCBRT ELSE IF INT RETURN VOID WHILE ID

%left ADD MINUS
%left TIMES DIV

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

program : declaration_list {puts("END");} 
	;

declaration_list : declaration_list declaration 
	| declaration
	;

declaration : var_declaration 
	| fun_declaration

var_declaration : type_specifier ID SC {puts("variable");}
	| type_specifier ID RBRACKET NUM LBRACKET SC
	;
type_specifier : INT 
	| VOID
	;

fun_declaration : type_specifier ID LPAREN params RPAREN compound_stmt
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
	| /*empty*/
	;
statement_list : statement_list statement 
	| /*empty*/
	;

statement : expression_stmt 
	| compound_stmt 
	| selection_stmt 
	| iteration_stmt 
    | return_stmt
    ;
expression_stmt : expression SC 
	| ;

selection_stmt : IF LPAREN expression RPAREN statement            
    | IF LPAREN expression RPAREN statement ELSE statement
    ;

iteration_stmt : WHILE LPAREN expression RPAREN statement
	;

return_stmt : RETURN SC 
	| RETURN expression SC
	;	

expression : var EQ expression 
	| simple_expression
	;
var : ID
	| ID LBRACKET expression RBRACKET 
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

factor : LPAREN expression RPAREN 
	| var 
	| call 
	| NUM
	;

call : ID LPAREN args RPAREN
	;
args : arg_list 
	|
	;
arg_list : arg_list COMMA expression 
	| expression
	;	

%%

int main() {
	yyin = stdin;
	do { 
		yyparse();
	} while(!feof(yyin));
	return 0;
}

void yyerror(char const* msg)
{
	std::cout<<"Syntax Error: " << msg << std::endl;
}
