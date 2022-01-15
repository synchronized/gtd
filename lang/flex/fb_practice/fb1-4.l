/******************************
 *
 * fb1-4.l
 *
 *****************************/

%{
	enum yytokentype{
		NUMBER = 258,
		ADD = 259,
		SUB = 260,
		MUL = 261,
		DIV = 262,
		ABS = 263,
		EOL = 264,
	};
	int yylval;
%}

%%
"+"		{ return ADD; }
"-"		{ return SUB; }
"*"		{ return MUL; }
"/"		{ return DIV; }
"|"		{ return ABS; }
[0-9]+	{ printf("NUMBER %s\n", yytext); yylval = atoi(yytext);return NUMBER; }
\n		{ return EOL; }
[ \t]	{ printf( "space char [%s]\n", yytext); }
.		{ printf( "unknow char :%s\n", yytext); }
%%
main(int argc, char **argv)
{
	int tok;
	printf("======================================\n");
	while(tok = yylex())
	{
		printf( "%d", tok);
		if(tok == NUMBER) printf(" = %d\n", yylval);
		else printf("\n");
	}
}
