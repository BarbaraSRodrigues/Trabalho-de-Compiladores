/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SINTATICO_H_INCLUDED
# define YY_YY_SINTATICO_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    T_PROGRAMA = 258,              /* T_PROGRAMA  */
    T_INICIO = 259,                /* T_INICIO  */
    T_FIM = 260,                   /* T_FIM  */
    T_INTEIRO = 261,               /* T_INTEIRO  */
    T_LEIA = 262,                  /* T_LEIA  */
    T_ESCREVA = 263,               /* T_ESCREVA  */
    T_ATRIB = 264,                 /* T_ATRIB  */
    T_ABRE = 265,                  /* T_ABRE  */
    T_FECHA = 266,                 /* T_FECHA  */
    T_MAIS = 267,                  /* T_MAIS  */
    T_MENOS = 268,                 /* T_MENOS  */
    T_MULT = 269,                  /* T_MULT  */
    T_DIV = 270,                   /* T_DIV  */
    T_SE = 271,                    /* T_SE  */
    T_ENTAO = 272,                 /* T_ENTAO  */
    T_SENAO = 273,                 /* T_SENAO  */
    T_FIMSE = 274,                 /* T_FIMSE  */
    T_ENQTO = 275,                 /* T_ENQTO  */
    T_FACA = 276,                  /* T_FACA  */
    T_FIMENQTO = 277,              /* T_FIMENQTO  */
    T_MAIOR = 278,                 /* T_MAIOR  */
    T_MENOR = 279,                 /* T_MENOR  */
    T_IGUAL = 280,                 /* T_IGUAL  */
    T_NAO = 281,                   /* T_NAO  */
    T_NUM = 282,                   /* T_NUM  */
    T_IDENTIF = 283                /* T_IDENTIF  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 34 "sintatico.y"

    int valor;
    char ident[100];
    ptno no;

#line 98 "sintatico.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SINTATICO_H_INCLUDED  */
