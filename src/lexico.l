%{
    #include <iostream>      // for I/O
    #include <string.h>      // for string handling
    #include <ctype.h>       // for character predicates
    #include <fstream>
    #include "parser.hpp"
    #include "tree.hpp"


%}

digit   [0-9]
key 	"else"|"if"|"int"|"return"|"void"|"while"
letter  [a-z|A-Z]
num     ({digit})*
id      {letter}({letter}|{digit})*
wa      ({digit})+({letter})({digit}|{letter})*
sym 	"+"|"-"|"*"|"/"|"<"|"<="|">"|">="|"=="|"!="|"="|";"|","|"("|")"|"["|"]"|"{"|"}"

%option noyywrap
%option yylineno

%%

[ \t\n]+ {}

"/*"    {
    int c;
    bool ntem = true;
    
    while((c = yyinput()) != 0) {

        if(c == EOF) {
            break;
        } else if(c == '*') {

            if((c = yyinput()) == '/') {
                ntem = false;
                break;
            }
            else
                unput(c);
        }
    }

    if(ntem) {
        return 0;
    }
}

"+"         return PLUS;
"-"         return MINUS;
"*"         return TIMES;
"/"         return DIV;
"<"         return LT;
"<="        return LEQ;
">"         return GT;
">="        return GEQ;
"=="        return EQ;
"!="        return DIF;
"="         return ASS;
";"         return SC;
","         return COMMA;
"("         return LPAREN;
")"         return RPAREN;
"["         return LBRACKET;
"]"         return RBRACKET;
"{"         return LCBRT;
"}"         return RCBRT;
"else"      return ELSE;
"if"        return IF;
"return"    return RETURN;
"while"     return WHILE;
"void"      return yylval.token = VOID;
"int"       return yylval.token = INT;

{num} { yylval.number = std::stoll(yytext); return NUM; }

{id} { yylval.id = std::string(yytext); return ID; }
   

. { std::cout << std::string(yytext) << "\" in line " << std::to_string(yylineno) << "is not a recognizable token \"" << std::endl; exit(1); }

  
%%
   
