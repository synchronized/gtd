/*********************************
 *
 * fb9-2.l
 * 可重入计算器-词法分析器
 *
 ********************************/

%option noyywrap nodefault yylineno reentrant bison-bridge

	/* %option header-file="fb9-2.flex.h" */

%{
#include "fb9-2.tab.h"
#include "fb9-2.funcs.h"
%}

	/* 浮点指数部分 */
EXP ([Ee][-+]?[0-9]+)

%%
%{
struct pcdata *pp = yyextra;
%}
	/* 单字符操作符 */
"+"	|
"-"	|
"*"	|
"/"	|
"="	|
"|"	|
","	|
";"	|
"("	|
")"	{ return yytext[0]; }

	/* 比较操作符 */
">"		{ yylval->fn = 1; return CMP; }
"<"		{ yylval->fn = 2; return CMP; }
"<>"	{ yylval->fn = 3; return CMP; }
"=="	{ yylval->fn = 4; return CMP; }
">="	{ yylval->fn = 5; return CMP; }
"<="	{ yylval->fn = 6; return CMP; }

	/* 关键字 */
"if"	{ return IF; }
"then"	{ return THEN; }
"else"	{ return ELSE; }
"while"	{ return WHILE; }
"do"	{ return DO; }
"let"	{ return LET; }

	/* 内置函数 */
"sqrt"	{ yylval->fn = B_sqrt; return FUNC; }
"exp"	{ yylval->fn = B_exp; return FUNC; }
"log"	{ yylval->fn = B_log; return FUNC; }
"print"	{ yylval->fn = B_print; return FUNC; }

[a-zA-Z][a-zA-Z0-9]*	{ yylval->s = lookup(pp, yytext); return NAME; }
[0-9]+"."[0-9]*{EXP}? 	|
"."?[0-9]+{EXP}?			{ yylval->d = atof(yytext); return NUMBER; }

	/* 忽略空白字符和注释 */
"//".*					
[ \t]
\\n		{ printf("> "); /* 忽略换行符 */}
<<EOF>>	{ exit(0); }

.		{ yyerror(pp, "mystery character %c\n", *yytext); }

%%
