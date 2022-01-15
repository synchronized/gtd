/**************************
 *
 * 正如 Unix的程序 
 * 
 **************************/

%{
int chars = 0;
int words = 0;
int lines = 0;

int totchars = 0;
int totwords = 0;
int totlines = 0;
%}
%%
[a-zA-Z]+	{ words++; chars += strlen(yytext);}
\n			{ chars++; lines++; }
.			{ chars++; }
%%

int main(int argc, char **argv)
{
	int i;
	if(argc < 2)
	{
		yylex();
		printf("%8d%8d%8d\n", lines, words, chars);
		return 0;
	}
	
	for(i=1; i<argc; i++)
	{
		FILE *f = fopen(argv[i], "r");

		if(!f)
		{
			perror(argv[i]);
			return 1;
		}
		yyrestart(f);
		yylex();
		fclose(f);

		printf("%8d%8d%8d\n", lines, words, chars);
		totchars += chars;
		totwords += words;
		totlines += lines;
	}
	printf("%8d%8d%8d\n", totlines, totwords, totchars);
	return 0;
}
