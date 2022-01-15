/***********************
 *
 * fb1-2.l
 *
 * [0-9]+	{ printf("NUMBER %S\n", yytext);} 
 *
[0-9]+	{ printf("NUMBER %S\n", yytext); return MY_TOKEN_E; } 
 *
 ***********************/

%%
"+"		{ printf("PLUS %s\n", yytext); }
"-"		{ printf("MINUS %s\n", yytext); }
"*"		{ printf("TIMES %s\n", yytext); }
"/"		{ printf("DIVIDE %s\n", yytext); }
"|"		{ printf("ABS %s\n", yytext); }
\n		{ printf("NEWLINE %s\n", yytext); }
[0-9]+	{ printf("NUMBER %s\n", yytext); } 
[ \t]	{ printf("TAB [%s]\n", yytext); }
.		{ printf("Mystery character :%s\n", yytext); }
%%

/*
int main(int argc, char** argv)
{
	printf("sizeof(wchar_t)=%u\n", sizeof(wchar_t));
	return 0;
}
*/
