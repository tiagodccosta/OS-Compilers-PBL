/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CMD_LS = 258,
     CMD_PWD = 259,
     CMD_HEAD = 260,
     CMD_TAIL = 261,
     CMD_MKDIR = 262,
     CMD_RMDIR = 263,
     CMD_FIND = 264,
     OPT_ALL = 265,
     OPT_LONG = 266,
     OPT_REVERSE = 267,
     OPT_LOGICAL = 268,
     OPT_PHYSICAL = 269,
     OPT_HELP = 270,
     OPT_LINES = 271,
     OPT_BYTES = 272,
     OPT_QUIET = 273,
     OPT_FOLLOW = 274,
     OPT_PARENTS = 275,
     OPT_VERBOSE = 276,
     OPT_MODE = 277,
     OPT_IGNORE = 278,
     OPT_NAME = 279,
     OPT_TYPE = 280,
     OPT_SIZE = 281,
     NEWLINE = 282,
     NUMBER = 283,
     STRING = 284
   };
#endif
/* Tokens.  */
#define CMD_LS 258
#define CMD_PWD 259
#define CMD_HEAD 260
#define CMD_TAIL 261
#define CMD_MKDIR 262
#define CMD_RMDIR 263
#define CMD_FIND 264
#define OPT_ALL 265
#define OPT_LONG 266
#define OPT_REVERSE 267
#define OPT_LOGICAL 268
#define OPT_PHYSICAL 269
#define OPT_HELP 270
#define OPT_LINES 271
#define OPT_BYTES 272
#define OPT_QUIET 273
#define OPT_FOLLOW 274
#define OPT_PARENTS 275
#define OPT_VERBOSE 276
#define OPT_MODE 277
#define OPT_IGNORE 278
#define OPT_NAME 279
#define OPT_TYPE 280
#define OPT_SIZE 281
#define NEWLINE 282
#define NUMBER 283
#define STRING 284




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 33 "command_parser.y"
{
    int num_value;
    char *str_value;
}
/* Line 1529 of yacc.c.  */
#line 112 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

