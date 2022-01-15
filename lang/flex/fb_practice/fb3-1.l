/*************************************
 *
 * fb3-1.l
 * 基于抽象语法树的计算器-词法分析器
 *
 ************************************/

%option noyywrap nodefault yylineno

%{
#include "fb3-1.h"
#include "fb3-1.tab.h"
%}

	/* 浮点指数部分 */
EXP ([Ee][-+]?[0-9]+)

%%
"+"	|
"-"	|
"*"	|
"/"	|
"|"	|
"("	|
")"	{ return yytext[0]; }

[0-9]+"."[0-9]*{EXP}? |
"."?[0-9]+{EXP}?	{
	yylval.d = atof(yytext); return NUMBER;
}

\n	{ return EOL;}
"//".*	{ /* 忽略注释 */}
[ \t]	{ /* 忽略空白字符 */ }
.	{ yyerror("Mystery character %c\n", *yytext); }
%%
