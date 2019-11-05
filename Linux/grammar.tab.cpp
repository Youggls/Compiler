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
#line 1 "grammar.y" /* yacc.c:339  */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "../common/trees.h"
class AbstractASTNode;
extern char *yytext;
extern int yylex();
extern int column;
extern FILE * yyin;
AbstractASTNode* root;
void yyerror(const char *str);

#line 80 "./Linux/grammar.tab.cpp" /* yacc.c:339  */

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
   by #include "grammar.tab.h".  */
#ifndef YY_YY_LINUX_GRAMMAR_TAB_H_INCLUDED
# define YY_YY_LINUX_GRAMMAR_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ASSIGNOP = 258,
    OR = 259,
    AND = 260,
    RELOP = 261,
    MINUS = 262,
    PLUS = 263,
    STAR = 264,
    DIV = 265,
    NOT = 266,
    LP = 267,
    RP = 268,
    LB = 269,
    RB = 270,
    LOWER_THAN_ELSE = 271,
    LC = 272,
    RC = 273,
    INT = 274,
    TYPE = 275,
    ID = 276,
    FOR = 277,
    SEMI = 278,
    COMMA = 279,
    RETURN = 280,
    IF = 281,
    ELSE = 282,
    WHILE = 283
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 15 "grammar.y" /* yacc.c:355  */

	AbstractASTNode* ast;
    char* str;

#line 154 "./Linux/grammar.tab.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_LINUX_GRAMMAR_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 185 "./Linux/grammar.tab.cpp" /* yacc.c:358  */

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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   526

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  29
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  78
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  147

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   283

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
      25,    26,    27,    28
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    43,    43,    47,    49,    52,    54,    56,    58,    60,
      62,    64,    69,    74,    76,    79,    81,    84,    86,    89,
      91,    96,    98,   101,   102,   106,   108,   110,   112,   117,
     119,   124,   126,   131,   137,   141,   147,   149,   151,   153,
     155,   157,   159,   161,   165,   167,   169,   171,   173,   175,
     177,   179,   185,   188,   191,   193,   195,   197,   200,   202,
     207,   209,   211,   213,   215,   217,   219,   221,   223,   225,
     227,   229,   231,   233,   235,   237,   239,   241,   243
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ASSIGNOP", "OR", "AND", "RELOP",
  "MINUS", "PLUS", "STAR", "DIV", "NOT", "LP", "RP", "LB", "RB",
  "LOWER_THAN_ELSE", "LC", "RC", "INT", "TYPE", "ID", "FOR", "SEMI",
  "COMMA", "RETURN", "IF", "ELSE", "WHILE", "$accept", "Program",
  "ExtDefList", "ExtDef", "ExtDecList", "Specifier", "VarDec", "FunDec",
  "VarList", "ParamDec", "CompSt", "StmtList", "SeleList", "ELSEIFList",
  "ELSEStmt", "ELSEIFStmt", "IFStmt", "FORLIST", "Stmt", "DefList", "Def",
  "DecList", "Dec", "Exp", "Args", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283
};
# endif

#define YYPACT_NINF -83

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-83)))

#define YYTABLE_NINF -53

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-53)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       2,    -5,   -83,    26,    32,   -83,    -7,   -83,   -83,   -83,
      17,   -83,    34,     1,     0,    -1,   -83,    36,    41,    45,
      57,   -83,   -83,   -83,    41,    55,    42,    54,   -83,   -83,
     -83,    66,    41,   -83,    81,    77,   -83,    60,   -83,   -83,
       7,    71,    73,   125,   -83,   -83,   435,   -83,    41,    38,
     435,   435,   435,   -83,   -83,    83,    93,   435,    96,    99,
     -83,   -83,    85,   -83,   338,   100,   503,   -83,   -83,   -83,
      76,   102,   467,   400,   279,   350,   435,   435,    53,    90,
     -83,   -83,   435,   435,   435,   435,   435,   435,   435,   435,
     435,   -83,   -83,   -83,   326,   105,   292,   106,   362,   -83,
     479,   491,   103,   107,   -83,   101,    90,   -83,   503,   313,
     512,   131,    76,    76,   102,   102,   454,   435,   -83,   403,
     374,   213,   305,   235,   257,   147,   -83,   -83,   -83,   503,
     416,   103,   -83,   419,   386,   103,   -83,   -83,   -83,   503,
     169,   503,   432,   191,   -83,   503,   -83
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    12,     0,     0,     3,     0,     9,     1,     4,
      13,     6,     0,    10,     0,     0,     5,     0,     0,     0,
       0,     8,     7,    16,    20,     0,    18,     0,    13,    11,
      22,     0,     0,    24,     0,    19,    15,     0,    14,    55,
      58,     0,    56,     0,    53,    17,     0,    54,     0,     0,
       0,     0,     0,    21,    75,    74,     0,     0,     0,     0,
      45,    47,    25,    23,     0,     0,    59,    57,    76,    51,
      69,    70,     0,     0,     0,     0,     0,     0,     0,    27,
      26,    29,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    44,    68,    72,    78,     0,     0,     0,     0,    46,
       0,     0,     0,    25,    32,     0,    30,    28,    60,    62,
      61,    63,    65,    64,    66,    67,     0,     0,    71,     0,
       0,     0,     0,     0,     0,     0,    33,    73,    77,    39,
       0,     0,    49,     0,     0,     0,    35,    48,    31,    43,
       0,    42,     0,     0,    50,    40,    34
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -83,   -83,   -83,   126,   115,     9,    35,   -83,    98,   -83,
     135,   -82,   -83,   -72,   -83,    78,   -70,   -83,   -76,   118,
     -83,   108,   -83,   -46,    43
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,    12,    32,    13,    14,    25,    26,
      60,    43,    61,    79,    80,    81,    62,    97,    63,    33,
      34,    41,    42,    64,    95
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      66,    19,   104,     1,    70,    71,    72,   106,   103,     6,
      46,    75,    23,     6,    10,    17,    11,    20,     7,     2,
     125,    17,     2,    21,    24,    18,     8,    94,    98,    15,
     100,   101,    -2,     1,   106,   126,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   132,    24,   136,   137,   140,
     120,    68,     2,   143,    49,    27,    30,    16,    31,    35,
      50,    69,    28,    30,    51,    52,    37,    40,    36,    38,
     102,    94,    54,   129,    55,    56,   134,     2,    57,    58,
       2,    59,    31,    40,   139,    88,    89,   141,   -52,    39,
      90,    17,   -52,   -52,    47,    73,   145,    48,   -52,   -52,
     -52,     2,   -52,   -52,    31,    74,   -52,   -52,    76,   -52,
     -24,    77,    78,    68,   -24,   -24,    90,   105,   118,   121,
     -24,   -24,   -24,     2,   -24,   -24,    49,    58,   -24,   -24,
       9,   -24,    50,    29,   -53,    45,    51,    52,    86,    87,
      88,    89,    20,    53,    54,    90,    55,    56,    49,    22,
      57,    58,    44,    59,    50,     0,    67,   107,    51,    52,
     128,     0,     0,     0,    20,   138,    54,     0,    55,    56,
      49,     0,    57,    58,     0,    59,    50,     0,     0,     0,
      51,    52,     0,     0,     0,     0,    20,   144,    54,     0,
      55,    56,    49,     0,    57,    58,     0,    59,    50,     0,
       0,     0,    51,    52,     0,     0,     0,     0,    20,   146,
      54,     0,    55,    56,    49,     0,    57,    58,     0,    59,
      50,     0,     0,     0,    51,    52,     0,     0,     0,     0,
     131,     0,    54,     0,    55,    56,    49,     0,    57,    58,
       0,    59,    50,     0,     0,     0,    51,    52,     0,     0,
       0,     0,   135,     0,    54,     0,    55,    56,    49,     0,
      57,    58,     0,    59,    50,     0,     0,     0,    51,    52,
       0,     0,     0,     0,    20,     0,    54,     0,    55,    56,
      65,     0,    57,    58,     0,    59,    50,     0,     0,     0,
      51,    52,     0,    65,     0,     0,     0,     0,    54,    50,
      55,     0,    96,    51,    52,     0,    65,     0,     0,     0,
       0,    54,    50,    55,     0,   119,    51,    52,    84,    85,
      86,    87,    88,    89,    54,     0,    55,    90,   133,    82,
      83,    84,    85,    86,    87,    88,    89,     0,     0,     0,
      90,    82,    83,    84,    85,    86,    87,    88,    89,     0,
     117,     0,    90,    82,    83,    84,    85,    86,    87,    88,
      89,    91,     0,     0,    90,    82,    83,    84,    85,    86,
      87,    88,    89,    99,     0,     0,    90,    82,    83,    84,
      85,    86,    87,    88,    89,   122,     0,     0,    90,    82,
      83,    84,    85,    86,    87,    88,    89,   130,     0,     0,
      90,    65,     0,     0,    65,     0,     0,    50,     0,   142,
      50,    51,    52,    93,    51,    52,   -36,    65,     0,    54,
      65,    55,    54,    50,    55,     0,    50,    51,    52,   -38,
      51,    52,   -37,    65,     0,    54,    65,    55,    54,    50,
      55,     0,    50,    51,    52,   -41,    51,    52,     0,     0,
       0,    54,     0,    55,    54,     0,    55,    82,    83,    84,
      85,    86,    87,    88,    89,     0,     0,     0,    90,   127,
      82,    83,    84,    85,    86,    87,    88,    89,     0,     0,
      92,    90,    82,    83,    84,    85,    86,    87,    88,    89,
       0,     0,   123,    90,    82,    83,    84,    85,    86,    87,
      88,    89,     0,     0,   124,    90,    82,    83,    84,    85,
      86,    87,    88,    89,     0,     0,     0,    90,    85,    86,
      87,    88,    89,     0,     0,     0,    90
};

static const yytype_int16 yycheck[] =
{
      46,     1,    78,     1,    50,    51,    52,    79,    78,     0,
       3,    57,    13,     4,    21,    14,    23,    17,    23,    20,
     102,    14,    20,    23,    15,    24,     0,    73,    74,    12,
      76,    77,     0,     1,   106,   105,    82,    83,    84,    85,
      86,    87,    88,    89,    90,   121,    37,   123,   124,   131,
      96,    13,    20,   135,     1,    19,    18,    23,     1,    24,
       7,    23,    21,    18,    11,    12,    24,    32,    13,    15,
      17,   117,    19,   119,    21,    22,   122,    20,    25,    26,
      20,    28,     1,    48,   130,     9,    10,   133,     7,    23,
      14,    14,    11,    12,    23,    12,   142,    24,    17,    18,
      19,    20,    21,    22,     1,    12,    25,    26,    12,    28,
       7,    12,    27,    13,    11,    12,    14,    27,    13,    13,
      17,    18,    19,    20,    21,    22,     1,    26,    25,    26,
       4,    28,     7,    18,    27,    37,    11,    12,     7,     8,
       9,    10,    17,    18,    19,    14,    21,    22,     1,    14,
      25,    26,    34,    28,     7,    -1,    48,    79,    11,    12,
     117,    -1,    -1,    -1,    17,    18,    19,    -1,    21,    22,
       1,    -1,    25,    26,    -1,    28,     7,    -1,    -1,    -1,
      11,    12,    -1,    -1,    -1,    -1,    17,    18,    19,    -1,
      21,    22,     1,    -1,    25,    26,    -1,    28,     7,    -1,
      -1,    -1,    11,    12,    -1,    -1,    -1,    -1,    17,    18,
      19,    -1,    21,    22,     1,    -1,    25,    26,    -1,    28,
       7,    -1,    -1,    -1,    11,    12,    -1,    -1,    -1,    -1,
      17,    -1,    19,    -1,    21,    22,     1,    -1,    25,    26,
      -1,    28,     7,    -1,    -1,    -1,    11,    12,    -1,    -1,
      -1,    -1,    17,    -1,    19,    -1,    21,    22,     1,    -1,
      25,    26,    -1,    28,     7,    -1,    -1,    -1,    11,    12,
      -1,    -1,    -1,    -1,    17,    -1,    19,    -1,    21,    22,
       1,    -1,    25,    26,    -1,    28,     7,    -1,    -1,    -1,
      11,    12,    -1,     1,    -1,    -1,    -1,    -1,    19,     7,
      21,    -1,    23,    11,    12,    -1,     1,    -1,    -1,    -1,
      -1,    19,     7,    21,    -1,    23,    11,    12,     5,     6,
       7,     8,     9,    10,    19,    -1,    21,    14,    23,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    -1,
      14,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      24,    -1,    14,     3,     4,     5,     6,     7,     8,     9,
      10,    23,    -1,    -1,    14,     3,     4,     5,     6,     7,
       8,     9,    10,    23,    -1,    -1,    14,     3,     4,     5,
       6,     7,     8,     9,    10,    23,    -1,    -1,    14,     3,
       4,     5,     6,     7,     8,     9,    10,    23,    -1,    -1,
      14,     1,    -1,    -1,     1,    -1,    -1,     7,    -1,    23,
       7,    11,    12,    13,    11,    12,    13,     1,    -1,    19,
       1,    21,    19,     7,    21,    -1,     7,    11,    12,    13,
      11,    12,    13,     1,    -1,    19,     1,    21,    19,     7,
      21,    -1,     7,    11,    12,    13,    11,    12,    -1,    -1,
      -1,    19,    -1,    21,    19,    -1,    21,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    -1,    -1,    14,    15,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    -1,
      13,    14,     3,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    13,    14,     3,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,    13,    14,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    -1,    14,     6,     7,
       8,     9,    10,    -1,    -1,    -1,    14
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    20,    30,    31,    32,    34,    23,     0,    32,
      21,    23,    33,    35,    36,    12,    23,    14,    24,     1,
      17,    23,    39,    13,    34,    37,    38,    19,    21,    33,
      18,     1,    34,    48,    49,    35,    13,    24,    15,    23,
      35,    50,    51,    40,    48,    37,     3,    23,    24,     1,
       7,    11,    12,    18,    19,    21,    22,    25,    26,    28,
      39,    41,    45,    47,    52,     1,    52,    50,    13,    23,
      52,    52,    52,    12,    12,    52,    12,    12,    27,    42,
      43,    44,     3,     4,     5,     6,     7,     8,     9,    10,
      14,    23,    13,    13,    52,    53,    23,    46,    52,    23,
      52,    52,    17,    45,    47,    27,    42,    44,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    24,    13,    23,
      52,    13,    23,    13,    13,    40,    45,    15,    53,    52,
      23,    17,    47,    23,    52,    17,    47,    47,    18,    52,
      40,    52,    23,    40,    18,    52,    18
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    29,    30,    31,    31,    32,    32,    32,    32,    32,
      33,    33,    34,    35,    35,    36,    36,    37,    37,    38,
      38,    39,    39,    40,    40,    41,    41,    41,    41,    42,
      42,    43,    43,    44,    45,    45,    46,    46,    46,    46,
      46,    46,    46,    46,    47,    47,    47,    47,    47,    47,
      47,    47,    48,    48,    49,    49,    50,    50,    51,    51,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    53,    53
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     3,     2,     3,     3,     2,
       1,     3,     1,     1,     4,     4,     3,     3,     1,     2,
       1,     4,     2,     2,     0,     1,     2,     2,     3,     1,
       2,     4,     2,     2,     7,     5,     2,     3,     3,     3,
       5,     4,     4,     4,     2,     1,     3,     1,     5,     5,
       7,     2,     1,     2,     3,     2,     1,     3,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     4,     3,     4,     1,     1,     2,     3,     1
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


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
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
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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
       'yyls': related to locations.

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

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
  *++yylsp = yylloc;
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 43 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1528 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 47 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1535 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 49 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1542 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 52 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1549 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 54 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1556 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 56 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1563 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 58 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1570 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 60 "grammar.y" /* yacc.c:1646  */
    { yyerrok; (yyval.ast) = NULL;}
#line 1576 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 62 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1583 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 64 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1590 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 69 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1597 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 74 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1604 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 76 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1611 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 79 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1618 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 81 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1625 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 84 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1632 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 86 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1639 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 89 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1646 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 91 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1653 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 96 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1660 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 98 "grammar.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1666 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 101 "grammar.y" /* yacc.c:1646  */
    {}
#line 1672 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 102 "grammar.y" /* yacc.c:1646  */
    {}
#line 1678 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 106 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1685 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 108 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1692 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 110 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1699 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 112 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1706 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 117 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1713 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 119 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1720 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 124 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1727 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 126 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1734 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 131 "grammar.y" /* yacc.c:1646  */
    {
        printf("ELSEIFStmt\n");
    }
#line 1742 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 137 "grammar.y" /* yacc.c:1646  */
    {
        printf("IFStmt\n");
    }
#line 1750 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 141 "grammar.y" /* yacc.c:1646  */
    {
        printf("IFStmt\n");
    }
#line 1758 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 147 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1765 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 149 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1772 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 151 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1779 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 153 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1786 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 155 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1793 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 157 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1800 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 159 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1807 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 161 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1814 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 165 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1821 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 167 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1828 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 169 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1835 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 171 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1842 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 173 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1849 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 175 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1856 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 177 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1863 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 179 "grammar.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1869 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 185 "grammar.y" /* yacc.c:1646  */
    {
	}
#line 1876 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 188 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1883 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 191 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1890 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 193 "grammar.y" /* yacc.c:1646  */
    { yyerrok; }
#line 1896 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 195 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1903 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 197 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1910 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 200 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1917 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 202 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1924 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 207 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1931 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 209 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1938 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 211 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1945 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 213 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1952 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 215 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1959 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 217 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1966 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 219 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1973 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 221 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1980 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 223 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1987 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 225 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 1994 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 227 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 2001 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 229 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 2008 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 231 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 2015 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 233 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 2022 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 235 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 2029 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 237 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 2036 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 239 "grammar.y" /* yacc.c:1646  */
    { yyerrok; }
#line 2042 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 241 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 2049 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 243 "grammar.y" /* yacc.c:1646  */
    {
    }
#line 2056 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
    break;


#line 2060 "./Linux/grammar.tab.cpp" /* yacc.c:1646  */
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
  *++yylsp = yyloc;

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

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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

  yyerror_range[1] = yylsp[1-yylen];
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
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
#line 247 "grammar.y" /* yacc.c:1906  */


void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}

int main(int argc,char* argv[])
{
    FILE* file = fopen(argv[1], "r");
    yyin = file;
    do {
		yyparse();
	} while(!feof(yyin));
    
    return 0;
}
