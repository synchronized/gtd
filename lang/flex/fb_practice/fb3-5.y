/***********************************************
 *
 * fb3-5.y
 * 高级计算器-语法(文法)分析器
 *
 **********************************************/

%{
#include <stdio.h>
#include <stdlib.h>
#include "fb3-5.h"
%}

%union {
	struct ast *a;
	double d;
	struct symbol *s;	//指定符号
	struct symlist *sl;
	int fn;				//指定函数
}

	/* 声明标记 */
%token <d> NUMBER
%token <s> NAME
%token <fn> FUNC
%token EOL

%token IF ELSE WHILE DO LET

%nonassoc <fn> CMP
%right '='
%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS

%type <a> exp stmt list explist
%type <sl> symlist

%start calclist

%%
stmt: IF '(' exp ')' '{' list '}' { $$ = newflow('I', $3, $6, NULL); }
	| IF '(' exp ')' '{' list '}' ELSE '{' list '}' { $$ = newflow('I', $3, $6, $10); }
	| WHILE '(' exp ')' '{' list '}' { $$ = newflow('W', $3, $6, NULL); }
	| DO '{' list '}' WHILE '(' exp ')' ';' { $$ = newflow('D', $7, $3, NULL); }
	| exp ';'
	;

list:	/* 空 */ { $$ = NULL; }
	| stmt list {
			if($2 == NULL)
				$$ = $1;
			else
				$$ = newast('L', $1, $2);
		}
	;

exp: exp CMP exp 	{ $$ = newcmp($2, $1, $3); }
	| exp '+' exp 	{ $$ = newast('+', $1, $3); }
	| exp '-' exp 	{ $$ = newast('-', $1, $3); }
	| exp '*' exp 	{ $$ = newast('*', $1, $3); }
	| exp '/' exp 	{ $$ = newast('/', $1, $3); }
	| '|' exp 		{ $$ = newast('|', $2, NULL); }
	| '(' exp ')' 	{ $$ = $2; }
	| '-' exp %prec UMINUS 	{ $$ = newast('M', $2, NULL); }
	| NUMBER 		{ $$ = newnum($1); }
	| NAME 			{ $$ = newref($1); }
	| NAME '=' exp	{ $$ = newasgn( $1, $3); }
	| FUNC '(' explist ')' { $$ = newfunc($1, $3); }
	| NAME '(' explist ')' { $$ = newcall($1, $3); }
	;

explist: exp
	| exp ',' explist { $$ = newast('L', $1, $3); }
	;

symlist: NAME 		{ $$ = newsymlist($1, NULL); }
	| NAME ',' symlist { $$ = newsymlist($1, $3); }
	;

calclist: /* 空 */
	| calclist stmt EOL {
			printf("= %4.4g\n> ", eval($2));
			treefree($2);
		}
	| calclist exp EOL {
			printf("= %4.4g\n> ", eval($2));
			treefree($2);
		}
	| calclist LET NAME '(' symlist ')' '{' list '}' EOL {
			dodef($3, $5, $8);
			printf("Defined %s\n> ", $3->name);
		}
	| calclist error EOL { yyerrok; printf("> "); }
	;

%%
