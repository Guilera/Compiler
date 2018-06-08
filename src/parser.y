%defines

%{
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
	char *id;
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

program : declaration_list { $$ = new Program($1)} // novo escopo
	;

declaration_list : declaration_list declaration { $$ = new DL1($1, $2);}
	| declaration { $$ = new DL2($1);}
	;

declaration : var_declaration { $$ = new D1($1); }
	| fun_declaration {$$ = new D2($1); }
}

var_declaration : type_specifier ID SC { $$ = new VD1($1,$2,$3);}
	| type_specifier ID RBRACKET NUM LBRACKET SC { $$ = new VD2($1,$2,$3,$4,$5,$6);}
	;
type_specifier : INT {$$ = new Type("INT");}
	| VOID {$$ = new Type("VOID");}
	;

fun_declaration : type_specifier ID LPAREN params RPAREN compound_stmt {$$ = new FD($1,$2,$3,$4,$5,$6);}
	;
params : param_list {$$ = new PS1($1);}
	| VOID {$$ = new Type("VOID");}
	;
param_list : param_list COMMA param {$$ = new PL1($1, ',', $3);}
	| param {$$ = new PL2($1);}
	;
param : type_specifier ID {$$ = new P1($1, $2);} 
	| type_specifier ID RBRACKET LBRACKET {$$ = new P2($1, $2, $3, $4);}
	;

compound_stmt : LCBRT local_declarations statement_list RCBRT {$$ = new CS($1, $2, $3, $4);}//novo escopo
	;

local_declarations : local_declarations var_declaration {$$ = new LD($1, $2);}
	| {$$ = NULL;} //empty
	;
statement_list : statement_list statement {$$ = new ST($1, $2);}
	| {$$ = NULL;} //empty
	;

statement : expression_stmt {$$ = new S1($1);}
	| compound_stmt {$$ = new S2($1);}
	| selection_stmt {$$ = new S3($1);}
	| iteration_stmt {$$ = new S4($1);}
    | return_stmt {$$ = new S5($1);}
    ;
expression_stmt : expression SC {$$ = new ES1($1,$2);}
	| {$$ = NULL;} //empty
	;

selection_stmt : IF LPAREN expression RPAREN statement {$$ = new SS1($1, $2, $3, $4, $5);}           
    | IF LPAREN expression RPAREN statement ELSE statement {$$ = new SS2($1, $2, $3, $4, $5, $6, $7);}
    ;

iteration_stmt : WHILE LPAREN expression RPAREN statement {$$ = new IS($1, $2, $3, $4, $5);}
	;

return_stmt : RETURN SC {$$ = new RS1($1, $2);}
	| RETURN expression SC {$$ = new RS2($1, $2, $3);}
	;	

expression : var EQ expression {$$ = new EX1($1,$2,$3);}
	| simple_expression {$$ = new EX2($1);}
	;
var : ID {$$ = new V1($1);}
	| ID LBRACKET expression RBRACKET {$$ = new V2($1,$2,$3,$4);}
	;

simple_expression : additive_expression relop additive_expression {$$ = new SE1($1,$2,$3);}
    | additive_expression {$$ = new SE2($1);}
    ;
relop : LEQ {$$ = new Rop($1);}
	| LT {$$ = new Rop($1);}
	| GT {$$ = new Rop($1);}
	| GEQ {$$ = new Rop($1);}
	| EQ {$$ = new Rop($1);}
	| DIF {$$ = new Rop($1);}
	;

additive_expression : additive_expression addop term {$$ = new AE1($1,$2,$3);}
	| term {$$ = new AE2($1);}
	;
addop : ADD {$$ = new Aop($1);}
	| MINUS {$$ = new Aop($1);}
	;
term : term mulop factor {$$ = new T1($1,$2,$3);} 
	| factor {$$ = new T2($1);}
	;
mulop : TIMES {$$ = new M1($1);}
	| DIV {$$ = new M2($1);}
	;


factor : LPAREN expression RPAREN {$$ = new F1($1,$2,$3);}
	| var {$$ = new F2($1);}
	| call {$$ = new F3($1);}
	| NUM {$$ = new F4($1);}
	;

call : ID LPAREN args RPAREN {$$ = new C($1,$2,$3,$4);}
	;
args : arg_list {$$ = new AR($1);}
	| {$$ = NULL;}
	;
arg_list : arg_list COMMA expression {$$ = new AL1($1);}
	| expression {$$ = new AL1($1);}
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
