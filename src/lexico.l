%option noyywrap

%{ 
    #include <iostream>      // for I/O
    #include <string.h>        // for string handling 
    #include <ctype.h>         // for character predicates
    #include <fstream>
    #include "parser.tab.h"
    

%}
   
digit   [0-9]
letter  [a-z|A-Z]
num     ({digit})*
id      {letter}({letter}|{digit})*
wa      ({digit})+({letter})({digit}|{letter})*
key 	"else"|"if"|"int"|"return"|"void"|"while"
sym 	"+"|"-"|"*"|"/"|"<"|"<="|">"|">="|"=="|"!="|"="|";"|","|"("|")"|"["|"]"|"{"|"}"

%%

" " {}
\t  {}
\n  {}    

{wa} {return 0;}


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

"+"     return ADD;
"-"     return MINUS;
"*"     return TIMES;
"/"     return DIV;
"<"     return LT;
"<="    return LEQ;
">"     return GT;
">="    return GEQ;
"=="    return EQ;
"!="    return DIF;
"="     return EQTO;
";"     return SC;
","     return COMMA;
"("     return LPAREN;
")"     return RPAREN;
"["     return RBRACKET;
"]"     return LBRACKET;
"{"     return LCBRT;
"}"     return RCBRT;
"else"  return ELSE;
"if"    return IF;
"int"   return INT;
"return"return RETURN;
"void"  return VOID;
"while" return WHILE;
  
{num} {                              // INTEGERS
    return NUM;
}

{id} {                 // VARIABLES
    return ID;
}
   

. {return 0;}

  
%%
   
