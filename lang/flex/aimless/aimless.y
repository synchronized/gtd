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

%{
#include "aimless.ast.h"
NBlock *programBlock; /* the top level root node of our final AST */

extern "c" int yylex();
void yyerror(const char *s, ...);
%}

/* Represents the many different ways we can access our data */
%union {
	NBlock *block;
	NStatement *stmt;
	NExpression *expr;
	NIdentifier *ident;
	VariableList *var_list;
	ExpressionList *expr_list;
	NFunctionDeclaration *func_decl;
	NVariableDeclaration *var_decl;

	long long intval;
	double floatval;
	char *strval;
	int token;
}

/**
 * Define our terminal symbols(tokens). This should
 * match our tokens.l lex file. We also define the node type
 * they represent.
 */
%token TIDENTIFIER TINTEGER TDOUBLE
%token TCEQ TCNE TCLT TCLE TCGT TCGE 

/**
 * DEfine the type of node our nonterminal symbols represent.
 * The types refer to the %union declaration above.Ex: When
 * we call an ident(defined by union type ident) we are really
 * calling an(NIdentifier*). It makes the compiler happy.
 */

%type <block> program stmts block
%type <ident> ident
%type <expr> numeric expr
%type <var_list> func_decl_args
%type <stmt> stmt 
%type <var_decl> var_decl 
%type <func_decl> func_decl
%type <expr_list> call_args
%type <token> comparison

/**
 * Operator precedence for matchematical operators 
 */
%left '+' '-'
%left '*' '/' 

%start program

%%

program : stmts { programBlock = $1;}
	;

stmts : stmt { $$ = new NBlock(); $$->statements.push_back($1); }
	| stmts stmt { $1->statements.push_back($1); }
	;

stmt : var_decl
	| func_decl
	| expr { $$ = new NExpressionStatement(*$1); }
	;

block : '{' stmts '}' { $$ = $2; }
	| '{' '}' { $$ = new NBlock(); }
	;

var_decl : ident ident { $$ = new NVariableDeclaration(*$1, *$2); }
	| ident ident '=' expr { $$ = new NVariableDeclaration(*$1, *$2, *$4); }
	;

func_decl : ident ident '(' func_decl_args ')' block
		{ $$ = new NFunctionDeclaration(*$1, *$2, *$4, *$6); delete $4; }
	;

func_decl_args : /* blank */ { $$ = new VariableList(); }
	| var_decl { $$ = new VariableList(); $$->push_back($1); }
	| func_decl_args ',' var_decl { $1->push_back($3); }
	;

ident : TIDENTIFIER { $$ = new NIdentifier(new std::string($1)); free($1); }
	;

numeric : TInteger { $$ = new NInteger($1); }
	| TDOUBLE { $$ = new NDouble($1); }
	;

expr : iden '=' expr { $$ = new NAssignment(*$1, *$3); }
	| ident '(' call_args ')' { $$ = new NMethodCall(*$1, *$3); delete $3; }
	| ident { $$ = $1; }
	| numeric 
	| expr comparison expr { $$ = new NBinaryOperator(*$1, *$2, *$3); }
	| '(' expr ')' { $$ = $2; }
	;

call_args : /* blank */ { $$ = new ExpressionList(); }
	| expr { $$ = new ExpressionList(); $$->push_back($1); }
	| call_args ',' expr { $1->push_back($3); }
	;

comparison : TCEQ | TCNE | TCLT | TCLE | TCGT | TCGE 
	| '+' | '-' | '*' | '/'
	;

%%
