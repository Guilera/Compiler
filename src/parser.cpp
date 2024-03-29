/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

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

#line 84 "parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.hpp".  */
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
#line 20 "parser.y" /* yacc.c:355  */

    #include <string>
    #include "tree.hpp"

    struct NEWTYPE {
        int token;
        int number;
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

#line 140 "parser.cpp" /* yacc.c:355  */

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

/* Copy the second part of user declarations.  */

#line 189 "parser.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   100

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  63
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  102

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   285

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    79,    79,    82,    83,    86,    87,    90,    91,    94,
      95,    98,   101,   102,   105,   106,   109,   110,   113,   116,
     117,   119,   120,   123,   124,   125,   126,   127,   129,   130,
     133,   134,   137,   140,   141,   144,   145,   148,   149,   152,
     153,   155,   156,   157,   158,   159,   160,   163,   164,   167,
     168,   171,   172,   174,   175,   178,   179,   180,   181,   184,
     187,   188,   191,   192
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "VOID", "NUM", "ID", "ELSE", "IF",
  "RETURN", "WHILE", "LT", "LEQ", "GT", "GEQ", "ASS", "DIF", "EQ", "SC",
  "COMMA", "LPAREN", "RPAREN", "RBRACKET", "LBRACKET", "LCBRT", "RCBRT",
  "PLUS", "MINUS", "TIMES", "DIV", "TAIL", "$accept", "program",
  "declaration_list", "declaration", "var_declaration", "type_specifier",
  "fun_declaration", "params", "param_list", "param", "compound_stmt",
  "local_declarations", "statement_list", "statement", "expression_stmt",
  "selection_stmt", "iteration_stmt", "return_stmt", "expression", "var",
  "simple_expression", "relop", "additive_expression", "addop", "term",
  "mulop", "factor", "call", "args", "arg_list", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285
};
# endif

#define YYPACT_NINF -60

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-60)))

#define YYTABLE_NINF -14

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       1,   -60,   -60,    15,     1,   -60,   -60,    34,   -60,   -60,
     -60,   -12,   -60,    59,    16,    23,    42,    43,    48,   -60,
      36,    49,    50,     1,    55,    53,   -60,   -60,   -60,   -60,
     -60,     1,   -60,    70,     4,     9,   -60,    37,    57,    41,
      58,   -60,    -4,   -60,   -60,   -60,   -60,   -60,   -60,   -60,
      61,    65,   -60,    39,    40,   -60,   -60,    -4,    -4,    -4,
     -60,    63,    -4,    62,   -60,    -4,   -60,   -60,   -60,   -60,
     -60,   -60,   -60,   -60,    -4,    -4,   -60,   -60,    -4,   -60,
      64,    67,    60,    66,   -60,    68,   -60,   -60,   -60,    44,
      40,   -60,   -60,    -4,   -60,    25,    25,   -60,    77,   -60,
      25,   -60
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     9,    10,     0,     2,     4,     5,     0,     6,     1,
       3,     0,     7,     0,     0,    10,     0,     0,    12,    15,
       0,    16,     0,     0,     0,     0,    20,    11,    14,     8,
      17,    22,    19,     0,     0,     0,    58,    37,     0,     0,
       0,    29,     0,    18,    24,    21,    23,    26,    25,    27,
       0,    56,    36,    40,    48,    52,    57,    61,     0,     0,
      33,     0,     0,     0,    28,     0,    42,    41,    43,    44,
      46,    45,    49,    50,     0,     0,    53,    54,     0,    63,
       0,    60,     0,     0,    34,     0,    55,    35,    56,    39,
      47,    51,    59,     0,    38,     0,     0,    62,    30,    32,
       0,    31
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -60,   -60,   -60,    84,    69,    -6,   -60,   -60,   -60,    71,
      73,   -60,   -60,   -59,   -60,   -60,   -60,   -60,   -39,   -36,
     -60,   -60,    17,   -60,    18,   -60,    12,   -60,   -60,   -60
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,     7,     8,    17,    18,    19,
      44,    31,    34,    45,    46,    47,    48,    49,    50,    51,
      52,    74,    53,    75,    54,    78,    55,    56,    80,    81
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      61,    36,    37,    63,     1,     2,    12,    16,    13,    36,
      37,    14,    38,    39,    40,     9,    42,    16,    79,    82,
      83,    20,    41,    85,    42,    33,    87,    12,    26,    43,
      36,    37,    14,    38,    39,    40,    98,    99,    88,    88,
      11,   101,    88,    41,   -13,    42,    36,    37,    21,    26,
      66,    67,    68,    69,    97,    70,    71,    57,    24,    60,
      58,    42,     1,    15,    22,    72,    73,    23,    76,    77,
      72,    73,    25,    29,    26,    30,    35,    59,    62,    64,
      65,    84,    94,    86,   100,    92,    93,    95,    10,    96,
      91,    89,     0,    90,    28,    27,     0,     0,     0,     0,
      32
};

static const yytype_int8 yycheck[] =
{
      39,     5,     6,    42,     3,     4,    18,    13,    20,     5,
       6,    23,     8,     9,    10,     0,    20,    23,    57,    58,
      59,     5,    18,    62,    20,    31,    65,    18,    24,    25,
       5,     6,    23,     8,     9,    10,    95,    96,    74,    75,
       6,   100,    78,    18,    21,    20,     5,     6,     6,    24,
      11,    12,    13,    14,    93,    16,    17,    20,    22,    18,
      23,    20,     3,     4,    21,    26,    27,    19,    28,    29,
      26,    27,    23,    18,    24,    22,     6,    20,    20,    18,
      15,    18,    22,    21,     7,    21,    19,    21,     4,    21,
      78,    74,    -1,    75,    23,    22,    -1,    -1,    -1,    -1,
      31
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,    32,    33,    34,    35,    36,    37,     0,
      34,     6,    18,    20,    23,     4,    36,    38,    39,    40,
       5,     6,    21,    19,    22,    23,    24,    41,    40,    18,
      22,    42,    35,    36,    43,     6,     5,     6,     8,     9,
      10,    18,    20,    25,    41,    44,    45,    46,    47,    48,
      49,    50,    51,    53,    55,    57,    58,    20,    23,    20,
      18,    49,    20,    49,    18,    15,    11,    12,    13,    14,
      16,    17,    26,    27,    52,    54,    28,    29,    56,    49,
      59,    60,    49,    49,    18,    49,    21,    49,    50,    53,
      55,    57,    21,    19,    22,    21,    21,    49,    44,    44,
       7,    44
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    35,    35,    36,
      36,    37,    38,    38,    39,    39,    40,    40,    41,    42,
      42,    43,    43,    44,    44,    44,    44,    44,    45,    45,
      46,    46,    47,    48,    48,    49,    49,    50,    50,    51,
      51,    52,    52,    52,    52,    52,    52,    53,    53,    54,
      54,    55,    55,    56,    56,    57,    57,    57,    57,    58,
      59,    59,    60,    60
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     6,     1,
       1,     6,     1,     1,     3,     1,     2,     4,     4,     2,
       0,     2,     0,     1,     1,     1,     1,     1,     2,     1,
       5,     7,     5,     2,     3,     3,     1,     1,     4,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     3,     1,     1,     1,     3,     1,     1,     1,     4,
       1,     0,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 79 "parser.y" /* yacc.c:1646  */
    { program.declaration_list = *(yyvsp[0].declaration_list); if(debug){ std::cout << "program decs" << std::endl;} }
#line 1340 "parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 82 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-1].declaration_list)->push_back((yyvsp[0].declaration)); (yyval.declaration_list) = (yyvsp[-1].declaration_list); if(debug){ std::cout << "push dec" << std::endl; }}
#line 1346 "parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 83 "parser.y" /* yacc.c:1646  */
    { (yyval.declaration_list) = std::make_shared<std::vector<std::shared_ptr<tree::Declaration>>>(); (yyval.declaration_list)->push_back((yyvsp[0].declaration)); if(debug){ std::cout << "reduce dec to dec_list" << std::endl; }}
#line 1352 "parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 86 "parser.y" /* yacc.c:1646  */
    { (yyval.declaration) = (yyvsp[0].var_declaration); if(debug){ std::cout << "reduce var_dec to declaration" << std::endl; }}
#line 1358 "parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 87 "parser.y" /* yacc.c:1646  */
    { (yyval.declaration) = (yyvsp[0].fun_declaration); if(debug){ std::cout << "reduce fun_dec to declaration" << std::endl; }}
#line 1364 "parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 90 "parser.y" /* yacc.c:1646  */
    { (yyval.var_declaration) = std::make_shared<tree::VariableDeclaration>((yyvsp[-2].token), (yyvsp[-1].id)); if(debug){ std::cout << "var_dec " << (yyvsp[-2].token) << " " << (yyvsp[-1].id) << std::endl; }}
#line 1370 "parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 91 "parser.y" /* yacc.c:1646  */
    { (yyval.var_declaration) = std::make_shared<tree::VariableDeclaration>((yyvsp[-5].token), (yyvsp[-4].id), (yyvsp[-2].number)); if(debug){ std::cout << "var_dec array" << std::endl; }}
#line 1376 "parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 94 "parser.y" /* yacc.c:1646  */
    { (yyval.token) = (yyvsp[0].token); if(debug){ std::cout << "type int" << std::endl; }}
#line 1382 "parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 95 "parser.y" /* yacc.c:1646  */
    { (yyval.token) = (yyvsp[0].token); if(debug){ std::cout << "type void" << std::endl; }}
#line 1388 "parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 98 "parser.y" /* yacc.c:1646  */
    { (yyval.fun_declaration) = std::make_shared<tree::FunctionDeclaration>((yyvsp[-5].token), (yyvsp[-4].id), *(yyvsp[-2].params), (yyvsp[0].compound_stmt)); if(debug){ std::cout << "fun_dec " << (yyvsp[-4].id) << std::endl; }}
#line 1394 "parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 101 "parser.y" /* yacc.c:1646  */
    { (yyval.params) = (yyvsp[0].params); if(debug){ std::cout << "reduce param_list to params" << std::endl; }}
#line 1400 "parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 102 "parser.y" /* yacc.c:1646  */
    { (yyval.params) = std::make_shared<std::vector<std::shared_ptr<tree::Param>>>(); if(debug){ std::cout << "create param_list(void)" << std::endl; }}
#line 1406 "parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 105 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].params)->push_back((yyvsp[0].param)); (yyval.params) = (yyvsp[-2].params); if(debug){ std::cout << "push param " << (yyvsp[0].param)->id << std::endl; }}
#line 1412 "parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 106 "parser.y" /* yacc.c:1646  */
    { (yyval.params) = std::make_shared<std::vector<std::shared_ptr<tree::Param>>>(); (yyval.params)->push_back((yyvsp[0].param)); if(debug){ std::cout << "reduce param " << (yyvsp[0].param)->id << " to param_list" << std::endl; }}
#line 1418 "parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 109 "parser.y" /* yacc.c:1646  */
    { (yyval.param) = std::make_shared<tree::Param>((yyvsp[-1].token), (yyvsp[0].id)); if(debug){ std::cout << "param " << (yyvsp[-1].token) << " " << (yyvsp[0].id) << std::endl; }}
#line 1424 "parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 110 "parser.y" /* yacc.c:1646  */
    { (yyval.param) = std::make_shared<tree::Param>((yyvsp[-3].token), (yyvsp[-2].id), true); if(debug){ std::cout << "array param " << (yyvsp[-3].token) << " " << (yyvsp[-2].id) << std::endl; }}
#line 1430 "parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 113 "parser.y" /* yacc.c:1646  */
    { (yyval.compound_stmt) = std::make_shared<tree::CompoundStatement>(*(yyvsp[-2].local_declarations), *(yyvsp[-1].statement_list)); if(debug){ std::cout << "reduce local+stmt to compound" << std::endl; }}
#line 1436 "parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 116 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-1].local_declarations)->push_back((yyvsp[0].var_declaration)); (yyval.local_declarations) = (yyvsp[-1].local_declarations); if(debug){ std::cout << "push var_declaration to local_declarations" << std::endl; }}
#line 1442 "parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 117 "parser.y" /* yacc.c:1646  */
    { (yyval.local_declarations) = std::make_shared<std::vector<std::shared_ptr<tree::VariableDeclaration>>>(); if(debug){ std::cout << "reduce empty to local_declarations" << std::endl; }}
#line 1448 "parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 119 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-1].statement_list)->push_back((yyvsp[0].statement)); (yyval.statement_list) = (yyvsp[-1].statement_list); if(debug){ std::cout << "push statement to statement_list" << std::endl; }}
#line 1454 "parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 120 "parser.y" /* yacc.c:1646  */
    { (yyval.statement_list) = std::make_shared<std::vector<std::shared_ptr<tree::Statement>>>(); if(debug){ std::cout << "reduce empty to statement_list" << std::endl; }}
#line 1460 "parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 123 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].statement); if(debug){ std::cout << "reduce expression_stmt to statement" << std::endl; }}
#line 1466 "parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 124 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].compound_stmt); if(debug){ std::cout << "reduce compound_stmt to statement" << std::endl; }}
#line 1472 "parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 125 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].statement); if(debug){ std::cout << "reduce iteration_stmt to statement" << std::endl; }}
#line 1478 "parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 126 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].statement); if(debug){ std::cout << "reduce selection_stmt to statement" << std::endl; }}
#line 1484 "parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 127 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].statement); if(debug){ std::cout << "reduce return_stmt to statement" << std::endl; }}
#line 1490 "parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 129 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[-1].expression); if(debug){ std::cout << "reduce expression to expression_stmt" << std::endl; }}
#line 1496 "parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 130 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = std::make_shared<tree::Expression>(); if(debug){ std::cout << "reduce empty expression to expression_stmt" << std::endl; }}
#line 1502 "parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 133 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = std::make_shared<tree::Selection>((yyvsp[-2].expression), (yyvsp[0].statement)); if(debug){ std::cout << "reduce single_if to selection_stmt" << std::endl; }}
#line 1508 "parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 134 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = std::make_shared<tree::Selection>((yyvsp[-4].expression), (yyvsp[-2].statement), (yyvsp[0].statement)); if(debug){ std::cout << "reduce if+else to selection_stmt" << std::endl; }}
#line 1514 "parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 137 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = std::make_shared<tree::Iteration>((yyvsp[-2].expression), (yyvsp[0].statement)); if(debug){ std::cout << "reduce while to iteration_stmt" << std::endl; }}
#line 1520 "parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 140 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = std::make_shared<tree::Return>(); if(debug){ std::cout << "reduce empty return to return_stmt" << std::endl; }}
#line 1526 "parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 141 "parser.y" /* yacc.c:1646  */
    { (yyval.statement) = std::make_shared<tree::Return>((yyvsp[-1].expression)); if(debug){ std::cout << "reduce return+expression to return_stmt" << std::endl; }}
#line 1532 "parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 144 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = std::make_shared<tree::Assign>((yyvsp[-2].variable), (yyvsp[0].expression)); if(debug){ std::cout << "reduce assign to expr" << std::endl; }}
#line 1538 "parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 145 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[0].expression); if(debug){ std::cout << "reduce simple_expr to expr" << std::endl; }}
#line 1544 "parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 148 "parser.y" /* yacc.c:1646  */
    { (yyval.variable) = std::make_shared<tree::Variable>((yyvsp[0].id)); if(debug){ std::cout << "simple var " << (yyvsp[0].id) << std::endl; }}
#line 1550 "parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 149 "parser.y" /* yacc.c:1646  */
    { (yyval.variable) = std::make_shared<tree::Variable>((yyvsp[-3].id), (yyvsp[-1].expression)); if(debug){ std::cout << "array var " << (yyvsp[-3].id); (yyvsp[-1].expression)->print(std::cout); std::cout << std::endl; }}
#line 1556 "parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 152 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = std::make_shared<tree::BinaryOperation>((yyvsp[-2].expression), (yyvsp[-1].op), (yyvsp[0].expression)); }
#line 1562 "parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 153 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[0].expression); if(debug){ std::cout << "reduce add_expr to simple_expr" << std::endl; }}
#line 1568 "parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 155 "parser.y" /* yacc.c:1646  */
    { (yyval.op) = std::string("<="); }
#line 1574 "parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 156 "parser.y" /* yacc.c:1646  */
    { (yyval.op) = std::string("<"); }
#line 1580 "parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 157 "parser.y" /* yacc.c:1646  */
    { (yyval.op) = std::string(">"); }
#line 1586 "parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 158 "parser.y" /* yacc.c:1646  */
    { (yyval.op) = std::string(">="); }
#line 1592 "parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 159 "parser.y" /* yacc.c:1646  */
    { (yyval.op) = std::string("=="); }
#line 1598 "parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 160 "parser.y" /* yacc.c:1646  */
    { (yyval.op) = std::string("!="); }
#line 1604 "parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 163 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = std::make_shared<tree::BinaryOperation>((yyvsp[-2].expression), (yyvsp[-1].op), (yyvsp[0].expression)); }
#line 1610 "parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 164 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[0].expression); if(debug){ std::cout << "reduce term to add_expr" << std::endl; }}
#line 1616 "parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 167 "parser.y" /* yacc.c:1646  */
    { (yyval.op) = std::string("+"); }
#line 1622 "parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 168 "parser.y" /* yacc.c:1646  */
    { (yyval.op) = std::string("-"); }
#line 1628 "parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 171 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = std::make_shared<tree::BinaryOperation>((yyvsp[-2].expression), (yyvsp[-1].op), (yyvsp[0].expression)); }
#line 1634 "parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 172 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[0].expression); if(debug){ std::cout << "reduce factor to term" << std::endl; }}
#line 1640 "parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 174 "parser.y" /* yacc.c:1646  */
    { (yyval.op) = std::string("*"); }
#line 1646 "parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 175 "parser.y" /* yacc.c:1646  */
    { (yyval.op) = std::string("/"); }
#line 1652 "parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 178 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[-1].expression); }
#line 1658 "parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 179 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[0].variable); if(debug){ std::cout << "reduce var " << (yyvsp[0].variable)->id << " to factor" << std::endl; }}
#line 1664 "parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 180 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[0].expression); if(debug){ std::cout << "reduce call to factor" << std::endl; }}
#line 1670 "parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 181 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = std::make_shared<tree::Number>((yyvsp[0].number)); if(debug){ std::cout << "reduce num " << (yyvsp[0].number) << " to factor" << std::endl; }}
#line 1676 "parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 184 "parser.y" /* yacc.c:1646  */
    { (yyval.expression) = std::make_shared<tree::FunctionCall>((yyvsp[-3].id), *(yyvsp[-1].expressions)); if(debug){ std::cout << "function call " << (yyvsp[-3].id) << std::endl; }}
#line 1682 "parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 187 "parser.y" /* yacc.c:1646  */
    { (yyval.expressions) = (yyvsp[0].expressions); if(debug){ std::cout << "reduce arg_list to args" << std::endl; }}
#line 1688 "parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 188 "parser.y" /* yacc.c:1646  */
    { (yyval.expressions) = std::make_shared<std::vector<std::shared_ptr<tree::Expression>>>(); if(debug){ std::cout << "reduce empty to args" << std::endl; }}
#line 1694 "parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 191 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].expressions)->push_back((yyvsp[0].expression)); (yyval.expressions) = (yyvsp[-2].expressions); if(debug){ std::cout << "push expression to arg_list" << std::endl; }}
#line 1700 "parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 192 "parser.y" /* yacc.c:1646  */
    { (yyval.expressions) = std::make_shared<std::vector<std::shared_ptr<tree::Expression>>>(); (yyval.expressions)->push_back((yyvsp[0].expression)); if(debug){ std::cout << "reduce expression to arg_list" << std::endl; }}
#line 1706 "parser.cpp" /* yacc.c:1646  */
    break;


#line 1710 "parser.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 195 "parser.y" /* yacc.c:1906  */


void yyerror(char const* msg) {
	std::cout << msg << " at line " << std::to_string(yylineno) << std::endl;
	exit(1);
}
