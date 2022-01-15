/*******************************
 *	fb1-5.l
 ******************************/

%{
#include "fb1-5.tab.h"
%}

%%

"+"				{ return ADD;}
"-"				{ return SUB;}
"*"				{ return MUL;}
"/"				{ return DIV;}
"|"				{ return ABS;}
"("				{ return OP; }
")"				{ return CP; }
"&"				{ return AND;}
"//".*			{ yylval = 0; return NUMBER; /* 忽略注释 */}
[ \t]			{ }
[+-]?(\d*\.\d+|\d+\.)(E[+-]?\d+)?	{ yylval = atoi(yytext); return NUMBER;}
0x[a-fA-F0-9]+	{ yylval = strtol(yytext, NULL, 16); return NUMBER;}
\n				{ return EOL;}
.				{ printf("unknow char:%s\n", yytext);}

%%
