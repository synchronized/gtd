/***********************************************
 *
 * fb3-5.l
 * 高级计算器-词法分析器
 *
 **********************************************/

%option noyywrap nodefault yylineno

%{
#include "fb3-5.h"
#include "fb3-5.tab.h"
%}

EXP ([Ee][-+]?[0-9]+)

%%
	/* 单一字符操作符 */
"+"	|
"-"	|
"*"	|
"/"	|
"="	|
"|"	|
","	|
";"	|
"("	|
")"	|
"{"	|
"}"	{ return yytext[0]; }

	/* 比较操作符,所有返回值都是CMP记号 */
">"		{ yylval.fn = 1; return CMP; }
"<"		{ yylval.fn = 2; return CMP; }
"<>"	{ yylval.fn = 3; return CMP; }
"=="	{ yylval.fn = 4; return CMP; }
">="	{ yylval.fn = 5; return CMP; }
"<="	{ yylval.fn = 6; return CMP; }

	/* 关键字 */
"if"	{ return IF; }
"else"	{ return ELSE; }
"while"	{ return WHILE; }
"do"	{ return DO; }
"let"	{ return LET; }

	/* 内置函数 */
"sqrt"	{ yylval.fn = B_sqrt; return FUNC; }
"exp"	{ yylval.fn = B_exp; return FUNC; }
"log"	{ yylval.fn = B_log; return FUNC; }
"print"	{ yylval.fn = B_print; return FUNC; }

	/* 名字 */
[a-zA-Z][a-zA-Z0-9]*	{ yylval.s = lookup(yytext); return NAME; }

[0-9]+"."[0-9]*{EXP}?	|
"."?[0-9]+{EXP}?		{ yylval.d = atof(yytext); return NUMBER; }

"//".*
[ \t]	/* 忽略空白字符 */

\\\n	{ printf("c> "); } /* 忽略续航符 */

\n 		{ return EOL; }

.		{ yyerror("Mystery character %c\n", *yytext); }

%%