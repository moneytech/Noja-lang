/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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
#line 67 "hoyo.y" /* yacc.c:1921  */

  i64 value_i64;
  f64 value_f64;
  char *value_string;
  char *label;

  AST_Node *node;

#line 123 "hoyo.tab.h" /* yacc.c:1921  */
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
