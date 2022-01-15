/**************************************
 *
 * fb9-1.l
 * 数字统计-词法分析器
 *
 *************************************/

%option noyywrap nodefault reentrant 
%{
	struct pwc { //our per-scanner data
		int chars;
		int words;
		int lines;
	};
%}
%optoin extra-type="struct pwc *"

%{
	struct pwc *pp = yyextra;
%}

%%
[a-zA-z]+ 	{ pp->words++; pp->chars += strlen(yytext); }
\n			{ pp->chars++; pp->lines++; }
.			{ pp->chars++; }

%%

int main(int argc, char **argv)
{
	struct pwc mypwc = {0, 0, 0};
	yycan_t scanner; //flex的实际数据
	if(yylex_init_extra(&mypwc, &scanner)) {
		perror("init alloc failed");
		return -1;
	}
	
	if(argc > 1)
	{
		FILE *f;
		if(!(f = fopen(argv[1], "r")))
		{
			perror(argv[1]);
			return -2;
		}
		yyset_in(f, canner);
	}
	else {
		yyset_in(stdin, scanner);
	}

	yylex(scanner);
	printf("%8d%8d%8d\n", mypwc.lines, mypwc.words, mypwc.chars);

	if(argc > 1)
		fclose(yyget_in(scanner));

	yylex_destory(scanner);

	return 0;
}
