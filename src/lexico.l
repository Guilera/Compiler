%{ 
    #include <iostream>      // for I/O
    #include <string.h>        // for string handling 
    #include <ctype.h>         // for character predicates
    #include <fstream>
    

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
\n  {
    line++;
}    

{wa} {
    write("ERROR", yytext);
    myfile.close();
    return 0;
}


"/*"    {
    int c;
    bool ntem = true;
    int linha = line;
    
    while((c = yyinput()) != 0) {

        if(c == EOF) {
            break;
        } else if(c == '\n')
            ++line;
        else if(c == '*') {

            if((c = yyinput()) == '/') {
                ntem = false;
                break;
            }
            else
                unput(c);
        }
    }

    if(ntem) {
        line = linha;
    	write("ERROR", "/*");
        myfile.close();
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
"("     return LBRACE;
")"     return RBRACE;
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
   

. {
    write("ERROR", yytext);   
    myfile.close();
    return 0;
}

  
%%
   
