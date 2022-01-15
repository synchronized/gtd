/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison implementation for Yacc-like parsers in C
   
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
#define YYBISON_VERSION "2.7.12-4996"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 8 "fb4-1.y"

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

char *filename; /* 给词法分析器使用的当前文件名 */
typedef struct YYLTYPE {
	int first_line;
	int first_column;
	int last_line;
	int last_column;
	char *filename;
} YYLTYPE;
#define YYLTYPE_IS_DECLARED 1 /* 告诉语法分析器我们使用自己的定义 */

void yyerror(char *s, ...);
void lyyerror(YYLTYPE t, char *s, ...);
void emit(char *s, ...);

int yycolumn = 1;
#define YY_SER_ACTION yylloc.first_line = yylloc.last_line = yylineno; \
	yylloc.first_column = yycolumn; yylloc.last_column = yycolumn + yyleng + 1; \
	yycolumn += yyleng;

#define YYLLOC_DEFAULT(Current, Rhs, N)							\
	do{															\
		if(N) {													\
			(Current).first_line = YYRHSLOC(Rhs, 1).first_line;	\
			(Current).first_column = YYRHSLOC(Rhs, 1).first_column; \
			(Current).last_line = YYRHSLOC(Rhs, N).last_line;	\
			(Current).last_column = YYRHSLOC(Rhs, N).last_line; \
			(Current).filename = YYRHSLOC(Rhs, 1).filename;		\
		} else {												\
			(Current).first_line = (Current).last_line = 		\
				YYRHSLOC(Rhs, 0).last_line;						\
			(Current).first_column = (Current).last_column = 	\
				YYRHSLOC(Rhs, 0).last_column;					\
			(Current).filename = NULL;							\
		}														\
	} while(0);


/* Line 371 of yacc.c  */
#line 111 "fb4-1.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
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
   by #include "fb4-1.tab.h".  */
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
/* Line 387 of yacc.c  */
#line 52 "fb4-1.y"

	int intval;
	double floatval;
	char *strval;
	int subtok;


/* Line 387 of yacc.c  */
#line 398 "fb4-1.tab.c"
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

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 439 "fb4-1.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif


/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

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
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  33
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1470

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  251
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  73
/* YYNRULES -- Number of rules.  */
#define YYNRULES  298
/* YYNRULES -- Number of states.  */
#define YYNSTATES  610

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   491

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    17,     2,     2,     2,    28,    22,     2,
     248,   249,    26,    24,   250,    25,   247,    27,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   246,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    30,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    21,     2,     2,     2,     2,     2,
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
      15,    16,    18,    19,    20,    23,    29,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,    10,    13,    17,    19,    23,    25,
      27,    29,    31,    33,    37,    41,    45,    49,    53,    57,
      60,    64,    68,    72,    76,    80,    84,    88,    91,    94,
      98,   104,   111,   118,   125,   129,   134,   138,   143,   147,
     153,   155,   159,   160,   162,   168,   175,   181,   188,   193,
     198,   203,   208,   213,   220,   225,   233,   235,   237,   239,
     246,   253,   257,   261,   265,   269,   273,   277,   281,   285,
     289,   294,   301,   305,   311,   316,   322,   326,   331,   335,
     340,   342,   344,   346,   349,   351,   355,   367,   368,   371,
     372,   377,   380,   385,   386,   388,   390,   391,   394,   395,
     398,   399,   403,   404,   409,   412,   413,   416,   418,   422,
     423,   426,   429,   432,   435,   438,   441,   444,   447,   449,
     453,   455,   459,   462,   463,   466,   468,   470,   474,   476,
     478,   482,   488,   492,   496,   498,   499,   505,   509,   515,
     522,   528,   529,   531,   533,   534,   536,   538,   540,   541,
     544,   547,   548,   550,   553,   558,   559,   566,   573,   580,
     583,   584,   586,   590,   594,   596,   604,   607,   610,   613,
     614,   621,   624,   629,   630,   633,   641,   643,   652,   653,
     658,   659,   662,   665,   668,   671,   673,   674,   675,   679,
     683,   689,   691,   693,   697,   701,   709,   713,   717,   723,
     729,   737,   739,   748,   756,   764,   766,   775,   776,   779,
     782,   786,   792,   798,   806,   808,   813,   818,   819,   822,
     824,   833,   844,   854,   866,   873,   882,   883,   885,   887,
     891,   897,   902,   908,   909,   913,   914,   918,   921,   925,
     929,   933,   937,   940,   946,   950,   953,   957,   958,   962,
     968,   969,   971,   972,   975,   978,   979,   984,   988,   991,
     995,   999,  1003,  1007,  1011,  1015,  1019,  1023,  1027,  1029,
    1031,  1033,  1035,  1037,  1041,  1047,  1050,  1055,  1057,  1059,
    1061,  1063,  1067,  1071,  1075,  1079,  1085,  1091,  1093,  1097,
    1101,  1102,  1104,  1106,  1108,  1111,  1113,  1117,  1121
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     252,     0,    -1,   259,   246,    -1,   252,   259,   246,    -1,
       1,   246,    -1,   252,     1,   246,    -1,     3,    -1,     3,
     247,     3,    -1,     8,    -1,     4,    -1,     5,    -1,     7,
      -1,     6,    -1,   253,    24,   253,    -1,   253,    25,   253,
      -1,   253,    26,   253,    -1,   253,    27,   253,    -1,   253,
      28,   253,    -1,   253,    29,   253,    -1,    25,   253,    -1,
     253,    12,   253,    -1,   253,    10,   253,    -1,   253,    11,
     253,    -1,   253,    21,   253,    -1,   253,    22,   253,    -1,
     253,    30,   253,    -1,   253,    23,   253,    -1,    18,   253,
      -1,    17,   253,    -1,   253,    20,   253,    -1,   253,    20,
     248,   260,   249,    -1,   253,    20,    37,   248,   260,   249,
      -1,   253,    20,   190,   248,   260,   249,    -1,   253,    20,
      33,   248,   260,   249,    -1,   253,    15,   151,    -1,   253,
      15,    18,   151,    -1,   253,    15,     6,    -1,   253,    15,
      18,     6,    -1,     8,     9,   253,    -1,   253,    19,   253,
      36,   253,    -1,   253,    -1,   253,   250,   254,    -1,    -1,
     254,    -1,   253,    16,   248,   254,   249,    -1,   253,    18,
      16,   248,   254,   249,    -1,   253,    16,   248,   260,   249,
      -1,   253,    18,    16,   248,   260,   249,    -1,    96,   248,
     260,   249,    -1,     3,   248,   255,   249,    -1,   245,   248,
      26,   249,    -1,   245,   248,   253,   249,    -1,   241,   248,
     254,   249,    -1,   241,   248,   253,   104,   253,   249,    -1,
     242,   248,   254,   249,    -1,   242,   248,   256,   253,   104,
     254,   249,    -1,   128,    -1,   215,    -1,    46,    -1,   243,
     248,   253,   250,   257,   249,    -1,   244,   248,   253,   250,
     257,   249,    -1,   121,   253,    72,    -1,   121,   253,    73,
      -1,   121,   253,    74,    -1,   121,   253,    75,    -1,   121,
     253,   239,    -1,   121,   253,   238,    -1,   121,   253,   110,
      -1,   121,   253,   111,    -1,   121,   253,   112,    -1,    50,
     253,   258,    93,    -1,    50,   253,   258,    91,   253,    93,
      -1,    50,   258,    93,    -1,    50,   258,    91,   253,    93,
      -1,   233,   253,   208,   253,    -1,   258,   233,   253,   208,
     253,    -1,   253,    14,   253,    -1,   253,    18,    14,   253,
      -1,   253,    13,   253,    -1,   253,    18,    13,   253,    -1,
      65,    -1,    63,    -1,    64,    -1,    43,   253,    -1,   260,
      -1,   184,   271,   272,    -1,   184,   271,   272,   104,   275,
     261,   262,   266,   267,   268,   269,    -1,    -1,   234,   253,
      -1,    -1,   107,    47,   263,   265,    -1,   253,   264,    -1,
     263,   250,   253,   264,    -1,    -1,    39,    -1,    81,    -1,
      -1,   236,   180,    -1,    -1,   108,   253,    -1,    -1,   158,
      47,   263,    -1,    -1,   131,   253,   250,   253,    -1,   131,
     253,    -1,    -1,   122,   270,    -1,     3,    -1,   270,   250,
       3,    -1,    -1,   271,    33,    -1,   271,    84,    -1,   271,
      85,    -1,   271,   109,    -1,   271,   203,    -1,   271,   200,
      -1,   271,   198,    -1,   271,   199,    -1,   273,    -1,   272,
     250,   273,    -1,    26,    -1,     3,   247,    26,    -1,   253,
     274,    -1,    -1,    38,     3,    -1,     3,    -1,   276,    -1,
     275,   250,   276,    -1,   277,    -1,   279,    -1,     3,   274,
     286,    -1,     3,   247,     3,   274,   286,    -1,   289,   278,
       3,    -1,   248,   275,   249,    -1,    38,    -1,    -1,   276,
     280,   124,   277,   284,    -1,   276,   203,   277,    -1,   276,
     203,   277,   153,   253,    -1,   276,   282,   281,   124,   277,
     285,    -1,   276,   149,   283,   124,   277,    -1,    -1,   116,
      -1,    62,    -1,    -1,   160,    -1,   130,    -1,   179,    -1,
      -1,   130,   281,    -1,   179,   281,    -1,    -1,   285,    -1,
     153,   253,    -1,   225,   248,   270,   249,    -1,    -1,   224,
     125,   287,   248,   288,   249,    -1,   114,   125,   287,   248,
     288,   249,    -1,   102,   125,   287,   248,   288,   249,    -1,
     101,   124,    -1,    -1,     3,    -1,   288,   250,     3,    -1,
     248,   260,   249,    -1,   290,    -1,    80,   291,   104,     3,
     261,   267,   268,    -1,   291,   141,    -1,   291,   166,    -1,
     291,   114,    -1,    -1,    80,   291,   292,   104,   275,   261,
      -1,     3,   293,    -1,   292,   250,     3,   293,    -1,    -1,
     247,    26,    -1,    80,   291,   104,   292,   225,   275,   261,
      -1,   294,    -1,   119,   296,   297,     3,   298,   229,   299,
     295,    -1,    -1,   154,   125,   222,   301,    -1,    -1,   296,
     141,    -1,   296,    79,    -1,   296,   109,    -1,   296,   114,
      -1,   122,    -1,    -1,    -1,   248,   270,   249,    -1,   248,
     300,   249,    -1,   299,   250,   248,   300,   249,    -1,   253,
      -1,    78,    -1,   300,   250,   253,    -1,   300,   250,    78,
      -1,   119,   296,   297,     3,   187,   301,   295,    -1,     3,
      20,   253,    -1,     3,    20,    78,    -1,   301,   250,     3,
      20,   253,    -1,   301,   250,     3,    20,    78,    -1,   119,
     296,   297,     3,   298,   260,   295,    -1,   302,    -1,   174,
     296,   297,     3,   298,   229,   299,   295,    -1,   174,   296,
     297,     3,   187,   301,   295,    -1,   174,   296,   297,     3,
     298,   260,   295,    -1,   303,    -1,   222,   304,   275,   187,
     305,   261,   267,   268,    -1,    -1,   296,   141,    -1,   296,
     114,    -1,     3,    20,   253,    -1,     3,   247,     3,    20,
     253,    -1,   305,   250,     3,    20,   253,    -1,   305,   250,
       3,   247,     3,    20,   253,    -1,   306,    -1,    61,    68,
     307,     3,    -1,    61,   181,   307,     3,    -1,    -1,   113,
      96,    -1,   308,    -1,    61,   309,   204,   307,     3,   248,
     310,   249,    -1,    61,   309,   204,   307,     3,   247,     3,
     248,   310,   249,    -1,    61,   309,   204,   307,     3,   248,
     310,   249,   319,    -1,    61,   309,   204,   307,     3,   247,
       3,   248,   310,   249,   319,    -1,    61,   309,   204,   307,
       3,   319,    -1,    61,   309,   204,   307,     3,   247,     3,
     319,    -1,    -1,   205,    -1,   311,    -1,   310,   250,   311,
      -1,   163,   125,   248,   270,   249,    -1,   125,   248,   270,
     249,    -1,   105,   125,   248,   270,   249,    -1,    -1,     3,
     317,   312,    -1,    -1,   312,    18,   151,    -1,   312,   151,
      -1,   312,    78,     4,    -1,   312,    78,     5,    -1,   312,
      78,     7,    -1,   312,    78,     6,    -1,   312,    40,    -1,
     312,   219,   248,   270,   249,    -1,   312,   219,   125,    -1,
     312,   125,    -1,   312,    56,     4,    -1,    -1,   248,     5,
     249,    -1,   248,     5,   250,     5,   249,    -1,    -1,    43,
      -1,    -1,   315,   221,    -1,   315,   240,    -1,    -1,   316,
      52,   187,     4,    -1,   316,    54,     4,    -1,    44,   313,
      -1,   211,   313,   315,    -1,   189,   313,   315,    -1,   144,
     313,   315,    -1,   120,   313,   315,    -1,    42,   313,   315,
      -1,   169,   313,   315,    -1,    87,   313,   315,    -1,   100,
     313,   315,    -1,    76,   313,   315,    -1,    70,    -1,   209,
      -1,   210,    -1,    71,    -1,   238,    -1,    52,   313,   316,
      -1,   231,   248,     5,   249,   316,    -1,    43,   313,    -1,
     230,   248,     5,   249,    -1,   213,    -1,    45,    -1,   143,
      -1,   138,    -1,   212,   314,   316,    -1,   207,   314,   316,
      -1,   145,   314,   316,    -1,   139,   314,   316,    -1,    94,
     248,   318,   249,   316,    -1,   187,   248,   318,   249,   316,
      -1,     4,    -1,   318,   250,     4,    -1,   320,   278,   260,
      -1,    -1,   114,    -1,   174,    -1,   321,    -1,   187,   322,
      -1,   323,    -1,   322,   250,   323,    -1,     8,    20,   253,
      -1,     8,     9,   253,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   327,   327,   328,   331,   332,   335,   336,   337,   338,
     339,   340,   341,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,   354,   355,   356,   357,   358,   359,   360,
     363,   364,   365,   366,   369,   370,   371,   372,   373,   376,
     379,   380,   383,   384,   387,   388,   389,   390,   391,   395,
     399,   400,   402,   403,   404,   405,   408,   409,   410,   413,
     414,   417,   418,   419,   420,   421,   422,   423,   424,   425,
     428,   429,   430,   431,   434,   435,   438,   439,   442,   443,
     446,   447,   448,   451,   454,   457,   459,   465,   466,   469,
     470,   473,   474,   477,   478,   479,   482,   483,   486,   487,
     490,   491,   494,   495,   496,   499,   500,   503,   504,   507,
     508,   510,   512,   514,   516,   518,   520,   522,   526,   527,
     528,   529,   532,   535,   536,   537,   540,   541,   544,   545,
     548,   549,   551,   552,   555,   556,   559,   561,   563,   565,
     567,   571,   572,   573,   576,   577,   580,   581,   584,   585,
     586,   589,   590,   593,   594,   597,   598,   600,   602,   606,
     607,   610,   611,   614,   618,   622,   626,   627,   628,   629,
     633,   637,   638,   642,   643,   646,   651,   654,   659,   660,
     663,   664,   665,   666,   667,   670,   671,   674,   675,   678,
     679,   682,   683,   684,   685,   688,   692,   695,   698,   701,
     706,   712,   715,   720,   725,   731,   734,   739,   740,   741,
     744,   747,   750,   753,   759,   762,   764,   768,   769,   774,
     777,   782,   787,   792,   797,   802,   807,   808,   811,   812,
     815,   816,   819,   822,   823,   825,   826,   828,   830,   832,
     834,   836,   838,   840,   842,   844,   846,   850,   851,   852,
     855,   856,   859,   860,   861,   864,   865,   866,   869,   870,
     871,   872,   874,   875,   876,   877,   878,   879,   880,   881,
     882,   883,   884,   885,   886,   887,   888,   889,   890,   891,
     892,   893,   894,   895,   896,   897,   898,   901,   902,   905,
     909,   910,   911,   915,   918,   921,   922,   925,   928
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NAME", "STRING", "INTNUM", "BOOL",
  "APPROXNUM", "USERVAR", "ASSIGN", "OR", "XOR", "ANDOP", "REGEXP", "LIKE",
  "IS", "IN", "'!'", "NOT", "BETWEEN", "COMPARISON", "'|'", "'&'", "SHIFT",
  "'+'", "'-'", "'*'", "'/'", "'%'", "MOD", "'^'", "UMINUS", "ADD", "ALL",
  "ALTER", "ANALYZE", "AND", "ANY", "AS", "ASC", "AUTO_INCREMENT",
  "BEFORE", "BIGINT", "BINARY", "BIT", "BLOB", "BOTH", "BY", "CALL",
  "CASSADE", "CASE", "CHANGE", "CHAR", "CHECK", "COLLATE", "COLUMN",
  "COMMENT", "CONDITION", "CONSTRAINT", "CONTINUE", "CONVERT", "CREATE",
  "CROSS", "CURRENT_DATE", "CURRENT_TIME", "CURRENT_TIMESTAMP",
  "CURRENT_USER", "CURSOR", "DATABASE", "DATABASES", "DATE", "DATETIME",
  "DAY_HOUR", "DAY_MICROSECOND", "DAY_MINUTE", "DAY_SECOND", "DECIMAL",
  "DECLARE", "DEFAULT", "DELAYED", "DELETE", "DESC", "DESCRIBE",
  "DETERMINISTIC", "DISTINCT", "DISTINCTROW", "DIV", "DOUBLE", "DROP",
  "DUAL", "EACH", "ELSE", "ELSEIF", "END", "ENUM", "ESCAPED", "EXISTS",
  "EXIT", "EXPLAIN", "FETCH", "FLOAT", "FOR", "FORCE", "FOREIGN", "FROM",
  "FULLTEXT", "GRANT", "GROUP", "HAVING", "HIGH_PRIORITY",
  "HOUR_MICROSECOND", "HOUR_MINUTE", "HOUR_SECOND", "IF", "IGNORE",
  "INFILE", "INNER", "INOUT", "INSENSITIVE", "INSERT", "INTEGER",
  "INTERVAL", "INTO", "ITERATE", "JOIN", "KEY", "KEYS", "KILL", "LEADING",
  "LEAVE", "LEFT", "LIMIT", "LINES", "LOAD", "LOCALTIME", "LOCALTIMESTAMP",
  "LOCK", "LONG", "LONGBLOB", "LONGTEXT", "LOOP", "LOW_PRIORITY", "MATCH",
  "MEDIUMBLOB", "MEDIUMINT", "MEDIUMTEXT", "MINUTE_MICROSECOND",
  "MINUTE_SECOND", "MODIFIES", "NATURAL", "NO_WRITE_TO_BINLOG", "NULLX",
  "NUMBER", "ON", "ONDUPLICATE", "OPTIMIZE", "OPTION", "OPTIONALLY",
  "ORDER", "OUT", "OUTER", "OUTFILE", "PRECISION", "PRIMARY", "PROCEDURE",
  "PURGE", "QUICK", "READ", "READS", "REAL", "REFERENCES", "RELEASE",
  "RENAME", "REPEAT", "REPLACE", "REQUIRE", "RESTRICT", "RETURN", "REVOKE",
  "RIGHT", "ROLLUP", "SCHEMA", "SCHEMAS", "SECOND_MICROSECOND", "SELECT",
  "SENSITIVE", "SEPARATOR", "SET", "SHOW", "SMALLINT", "SOME", "SONAME",
  "SPATIAL", "SPECIFIC", "SQL", "SQLEXCEPTION", "SQLSTATE", "SQLWARNING",
  "SQL_BIG_RESULT", "SQL_CALL_FOUND_ROWS", "SQL_SMALL_RESULT", "SSL",
  "STARTING", "STRAIGHT_JOIN", "TABLE", "TEMPORARY", "TERMIMATED", "TEXT",
  "THEN", "TIME", "TIMESTAMP", "TINYINT", "TINYTEXT", "TINYBLOB", "TO",
  "TRAILING", "TRIGGER", "UNDO", "UNION", "UNIQUE", "UNLOCK", "UNSIGNED",
  "UPDATE", "USAGE", "USE", "USING", "UTC_DATE", "UTC_TIME",
  "UTC_TIMESTAMP", "VALUES", "VARBINARY", "VARCHAR", "VARYING", "WHEN",
  "WHERE", "WHILE", "WITH", "WRITE", "YEAR", "YEAR_MONTH", "ZEROFILL",
  "FSUBSTRING", "FTRIM", "FDATE_ADD", "FDATE_SUB", "FCOUNT", "';'", "'.'",
  "'('", "')'", "','", "$accept", "stmt_list", "expr", "val_list",
  "opt_val_list", "trim_ltb", "interval_exp", "case_list", "stmt",
  "select_stmt", "opt_where", "opt_groupby", "groupby_list",
  "opt_asc_desc", "opt_with_rollup", "opt_having", "opt_orderby",
  "opt_limit", "opt_into_list", "column_list", "select_opts",
  "select_expr_list", "select_expr", "opt_as_alias", "table_references",
  "table_reference", "table_factor", "opt_as", "join_table",
  "opt_inner_cross", "opt_outer", "left_or_right",
  "opt_left_or_right_outer", "opt_join_condition", "join_condition",
  "index_hint", "opt_for_join", "index_list", "table_subquery",
  "delete_stmt", "delete_opts", "delete_list", "opt_dot_star",
  "insert_stmt", "opt_ondupupdate", "insert_opts", "opt_into",
  "opt_col_names", "insert_vals_list", "insert_vals", "insert_asgn_list",
  "replace_stmt", "update_stmt", "update_opts", "update_asgn_list",
  "create_database_stmt", "opt_if_not_exists", "create_table_stmt",
  "opt_temporary", "create_col_list", "create_definition", "column_atts",
  "opt_length", "opt_binary", "opt_uz", "opt_csc", "data_type",
  "enum_list", "create_select_statement", "opt_ignore_replace", "set_stmt",
  "set_list", "set_expr", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,    33,   272,   273,
     274,   124,    38,   275,    43,    45,    42,    47,    37,   276,
      94,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,   355,
     356,   357,   358,   359,   360,   361,   362,   363,   364,   365,
     366,   367,   368,   369,   370,   371,   372,   373,   374,   375,
     376,   377,   378,   379,   380,   381,   382,   383,   384,   385,
     386,   387,   388,   389,   390,   391,   392,   393,   394,   395,
     396,   397,   398,   399,   400,   401,   402,   403,   404,   405,
     406,   407,   408,   409,   410,   411,   412,   413,   414,   415,
     416,   417,   418,   419,   420,   421,   422,   423,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   433,   434,   435,
     436,   437,   438,   439,   440,   441,   442,   443,   444,   445,
     446,   447,   448,   449,   450,   451,   452,   453,   454,   455,
     456,   457,   458,   459,   460,   461,   462,   463,   464,   465,
     466,   467,   468,   469,   470,   471,   472,   473,   474,   475,
     476,   477,   478,   479,   480,   481,   482,   483,   484,   485,
     486,   487,   488,   489,   490,   491,    59,    46,    40,    41,
      44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   251,   252,   252,   252,   252,   253,   253,   253,   253,
     253,   253,   253,   253,   253,   253,   253,   253,   253,   253,
     253,   253,   253,   253,   253,   253,   253,   253,   253,   253,
     253,   253,   253,   253,   253,   253,   253,   253,   253,   253,
     254,   254,   255,   255,   253,   253,   253,   253,   253,   253,
     253,   253,   253,   253,   253,   253,   256,   256,   256,   253,
     253,   257,   257,   257,   257,   257,   257,   257,   257,   257,
     253,   253,   253,   253,   258,   258,   253,   253,   253,   253,
     253,   253,   253,   253,   259,   260,   260,   261,   261,   262,
     262,   263,   263,   264,   264,   264,   265,   265,   266,   266,
     267,   267,   268,   268,   268,   269,   269,   270,   270,   271,
     271,   271,   271,   271,   271,   271,   271,   271,   272,   272,
     272,   272,   273,   274,   274,   274,   275,   275,   276,   276,
     277,   277,   277,   277,   278,   278,   279,   279,   279,   279,
     279,   280,   280,   280,   281,   281,   282,   282,   283,   283,
     283,   284,   284,   285,   285,   286,   286,   286,   286,   287,
     287,   288,   288,   289,   259,   290,   291,   291,   291,   291,
     290,   292,   292,   293,   293,   290,   259,   294,   295,   295,
     296,   296,   296,   296,   296,   297,   297,   298,   298,   299,
     299,   300,   300,   300,   300,   294,   301,   301,   301,   301,
     294,   259,   302,   302,   302,   259,   303,   304,   304,   304,
     305,   305,   305,   305,   259,   306,   306,   307,   307,   259,
     308,   308,   308,   308,   308,   308,   309,   309,   310,   310,
     311,   311,   311,   311,   311,   312,   312,   312,   312,   312,
     312,   312,   312,   312,   312,   312,   312,   313,   313,   313,
     314,   314,   315,   315,   315,   316,   316,   316,   317,   317,
     317,   317,   317,   317,   317,   317,   317,   317,   317,   317,
     317,   317,   317,   317,   317,   317,   317,   317,   317,   317,
     317,   317,   317,   317,   317,   317,   317,   318,   318,   319,
     320,   320,   320,   259,   321,   322,   322,   323,   323
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     3,     2,     3,     1,     3,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     2,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     3,
       5,     6,     6,     6,     3,     4,     3,     4,     3,     5,
       1,     3,     0,     1,     5,     6,     5,     6,     4,     4,
       4,     4,     4,     6,     4,     7,     1,     1,     1,     6,
       6,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       4,     6,     3,     5,     4,     5,     3,     4,     3,     4,
       1,     1,     1,     2,     1,     3,    11,     0,     2,     0,
       4,     2,     4,     0,     1,     1,     0,     2,     0,     2,
       0,     3,     0,     4,     2,     0,     2,     1,     3,     0,
       2,     2,     2,     2,     2,     2,     2,     2,     1,     3,
       1,     3,     2,     0,     2,     1,     1,     3,     1,     1,
       3,     5,     3,     3,     1,     0,     5,     3,     5,     6,
       5,     0,     1,     1,     0,     1,     1,     1,     0,     2,
       2,     0,     1,     2,     4,     0,     6,     6,     6,     2,
       0,     1,     3,     3,     1,     7,     2,     2,     2,     0,
       6,     2,     4,     0,     2,     7,     1,     8,     0,     4,
       0,     2,     2,     2,     2,     1,     0,     0,     3,     3,
       5,     1,     1,     3,     3,     7,     3,     3,     5,     5,
       7,     1,     8,     7,     7,     1,     8,     0,     2,     2,
       3,     5,     5,     7,     1,     4,     4,     0,     2,     1,
       8,    10,     9,    11,     6,     8,     0,     1,     1,     3,
       5,     4,     5,     0,     3,     0,     3,     2,     3,     3,
       3,     3,     2,     5,     3,     2,     3,     0,     3,     5,
       0,     1,     0,     2,     2,     0,     4,     3,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     1,
       1,     1,     1,     3,     5,     2,     4,     1,     1,     1,
       1,     3,     3,     3,     3,     5,     5,     1,     3,     3,
       0,     1,     1,     1,     2,     1,     3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     0,   226,   169,   180,   180,   109,     0,   180,     0,
       0,    84,   164,   176,   201,   205,   214,   219,   293,     4,
     217,   217,   227,     0,     0,   186,   186,     0,     0,   294,
     295,     0,     0,     1,     0,     0,     2,     0,     0,     0,
     217,   173,     0,   168,   166,   167,     0,   182,   183,   184,
     185,   181,     0,     0,     6,     9,    10,    12,    11,     8,
       0,     0,     0,   120,   110,     0,     0,    81,    82,    80,
     111,   112,     0,   113,   116,   117,   115,   114,     0,     0,
       0,     0,     0,   123,    85,   118,     0,     0,     0,   184,
     181,   123,     0,     0,   126,   128,   129,   135,     5,     3,
     218,   215,   216,     0,     0,   171,    87,     0,     0,     0,
     187,   187,     0,    42,     0,     6,    28,    27,    19,    83,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   125,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   122,     0,     0,   298,   297,   296,     0,   155,     0,
       0,     0,     0,   143,   142,   146,   148,   147,     0,     0,
     144,   134,     0,   290,   174,     0,   100,     0,    87,   173,
       0,     0,     0,     0,     0,     7,   121,    40,    43,     0,
      38,     0,     0,     0,     0,    72,     0,     0,    40,     0,
      58,    56,    57,     0,     0,     0,     0,     0,     0,    21,
      22,    20,    78,    76,    36,     0,    34,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    29,    23,    24,    26,
      13,    14,    15,    16,    17,    18,    25,   124,    87,   119,
     123,     0,     0,     0,   130,   163,   133,     0,    87,   127,
     144,   144,     0,   137,     0,   145,     0,   132,   291,   292,
       0,   233,   224,   135,    88,     0,   102,    87,   170,   172,
       0,   178,   107,     0,     0,   178,   178,     0,   178,     0,
      49,     0,     0,    70,     0,     0,    48,     0,    52,    54,
       0,     0,     0,    50,    51,    37,    35,     0,     0,    79,
      77,     0,     0,     0,     0,     0,     0,    89,   155,   160,
     160,   160,     0,     0,     0,   100,   149,   150,     0,     0,
     151,     0,   290,     0,     0,     0,     0,     0,   228,     0,
       0,     0,   165,   175,     0,     0,     0,   195,   188,     0,
       0,   178,   200,   203,   178,   204,    41,    74,     0,    73,
       0,     0,     0,     0,     0,     0,    44,    46,     0,     0,
      39,     0,     0,     0,    30,     0,    98,   131,     0,     0,
       0,     0,   210,     0,     0,   102,   140,   138,     0,     0,
     136,   152,     0,   233,   225,   247,   247,   247,   278,   247,
     268,   271,   247,   247,     0,   247,   247,   280,   250,   279,
     247,   250,   247,     0,   247,   250,   269,   270,   247,   250,
     277,     0,     0,   272,   235,     0,     0,     0,   290,   233,
     289,    93,   101,   104,   197,   196,     0,     0,   108,   192,
     191,     0,     0,   177,   202,    71,    75,    53,     0,     0,
      59,    60,    45,    47,    33,    31,    32,     0,     0,   100,
     159,     0,     0,     0,     0,     0,     0,   206,   153,     0,
     139,     0,     0,   252,   275,   258,   255,   252,   252,     0,
     252,   252,   251,   255,   252,   255,   252,     0,   252,   255,
     252,   255,     0,     0,   234,     0,     0,     0,   222,   229,
      94,    95,    91,     0,     0,     0,     0,   189,     0,     0,
      55,    61,    62,    63,    64,    67,    68,    69,    66,    65,
      96,    99,   102,   161,     0,     0,     0,   211,   212,     0,
       0,   290,     0,   263,   273,   267,   265,   287,     0,   266,
     262,   284,   261,   283,   264,     0,   260,   282,   259,   281,
       0,     0,     0,   242,     0,     0,   245,   237,     0,     0,
     231,     0,    93,   103,   179,   199,   198,   194,   193,     0,
       0,    90,   105,   158,     0,   157,   156,     0,   154,   223,
     248,     0,   253,   254,     0,     0,   255,     0,   255,   276,
     255,   236,   246,   238,   239,   241,   240,   244,     0,   232,
     230,    92,   190,    97,     0,    86,   162,   213,     0,     0,
     257,   285,   288,   286,   274,     0,   106,   249,   256,   243
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     9,   187,   188,   189,   204,   354,   122,    10,    11,
     176,   366,   422,   492,   561,   449,   266,   332,   595,   273,
      27,    84,    85,   151,    93,    94,    95,   172,    96,   169,
     256,   170,   252,   380,   381,   244,   369,   514,    97,    12,
      24,    46,   105,    13,   337,    25,    52,   182,   341,   431,
     271,    14,    15,    32,   248,    16,    38,    17,    23,   327,
     328,   484,   463,   473,   523,   524,   414,   528,   262,   263,
      18,    29,    30
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -402
static const yytype_int16 yypact[] =
{
     148,  -179,    -7,  -402,  -402,  -402,  -402,    90,     0,   963,
    -116,  -402,  -402,  -402,  -402,  -402,  -402,  -402,  -402,  -402,
      25,    25,  -402,    -1,    20,   257,   257,   147,   126,   -56,
    -402,    99,     1,  -402,   -21,   -17,  -402,   143,   260,   279,
      25,    52,   294,  -402,  -402,  -402,   -92,  -402,  -402,  -402,
    -402,  -402,   299,   303,  -193,  -402,  -402,  -402,  -402,   301,
     632,   632,   632,  -402,  -402,   632,   266,  -402,  -402,  -402,
    -402,  -402,    67,  -402,  -402,  -402,  -402,  -402,    72,    80,
      95,   101,   111,  1381,   -91,  -402,   632,   632,    90,     2,
       3,     5,    -2,  -160,   286,  -402,  -402,   323,  -402,  -402,
    -402,  -402,  -402,   362,   343,  -402,    71,    28,     1,   371,
    -165,  -159,    68,   632,   632,   -64,  1006,  1006,  -402,  -402,
     632,   931,   -77,   215,   632,   216,   632,   632,   350,  -402,
     632,   632,   632,   632,   632,    11,   153,   231,   632,    45,
     632,   632,   632,   632,   632,   632,   632,   632,   632,   632,
     400,  -402,     1,   632,  1402,  1402,  -402,   416,   -45,   181,
     -43,   431,     1,  -402,  -402,  -402,  -100,  -402,     1,   313,
     281,  -402,   447,   -72,  -402,   632,   296,     1,  -169,    52,
     449,   452,  -152,   449,  -104,  -402,  -402,   745,  -402,   207,
    1402,   465,   978,   -67,   632,  -402,   632,   221,   724,   224,
    -402,  -402,  -402,   225,   632,   766,   787,   239,   868,  1422,
    1071,   842,  1440,  1440,  -402,    12,  -402,   379,   632,   632,
     244,  1351,   245,   246,   247,   215,  1166,   943,   683,   664,
     312,   312,   470,   470,   470,   470,  -402,  -402,  -169,  -402,
      53,   376,   377,   378,  -402,  -402,  -402,   -11,  -103,   286,
     281,   281,   381,   353,     1,  -402,   388,  -402,  -402,  -402,
     510,    18,  -402,   323,  1402,   467,   384,  -169,  -402,  -402,
     499,  -110,  -402,    27,   277,   373,  -110,   277,   373,   632,
    -402,   632,   632,  -402,  1275,  1034,  -402,   632,  -402,  -402,
    1188,   410,   410,  -402,  -402,  -402,  -402,   283,   284,  1440,
    1440,   379,   632,   215,   215,   215,   285,   428,   -45,   438,
     438,   438,   632,   538,   542,   296,  -402,  -402,     1,   632,
    -133,     1,   -78,  1036,   421,   305,   422,    51,  -402,   215,
     632,   632,  -402,  -402,   473,   424,   551,  -402,  -402,   552,
     479,   -82,  -402,  -402,   -82,  -402,  -402,  1402,  1296,  -402,
     632,   889,   632,   632,   307,   311,  -402,  -402,   317,   321,
     641,   322,   324,   328,  -402,   515,   471,  -402,   454,   333,
     334,   335,  1402,   564,   -10,   384,  -402,  1402,   632,   348,
    -402,  -402,  -133,    18,  -402,   349,   349,   349,  -402,   349,
    -402,  -402,   349,   349,   354,   349,   349,  -402,   555,  -402,
     349,   555,   349,   355,   349,   555,  -402,  -402,   349,   555,
    -402,   356,   357,  -402,  -402,   358,   452,   360,   -89,    18,
    -402,  1317,   351,   819,  -402,  1402,   387,   590,  -402,  -402,
    1402,    75,   363,  -402,  -402,  -402,  1402,  -402,   369,   910,
    -402,  -402,  -402,  -402,  -402,  -402,  -402,   632,   632,   296,
    -402,   616,   616,   616,   632,   632,   625,  -402,  1402,   452,
    -402,    84,   624,  -402,  -402,  -402,  -402,  -402,  -402,   626,
    -402,  -402,  -402,  -402,  -402,  -402,  -402,   626,  -402,  -402,
    -402,  -402,   628,   636,   186,   452,   114,   452,  -402,  -402,
    -402,  -402,  -402,   632,   632,   449,   582,  -402,   609,   479,
    -402,  -402,  -402,  -402,  -402,  -402,  -402,  -402,  -402,  -402,
     -35,  1402,   384,  -402,   123,   128,   131,  1402,  1402,   611,
     145,   -46,   157,  -176,   164,  -176,  -176,  -402,   159,  -176,
    -176,   164,  -176,   164,  -176,   162,  -176,   164,  -176,   164,
     393,   394,   493,  -402,   644,    69,  -402,  -402,  -106,   168,
    -402,   174,  1317,  1402,   401,  -402,  1402,  -402,  1402,   176,
     474,  -402,   531,  -402,   652,  -402,  -402,   632,  -402,  -402,
    -402,   651,  -402,  -402,   489,   654,  -402,   673,  -402,  -402,
    -402,  -402,  -402,  -402,  -402,  -402,  -402,  -402,   452,  -402,
    -402,  -402,  -402,  -402,   452,  -402,  -402,  1402,   430,   676,
    -402,   164,  -402,   164,   164,   183,   433,  -402,  -402,  -402
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -402,  -402,   -27,   -84,  -402,  -402,   389,   563,   677,   135,
      60,  -402,   238,   146,  -402,  -402,  -278,  -368,  -402,  -401,
    -402,  -402,   546,   -80,    37,   539,  -122,   437,  -402,  -402,
      44,  -402,  -402,  -402,   320,   395,   138,    10,  -402,  -402,
    -402,   662,   540,  -402,  -139,   180,   699,   615,   450,   230,
    -181,  -402,  -402,  -402,  -402,  -402,    26,  -402,  -402,   347,
     314,  -402,   172,  -144,    50,   -28,  -402,   254,  -291,  -402,
    -402,  -402,   653
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -222
static const yytype_int16 yytable[] =
{
      83,    91,   276,  -207,    91,  -209,  -208,   457,   129,   312,
     455,   158,   108,   152,   194,   486,   195,   214,   295,   587,
     378,   323,   180,    41,   282,   258,   283,   161,   183,   215,
     250,   384,     6,   116,   117,   118,   258,   375,   119,   121,
     199,   203,   258,   150,   335,   572,   253,    39,   115,    55,
      56,    57,    58,    59,   112,   113,   129,   241,   520,   154,
     155,    20,    60,    61,   573,   175,   103,    19,   258,   242,
      62,   185,   335,   583,   584,   585,   586,   274,   222,   251,
       6,   162,   223,   181,   549,   259,   551,   190,    65,   181,
     162,   150,   379,   192,   186,    66,   259,   198,    28,   205,
     206,   208,   259,   209,   210,   211,   212,   213,    67,    68,
      69,   221,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   324,    42,   277,    83,   488,   259,   160,
      36,   175,   320,   297,    43,    86,   342,   343,    37,   345,
     336,    72,   588,   325,   562,   178,    87,   314,   264,     1,
      54,    55,    56,    57,    58,    59,   196,  -220,   109,   153,
     308,    44,   216,   296,    60,    61,   196,   284,   432,   285,
     383,   512,    62,    63,    21,   260,   261,   290,    47,   243,
      64,   326,     6,   191,   113,    26,    45,   605,    31,   238,
      65,   299,   300,   606,    88,   346,   376,    66,    22,   382,
    -221,   560,   433,    40,   542,   434,   246,   162,    48,     2,
      67,    68,    69,    89,   267,   493,   574,   358,   575,   115,
      55,    56,    57,    58,    59,    98,   543,   159,     3,    99,
     569,    70,    71,    60,    61,   224,   313,   456,   268,   100,
      90,    62,   544,    72,   218,   219,    92,   220,  -207,    92,
    -209,  -208,   157,   177,   347,   348,    73,   475,   197,    65,
     351,   479,   200,   101,   545,   481,    66,     4,   438,   115,
      55,    56,    57,    58,    59,   360,   338,   339,   109,    67,
      68,    69,   102,    60,    61,   372,    78,    79,    80,    81,
      82,    62,   377,   225,   316,   317,  -173,   106,   307,   104,
     418,   419,   110,   421,   423,   175,   111,   425,   315,    65,
     114,   546,    72,   430,   554,   123,    66,   275,   104,   278,
     124,  -173,     5,   436,   497,   498,   439,   333,   125,    67,
      68,    69,     6,   521,   419,     7,    47,   547,   145,   146,
     147,   148,   149,   126,   201,    74,    75,    76,   163,   127,
      77,   458,   298,   115,    55,    56,    57,    58,    59,   128,
     306,   171,    72,   550,   339,   173,    48,    60,    61,   174,
       8,    49,   563,   564,   179,    62,   207,   565,   564,    50,
     566,   564,   115,    55,    56,    57,    58,    59,    78,    79,
      80,    81,    82,    65,   568,   339,    60,    61,    51,     6,
      66,   217,   164,   237,    62,   548,   570,   571,   576,   577,
    -141,   578,   577,    67,    68,    69,   165,   589,   339,   240,
     421,   511,    65,   590,   339,   592,   498,   517,   518,    66,
     245,   202,   609,   339,   247,   166,   359,   254,   361,   362,
     363,   255,    67,    68,    69,   531,    72,   533,   370,   371,
     257,   537,   270,   539,   265,   272,   280,    78,    79,    80,
      81,    82,   515,   516,   420,   167,   552,   553,   185,   556,
     286,   558,   430,   288,   289,    72,   115,    55,    56,    57,
      58,    59,   115,    55,    56,    57,    58,    59,   293,   168,
      60,    61,   301,   303,   304,   305,    60,    61,    62,   120,
     149,   309,   310,   311,    62,   318,   319,    78,    79,    80,
      81,    82,   321,   322,   330,   331,    65,   525,   526,   334,
     529,   530,    65,    66,   532,   340,   534,   335,   536,    66,
     538,   353,   356,   357,   364,   365,    67,    68,    69,   368,
     597,   373,    67,    68,    69,   374,   415,   417,   601,   426,
     603,   424,   604,   416,   427,   428,   440,   429,   464,   465,
     441,   466,   447,     6,   467,   468,   442,   470,   471,    72,
     443,   444,   474,   445,   476,    72,   478,   446,   450,   448,
     480,   451,   452,   453,   454,   115,    55,    56,    57,    58,
      59,    78,    79,    80,    81,    82,   459,   462,   472,    60,
      61,   493,   469,   477,   482,   483,   485,    62,   487,   495,
     496,   499,   115,    55,    56,    57,    58,    59,   500,   513,
      78,    79,    80,    81,    82,    65,    60,    61,   519,   522,
     527,   567,    66,   540,    62,   115,    55,    56,    57,    58,
      59,   541,   579,   580,   581,    67,    68,    69,   582,    60,
      61,   336,    65,   594,   593,   596,   598,    62,   600,    66,
     555,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,    67,    68,    69,    65,   599,   602,    72,   607,
     608,   355,    66,   339,   193,   510,    35,   557,   143,   144,
     145,   146,   147,   148,   149,    67,    68,    69,   591,   239,
     329,   249,   460,   367,   107,    72,   142,   143,   144,   145,
     146,   147,   148,   149,    78,    79,    80,    81,    82,   269,
      78,    79,    80,    81,    82,    53,   184,   344,    72,   559,
     461,   535,     0,   489,   130,   131,   132,   133,   134,   135,
     136,   156,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   130,   131,   132,   133,   134,
     135,   136,     0,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   130,   131,   132,   133,
     134,   135,   136,     0,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   130,   131,   132,
     133,   134,   135,   136,     0,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,     0,     0,
       0,     0,     0,    78,    79,    80,    81,    82,   287,   130,
     131,   132,   133,   134,   135,   136,     0,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
      78,    79,    80,    81,    82,   133,   134,   135,   136,     0,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,    78,    79,    80,    81,    82,   130,   131,
     132,   133,   134,   135,   136,     0,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   130,
     131,   132,   133,   134,   135,   136,     0,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     130,   131,   132,   133,   134,   135,   136,     0,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   130,   131,   132,   133,   134,   135,   136,     0,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,     0,    33,    34,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   279,     0,     0,     0,     0,     0,
       0,     0,   501,   502,   503,   504,     0,     0,   130,   131,
     132,   133,   134,   135,   136,   279,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,     0,
       0,     0,     0,     0,     0,     0,   291,     0,     0,     0,
     505,   506,   507,     0,     2,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   292,     0,     0,
       0,     0,     0,     3,   130,   131,   132,   133,   134,   135,
     136,     0,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,     0,     0,     0,     0,   494,
       0,     0,     0,     0,     0,     0,     0,     0,   385,   386,
     387,   388,     4,   132,   133,   134,   135,   136,   389,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,     0,     0,     0,     0,   390,   391,     0,     0,
       0,     0,   392,     0,     0,     0,     0,   294,     0,     0,
       0,     0,     0,   393,     0,     0,     0,     0,     0,     0,
     394,     0,     0,     0,     0,     0,   395,     5,   437,     0,
       0,     0,     0,     0,     0,     0,     0,     6,   508,   509,
       7,     0,     0,     0,     0,     0,   396,     0,     0,     0,
       0,     0,     0,     0,   120,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   397,   398,     0,     0,     0,   399,
     400,   401,     0,     0,     0,     8,   281,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,     0,   130,   131,
     132,   133,   134,   135,   136,   402,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,     0,
       0,     0,     0,   403,     0,   404,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   350,   405,     0,   406,   407,   408,   409,   410,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   411,   412,     0,     0,
       0,     0,     0,     0,   413,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   130,   131,   132,   133,   134,
     135,   136,   352,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   130,   131,   132,   133,
     134,   135,   136,     0,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   130,   131,   132,
     133,   134,   135,   136,     0,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,     0,     0,
       0,     0,     0,     0,     0,     0,   490,     0,     0,     0,
       0,   130,   131,   132,   133,   134,   135,   136,   349,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,     0,     0,   129,     0,     0,   302,     0,   435,
       0,   130,   131,   132,   133,   134,   135,   136,   491,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   130,   131,   132,   133,   134,   135,   136,   150,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   131,   132,   133,   134,   135,   136,     0,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,  -222,  -222,  -222,  -222,     0,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-402)))

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-222)))

static const yytype_int16 yycheck[] =
{
      27,     3,   183,     3,     3,     3,     3,   375,     3,    20,
      20,    91,   104,   104,    91,   416,    93,     6,     6,   125,
     153,     3,   187,     3,    91,   114,    93,   187,   187,    18,
     130,   322,   184,    60,    61,    62,   114,   315,    65,    66,
     124,   125,   114,    38,   154,   221,   168,    21,     3,     4,
       5,     6,     7,     8,   247,   248,     3,   102,   459,    86,
      87,    68,    17,    18,   240,   234,    40,   246,   114,   114,
      25,     3,   154,     4,     5,     6,     7,   229,    33,   179,
     184,   250,    37,   248,   485,   174,   487,   114,    43,   248,
     250,    38,   225,   120,    26,    50,   174,   124,     8,   126,
     127,   128,   174,   130,   131,   132,   133,   134,    63,    64,
      65,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   105,   104,   229,   153,   418,   174,    92,
     246,   234,   254,   217,   114,     9,   275,   276,   113,   278,
     250,    96,   248,   125,   512,   108,    20,   250,   175,     1,
       3,     4,     5,     6,     7,     8,   233,   246,   250,   250,
     240,   141,   151,   151,    17,    18,   233,   194,   250,   196,
     248,   449,    25,    26,   181,   247,   248,   204,    79,   224,
      33,   163,   184,   247,   248,     5,   166,   588,     8,   152,
      43,   218,   219,   594,   250,   279,   318,    50,   205,   321,
     246,   236,   341,   204,    18,   344,   249,   250,   109,    61,
      63,    64,    65,   114,   177,   250,    52,   301,    54,     3,
       4,     5,     6,     7,     8,   246,    40,    92,    80,   246,
     521,    84,    85,    17,    18,   190,   247,   247,   178,    96,
     141,    25,    56,    96,    13,    14,   248,    16,   248,   248,
     248,   248,   247,   225,   281,   282,   109,   401,   123,    43,
     287,   405,    46,     3,    78,   409,    50,   119,   352,     3,
       4,     5,     6,     7,     8,   302,   249,   250,   250,    63,
      64,    65,     3,    17,    18,   312,   241,   242,   243,   244,
     245,    25,   319,   248,   250,   251,   225,     3,   238,   247,
     249,   250,     3,   330,   331,   234,     3,   334,   248,    43,
       9,   125,    96,   340,   495,   248,    50,   182,   247,   184,
     248,   250,   174,   350,   249,   250,   353,   267,   248,    63,
      64,    65,   184,   249,   250,   187,    79,   151,    26,    27,
      28,    29,    30,   248,   128,   198,   199,   200,    62,   248,
     203,   378,   217,     3,     4,     5,     6,     7,     8,   248,
     225,    38,    96,   249,   250,     3,   109,    17,    18,    26,
     222,   114,   249,   250,     3,    25,    26,   249,   250,   122,
     249,   250,     3,     4,     5,     6,     7,     8,   241,   242,
     243,   244,   245,    43,   249,   250,    17,    18,   141,   184,
      50,   248,   116,     3,    25,   219,   249,   250,   249,   250,
     124,   249,   250,    63,    64,    65,   130,   249,   250,     3,
     447,   448,    43,   249,   250,   249,   250,   454,   455,    50,
     249,   215,   249,   250,     3,   149,   301,   124,   303,   304,
     305,   160,    63,    64,    65,   473,    96,   475,   310,   311,
       3,   479,     3,   481,   158,     3,   249,   241,   242,   243,
     244,   245,   452,   453,   329,   179,   493,   494,     3,   496,
     249,   498,   499,   249,   249,    96,     3,     4,     5,     6,
       7,     8,     3,     4,     5,     6,     7,     8,   249,   203,
      17,    18,   248,   248,   248,   248,    17,    18,    25,   233,
      30,   125,   125,   125,    25,   124,   153,   241,   242,   243,
     244,   245,   124,     3,    47,   131,    43,   467,   468,    20,
     470,   471,    43,    50,   474,   248,   476,   154,   478,    50,
     480,   121,   249,   249,   249,   107,    63,    64,    65,   101,
     567,     3,    63,    64,    65,     3,   125,   125,   576,   125,
     578,    78,   580,   248,     3,     3,   249,    78,   386,   387,
     249,   389,    47,   184,   392,   393,   249,   395,   396,    96,
     249,   249,   400,   249,   402,    96,   404,   249,   124,   108,
     408,   248,   248,   248,    20,     3,     4,     5,     6,     7,
       8,   241,   242,   243,   244,   245,   248,   248,    43,    17,
      18,   250,   248,   248,   248,   248,   248,    25,   248,   222,
      20,   248,     3,     4,     5,     6,     7,     8,   249,     3,
     241,   242,   243,   244,   245,    43,    17,    18,     3,     5,
       4,    20,    50,     5,    25,     3,     4,     5,     6,     7,
       8,     5,   249,   249,   151,    63,    64,    65,     4,    17,
      18,   250,    43,   122,   180,     3,     5,    25,     4,    50,
      78,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    63,    64,    65,    43,   187,     4,    96,   249,
       4,   292,    50,   250,   121,   447,     9,    78,    24,    25,
      26,    27,    28,    29,    30,    63,    64,    65,   552,   153,
     263,   162,   382,   308,    42,    96,    23,    24,    25,    26,
      27,    28,    29,    30,   241,   242,   243,   244,   245,   179,
     241,   242,   243,   244,   245,    26,   111,   277,    96,   499,
     383,   477,    -1,   419,    10,    11,    12,    13,    14,    15,
      16,    88,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    10,    11,    12,    13,    14,
      15,    16,    -1,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    10,    11,    12,    13,
      14,    15,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    10,    11,    12,
      13,    14,    15,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    -1,    -1,
      -1,    -1,    -1,   241,   242,   243,   244,   245,   104,    10,
      11,    12,    13,    14,    15,    16,    -1,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
     241,   242,   243,   244,   245,    13,    14,    15,    16,    -1,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   241,   242,   243,   244,   245,    10,    11,
      12,    13,    14,    15,    16,    -1,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    10,
      11,    12,    13,    14,    15,    16,    -1,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      10,    11,    12,    13,    14,    15,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    10,    11,    12,    13,    14,    15,    16,    -1,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    -1,     0,     1,    22,    23,    24,    25,    26,
      27,    28,    29,    30,   250,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    73,    74,    75,    -1,    -1,    10,    11,
      12,    13,    14,    15,    16,   250,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   250,    -1,    -1,    -1,
     110,   111,   112,    -1,    61,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,   250,    -1,    -1,
      -1,    -1,    -1,    80,    10,    11,    12,    13,    14,    15,
      16,    -1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    -1,    -1,    -1,    -1,   250,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    43,
      44,    45,   119,    12,    13,    14,    15,    16,    52,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    -1,    -1,    -1,    -1,    70,    71,    -1,    -1,
      -1,    -1,    76,    -1,    -1,    -1,    -1,   249,    -1,    -1,
      -1,    -1,    -1,    87,    -1,    -1,    -1,    -1,    -1,    -1,
      94,    -1,    -1,    -1,    -1,    -1,   100,   174,   249,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   184,   238,   239,
     187,    -1,    -1,    -1,    -1,    -1,   120,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   233,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   138,   139,    -1,    -1,    -1,   143,
     144,   145,    -1,    -1,    -1,   222,   208,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    -1,    10,    11,
      12,    13,    14,    15,    16,   169,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    -1,
      -1,    -1,    -1,   187,    -1,   189,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   208,   207,    -1,   209,   210,   211,   212,   213,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   230,   231,    -1,    -1,
      -1,    -1,    -1,    -1,   238,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    10,    11,    12,    13,    14,
      15,    16,   104,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    10,    11,    12,    13,
      14,    15,    16,    -1,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    10,    11,    12,
      13,    14,    15,    16,    -1,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    10,    11,    12,    13,    14,    15,    16,    93,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    -1,    -1,     3,    -1,    -1,    36,    -1,    93,
      -1,    10,    11,    12,    13,    14,    15,    16,    81,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    10,    11,    12,    13,    14,    15,    16,    38,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    11,    12,    13,    14,    15,    16,    -1,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    13,    14,    15,    16,    -1,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     1,    61,    80,   119,   174,   184,   187,   222,   252,
     259,   260,   290,   294,   302,   303,   306,   308,   321,   246,
      68,   181,   205,   309,   291,   296,   296,   271,     8,   322,
     323,   296,   304,     0,     1,   259,   246,   113,   307,   307,
     204,     3,   104,   114,   141,   166,   292,    79,   109,   114,
     122,   141,   297,   297,     3,     4,     5,     6,     7,     8,
      17,    18,    25,    26,    33,    43,    50,    63,    64,    65,
      84,    85,    96,   109,   198,   199,   200,   203,   241,   242,
     243,   244,   245,   253,   272,   273,     9,    20,   250,   114,
     141,     3,   248,   275,   276,   277,   279,   289,   246,   246,
      96,     3,     3,   307,   247,   293,     3,   292,   104,   250,
       3,     3,   247,   248,     9,     3,   253,   253,   253,   253,
     233,   253,   258,   248,   248,   248,   248,   248,   248,     3,
      10,    11,    12,    13,    14,    15,    16,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      38,   274,   104,   250,   253,   253,   323,   247,   274,   260,
     275,   187,   250,    62,   116,   130,   149,   179,   203,   280,
     282,    38,   278,     3,    26,   234,   261,   225,   275,     3,
     187,   248,   298,   187,   298,     3,    26,   253,   254,   255,
     253,   247,   253,   258,    91,    93,   233,   260,   253,   254,
      46,   128,   215,   254,   256,   253,   253,    26,   253,   253,
     253,   253,   253,   253,     6,    18,   151,   248,    13,    14,
      16,   253,    33,    37,   190,   248,   253,   253,   253,   253,
     253,   253,   253,   253,   253,   253,   253,     3,   275,   273,
       3,   102,   114,   224,   286,   249,   249,     3,   305,   276,
     130,   179,   283,   277,   124,   160,   281,     3,   114,   174,
     247,   248,   319,   320,   253,   158,   267,   275,   261,   293,
       3,   301,     3,   270,   229,   260,   301,   229,   260,   250,
     249,   208,    91,    93,   253,   253,   249,   104,   249,   249,
     253,   250,   250,   249,   249,     6,   151,   254,   260,   253,
     253,   248,    36,   248,   248,   248,   260,   261,   274,   125,
     125,   125,    20,   247,   250,   261,   281,   281,   124,   153,
     277,   124,     3,     3,   105,   125,   163,   310,   311,   278,
      47,   131,   268,   261,    20,   154,   250,   295,   249,   250,
     248,   299,   295,   295,   299,   295,   254,   253,   253,    93,
     208,   253,   104,   121,   257,   257,   249,   249,   254,   260,
     253,   260,   260,   260,   249,   107,   262,   286,   101,   287,
     287,   287,   253,     3,     3,   267,   277,   253,   153,   225,
     284,   285,   277,   248,   319,    42,    43,    44,    45,    52,
      70,    71,    76,    87,    94,   100,   120,   138,   139,   143,
     144,   145,   169,   187,   189,   207,   209,   210,   211,   212,
     213,   230,   231,   238,   317,   125,   248,   125,   249,   250,
     260,   253,   263,   253,    78,   253,   125,     3,     3,    78,
     253,   300,   250,   295,   295,    93,   253,   249,   254,   253,
     249,   249,   249,   249,   249,   249,   249,    47,   108,   266,
     124,   248,   248,   248,    20,    20,   247,   268,   253,   248,
     285,   310,   248,   313,   313,   313,   313,   313,   313,   248,
     313,   313,    43,   314,   313,   314,   313,   248,   313,   314,
     313,   314,   248,   248,   312,   248,   270,   248,   319,   311,
      39,    81,   264,   250,   250,   222,    20,   249,   250,   248,
     249,    72,    73,    74,    75,   110,   111,   112,   238,   239,
     263,   253,   267,     3,   288,   288,   288,   253,   253,     3,
     270,   249,     5,   315,   316,   315,   315,     4,   318,   315,
     315,   316,   315,   316,   315,   318,   315,   316,   315,   316,
       5,     5,    18,    40,    56,    78,   125,   151,   219,   270,
     249,   270,   253,   253,   301,    78,   253,    78,   253,   300,
     236,   265,   268,   249,   250,   249,   249,    20,   249,   319,
     249,   250,   221,   240,    52,    54,   249,   250,   249,   249,
     249,   151,     4,     4,     5,     6,     7,   125,   248,   249,
     249,   264,   249,   180,   122,   269,     3,   253,     5,   187,
       4,   316,     4,   316,   316,   270,   270,   249,     4,   249
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (YYID (N))                                                     \
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
    while (YYID (0))
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

__attribute__((__unused__))
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
#else
static unsigned
yy_location_print_ (yyo, yylocp)
    FILE *yyo;
    YYLTYPE const * const yylocp;
#endif
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += fprintf (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += fprintf (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += fprintf (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += fprintf (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += fprintf (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {
      case 3: /* NAME */
/* Line 1393 of yacc.c  */
#line 59 "fb4-1.y"
        { 
	printf("free at %d %s\n", (*yylocationp).first_line, ((*yyvaluep).strval)); free(((*yyvaluep).strval));
	
};
/* Line 1393 of yacc.c  */
#line 2242 "fb4-1.tab.c"
        break;
      case 4: /* STRING */
/* Line 1393 of yacc.c  */
#line 59 "fb4-1.y"
        { 
	printf("free at %d %s\n", (*yylocationp).first_line, ((*yyvaluep).strval)); free(((*yyvaluep).strval));
	
};
/* Line 1393 of yacc.c  */
#line 2252 "fb4-1.tab.c"
        break;
      case 8: /* USERVAR */
/* Line 1393 of yacc.c  */
#line 59 "fb4-1.y"
        { 
	printf("free at %d %s\n", (*yylocationp).first_line, ((*yyvaluep).strval)); free(((*yyvaluep).strval));
	
};
/* Line 1393 of yacc.c  */
#line 2262 "fb4-1.tab.c"
        break;

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

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

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

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
      yychar = YYLEX;
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
     `$$ = $1'.

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
        case 4:
/* Line 1787 of yacc.c  */
#line 331 "fb4-1.y"
    { yyerror("First statement discarded, try again"); }
    break;

  case 5:
/* Line 1787 of yacc.c  */
#line 332 "fb4-1.y"
    { yyerror("Current statement discarded, try again"); }
    break;

  case 6:
/* Line 1787 of yacc.c  */
#line 335 "fb4-1.y"
    { emit("NAME %s", (yyvsp[(1) - (1)].strval)); free((yyvsp[(1) - (1)].strval)); }
    break;

  case 7:
/* Line 1787 of yacc.c  */
#line 336 "fb4-1.y"
    { emit("FIELDNAME %s.%s", (yyvsp[(1) - (3)].strval), (yyvsp[(3) - (3)].strval)); free((yyvsp[(1) - (3)].strval)); free((yyvsp[(3) - (3)].strval)); }
    break;

  case 8:
/* Line 1787 of yacc.c  */
#line 337 "fb4-1.y"
    { emit("USERVAR %s", (yyvsp[(1) - (1)].strval)); free((yyvsp[(1) - (1)].strval)); }
    break;

  case 9:
/* Line 1787 of yacc.c  */
#line 338 "fb4-1.y"
    { emit("STRING %s", (yyvsp[(1) - (1)].strval)); free((yyvsp[(1) - (1)].strval)); }
    break;

  case 10:
/* Line 1787 of yacc.c  */
#line 339 "fb4-1.y"
    { emit("NUMBER %d", (yyvsp[(1) - (1)].intval)); }
    break;

  case 11:
/* Line 1787 of yacc.c  */
#line 340 "fb4-1.y"
    { emit("FLOAT %g", (yyvsp[(1) - (1)].floatval)); }
    break;

  case 12:
/* Line 1787 of yacc.c  */
#line 341 "fb4-1.y"
    { emit("BOOL %d", (yyvsp[(1) - (1)].intval)); }
    break;

  case 13:
/* Line 1787 of yacc.c  */
#line 344 "fb4-1.y"
    { emit("ADD"); }
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 345 "fb4-1.y"
    { emit("SUB"); }
    break;

  case 15:
/* Line 1787 of yacc.c  */
#line 346 "fb4-1.y"
    { emit("MUL"); }
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 347 "fb4-1.y"
    { emit("DIV"); }
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 348 "fb4-1.y"
    { emit("MOD"); }
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 349 "fb4-1.y"
    { emit("MOD"); }
    break;

  case 19:
/* Line 1787 of yacc.c  */
#line 350 "fb4-1.y"
    { emit("NEG"); }
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 351 "fb4-1.y"
    { emit("AND"); }
    break;

  case 21:
/* Line 1787 of yacc.c  */
#line 352 "fb4-1.y"
    { emit("OR"); }
    break;

  case 22:
/* Line 1787 of yacc.c  */
#line 353 "fb4-1.y"
    { emit("XOR"); }
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 354 "fb4-1.y"
    { emit("BITOR"); }
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 355 "fb4-1.y"
    { emit("BITAND"); }
    break;

  case 25:
/* Line 1787 of yacc.c  */
#line 356 "fb4-1.y"
    { emit("BITXOR"); }
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 357 "fb4-1.y"
    { emit("SHIFT %s", (yyvsp[(2) - (3)].subtok)==1?"left":"right"); }
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 358 "fb4-1.y"
    { emit("NOT"); }
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 359 "fb4-1.y"
    { emit("NOT"); }
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 360 "fb4-1.y"
    { emit("CMP %d", (yyvsp[(2) - (3)].subtok)); }
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 363 "fb4-1.y"
    { emit("CMPSELECT %d", (yyvsp[(2) - (5)].subtok)); }
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 364 "fb4-1.y"
    { emit("CMPANYSELECT %d", (yyvsp[(2) - (6)].subtok)); }
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 365 "fb4-1.y"
    { emit("CMPANYSELECT %d", (yyvsp[(2) - (6)].subtok)); }
    break;

  case 33:
/* Line 1787 of yacc.c  */
#line 366 "fb4-1.y"
    { emit("CMPALLSELECT %d", (yyvsp[(2) - (6)].subtok)); }
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 369 "fb4-1.y"
    { emit("ISNULL"); }
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 370 "fb4-1.y"
    { emit("ISNULL"); emit("NOT"); }
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 371 "fb4-1.y"
    { emit("ISBOOL %d", (yyvsp[(3) - (3)].intval)); }
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 372 "fb4-1.y"
    { emit("ISBOOL %d", (yyvsp[(4) - (4)].intval)); emit("NOT"); }
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 373 "fb4-1.y"
    { emit("ASSIGN @%s", (yyvsp[(1) - (3)].strval)); free((yyvsp[(1) - (3)].strval)); }
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 376 "fb4-1.y"
    { emit("BETWEEN"); }
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 379 "fb4-1.y"
    { (yyval.intval) = 1; }
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 380 "fb4-1.y"
    { (yyval.intval) = 1 + (yyvsp[(3) - (3)].intval); }
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 383 "fb4-1.y"
    { (yyval.intval) = 0; }
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 384 "fb4-1.y"
    { (yyval.intval) = (yyvsp[(1) - (1)].intval); }
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 387 "fb4-1.y"
    { emit("ISIN %d", (yyvsp[(4) - (5)].intval)); }
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 388 "fb4-1.y"
    { emit("ISIN %d", (yyvsp[(5) - (6)].intval));  emit("NOT"); }
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 389 "fb4-1.y"
    { emit("CMPANYSELECT 4"); }
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 390 "fb4-1.y"
    { emit("CMPALLSELECT 3"); }
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 391 "fb4-1.y"
    { emit("EXISTSSELECT"); if((yyvsp[(1) - (4)].subtok)) emit("NOT"); }
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 395 "fb4-1.y"
    { emit("CALL %d %s", (yyvsp[(3) - (4)].intval), (yyvsp[(1) - (4)].strval)); }
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 399 "fb4-1.y"
    { emit("COUNTALL"); }
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 400 "fb4-1.y"
    { emit("CALL 1 COUNT"); }
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 402 "fb4-1.y"
    { emit("CALL %d SUBSTR", (yyvsp[(3) - (4)].intval)); }
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 403 "fb4-1.y"
    { emit("CALL 2 SUBSTR"); }
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 404 "fb4-1.y"
    { emit("CALL %d TRIM", (yyvsp[(3) - (4)].intval)); }
    break;

  case 55:
/* Line 1787 of yacc.c  */
#line 405 "fb4-1.y"
    { emit("CALL 3 TRIM"); }
    break;

  case 56:
/* Line 1787 of yacc.c  */
#line 408 "fb4-1.y"
    { emit("NUMBER 1"); }
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 409 "fb4-1.y"
    { emit("NUMBER 2"); }
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 410 "fb4-1.y"
    { emit("NUMBER 3"); }
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 413 "fb4-1.y"
    { emit("CALL 3 DATE_ADD"); }
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 414 "fb4-1.y"
    { emit("CALL 3 DATE_SUB"); }
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 417 "fb4-1.y"
    { emit("NUMBER 1"); }
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 418 "fb4-1.y"
    { emit("NUMBER 2"); }
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 419 "fb4-1.y"
    { emit("NUMBER 3"); }
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 420 "fb4-1.y"
    { emit("NUMBER 4"); }
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 421 "fb4-1.y"
    { emit("NUMBER 5"); }
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 422 "fb4-1.y"
    { emit("NUMBER 6"); }
    break;

  case 67:
/* Line 1787 of yacc.c  */
#line 423 "fb4-1.y"
    { emit("NUMBER 7"); }
    break;

  case 68:
/* Line 1787 of yacc.c  */
#line 424 "fb4-1.y"
    { emit("NUMBER 8"); }
    break;

  case 69:
/* Line 1787 of yacc.c  */
#line 425 "fb4-1.y"
    { emit("NUMBER 9"); }
    break;

  case 70:
/* Line 1787 of yacc.c  */
#line 428 "fb4-1.y"
    { emit("CASEVAL %d 0", (yyvsp[(3) - (4)].intval)); }
    break;

  case 71:
/* Line 1787 of yacc.c  */
#line 429 "fb4-1.y"
    { emit("CASEVAL %d 1", (yyvsp[(3) - (6)].intval)); }
    break;

  case 72:
/* Line 1787 of yacc.c  */
#line 430 "fb4-1.y"
    { emit("CASE %d 0", (yyvsp[(2) - (3)].intval)); }
    break;

  case 73:
/* Line 1787 of yacc.c  */
#line 431 "fb4-1.y"
    { emit("CASE %d 1", (yyvsp[(2) - (5)].intval)); }
    break;

  case 74:
/* Line 1787 of yacc.c  */
#line 434 "fb4-1.y"
    { (yyval.intval) = 1; }
    break;

  case 75:
/* Line 1787 of yacc.c  */
#line 435 "fb4-1.y"
    { (yyval.intval) = (yyvsp[(1) - (5)].intval) + 1; }
    break;

  case 76:
/* Line 1787 of yacc.c  */
#line 438 "fb4-1.y"
    { emit("LIKE"); }
    break;

  case 77:
/* Line 1787 of yacc.c  */
#line 439 "fb4-1.y"
    { emit("LIKE"); emit("NOT"); }
    break;

  case 78:
/* Line 1787 of yacc.c  */
#line 442 "fb4-1.y"
    { emit("REGEXP"); }
    break;

  case 79:
/* Line 1787 of yacc.c  */
#line 443 "fb4-1.y"
    { emit("REGEXP"); emit("NOT"); }
    break;

  case 80:
/* Line 1787 of yacc.c  */
#line 446 "fb4-1.y"
    { emit("NOW"); }
    break;

  case 81:
/* Line 1787 of yacc.c  */
#line 447 "fb4-1.y"
    { emit("NOW"); }
    break;

  case 82:
/* Line 1787 of yacc.c  */
#line 448 "fb4-1.y"
    { emit("NOW"); }
    break;

  case 83:
/* Line 1787 of yacc.c  */
#line 451 "fb4-1.y"
    { emit("STRTOBIN"); }
    break;

  case 84:
/* Line 1787 of yacc.c  */
#line 454 "fb4-1.y"
    { emit("STMT"); }
    break;

  case 85:
/* Line 1787 of yacc.c  */
#line 458 "fb4-1.y"
    { emit("SELECTNODATA %d %d", (yyvsp[(2) - (3)].intval), (yyvsp[(3) - (3)].intval)); }
    break;

  case 86:
/* Line 1787 of yacc.c  */
#line 462 "fb4-1.y"
    { emit("SELECT %d %d %d", (yyvsp[(2) - (11)].intval), (yyvsp[(3) - (11)].intval), (yyvsp[(5) - (11)].intval)); }
    break;

  case 88:
/* Line 1787 of yacc.c  */
#line 466 "fb4-1.y"
    { emit("WHERE"); }
    break;

  case 90:
/* Line 1787 of yacc.c  */
#line 470 "fb4-1.y"
    { emit("GROUPBYLIST %d %d", (yyvsp[(3) - (4)].intval), (yyvsp[(4) - (4)].intval)); }
    break;

  case 91:
/* Line 1787 of yacc.c  */
#line 473 "fb4-1.y"
    { emit("GROUPBY %d", (yyvsp[(2) - (2)].intval)); (yyval.intval) = 1; }
    break;

  case 92:
/* Line 1787 of yacc.c  */
#line 474 "fb4-1.y"
    { emit("GROUPBY %d", (yyvsp[(4) - (4)].intval)); (yyval.intval) = (yyvsp[(1) - (4)].intval) +1; }
    break;

  case 93:
/* Line 1787 of yacc.c  */
#line 477 "fb4-1.y"
    { (yyval.intval) = 0; }
    break;

  case 94:
/* Line 1787 of yacc.c  */
#line 478 "fb4-1.y"
    { (yyval.intval) = 0; }
    break;

  case 95:
/* Line 1787 of yacc.c  */
#line 479 "fb4-1.y"
    { (yyval.intval) = 1; }
    break;

  case 96:
/* Line 1787 of yacc.c  */
#line 482 "fb4-1.y"
    { (yyval.intval) = 0; }
    break;

  case 97:
/* Line 1787 of yacc.c  */
#line 483 "fb4-1.y"
    { (yyval.intval) = 1; }
    break;

  case 99:
/* Line 1787 of yacc.c  */
#line 487 "fb4-1.y"
    { emit("HAVING"); }
    break;

  case 101:
/* Line 1787 of yacc.c  */
#line 491 "fb4-1.y"
    { emit("ORDERBY %d", (yyvsp[(3) - (3)].intval)); }
    break;

  case 103:
/* Line 1787 of yacc.c  */
#line 495 "fb4-1.y"
    { emit("LIMIT 2"); }
    break;

  case 104:
/* Line 1787 of yacc.c  */
#line 496 "fb4-1.y"
    { emit("LIMIT 1"); }
    break;

  case 106:
/* Line 1787 of yacc.c  */
#line 500 "fb4-1.y"
    { emit("INTO %d", (yyvsp[(2) - (2)].intval)); }
    break;

  case 107:
/* Line 1787 of yacc.c  */
#line 503 "fb4-1.y"
    { emit("COLUMN %s", (yyvsp[(1) - (1)].strval)); free((yyvsp[(1) - (1)].strval)); (yyval.intval) = 1; }
    break;

  case 108:
/* Line 1787 of yacc.c  */
#line 504 "fb4-1.y"
    { emit("COLUMN %s", (yyvsp[(3) - (3)].strval)); free((yyvsp[(3) - (3)].strval)); (yyval.intval) = (yyval.intval) + 1; }
    break;

  case 109:
/* Line 1787 of yacc.c  */
#line 507 "fb4-1.y"
    { (yyval.intval) = 0; }
    break;

  case 110:
/* Line 1787 of yacc.c  */
#line 509 "fb4-1.y"
    { if((yyvsp[(1) - (2)].intval) & 01) lyyerror((yylsp[(2) - (2)]), "duplicate ALL option"); (yyval.intval) = (yyvsp[(1) - (2)].intval) | 01; }
    break;

  case 111:
/* Line 1787 of yacc.c  */
#line 511 "fb4-1.y"
    { if((yyvsp[(1) - (2)].intval) & 02) lyyerror((yylsp[(2) - (2)]), "duplicate DISTINCT option"); (yyval.intval) = (yyvsp[(1) - (2)].intval) | 02; }
    break;

  case 112:
/* Line 1787 of yacc.c  */
#line 513 "fb4-1.y"
    { if((yyvsp[(1) - (2)].intval) & 04) lyyerror((yylsp[(2) - (2)]), "duplicate DISTINCTROW option"); (yyval.intval) = (yyvsp[(1) - (2)].intval) | 04; }
    break;

  case 113:
/* Line 1787 of yacc.c  */
#line 515 "fb4-1.y"
    { if((yyvsp[(1) - (2)].intval) & 010) lyyerror((yylsp[(2) - (2)]), "duplicate HIGH_PRIORITY option"); (yyval.intval) = (yyvsp[(1) - (2)].intval) | 010; }
    break;

  case 114:
/* Line 1787 of yacc.c  */
#line 517 "fb4-1.y"
    { if((yyvsp[(1) - (2)].intval) & 020) lyyerror((yylsp[(2) - (2)]), "duplicate STRAIGHT_JOIN option"); (yyval.intval) = (yyvsp[(1) - (2)].intval) | 020; }
    break;

  case 115:
/* Line 1787 of yacc.c  */
#line 519 "fb4-1.y"
    { if((yyvsp[(1) - (2)].intval) & 040) lyyerror((yylsp[(2) - (2)]), "duplicate SQL_SMALL_RESULT option"); (yyval.intval) = (yyvsp[(1) - (2)].intval) | 040; }
    break;

  case 116:
/* Line 1787 of yacc.c  */
#line 521 "fb4-1.y"
    { if((yyvsp[(1) - (2)].intval) & 0100) lyyerror((yylsp[(2) - (2)]), "duplicate SQL_BIG_RESULT option"); (yyval.intval) = (yyvsp[(1) - (2)].intval) | 0100; }
    break;

  case 117:
/* Line 1787 of yacc.c  */
#line 523 "fb4-1.y"
    { if((yyvsp[(1) - (2)].intval) & 0200) lyyerror((yylsp[(2) - (2)]), "duplicate SQL_CALL_FOUND_ROWS option"); (yyval.intval) = (yyvsp[(1) - (2)].intval) | 0200; }
    break;

  case 118:
/* Line 1787 of yacc.c  */
#line 526 "fb4-1.y"
    { (yyval.intval) = 1; }
    break;

  case 119:
/* Line 1787 of yacc.c  */
#line 527 "fb4-1.y"
    { (yyval.intval) = (yyvsp[(1) - (3)].intval) + 1; }
    break;

  case 120:
/* Line 1787 of yacc.c  */
#line 528 "fb4-1.y"
    { emit("SELECTALL"); (yyval.intval) = 1; }
    break;

  case 121:
/* Line 1787 of yacc.c  */
#line 529 "fb4-1.y"
    { emit("SELECTNAMEALL %s", (yyvsp[(1) - (3)].strval)); free((yyvsp[(1) - (3)].strval)); (yyval.intval) = 1; }
    break;

  case 124:
/* Line 1787 of yacc.c  */
#line 536 "fb4-1.y"
    { emit("ALIAS %s", (yyvsp[(2) - (2)].strval)); free((yyvsp[(2) - (2)].strval)); }
    break;

  case 125:
/* Line 1787 of yacc.c  */
#line 537 "fb4-1.y"
    { emit("ALIAS %s", (yyvsp[(1) - (1)].strval)); free((yyvsp[(1) - (1)].strval)); }
    break;

  case 126:
/* Line 1787 of yacc.c  */
#line 540 "fb4-1.y"
    { (yyval.intval) = 1; }
    break;

  case 127:
/* Line 1787 of yacc.c  */
#line 541 "fb4-1.y"
    { (yyval.intval) = (yyvsp[(1) - (3)].intval) + 1; }
    break;

  case 130:
/* Line 1787 of yacc.c  */
#line 548 "fb4-1.y"
    { emit("TABLE %s", (yyvsp[(1) - (3)].strval)); free((yyvsp[(1) - (3)].strval)); }
    break;

  case 131:
/* Line 1787 of yacc.c  */
#line 550 "fb4-1.y"
    { emit("TABLE %s.%s", (yyvsp[(1) - (5)].strval), (yyvsp[(3) - (5)].strval)); free((yyvsp[(1) - (5)].strval)); free((yyvsp[(3) - (5)].strval)); }
    break;

  case 132:
/* Line 1787 of yacc.c  */
#line 551 "fb4-1.y"
    { emit("SUBQUERYAS %s", (yyvsp[(3) - (3)].strval)); free((yyvsp[(3) - (3)].strval)); }
    break;

  case 133:
/* Line 1787 of yacc.c  */
#line 552 "fb4-1.y"
    { emit("TABLEREFERENCES %d", (yyvsp[(2) - (3)].intval)); }
    break;

  case 136:
/* Line 1787 of yacc.c  */
#line 560 "fb4-1.y"
    { emit("JOIN %d", 100+(yyvsp[(2) - (5)].intval)); }
    break;

  case 137:
/* Line 1787 of yacc.c  */
#line 562 "fb4-1.y"
    { emit("JOIN %d", 200); }
    break;

  case 138:
/* Line 1787 of yacc.c  */
#line 564 "fb4-1.y"
    { emit("JOIN %d", 200); }
    break;

  case 139:
/* Line 1787 of yacc.c  */
#line 566 "fb4-1.y"
    { emit("JOIN %d", 300 + (yyvsp[(2) - (6)].intval) + (yyvsp[(3) - (6)].intval)); }
    break;

  case 140:
/* Line 1787 of yacc.c  */
#line 568 "fb4-1.y"
    { emit("JOIN %d", 400 + (yyvsp[(3) - (5)].intval)); }
    break;

  case 141:
/* Line 1787 of yacc.c  */
#line 571 "fb4-1.y"
    { (yyval.intval) = 0; }
    break;

  case 142:
/* Line 1787 of yacc.c  */
#line 572 "fb4-1.y"
    { (yyval.intval) = 1; }
    break;

  case 143:
/* Line 1787 of yacc.c  */
#line 573 "fb4-1.y"
    { (yyval.intval) = 2; }
    break;

  case 144:
/* Line 1787 of yacc.c  */
#line 576 "fb4-1.y"
    { (yyval.intval) = 0; }
    break;

  case 145:
/* Line 1787 of yacc.c  */
#line 577 "fb4-1.y"
    { (yyval.intval) = 4; }
    break;

  case 146:
/* Line 1787 of yacc.c  */
#line 580 "fb4-1.y"
    { (yyval.intval) = 1; }
    break;

  case 147:
/* Line 1787 of yacc.c  */
#line 581 "fb4-1.y"
    { (yyval.intval) = 2; }
    break;

  case 148:
/* Line 1787 of yacc.c  */
#line 584 "fb4-1.y"
    { (yyval.intval) = 0; }
    break;

  case 149:
/* Line 1787 of yacc.c  */
#line 585 "fb4-1.y"
    { (yyval.intval) = 1 + (yyvsp[(2) - (2)].intval); }
    break;

  case 150:
/* Line 1787 of yacc.c  */
#line 586 "fb4-1.y"
    { (yyval.intval) = 2 + (yyvsp[(2) - (2)].intval); }
    break;

  case 153:
/* Line 1787 of yacc.c  */
#line 593 "fb4-1.y"
    { emit("ONEXPR"); }
    break;

  case 154:
/* Line 1787 of yacc.c  */
#line 594 "fb4-1.y"
    { emit("USING %d", (yyvsp[(3) - (4)].intval)); }
    break;

  case 156:
/* Line 1787 of yacc.c  */
#line 599 "fb4-1.y"
    { emit("INDEXHINT %d %d", (yyvsp[(5) - (6)].intval), 10 + (yyvsp[(3) - (6)].intval)); }
    break;

  case 157:
/* Line 1787 of yacc.c  */
#line 601 "fb4-1.y"
    { emit("INDEXHINT %d %d", (yyvsp[(5) - (6)].intval), 20 + (yyvsp[(3) - (6)].intval)); }
    break;

  case 158:
/* Line 1787 of yacc.c  */
#line 603 "fb4-1.y"
    { emit("INDEXHINT %d %d", (yyvsp[(5) - (6)].intval), 30 + (yyvsp[(3) - (6)].intval)); }
    break;

  case 159:
/* Line 1787 of yacc.c  */
#line 606 "fb4-1.y"
    { (yyval.intval) = 1; }
    break;

  case 160:
/* Line 1787 of yacc.c  */
#line 607 "fb4-1.y"
    { (yyval.intval) = 0; }
    break;

  case 161:
/* Line 1787 of yacc.c  */
#line 610 "fb4-1.y"
    { emit("INDEX %s", (yyvsp[(1) - (1)].strval)); free((yyvsp[(1) - (1)].strval)); (yyval.intval) = 1; }
    break;

  case 162:
/* Line 1787 of yacc.c  */
#line 611 "fb4-1.y"
    { emit("INDEX %s", (yyvsp[(3) - (3)].strval)); free((yyvsp[(3) - (3)].strval)); (yyval.intval) = (yyvsp[(1) - (3)].intval) + 1; }
    break;

  case 163:
/* Line 1787 of yacc.c  */
#line 614 "fb4-1.y"
    { emit("SUBQAUERY"); }
    break;

  case 164:
/* Line 1787 of yacc.c  */
#line 618 "fb4-1.y"
    { emit("STMT"); }
    break;

  case 165:
/* Line 1787 of yacc.c  */
#line 623 "fb4-1.y"
    { emit("DELETEONE %d %s", (yyvsp[(2) - (7)].intval), (yyvsp[(4) - (7)].strval)); }
    break;

  case 166:
/* Line 1787 of yacc.c  */
#line 626 "fb4-1.y"
    { (yyval.intval) = (yyvsp[(1) - (2)].intval) + 01; }
    break;

  case 167:
/* Line 1787 of yacc.c  */
#line 627 "fb4-1.y"
    { (yyval.intval) = (yyvsp[(1) - (2)].intval) + 02; }
    break;

  case 168:
/* Line 1787 of yacc.c  */
#line 628 "fb4-1.y"
    { (yyval.intval) = (yyvsp[(1) - (2)].intval) + 04; }
    break;

  case 169:
/* Line 1787 of yacc.c  */
#line 629 "fb4-1.y"
    { (yyval.intval) = 0; }
    break;

  case 170:
/* Line 1787 of yacc.c  */
#line 634 "fb4-1.y"
    { emit("DELETEMULTI %d %d %d", (yyvsp[(2) - (6)].intval), (yyvsp[(3) - (6)].intval), (yyvsp[(5) - (6)].intval)); }
    break;

  case 171:
/* Line 1787 of yacc.c  */
#line 637 "fb4-1.y"
    { emit( "TABLE %s", (yyvsp[(1) - (2)].strval)); free((yyvsp[(1) - (2)].strval)); (yyval.intval) = 1; }
    break;

  case 172:
/* Line 1787 of yacc.c  */
#line 639 "fb4-1.y"
    { emit("TABLE %s", (yyvsp[(3) - (4)].strval)); free((yyvsp[(3) - (4)].strval)); (yyval.intval) = (yyvsp[(1) - (4)].intval) + 1; }
    break;

  case 175:
/* Line 1787 of yacc.c  */
#line 647 "fb4-1.y"
    { emit("DELETEMULTI %d %d %d", (yyvsp[(2) - (7)].intval), (yyvsp[(4) - (7)].intval), (yyvsp[(6) - (7)].intval)); }
    break;

  case 176:
/* Line 1787 of yacc.c  */
#line 651 "fb4-1.y"
    { emit("STMT"); }
    break;

  case 177:
/* Line 1787 of yacc.c  */
#line 656 "fb4-1.y"
    { emit("INSERTVALS %d %d %s", (yyvsp[(2) - (8)].intval), (yyvsp[(7) - (8)].intval), (yyvsp[(4) - (8)].strval)); free((yyvsp[(4) - (8)].strval)); }
    break;

  case 179:
/* Line 1787 of yacc.c  */
#line 660 "fb4-1.y"
    { emit("DUPUPDATE %d", (yyvsp[(4) - (4)].intval)); }
    break;

  case 180:
/* Line 1787 of yacc.c  */
#line 663 "fb4-1.y"
    { (yyval.intval) = 0; }
    break;

  case 181:
/* Line 1787 of yacc.c  */
#line 664 "fb4-1.y"
    { (yyval.intval) = (yyvsp[(1) - (2)].intval) | 01; }
    break;

  case 182:
/* Line 1787 of yacc.c  */
#line 665 "fb4-1.y"
    { (yyval.intval) = (yyvsp[(1) - (2)].intval) | 02; }
    break;

  case 183:
/* Line 1787 of yacc.c  */
#line 666 "fb4-1.y"
    { (yyval.intval) = (yyvsp[(1) - (2)].intval) | 04; }
    break;

  case 184:
/* Line 1787 of yacc.c  */
#line 667 "fb4-1.y"
    { (yyval.intval) = (yyvsp[(1) - (2)].intval) | 010; }
    break;

  case 188:
/* Line 1787 of yacc.c  */
#line 675 "fb4-1.y"
    { emit("INSERTCOLS %d", (yyvsp[(2) - (3)].intval)); }
    break;

  case 189:
/* Line 1787 of yacc.c  */
#line 678 "fb4-1.y"
    { emit("VALUES %d", (yyvsp[(2) - (3)].intval)); (yyval.intval) = 1; }
    break;

  case 190:
/* Line 1787 of yacc.c  */
#line 679 "fb4-1.y"
    { emit("VALUES %d", (yyvsp[(4) - (5)].intval)); (yyval.intval) = (yyvsp[(1) - (5)].intval) + 1;}
    break;

  case 191:
/* Line 1787 of yacc.c  */
#line 682 "fb4-1.y"
    { (yyval.intval) = 1; }
    break;

  case 192:
/* Line 1787 of yacc.c  */
#line 683 "fb4-1.y"
    { emit("DEFAULT"); (yyval.intval) = 1; }
    break;

  case 193:
/* Line 1787 of yacc.c  */
#line 684 "fb4-1.y"
    { (yyval.intval) = (yyvsp[(1) - (3)].intval) + 1; }
    break;

  case 194:
/* Line 1787 of yacc.c  */
#line 685 "fb4-1.y"
    { emit("DEFAULT"); (yyval.intval) = (yyvsp[(1) - (3)].intval) + 1; }
    break;

  case 195:
/* Line 1787 of yacc.c  */
#line 689 "fb4-1.y"
    { emit("INSERTASGN %d %d %s", (yyvsp[(2) - (7)].intval), (yyvsp[(6) - (7)].intval), (yyvsp[(4) - (7)].strval)); free((yyvsp[(4) - (7)].strval)); }
    break;

  case 196:
/* Line 1787 of yacc.c  */
#line 693 "fb4-1.y"
    { if((yyvsp[(2) - (3)].subtok) != 4) { yyerror("bad insert assignment to %s", (yyvsp[(1) - (3)].strval)); YYERROR; }
			emit("ASSIGN %s", (yyvsp[(1) - (3)].strval)); free((yyvsp[(1) - (3)].strval)); (yyval.intval) = 1; }
    break;

  case 197:
/* Line 1787 of yacc.c  */
#line 696 "fb4-1.y"
    { if((yyvsp[(2) - (3)].subtok) != 4) { yyerror("bad insert assignment to %s", (yyvsp[(1) - (3)].strval)); YYERROR; }
			emit("DEFAULT"); emit("ASSIGN %s", (yyvsp[(1) - (3)].strval)); free((yyvsp[(1) - (3)].strval)); (yyval.intval) = 1; }
    break;

  case 198:
/* Line 1787 of yacc.c  */
#line 699 "fb4-1.y"
    { if((yyvsp[(4) - (5)].subtok) != 4) { yyerror("bad insert assignment to %s", (yyvsp[(3) - (5)].strval)); YYERROR; }
			emit("ASSIGN %s", (yyvsp[(3) - (5)].strval)); free((yyvsp[(3) - (5)].strval)); (yyval.intval) = (yyvsp[(1) - (5)].intval) + 1; }
    break;

  case 199:
/* Line 1787 of yacc.c  */
#line 702 "fb4-1.y"
    { if((yyvsp[(4) - (5)].subtok) != 4) { yyerror("bad insert assignment to %s", (yyvsp[(3) - (5)].strval)); YYERROR; }
			emit("DEFAULT"); emit("ASSIGN %s", (yyvsp[(3) - (5)].strval)); free((yyvsp[(3) - (5)].strval)); (yyval.intval) = (yyvsp[(1) - (5)].intval) + 1; }
    break;

  case 200:
/* Line 1787 of yacc.c  */
#line 708 "fb4-1.y"
    { emit("INSERTSELECT %d %s", (yyvsp[(2) - (7)].intval), (yyvsp[(4) - (7)].strval)); free((yyvsp[(4) - (7)].strval)); }
    break;

  case 201:
/* Line 1787 of yacc.c  */
#line 712 "fb4-1.y"
    { emit("STMT"); }
    break;

  case 202:
/* Line 1787 of yacc.c  */
#line 717 "fb4-1.y"
    { emit("REPLACEVALS %d %d %s", (yyvsp[(2) - (8)].intval), (yyvsp[(7) - (8)].intval), (yyvsp[(4) - (8)].strval)); free((yyvsp[(4) - (8)].strval)); }
    break;

  case 203:
/* Line 1787 of yacc.c  */
#line 722 "fb4-1.y"
    { emit("REPLACEASGN %d %d %s", (yyvsp[(2) - (7)].intval), (yyvsp[(6) - (7)].intval), (yyvsp[(4) - (7)].strval)); free((yyvsp[(4) - (7)].strval)); }
    break;

  case 204:
/* Line 1787 of yacc.c  */
#line 727 "fb4-1.y"
    { emit("REPLACESELECT %d %s", (yyvsp[(2) - (7)].intval), (yyvsp[(4) - (7)].strval)); free((yyvsp[(4) - (7)].strval)); }
    break;

  case 205:
/* Line 1787 of yacc.c  */
#line 731 "fb4-1.y"
    { emit("STMT"); }
    break;

  case 206:
/* Line 1787 of yacc.c  */
#line 736 "fb4-1.y"
    { emit("UPDATE %d %d %d", (yyvsp[(2) - (8)].intval), (yyvsp[(3) - (8)].intval), (yyvsp[(5) - (8)].intval)); }
    break;

  case 207:
/* Line 1787 of yacc.c  */
#line 739 "fb4-1.y"
    { (yyval.intval) = 0; }
    break;

  case 208:
/* Line 1787 of yacc.c  */
#line 740 "fb4-1.y"
    { (yyval.intval) = (yyvsp[(1) - (2)].intval) | 01; }
    break;

  case 209:
/* Line 1787 of yacc.c  */
#line 741 "fb4-1.y"
    { (yyval.intval) = (yyvsp[(1) - (2)].intval) | 010; }
    break;

  case 210:
/* Line 1787 of yacc.c  */
#line 745 "fb4-1.y"
    { if((yyvsp[(2) - (3)].subtok) != 4) { yyerror("bad update assignment to %s", (yyvsp[(1) - (3)].strval)); YYERROR; }
			emit("ASSIGN %s", (yyvsp[(1) - (3)].strval)); free((yyvsp[(1) - (3)].strval)); (yyval.intval) = 1; }
    break;

  case 211:
/* Line 1787 of yacc.c  */
#line 748 "fb4-1.y"
    { if((yyvsp[(4) - (5)].subtok) != 4) { yyerror("bad update assignment to %s", (yyvsp[(1) - (5)].strval)); YYERROR; }
			emit("ASSIGN %s.%s", (yyvsp[(1) - (5)].strval), (yyvsp[(3) - (5)].strval)); free((yyvsp[(1) - (5)].strval)); free((yyvsp[(3) - (5)].strval)); (yyval.intval) = 1; }
    break;

  case 212:
/* Line 1787 of yacc.c  */
#line 751 "fb4-1.y"
    { if((yyvsp[(4) - (5)].subtok) != 4) { yyerror("bad update assignment to %s", (yyvsp[(3) - (5)].strval)); YYERROR; }
			emit("ASSIGN %s", (yyvsp[(3) - (5)].strval)); free((yyvsp[(3) - (5)].strval)); (yyval.intval) = (yyvsp[(1) - (5)].intval) + 1; }
    break;

  case 213:
/* Line 1787 of yacc.c  */
#line 754 "fb4-1.y"
    { if((yyvsp[(6) - (7)].subtok) != 4) { yyerror("bad update assignment to %s", (yyvsp[(3) - (7)].strval)); YYERROR; }
			emit("ASSIGN %s.%s", (yyvsp[(3) - (7)].strval), (yyvsp[(5) - (7)].strval)); free((yyvsp[(3) - (7)].strval)); free((yyvsp[(5) - (7)].strval)); (yyval.intval) = (yyvsp[(1) - (7)].intval) + 1; }
    break;

  case 214:
/* Line 1787 of yacc.c  */
#line 759 "fb4-1.y"
    { emit("STMT"); }
    break;

  case 215:
/* Line 1787 of yacc.c  */
#line 763 "fb4-1.y"
    { emit("CREATEDATABASE %d %s", (yyvsp[(3) - (4)].intval), (yyvsp[(4) - (4)].strval)); free((yyvsp[(4) - (4)].strval)); }
    break;

  case 216:
/* Line 1787 of yacc.c  */
#line 765 "fb4-1.y"
    { emit("CREATEDATABASE %d %s", (yyvsp[(3) - (4)].intval), (yyvsp[(4) - (4)].strval)); free((yyvsp[(4) - (4)].strval)); }
    break;

  case 217:
/* Line 1787 of yacc.c  */
#line 768 "fb4-1.y"
    { (yyval.intval) = 0; }
    break;

  case 218:
/* Line 1787 of yacc.c  */
#line 769 "fb4-1.y"
    { if(!(yyvsp[(2) - (2)].subtok)) { yyerror("IF EXISTS doesn't exist"); YYERROR; }
		(yyval.intval) = (yyvsp[(2) - (2)].subtok); /* NOT EXISTS hack */ }
    break;

  case 219:
/* Line 1787 of yacc.c  */
#line 774 "fb4-1.y"
    { emit("STMT"); }
    break;

  case 220:
/* Line 1787 of yacc.c  */
#line 779 "fb4-1.y"
    { emit("CREATE %d %d %d %s", (yyvsp[(2) - (8)].intval), (yyvsp[(4) - (8)].intval), (yyvsp[(7) - (8)].intval), (yyvsp[(5) - (8)].strval)); free((yyvsp[(5) - (8)].strval)); }
    break;

  case 221:
/* Line 1787 of yacc.c  */
#line 784 "fb4-1.y"
    { emit("CREATE %d %d %d %s.%s", (yyvsp[(2) - (10)].intval), (yyvsp[(4) - (10)].intval), (yyvsp[(9) - (10)].intval), (yyvsp[(5) - (10)].strval), (yyvsp[(7) - (10)].strval)); free((yyvsp[(5) - (10)].strval)); free((yyvsp[(7) - (10)].strval)); }
    break;

  case 222:
/* Line 1787 of yacc.c  */
#line 789 "fb4-1.y"
    { emit("CREATESELECT %d %d %d %s", (yyvsp[(2) - (9)].intval), (yyvsp[(4) - (9)].intval), (yyvsp[(7) - (9)].intval), (yyvsp[(5) - (9)].strval)); free((yyvsp[(5) - (9)].strval)); }
    break;

  case 223:
/* Line 1787 of yacc.c  */
#line 794 "fb4-1.y"
    { emit("CREATESELECT %d %d %d %s.%s", (yyvsp[(2) - (11)].intval), (yyvsp[(4) - (11)].intval), (yyvsp[(9) - (11)].intval), (yyvsp[(5) - (11)].strval), (yyvsp[(7) - (11)].strval)); free((yyvsp[(5) - (11)].strval)); free((yyvsp[(7) - (11)].strval)); }
    break;

  case 224:
/* Line 1787 of yacc.c  */
#line 799 "fb4-1.y"
    { emit("CREATESELECT %d %d 0 %s", (yyvsp[(2) - (6)].intval), (yyvsp[(4) - (6)].intval), (yyvsp[(5) - (6)].strval)); free((yyvsp[(5) - (6)].strval)); }
    break;

  case 225:
/* Line 1787 of yacc.c  */
#line 804 "fb4-1.y"
    { emit("CREATESELECT %d %d 0 %s.%s", (yyvsp[(2) - (8)].intval), (yyvsp[(4) - (8)].intval), (yyvsp[(5) - (8)].strval), (yyvsp[(7) - (8)].strval)); free((yyvsp[(5) - (8)].strval)); free((yyvsp[(7) - (8)].strval)); }
    break;

  case 226:
/* Line 1787 of yacc.c  */
#line 807 "fb4-1.y"
    { (yyval.intval) = 0; }
    break;

  case 227:
/* Line 1787 of yacc.c  */
#line 808 "fb4-1.y"
    { (yyval.intval) = 1; }
    break;

  case 228:
/* Line 1787 of yacc.c  */
#line 811 "fb4-1.y"
    { (yyval.intval) = 1; }
    break;

  case 229:
/* Line 1787 of yacc.c  */
#line 812 "fb4-1.y"
    { (yyval.intval) = (yyvsp[(1) - (3)].intval) + 1; }
    break;

  case 230:
/* Line 1787 of yacc.c  */
#line 815 "fb4-1.y"
    { emit("PRIKEY %d", (yyvsp[(4) - (5)].intval)); }
    break;

  case 231:
/* Line 1787 of yacc.c  */
#line 816 "fb4-1.y"
    { emit("KEY %d", (yyvsp[(3) - (4)].intval)); }
    break;

  case 232:
/* Line 1787 of yacc.c  */
#line 819 "fb4-1.y"
    { emit("TEXTINDEX %d", (yyvsp[(4) - (5)].intval)); }
    break;

  case 233:
/* Line 1787 of yacc.c  */
#line 822 "fb4-1.y"
    { emit("STARTCOL"); }
    break;

  case 234:
/* Line 1787 of yacc.c  */
#line 823 "fb4-1.y"
    { emit("COLUMNDEF %d %s", (yyvsp[(3) - (3)].intval), (yyvsp[(1) - (3)].strval)); free((yyvsp[(1) - (3)].strval)); }
    break;

  case 235:
/* Line 1787 of yacc.c  */
#line 825 "fb4-1.y"
    { (yyval.intval) = 0; }
    break;

  case 236:
/* Line 1787 of yacc.c  */
#line 827 "fb4-1.y"
    { emit("ATTR NOT NULL"); (yyval.intval) = (yyvsp[(1) - (3)].intval) + 1; }
    break;

  case 237:
/* Line 1787 of yacc.c  */
#line 829 "fb4-1.y"
    { emit("ATTR NULL"); (yyval.intval) = (yyvsp[(1) - (2)].intval) + 1; }
    break;

  case 238:
/* Line 1787 of yacc.c  */
#line 831 "fb4-1.y"
    { emit("ATTR DEFAULT STRING %s", (yyvsp[(3) - (3)].strval)); free((yyvsp[(3) - (3)].strval)); (yyval.intval) = (yyvsp[(1) - (3)].intval) + 1; }
    break;

  case 239:
/* Line 1787 of yacc.c  */
#line 833 "fb4-1.y"
    { emit("ATTR DEFAULT NUMBER %d", (yyvsp[(3) - (3)].intval)); (yyval.intval) = (yyvsp[(1) - (3)].intval) + 1; }
    break;

  case 240:
/* Line 1787 of yacc.c  */
#line 835 "fb4-1.y"
    { emit("ATTR DEFAULT FLOAT %g", (yyvsp[(3) - (3)].floatval)); (yyval.intval) = (yyvsp[(1) - (3)].intval) + 1; }
    break;

  case 241:
/* Line 1787 of yacc.c  */
#line 837 "fb4-1.y"
    { emit("ATTR DEFAULT BOOL %d", (yyvsp[(3) - (3)].intval)); (yyval.intval) = (yyvsp[(1) - (3)].intval) + 1; }
    break;

  case 242:
/* Line 1787 of yacc.c  */
#line 839 "fb4-1.y"
    { emit("ATTR AUTOINC"); (yyval.intval) = (yyvsp[(1) - (2)].intval) + 1; }
    break;

  case 243:
/* Line 1787 of yacc.c  */
#line 841 "fb4-1.y"
    { emit("ATTR UNIQUEKEY %d", (yyvsp[(4) - (5)].intval)); (yyval.intval) = (yyvsp[(1) - (5)].intval) + 1; }
    break;

  case 244:
/* Line 1787 of yacc.c  */
#line 843 "fb4-1.y"
    { emit("ATTR UNIQUEKEY"); (yyval.intval) = (yyvsp[(1) - (3)].intval) + 1; }
    break;

  case 245:
/* Line 1787 of yacc.c  */
#line 845 "fb4-1.y"
    { emit("ATTR PRIKEY"); (yyval.intval) = (yyvsp[(1) - (2)].intval) + 1; }
    break;

  case 246:
/* Line 1787 of yacc.c  */
#line 847 "fb4-1.y"
    { emit("ATTR COMMENT %s", (yyvsp[(3) - (3)].strval)); free((yyvsp[(3) - (3)].strval)); (yyval.intval) = (yyvsp[(1) - (3)].intval) + 1; }
    break;

  case 247:
/* Line 1787 of yacc.c  */
#line 850 "fb4-1.y"
    { (yyval.intval) = 0; }
    break;

  case 248:
/* Line 1787 of yacc.c  */
#line 851 "fb4-1.y"
    { (yyval.intval) = (yyvsp[(2) - (3)].intval); }
    break;

  case 249:
/* Line 1787 of yacc.c  */
#line 852 "fb4-1.y"
    { (yyval.intval) = (yyvsp[(2) - (5)].intval) + 1000*(yyvsp[(4) - (5)].intval); }
    break;

  case 250:
/* Line 1787 of yacc.c  */
#line 855 "fb4-1.y"
    { (yyval.intval) = 0; }
    break;

  case 251:
/* Line 1787 of yacc.c  */
#line 856 "fb4-1.y"
    { (yyval.intval) = 4000; }
    break;

  case 252:
/* Line 1787 of yacc.c  */
#line 859 "fb4-1.y"
    { (yyval.intval) = 0; }
    break;

  case 253:
/* Line 1787 of yacc.c  */
#line 860 "fb4-1.y"
    { (yyval.intval) = (yyvsp[(1) - (2)].intval) | 1000; }
    break;

  case 254:
/* Line 1787 of yacc.c  */
#line 861 "fb4-1.y"
    { (yyval.intval) = (yyvsp[(1) - (2)].intval) | 2000; }
    break;

  case 256:
/* Line 1787 of yacc.c  */
#line 865 "fb4-1.y"
    { emit("COLCHARSET %s", (yyvsp[(4) - (4)].strval)); free((yyvsp[(4) - (4)].strval)); }
    break;

  case 257:
/* Line 1787 of yacc.c  */
#line 866 "fb4-1.y"
    { emit("COLCOLLATE %s", (yyvsp[(3) - (3)].strval)); free((yyvsp[(3) - (3)].strval)); }
    break;

  case 258:
/* Line 1787 of yacc.c  */
#line 869 "fb4-1.y"
    { (yyval.intval) = 10000 + (yyvsp[(2) - (2)].intval); }
    break;

  case 259:
/* Line 1787 of yacc.c  */
#line 870 "fb4-1.y"
    { (yyval.intval) = 10000 + (yyvsp[(2) - (3)].intval); }
    break;

  case 260:
/* Line 1787 of yacc.c  */
#line 871 "fb4-1.y"
    { (yyval.intval) = 20000 + (yyvsp[(2) - (3)].intval) + (yyvsp[(3) - (3)].intval); }
    break;

  case 261:
/* Line 1787 of yacc.c  */
#line 872 "fb4-1.y"
    { (yyval.intval) = 30000 + (yyvsp[(2) - (3)].intval) + (yyvsp[(3) - (3)].intval); }
    break;

  case 262:
/* Line 1787 of yacc.c  */
#line 874 "fb4-1.y"
    { (yyval.intval) = 5000 + (yyvsp[(2) - (3)].intval) + (yyvsp[(3) - (3)].intval); }
    break;

  case 263:
/* Line 1787 of yacc.c  */
#line 875 "fb4-1.y"
    { (yyval.intval) = 60000 + (yyvsp[(2) - (3)].intval) + (yyvsp[(3) - (3)].intval); }
    break;

  case 264:
/* Line 1787 of yacc.c  */
#line 876 "fb4-1.y"
    { (yyval.intval) = 70000 + (yyvsp[(2) - (3)].intval) + (yyvsp[(3) - (3)].intval); }
    break;

  case 265:
/* Line 1787 of yacc.c  */
#line 877 "fb4-1.y"
    { (yyval.intval) = 80000 + (yyvsp[(2) - (3)].intval) + (yyvsp[(3) - (3)].intval); }
    break;

  case 266:
/* Line 1787 of yacc.c  */
#line 878 "fb4-1.y"
    { (yyval.intval) = 90000 + (yyvsp[(2) - (3)].intval) + (yyvsp[(3) - (3)].intval); }
    break;

  case 267:
/* Line 1787 of yacc.c  */
#line 879 "fb4-1.y"
    { (yyval.intval) = 110000 + (yyvsp[(2) - (3)].intval) + (yyvsp[(3) - (3)].intval); }
    break;

  case 268:
/* Line 1787 of yacc.c  */
#line 880 "fb4-1.y"
    { (yyval.intval) = 100001; }
    break;

  case 269:
/* Line 1787 of yacc.c  */
#line 881 "fb4-1.y"
    { (yyval.intval) = 100002; }
    break;

  case 270:
/* Line 1787 of yacc.c  */
#line 882 "fb4-1.y"
    { (yyval.intval) = 100003; }
    break;

  case 271:
/* Line 1787 of yacc.c  */
#line 883 "fb4-1.y"
    { (yyval.intval) = 100004; }
    break;

  case 272:
/* Line 1787 of yacc.c  */
#line 884 "fb4-1.y"
    { (yyval.intval) = 100005; }
    break;

  case 273:
/* Line 1787 of yacc.c  */
#line 885 "fb4-1.y"
    { (yyval.intval) = 120000 + (yyvsp[(2) - (3)].intval); }
    break;

  case 274:
/* Line 1787 of yacc.c  */
#line 886 "fb4-1.y"
    { (yyval.intval) = 130000 + (yyvsp[(3) - (5)].intval); }
    break;

  case 275:
/* Line 1787 of yacc.c  */
#line 887 "fb4-1.y"
    { (yyval.intval) = 140000 + (yyvsp[(2) - (2)].intval); }
    break;

  case 276:
/* Line 1787 of yacc.c  */
#line 888 "fb4-1.y"
    { (yyval.intval) = 15000 + (yyvsp[(3) - (4)].intval); }
    break;

  case 277:
/* Line 1787 of yacc.c  */
#line 889 "fb4-1.y"
    { (yyval.intval) = 160001; }
    break;

  case 278:
/* Line 1787 of yacc.c  */
#line 890 "fb4-1.y"
    { (yyval.intval) = 160002; }
    break;

  case 279:
/* Line 1787 of yacc.c  */
#line 891 "fb4-1.y"
    { (yyval.intval) = 160003; }
    break;

  case 280:
/* Line 1787 of yacc.c  */
#line 892 "fb4-1.y"
    { (yyval.intval) = 160004; }
    break;

  case 281:
/* Line 1787 of yacc.c  */
#line 893 "fb4-1.y"
    { (yyval.intval) = 170000 + (yyvsp[(2) - (3)].intval); }
    break;

  case 282:
/* Line 1787 of yacc.c  */
#line 894 "fb4-1.y"
    { (yyval.intval) = 171000 + (yyvsp[(2) - (3)].intval); }
    break;

  case 283:
/* Line 1787 of yacc.c  */
#line 895 "fb4-1.y"
    { (yyval.intval) = 172000 + (yyvsp[(2) - (3)].intval); }
    break;

  case 284:
/* Line 1787 of yacc.c  */
#line 896 "fb4-1.y"
    { (yyval.intval) = 173000 + (yyvsp[(2) - (3)].intval); }
    break;

  case 285:
/* Line 1787 of yacc.c  */
#line 897 "fb4-1.y"
    { (yyval.intval) = 200000 + (yyvsp[(3) - (5)].intval); }
    break;

  case 286:
/* Line 1787 of yacc.c  */
#line 898 "fb4-1.y"
    { (yyval.intval) = 210000 + (yyvsp[(3) - (5)].intval); }
    break;

  case 287:
/* Line 1787 of yacc.c  */
#line 901 "fb4-1.y"
    { emit("ENUMVAL %s", (yyvsp[(1) - (1)].strval)); free((yyvsp[(1) - (1)].strval)); (yyval.intval) = 1; }
    break;

  case 288:
/* Line 1787 of yacc.c  */
#line 902 "fb4-1.y"
    { emit("ENUMVAL %s", (yyvsp[(3) - (3)].strval)); free((yyvsp[(3) - (3)].strval)); (yyval.intval) = (yyvsp[(1) - (3)].intval) + 1; }
    break;

  case 289:
/* Line 1787 of yacc.c  */
#line 906 "fb4-1.y"
    { emit("CREATESELECT %d", (yyvsp[(1) - (3)].intval)); }
    break;

  case 290:
/* Line 1787 of yacc.c  */
#line 909 "fb4-1.y"
    { (yyval.intval) = 0; }
    break;

  case 291:
/* Line 1787 of yacc.c  */
#line 910 "fb4-1.y"
    { (yyval.intval) = 1; }
    break;

  case 292:
/* Line 1787 of yacc.c  */
#line 911 "fb4-1.y"
    { (yyval.intval) = 2; }
    break;

  case 293:
/* Line 1787 of yacc.c  */
#line 915 "fb4-1.y"
    { emit("STMT"); }
    break;

  case 297:
/* Line 1787 of yacc.c  */
#line 926 "fb4-1.y"
    { if((yyvsp[(2) - (3)].subtok) != 4) { yyerror("bad set to @%s", (yyvsp[(1) - (3)].strval)); YYERROR; }
			emit("set %s", (yyvsp[(1) - (3)].strval)); free((yyvsp[(1) - (3)].strval)); }
    break;

  case 298:
/* Line 1787 of yacc.c  */
#line 928 "fb4-1.y"
    { emit("SET %s", (yyvsp[(1) - (3)].strval)); free((yyvsp[(1) - (3)].strval)); }
    break;


/* Line 1787 of yacc.c  */
#line 4208 "fb4-1.tab.c"
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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
  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2050 of yacc.c  */
#line 931 "fb4-1.y"


void emit(char *s, ...)
{
	extern yylineno;
	va_list ap;
	va_start(ap, s);

	printf("rpn: ");
	vfprintf(stdout, s, ap);
	printf("\n");
}

void yyerror(char *s, ...)
{
	extern yylineno;
	va_list ap;
	va_start(ap, s);
	
	if(yylloc.first_line)
		fprintf(stderr, "%d.%d-%d.%d:error: ", 
			yylloc.first_line,
			yylloc.first_column,
			yylloc.last_line,
			yylloc.last_column
		);
	//fprintf(stderr, "%d: error: ", yylineno);
	vfprintf(stderr, s, ap);
	fprintf(stderr, "\n");
}

void lyyerror(YYLTYPE t, char *s, ...)
{
	va_list ap;
	va_start(ap, s);
	
	if(t.first_line)
		fprintf(stderr, "%s:%d.%d-%d.%d:error: ", 
			t.filename,
			t.first_line, t.first_column,
			t.last_line, t.last_column
		);
	vfprintf(stderr, s, ap);
	fprintf(stderr, "\n");
}

int main(int argc, char** argv) 
{
	extern FILE *yyin;

	if(argc > 1 && !strcmp(argv[1], "-d"))
	{
		yydebug = 1; argc--; argv++;
	}

	if(argc > 1 && (yyin = fopen(argv[1], "r")) == NULL)
	{
		perror(argv[1]);
		exit(1);
	}

	if(!yyparse())
	{
		printf("SQL parse worked\n");
	}
	else 
	{
		printf("SQL parse failed\n");
	}
}
