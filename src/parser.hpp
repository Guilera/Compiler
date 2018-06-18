/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 20 "parser.y" /* yacc.c:1909  */

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

#line 69 "parser.hpp" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    VOID = 259,
    NUM = 260,
    ID = 261,
    ELSE = 262,
    IF = 263,
    RETURN = 264,
    WHILE = 265,
    LT = 266,
    LEQ = 267,
    GT = 268,
    GEQ = 269,
    ASS = 270,
    DIF = 271,
    EQ = 272,
    SC = 273,
    COMMA = 274,
    LPAREN = 275,
    RPAREN = 276,
    RBRACKET = 277,
    LBRACKET = 278,
    LCBRT = 279,
    RCBRT = 280,
    PLUS = 281,
    MINUS = 282,
    TIMES = 283,
    DIV = 284,
    TAIL = 285
  };
#endif

/* Value type.  */


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
