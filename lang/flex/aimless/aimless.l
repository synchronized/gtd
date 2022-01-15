/*******************************************
 *
 * aimless.y
 * 简易计算机语言-语法分析器
 * 
 * 基本语法:
 * int do_math(int a) {  
 * 	int x = a * 5 + 3
 * } 
 * do_math(10)
 *
 ******************************************/

%option noyywrap nodefault yylineno
%{
#include <string>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "armless.ast.h"
#include "armless.tab.h"
#include "armless.hpp"
#define TOKEN(t) (yylval.token = t)
%}

%%

[\t ]
\n						{ yylineno++; }
[a-zA-Z_][a-zA-Z0-9_]*	{ yylval.strval = strdup(yytext); return TIDENTIFIER; }
[0-9]+\.[0-9]*			{ yylval.floatval = atof(yytext); return TDOUBLE; }
[0-9]+					{ yylval.intval = atoi(yytext); return TINTEGER; }

"=="					{ return TOKEN(TCEQ); }
"!="					{ return TOKEN(TCNE); }
"<"						{ return TOKEN(TCLT); }
"<="					{ return TOKEN(TCLE); }
">"						{ return TOKEN(TCGT); }
">="					{ return TOKEN(TCGE); }

"="						|
"("						|
")"						|
"{"						|
"}"						|
"."						|
","						|
"+"						|
"-"						|
"*"						|
"/"						{ return TOKEN(*yytext); }

.						{ printf("unknown token!\n"); yyterminate(); }
%%
