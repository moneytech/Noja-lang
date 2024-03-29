/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.3.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 3 "hoyo.y" /* yacc.c:337  */

  
  #include "header.h"

  extern int yylex();
  extern int yyparse(AST_Node**);
  extern FILE *yyin;
  void yyerror(AST_Node **, const char *s);

  #ifdef YYDEBUG
  yydebug = 1;
  #endif


#line 85 "hoyo.tab.c" /* yacc.c:337  */
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "hoyo.tab.h".  */
#ifndef YY_YY_HOYO_TAB_H_INCLUDED
# define YY_YY_HOYO_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    FLOAT = 259,
    STRING = 260,
    LABEL = 261,
    ADD = 262,
    SUB = 263,
    MUL = 264,
    DIV = 265,
    EQL = 266,
    NQL = 267,
    LSS = 268,
    GRT = 269,
    LEQ = 270,
    GEQ = 271,
    AND = 272,
    OR = 273,
    XOR = 274,
    ASSIGN = 275,
    BRK_OP = 276,
    BRK_CL = 277,
    R_ARROW = 278,
    COMMA = 279,
    BRK_C_OP = 280,
    BRK_C_CL = 281,
    SEMICOLON = 282,
    IMPORT = 283,
    FROM = 284,
    AS = 285,
    CLASS = 286,
    NOT = 287,
    FOR = 288,
    WHILE = 289,
    DO = 290,
    IF = 291,
    ELSE = 292,
    PRINT = 293,
    BREAK = 294,
    CONTINUE = 295,
    RETURN = 296,
    BRK_S_OP = 297,
    BRK_S_CL = 298,
    DOT = 299,
    DDOTS = 300,
    FUNCTION = 301,
    DOLLA = 302,
    TRUE = 303,
    FALSE = 304,
    BREAKPOINT = 305,
    T_ADD = 306,
    T_SUB = 307,
    T_MUL = 308,
    T_DIV = 309,
    T_MOD = 310
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 70 "hoyo.y" /* yacc.c:352  */

  i64 value_i64;
  f64 value_f64;
  char *value_string;
  char *label;

  AST_Node *node;

#line 193 "hoyo.tab.c" /* yacc.c:352  */
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
int yyparse (AST_Node **root);

#endif /* !YY_YY_HOYO_TAB_H_INCLUDED  */



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
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
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
#  define YYSIZE_T unsigned
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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   547

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  167

#define YYUNDEFTOK  2
#define YYMAXUTOK   310

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    92,    92,    95,    96,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   115,   116,   120,   124,
     125,   126,   130,   131,   135,   136,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     155,   156,   157,   158,   159,   160,   164,   165,   166,   170,
     171,   172,   176,   177,   178,   179,   180,   181,   182,   186,
     187,   188,   189,   193,   202,   206,   207,   208,   209,   212,
     213,   216,   217,   221,   223,   227,   228,   232
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "STRING", "LABEL", "ADD",
  "SUB", "MUL", "DIV", "EQL", "NQL", "LSS", "GRT", "LEQ", "GEQ", "AND",
  "OR", "XOR", "ASSIGN", "BRK_OP", "BRK_CL", "R_ARROW", "COMMA",
  "BRK_C_OP", "BRK_C_CL", "SEMICOLON", "IMPORT", "FROM", "AS", "CLASS",
  "NOT", "FOR", "WHILE", "DO", "IF", "ELSE", "PRINT", "BREAK", "CONTINUE",
  "RETURN", "BRK_S_OP", "BRK_S_CL", "DOT", "DDOTS", "FUNCTION", "DOLLA",
  "TRUE", "FALSE", "BREAKPOINT", "T_ADD", "T_SUB", "T_MUL", "T_DIV",
  "T_MOD", "$accept", "everything", "statements", "statement",
  "class_decl_inner", "class_decl", "import", "label_list", "func_decl",
  "term", "exp_multiplicative", "exp_additive", "exp_relational",
  "exp_logical", "exp", "dict_inner", "dict", "exp_list",
  "ifelse_statement", "if_statement", "while_statement", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310
};
# endif

#define YYPACT_NINF -56

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-56)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -56,    17,   486,   -56,   -56,   -56,   -56,   -56,   498,     9,
      24,    37,   498,   498,    35,    39,    43,   498,    16,    68,
     -19,   -56,   -56,    97,   -56,   -56,    99,   -56,     2,    40,
      98,    62,   105,   107,   -56,   -56,    45,   -56,   113,    84,
      92,   -56,    51,   109,   120,   121,   -12,   498,   -56,   -56,
     130,   -56,   -56,   -16,   126,    18,   -56,   486,   -56,   -56,
     498,   498,    46,   498,   152,   498,   498,   498,   498,   498,
     498,   498,   498,   498,   498,   498,   498,   -56,   134,   -56,
     498,   498,    55,   -56,   154,   -56,   -56,   -56,   486,    65,
     -56,   498,   -56,    47,   -56,    -9,    75,   102,   -56,   -14,
     -14,   -56,    78,   118,   -56,   -56,   -56,   -56,   -56,   -56,
     -56,   -56,   -56,   -56,   -56,   -56,   -56,   -56,   -56,   -56,
     117,   119,   136,    -1,   150,   198,   -56,   139,   -56,   138,
      79,   -56,   486,    -7,   161,   -56,   -56,   -56,   246,   498,
     498,   163,   -56,   -56,   -56,   -56,   -56,   -56,   144,   294,
     -56,   -56,   486,   -56,   -56,   -56,   -56,   -56,   342,   -56,
     -56,   390,   -56,   -56,   438,   -56,   -56
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     2,     1,    26,    27,    28,    37,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    29,    30,     0,     4,    15,     0,    13,    48,    51,
      58,    62,    64,     0,    36,    11,    74,    12,     0,     0,
       0,    69,     0,    19,     0,     0,     0,     0,     7,     8,
       0,    31,    71,     0,     0,     0,     3,     0,     9,    14,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     5,     0,    33,
       0,     0,     0,    70,     0,    16,     3,     3,     0,     0,
      10,     0,    32,     0,    22,     0,     0,     0,    45,    46,
      47,    34,     0,     0,    38,    49,    50,    56,    57,    52,
      53,    54,    55,    59,    60,    61,    63,     3,    65,    66,
       0,     0,    20,     0,     0,     0,    76,     0,    72,     0,
       0,     3,     0,     0,     0,    42,    35,    39,     0,     0,
       0,     0,    18,    17,    77,    75,     6,     3,     0,     0,
      44,     3,     0,    23,    73,    67,    68,    21,     0,     3,
      41,     0,    43,    24,     0,    40,    25
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -56,   -56,   -55,   -54,   -56,   -56,   -56,    77,    49,    30,
      56,    48,    11,   101,    -8,   -56,   -56,    -5,   -56,   -56,
     -56
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,    24,   123,    25,    26,    96,    27,    28,
      29,    30,    31,    32,    33,    42,    34,    53,    35,    36,
      37
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      38,    97,    55,    98,    45,    46,    56,    62,    91,    50,
      52,    60,    61,    87,    39,    40,   131,     3,   151,     4,
       5,     6,     7,    62,    94,   142,    57,    92,    63,    43,
      64,   124,   125,    88,   126,    41,   132,     8,   152,    52,
      95,     9,    89,    44,    63,    19,    64,    65,    66,     4,
       5,     6,     7,    94,    52,   103,    47,   102,    18,    51,
     120,   121,   138,    20,    21,    22,    48,     8,   101,   129,
      49,     9,   118,   119,    54,    82,   149,    83,   150,    73,
      74,    75,    78,   128,   113,   114,   115,   127,    18,    91,
      99,   100,   158,    20,    21,    22,   161,   133,   162,   134,
     136,   148,    91,   134,   164,     4,     5,     6,     7,    67,
      68,    69,    70,    71,    72,   107,   108,   109,   110,   111,
     112,   105,   106,     8,    58,    76,    59,     9,   135,    80,
      10,   155,   156,    11,    77,    79,    12,    81,    13,    84,
      14,    15,    16,    17,    18,    85,    86,    93,    19,    20,
      21,    22,    23,     4,     5,     6,     7,    90,   104,   117,
     122,   137,   139,   147,   140,   141,   146,   153,   157,   159,
     130,     8,   143,     0,     0,     9,   144,   116,    10,     0,
       0,    11,     0,     0,    12,     0,    13,     0,    14,    15,
      16,    17,    18,     0,     0,     0,    19,    20,    21,    22,
      23,     4,     5,     6,     7,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     8,
       0,     0,     0,     9,   145,     0,    10,     0,     0,    11,
       0,     0,    12,     0,    13,     0,    14,    15,    16,    17,
      18,     0,     0,     0,    19,    20,    21,    22,    23,     4,
       5,     6,     7,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     8,     0,     0,
       0,     9,   154,     0,    10,     0,     0,    11,     0,     0,
      12,     0,    13,     0,    14,    15,    16,    17,    18,     0,
       0,     0,    19,    20,    21,    22,    23,     4,     5,     6,
       7,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     8,     0,     0,     0,     9,
     160,     0,    10,     0,     0,    11,     0,     0,    12,     0,
      13,     0,    14,    15,    16,    17,    18,     0,     0,     0,
      19,    20,    21,    22,    23,     4,     5,     6,     7,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     8,     0,     0,     0,     9,   163,     0,
      10,     0,     0,    11,     0,     0,    12,     0,    13,     0,
      14,    15,    16,    17,    18,     0,     0,     0,    19,    20,
      21,    22,    23,     4,     5,     6,     7,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     8,     0,     0,     0,     9,   165,     0,    10,     0,
       0,    11,     0,     0,    12,     0,    13,     0,    14,    15,
      16,    17,    18,     0,     0,     0,    19,    20,    21,    22,
      23,     4,     5,     6,     7,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     8,
       0,     0,     0,     9,   166,     0,    10,     0,     0,    11,
       0,     0,    12,     0,    13,     0,    14,    15,    16,    17,
      18,     0,     0,     0,    19,    20,    21,    22,    23,     4,
       5,     6,     7,     0,     0,     0,     0,     0,     0,     0,
       0,     4,     5,     6,     7,     0,     0,     8,     0,     0,
       0,     9,     0,     0,    10,     0,     0,    11,     0,     8,
      12,     0,    13,     9,    14,    15,    16,    17,    18,     0,
       0,     0,    19,    20,    21,    22,    23,     0,     0,     0,
      18,     0,     0,     0,     0,    20,    21,    22
};

static const yytype_int16 yycheck[] =
{
       8,    56,    21,    57,    12,    13,    25,    21,    24,    17,
      18,     9,    10,    25,     5,     6,    25,     0,    25,     3,
       4,     5,     6,    21,     6,    26,    45,    43,    42,     5,
      44,    86,    87,    45,    88,    26,    45,    21,    45,    47,
      22,    25,    47,     6,    42,    46,    44,     7,     8,     3,
       4,     5,     6,     6,    62,    63,    21,    62,    42,    43,
       5,     6,   117,    47,    48,    49,    27,    21,    22,    22,
      27,    25,    80,    81,     6,    24,   131,    26,   132,    17,
      18,    19,    37,    91,    73,    74,    75,    22,    42,    24,
      60,    61,   147,    47,    48,    49,   151,    22,   152,    24,
      22,    22,    24,    24,   159,     3,     4,     5,     6,    11,
      12,    13,    14,    15,    16,    67,    68,    69,    70,    71,
      72,    65,    66,    21,    27,    20,    27,    25,    26,    45,
      28,   139,   140,    31,    27,    22,    34,    45,    36,    30,
      38,    39,    40,    41,    42,    25,    25,    21,    46,    47,
      48,    49,    50,     3,     4,     5,     6,    27,     6,    25,
       6,    43,    45,    25,    45,    29,    27,     6,     5,    25,
      93,    21,   123,    -1,    -1,    25,    26,    76,    28,    -1,
      -1,    31,    -1,    -1,    34,    -1,    36,    -1,    38,    39,
      40,    41,    42,    -1,    -1,    -1,    46,    47,    48,    49,
      50,     3,     4,     5,     6,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    -1,    -1,    25,    26,    -1,    28,    -1,    -1,    31,
      -1,    -1,    34,    -1,    36,    -1,    38,    39,    40,    41,
      42,    -1,    -1,    -1,    46,    47,    48,    49,    50,     3,
       4,     5,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    -1,    -1,
      -1,    25,    26,    -1,    28,    -1,    -1,    31,    -1,    -1,
      34,    -1,    36,    -1,    38,    39,    40,    41,    42,    -1,
      -1,    -1,    46,    47,    48,    49,    50,     3,     4,     5,
       6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    21,    -1,    -1,    -1,    25,
      26,    -1,    28,    -1,    -1,    31,    -1,    -1,    34,    -1,
      36,    -1,    38,    39,    40,    41,    42,    -1,    -1,    -1,
      46,    47,    48,    49,    50,     3,     4,     5,     6,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    -1,    -1,    25,    26,    -1,
      28,    -1,    -1,    31,    -1,    -1,    34,    -1,    36,    -1,
      38,    39,    40,    41,    42,    -1,    -1,    -1,    46,    47,
      48,    49,    50,     3,     4,     5,     6,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    -1,    -1,    -1,    25,    26,    -1,    28,    -1,
      -1,    31,    -1,    -1,    34,    -1,    36,    -1,    38,    39,
      40,    41,    42,    -1,    -1,    -1,    46,    47,    48,    49,
      50,     3,     4,     5,     6,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    -1,    -1,    25,    26,    -1,    28,    -1,    -1,    31,
      -1,    -1,    34,    -1,    36,    -1,    38,    39,    40,    41,
      42,    -1,    -1,    -1,    46,    47,    48,    49,    50,     3,
       4,     5,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,    -1,    -1,    21,    -1,    -1,
      -1,    25,    -1,    -1,    28,    -1,    -1,    31,    -1,    21,
      34,    -1,    36,    25,    38,    39,    40,    41,    42,    -1,
      -1,    -1,    46,    47,    48,    49,    50,    -1,    -1,    -1,
      42,    -1,    -1,    -1,    -1,    47,    48,    49
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    57,    58,     0,     3,     4,     5,     6,    21,    25,
      28,    31,    34,    36,    38,    39,    40,    41,    42,    46,
      47,    48,    49,    50,    59,    61,    62,    64,    65,    66,
      67,    68,    69,    70,    72,    74,    75,    76,    70,     5,
       6,    26,    71,     5,     6,    70,    70,    21,    27,    27,
      70,    43,    70,    73,     6,    21,    25,    45,    27,    27,
       9,    10,    21,    42,    44,     7,     8,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    27,    37,    22,
      45,    45,    24,    26,    30,    25,    25,    25,    45,    73,
      27,    24,    43,    21,     6,    22,    63,    58,    59,    65,
      65,    22,    73,    70,     6,    66,    66,    67,    67,    67,
      67,    67,    67,    68,    68,    68,    69,    25,    70,    70,
       5,     6,     6,    60,    58,    58,    59,    22,    70,    22,
      63,    25,    45,    22,    24,    26,    22,    43,    58,    45,
      45,    29,    26,    64,    26,    26,    27,    25,    22,    58,
      59,    25,    45,     6,    26,    70,    70,     5,    58,    25,
      26,    58,    59,    26,    58,    26,    26
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    56,    57,    58,    58,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    60,    60,    61,    62,
      62,    62,    63,    63,    64,    64,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    66,    66,    66,    67,
      67,    67,    68,    68,    68,    68,    68,    68,    68,    69,
      69,    69,    69,    70,    70,    71,    71,    71,    71,    72,
      72,    73,    73,    74,    74,    75,    75,    76
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     5,     2,     2,     2,
       3,     1,     1,     1,     2,     1,     0,     2,     5,     2,
       4,     6,     1,     3,     7,     8,     1,     1,     1,     1,
       1,     2,     3,     3,     3,     4,     1,     1,     3,     4,
       7,     6,     4,     6,     5,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     3,     3,     1,     3,
       3,     3,     1,     3,     1,     3,     3,     5,     5,     2,
       3,     1,     3,     5,     1,     5,     4,     5
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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
        yyerror (root, YY_("syntax error: cannot back up")); \
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
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
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
                  Type, Value, Location, root); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, AST_Node **root)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  YYUSE (root);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, AST_Node **root)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp, root);
  YYFPRINTF (yyo, ")");
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, AST_Node **root)
{
  unsigned long yylno = yyrline[yyrule];
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
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , root);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, root); \
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
            else
              goto append;

          append:
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

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
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
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
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
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, AST_Node **root)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (root);
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
yyparse (AST_Node **root)
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
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
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
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
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
| yyreduce -- do a reduction.  |
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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 92 "hoyo.y" /* yacc.c:1652  */
    {*root = (yyvsp[0].node);}
#line 1587 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 3:
#line 95 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_Block_create(0); }
#line 1593 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 4:
#line 96 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = (yyvsp[-1].node); AST_Node_append((yyval.node), (yyvsp[0].node)); }
#line 1599 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 5:
#line 101 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 1605 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 6:
#line 102 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_Print_create((yyvsp[-2].node)); }
#line 1611 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 7:
#line 103 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_create(NODE_BREAK); }
#line 1617 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 8:
#line 104 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_create(NODE_CONTINUE); }
#line 1623 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 9:
#line 105 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_create(NODE_BREAKPOINT); }
#line 1629 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 10:
#line 106 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_Return_create((yyvsp[-1].node)); }
#line 1635 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 11:
#line 107 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1641 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 12:
#line 108 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1647 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 13:
#line 109 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1653 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 14:
#line 110 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = (yyvsp[-1].node); }
#line 1659 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 16:
#line 115 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_Block_create(0); }
#line 1665 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 17:
#line 116 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = (yyvsp[-1].node); AST_Node_append((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1671 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 18:
#line 120 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_Class_create((yyvsp[-3].label), (yyvsp[-1].node)); }
#line 1677 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 19:
#line 124 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_import_create((yyvsp[0].value_string), 0);  }
#line 1683 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 20:
#line 125 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_import_create((yyvsp[-2].value_string), (yyvsp[0].label)); }
#line 1689 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 21:
#line 126 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_import_create((yyvsp[-4].value_string), (yyvsp[-2].label)); }
#line 1695 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 22:
#line 130 "hoyo.y" /* yacc.c:1652  */
    {(yyval.node) = AST_Node_LabelList_create(); AST_Node_LabelList_append((yyval.node), (yyvsp[0].label)); }
#line 1701 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 23:
#line 131 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = (yyvsp[-2].node); AST_Node_LabelList_append((yyval.node), (yyvsp[0].label)); }
#line 1707 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 24:
#line 135 "hoyo.y" /* yacc.c:1652  */
    {(yyval.node) = AST_Node_ObjectFunction_create((yyvsp[-5].label), 0, (yyvsp[-1].node));}
#line 1713 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 25:
#line 136 "hoyo.y" /* yacc.c:1652  */
    {(yyval.node) = AST_Node_ObjectFunction_create((yyvsp[-6].label), (yyvsp[-4].node), (yyvsp[-1].node));}
#line 1719 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 26:
#line 140 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_i64((yyvsp[0].value_i64));    }
#line 1725 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 27:
#line 141 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_f64((yyvsp[0].value_f64));    }
#line 1731 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 28:
#line 142 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_string((yyvsp[0].value_string)); }
#line 1737 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 29:
#line 143 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_true();     }
#line 1743 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 30:
#line 144 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_false();    }
#line 1749 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 31:
#line 145 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_array(0);   }
#line 1755 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 32:
#line 146 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_array((yyvsp[-1].node));  }
#line 1761 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 33:
#line 147 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = (yyvsp[-1].node);                  }
#line 1767 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 34:
#line 148 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_operator(EXP_CALL, (yyvsp[-2].node), 0);  }
#line 1773 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 35:
#line 149 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_operator(EXP_CALL, (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 1779 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 36:
#line 150 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_dict((yyvsp[0].node));   }
#line 1785 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 37:
#line 151 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_label((yyvsp[0].label));  }
#line 1791 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 38:
#line 152 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_operator(EXP_SELECT_ATTR, (yyvsp[-2].node), AST_Node_label((yyvsp[0].label)));  }
#line 1797 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 39:
#line 153 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_operator(EXP_SELECT, (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 1803 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 40:
#line 155 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_lambda(AST_Node_ObjectFunction_create(0, (yyvsp[-4].node), (yyvsp[-1].node))); }
#line 1809 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 41:
#line 156 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_lambda(AST_Node_ObjectFunction_create(0, 0, (yyvsp[-1].node))); }
#line 1815 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 42:
#line 157 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_lambda(AST_Node_ObjectFunction_create(0, 0, (yyvsp[-1].node))); }
#line 1821 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 43:
#line 158 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_lambda(AST_Node_ObjectFunction_create(0, (yyvsp[-3].node), AST_Node_Block_create((yyvsp[0].node)))); }
#line 1827 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 44:
#line 159 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_lambda(AST_Node_ObjectFunction_create(0, 0, AST_Node_Block_create((yyvsp[0].node)))); }
#line 1833 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 45:
#line 160 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_lambda(AST_Node_ObjectFunction_create(0, 0, AST_Node_Block_create((yyvsp[0].node)))); }
#line 1839 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 46:
#line 164 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_operator(EXP_MUL, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1845 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 47:
#line 165 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_operator(EXP_DIV, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1851 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 48:
#line 166 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1857 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 49:
#line 170 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_operator(EXP_ADD, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1863 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 50:
#line 171 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_operator(EXP_SUB, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1869 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 51:
#line 172 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1875 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 52:
#line 176 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_operator(EXP_LSS, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1881 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 53:
#line 177 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_operator(EXP_GRT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1887 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 54:
#line 178 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_operator(EXP_LEQ, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1893 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 55:
#line 179 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_operator(EXP_GEQ, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1899 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 56:
#line 180 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_operator(EXP_EQL, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1905 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 57:
#line 181 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_operator(EXP_NQL, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1911 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 58:
#line 182 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1917 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 59:
#line 186 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_operator(EXP_AND, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1923 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 60:
#line 187 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_operator(EXP_OR , (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1929 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 61:
#line 188 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_operator(EXP_XOR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1935 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 62:
#line 189 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1941 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 63:
#line 193 "hoyo.y" /* yacc.c:1652  */
    {

    if((yyvsp[-2].node)->flags & EXP_ASSIGNABLE) {
    } else {
      assert(0);
    }

    (yyval.node) = AST_Node_operator(EXP_ASSIGN , (yyvsp[-2].node), (yyvsp[0].node));
  }
#line 1955 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 64:
#line 202 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1961 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 65:
#line 206 "hoyo.y" /* yacc.c:1652  */
    {(yyval.node) = AST_Node_Dict_create(); AST_Node_Dict_append((yyval.node), (yyvsp[-2].value_string), (yyvsp[0].node)); }
#line 1967 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 66:
#line 207 "hoyo.y" /* yacc.c:1652  */
    {(yyval.node) = AST_Node_Dict_create(); AST_Node_Dict_append((yyval.node), (yyvsp[-2].label), (yyvsp[0].node)); }
#line 1973 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 67:
#line 208 "hoyo.y" /* yacc.c:1652  */
    {(yyval.node) = (yyvsp[-4].node);                     AST_Node_Dict_append((yyval.node), (yyvsp[-2].value_string), (yyvsp[0].node)); }
#line 1979 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 68:
#line 209 "hoyo.y" /* yacc.c:1652  */
    {(yyval.node) = (yyvsp[-4].node);                     AST_Node_Dict_append((yyval.node), (yyvsp[-2].label), (yyvsp[0].node)); }
#line 1985 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 69:
#line 212 "hoyo.y" /* yacc.c:1652  */
    {(yyval.node) = AST_Node_Dict_create();}
#line 1991 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 70:
#line 213 "hoyo.y" /* yacc.c:1652  */
    {(yyval.node) = (yyvsp[-1].node);}
#line 1997 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 71:
#line 216 "hoyo.y" /* yacc.c:1652  */
    {(yyval.node)=AST_Node_ExpList_create();AST_Node_ExpList_append((yyval.node), (yyvsp[0].node));}
#line 2003 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 72:
#line 217 "hoyo.y" /* yacc.c:1652  */
    {(yyval.node)= (yyvsp[-2].node); AST_Node_ExpList_append((yyvsp[-2].node), (yyvsp[0].node));}
#line 2009 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 73:
#line 221 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = (yyvsp[-4].node); AST_Node_If_append_else((yyval.node), (yyvsp[-1].node)); }
#line 2015 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 74:
#line 223 "hoyo.y" /* yacc.c:1652  */
    {(yyval.node) = (yyvsp[0].node);}
#line 2021 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 75:
#line 227 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_If_create((yyvsp[-3].node), (yyvsp[-1].node), 0); }
#line 2027 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 76:
#line 228 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_If_create((yyvsp[-2].node), AST_Node_Block_create((yyvsp[0].node)), 0); }
#line 2033 "hoyo.tab.c" /* yacc.c:1652  */
    break;

  case 77:
#line 232 "hoyo.y" /* yacc.c:1652  */
    { (yyval.node) = AST_Node_While_create((yyvsp[-3].node), (yyvsp[-1].node)); }
#line 2039 "hoyo.tab.c" /* yacc.c:1652  */
    break;


#line 2043 "hoyo.tab.c" /* yacc.c:1652  */
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
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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
      yyerror (root, YY_("syntax error"));
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
        yyerror (root, yymsgp);
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
                      yytoken, &yylval, &yylloc, root);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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
                  yystos[yystate], yyvsp, yylsp, root);
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
  yyerror (root, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, root);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp, root);
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
#line 237 "hoyo.y" /* yacc.c:1918  */


AST_Node *AST_Build(char *path) {

  // lex through the input:

  FILE *fp = fopen(path, "r");

  if(!fp){
    printf("No target '%s'.\n", path);
    return 0;
  }

  yyin = fp;

  yylineno = 1;

  AST_Node *root = 0;

  char n = yyparse(&root);

  fclose(fp);

  if(n) {
    return 0;
  }

  return root;
}

void yyerror(AST_Node **root, const char *s) {
  printf("Syntax error on line %d.\n", yylineno);
}
