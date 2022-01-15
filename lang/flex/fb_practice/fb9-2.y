/*********************************
 *
 * fb9-2.y
 * 可重入计算器-语法分析器
 *
 ********************************/

%define api.pure
/* struct pcdata *pp */
%parse-param { struct pcdata *pp }

%{
#include <stdio.h>
#include <stdlib.h>
//#include "fb9-2.flex.h"
#include "fb9-2.funcs.h"
#define YYLEX_PARAM pp->scaninfo
%}

%union {
	struct ast *a;
	double d;
	struct symbol *s; 	/* 符号 */
	struct symlist *sl;
	int fn; 			/* 函数 */
}

	/* 声明 */
%token <d> NUMBER
%token <s> NAME
%token <fn> FUNC
%token EOL

%token IF THEN ELSE WHILE DO LET

%nonassoc <fn> CMP
%right '='
%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS

%type <a> exp stmt list explist
%type <sl> symlist

%start calc
%%

calc: /* 空 */ EOL { pp->ast = NULL; YYACCEPT; }
	| stmt EOL { pp->ast = $1; YYACCEPT; }
	| LET NAME '(' symlist ')' '{' list '}' EOL
		{ dodef( pp, $2, $4, $7); 
			printf("%d: Defined %s\n", yyget_lineno(pp->scaninfo), $2->name);
			pp->ast = NULL; YYACCEPT; }
	;

stmt: IF '(' exp ')' '{' list '}' { $$ = newflow(pp, 'I', $3, $6, NULL); }
	| IF '(' exp ')' '{' list '}' ELSE '{' list '}' { $$ = newflow(pp, 'I', $3, $6, $10); }
	| WHILE '(' exp ')' '{' list '}' { $$ = newflow(pp, 'W', $3, $6, NULL); }
	| DO '{' list '}' WHILE '(' exp ')' { $$ = newflow(pp, 'D', $7, $3, NULL); }
	| exp
	;

list: /* 空 */ { $$ = NULL; }
	| stmt ';' list 
		{ if($3 == NULL)
			$$ = $1;
		else 
			$$ = newast(pp, 'L', $1, $3);
		}
	;

exp: exp CMP exp { $$ = newcmp(pp, $2, $1, $3); }
	| exp '+' exp { $$ = newast(pp, '+', $1, $3); }
	| exp '-' exp { $$ = newast(pp, '-', $1, $3); }
	| exp '*' exp { $$ = newast(pp, '*', $1, $3); }
	| exp '/' exp { $$ = newast(pp, '/', $1, $3); }
	| '|' exp { $$ = newast(pp, '|', $2, NULL); }
	| '(' exp ')' { $$ = $2; }
	| '-' exp %prec UMINUS { $$ = newast(pp, 'M', $2, NULL); }
	| NUMBER { $$ = newnum(pp, $1); }
	| FUNC '(' explist')' { $$ = newfunc(pp, $1, $3); }
	| NAME { $$ = newref(pp, $1); }
	| NAME '=' exp { $$ = newasgn(pp, $1, $3); }
	| NAME '(' explist ')' { $$ = newcall(pp, $1, $3); }
	;

explist: exp
	| exp ',' explist { $$ = newast(pp, 'L', $1, $3); }
	;

symlist: NAME { $$ = newsymlist(pp, $1, NULL); }
	| NAME ',' symlist { $$ = newsymlist(pp, $1, $3); }
	;

%%

