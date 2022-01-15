/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.
   
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

#ifndef YY_YY_FB4_1_TAB_H_INCLUDED
# define YY_YY_FB4_1_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NAME = 258,
     STRING = 259,
     INTNUM = 260,
     BOOL = 261,
     APPROXNUM = 262,
     USERVAR = 263,
     ASSIGN = 264,
     OR = 265,
     XOR = 266,
     ANDOP = 267,
     REGEXP = 268,
     LIKE = 269,
     IS = 270,
     IN = 271,
     NOT = 272,
     BETWEEN = 273,
     COMPARISON = 274,
     SHIFT = 275,
     MOD = 276,
     UMINUS = 277,
     ADD = 278,
     ALL = 279,
     ALTER = 280,
     ANALYZE = 281,
     AND = 282,
     ANY = 283,
     AS = 284,
     ASC = 285,
     AUTO_INCREMENT = 286,
     BEFORE = 287,
     BIGINT = 288,
     BINARY = 289,
     BIT = 290,
     BLOB = 291,
     BOTH = 292,
     BY = 293,
     CALL = 294,
     CASSADE = 295,
     CASE = 296,
     CHANGE = 297,
     CHAR = 298,
     CHECK = 299,
     COLLATE = 300,
     COLUMN = 301,
     COMMENT = 302,
     CONDITION = 303,
     CONSTRAINT = 304,
     CONTINUE = 305,
     CONVERT = 306,
     CREATE = 307,
     CROSS = 308,
     CURRENT_DATE = 309,
     CURRENT_TIME = 310,
     CURRENT_TIMESTAMP = 311,
     CURRENT_USER = 312,
     CURSOR = 313,
     DATABASE = 314,
     DATABASES = 315,
     DATE = 316,
     DATETIME = 317,
     DAY_HOUR = 318,
     DAY_MICROSECOND = 319,
     DAY_MINUTE = 320,
     DAY_SECOND = 321,
     DECIMAL = 322,
     DECLARE = 323,
     DEFAULT = 324,
     DELAYED = 325,
     DELETE = 326,
     DESC = 327,
     DESCRIBE = 328,
     DETERMINISTIC = 329,
     DISTINCT = 330,
     DISTINCTROW = 331,
     DIV = 332,
     DOUBLE = 333,
     DROP = 334,
     DUAL = 335,
     EACH = 336,
     ELSE = 337,
     ELSEIF = 338,
     END = 339,
     ENUM = 340,
     ESCAPED = 341,
     EXISTS = 342,
     EXIT = 343,
     EXPLAIN = 344,
     FETCH = 345,
     FLOAT = 346,
     FOR = 347,
     FORCE = 348,
     FOREIGN = 349,
     FROM = 350,
     FULLTEXT = 351,
     GRANT = 352,
     GROUP = 353,
     HAVING = 354,
     HIGH_PRIORITY = 355,
     HOUR_MICROSECOND = 356,
     HOUR_MINUTE = 357,
     HOUR_SECOND = 358,
     IF = 359,
     IGNORE = 360,
     INFILE = 361,
     INNER = 362,
     INOUT = 363,
     INSENSITIVE = 364,
     INSERT = 365,
     INTEGER = 366,
     INTERVAL = 367,
     INTO = 368,
     ITERATE = 369,
     JOIN = 370,
     KEY = 371,
     KEYS = 372,
     KILL = 373,
     LEADING = 374,
     LEAVE = 375,
     LEFT = 376,
     LIMIT = 377,
     LINES = 378,
     LOAD = 379,
     LOCALTIME = 380,
     LOCALTIMESTAMP = 381,
     LOCK = 382,
     LONG = 383,
     LONGBLOB = 384,
     LONGTEXT = 385,
     LOOP = 386,
     LOW_PRIORITY = 387,
     MATCH = 388,
     MEDIUMBLOB = 389,
     MEDIUMINT = 390,
     MEDIUMTEXT = 391,
     MINUTE_MICROSECOND = 392,
     MINUTE_SECOND = 393,
     MODIFIES = 394,
     NATURAL = 395,
     NO_WRITE_TO_BINLOG = 396,
     NULLX = 397,
     NUMBER = 398,
     ON = 399,
     ONDUPLICATE = 400,
     OPTIMIZE = 401,
     OPTION = 402,
     OPTIONALLY = 403,
     ORDER = 404,
     OUT = 405,
     OUTER = 406,
     OUTFILE = 407,
     PRECISION = 408,
     PRIMARY = 409,
     PROCEDURE = 410,
     PURGE = 411,
     QUICK = 412,
     READ = 413,
     READS = 414,
     REAL = 415,
     REFERENCES = 416,
     RELEASE = 417,
     RENAME = 418,
     REPEAT = 419,
     REPLACE = 420,
     REQUIRE = 421,
     RESTRICT = 422,
     RETURN = 423,
     REVOKE = 424,
     RIGHT = 425,
     ROLLUP = 426,
     SCHEMA = 427,
     SCHEMAS = 428,
     SECOND_MICROSECOND = 429,
     SELECT = 430,
     SENSITIVE = 431,
     SEPARATOR = 432,
     SET = 433,
     SHOW = 434,
     SMALLINT = 435,
     SOME = 436,
     SONAME = 437,
     SPATIAL = 438,
     SPECIFIC = 439,
     SQL = 440,
     SQLEXCEPTION = 441,
     SQLSTATE = 442,
     SQLWARNING = 443,
     SQL_BIG_RESULT = 444,
     SQL_CALL_FOUND_ROWS = 445,
     SQL_SMALL_RESULT = 446,
     SSL = 447,
     STARTING = 448,
     STRAIGHT_JOIN = 449,
     TABLE = 450,
     TEMPORARY = 451,
     TERMIMATED = 452,
     TEXT = 453,
     THEN = 454,
     TIME = 455,
     TIMESTAMP = 456,
     TINYINT = 457,
     TINYTEXT = 458,
     TINYBLOB = 459,
     TO = 460,
     TRAILING = 461,
     TRIGGER = 462,
     UNDO = 463,
     UNION = 464,
     UNIQUE = 465,
     UNLOCK = 466,
     UNSIGNED = 467,
     UPDATE = 468,
     USAGE = 469,
     USE = 470,
     USING = 471,
     UTC_DATE = 472,
     UTC_TIME = 473,
     UTC_TIMESTAMP = 474,
     VALUES = 475,
     VARBINARY = 476,
     VARCHAR = 477,
     VARYING = 478,
     WHEN = 479,
     WHERE = 480,
     WHILE = 481,
     WITH = 482,
     WRITE = 483,
     YEAR = 484,
     YEAR_MONTH = 485,
     ZEROFILL = 486,
     FSUBSTRING = 487,
     FTRIM = 488,
     FDATE_ADD = 489,
     FDATE_SUB = 490,
     FCOUNT = 491
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2053 of yacc.c  */
#line 52 "fb4-1.y"

	int intval;
	double floatval;
	char *strval;
	int subtok;


/* Line 2053 of yacc.c  */
#line 301 "fb4-1.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;
extern YYLTYPE yylloc;
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_FB4_1_TAB_H_INCLUDED  */
