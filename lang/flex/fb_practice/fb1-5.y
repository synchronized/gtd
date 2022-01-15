/****************************
 * fb1-5.y
 ***************************/

/* 计算器 */
%{
#include <stdio.h>
%}

/* declare tokens */
%token NUMBER
%token ADD SUB MUL DIV ABS
%token EOL
%token OP CP
%token AND

%%

calclist: /* empty rule */                         /*从输入开头进行匹配*/
	| calclist exp EOL { printf("=%d\n", $2); }    /*EOL 代表一个表达式的结束*/
	;

exp: exp2 /* default */  { $$ = $1; }
	| exp ADD exp2 { $$ = $1 + $3; }
	| exp SUB exp2 { $$ = $1 - $3; }
	;

exp2: factor /* default */ { $$ = $1; }
	| exp2 ABS factor { $$ = $1 | $3; }
	| exp2 AND factor { $$ = $1 & $3; }
	;

factor: term /* default */  { $$ = $1; }
	| factor MUL term { $$ = $1 * $3; }
	| factor DIV term { $$ = $1 / $3; }
	;

term: NUMBER /* default */ { $$ = $1; }
	| ABS term { $$ = $2 >= 0 ? $2 : -$2;}
	| OP exp CP { $$ = $2; }
	;

%%

main(int argc, char** argv)
{
	yyparse();
}

yyerror(char* e)
{
	fprintf(stderr, "eerror: %s\n", e);
}
