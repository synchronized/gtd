/**************************
 *
 * fb2-5.l
 *
 *************************/

%option noyywrap nodefault yylineno

%x COMMENT
%x IFILE

	/* 一些复杂的命名模式 */
	/* 通用字符名 */
UCN (\\u[0-9a-fA-F]{4}|\\u[0-9a-fA-F]{8})
	/* 浮点指数部分 */
EXP ([Ee][-+]?[0-9]+)
	/* 整数长度 */
ILEN ([Uu](L|l|LL|ll)?|(L|l|LL|ll)[Uu]?)

	/* 符号表 */
%{
	struct symbol{
		char *name;
		struct ref *reflist;
	};

	struct ref{
		struct ref *next;
		char *filename;
		int lineno;
		int flags;	//01 - definition
	};

	//简单固定大小的hash
	#define NHASH 9997
	struct symbol symtab[NHASH];
	struct symbol *lookup(char* word);
	void addref(int lineno, char *filename, char *word, int flags);
	void printrefs(void);

	char* curfilename;

	struct bufstack{
		struct bufstack *prev;	//前一条目
		YY_BUFFER_STATE bs;		//保存的缓冲区
		int lineno;				//保存的文件行号
		char *filename;			//保存的文件名称
		FILE *f;				//保存的文件句柄
	};
	struct bufstack *curbs;

	int newfile(char *fn);
	int popfile(void);

	int defining;	//名称是否定义
%}

%%
	/* 注释 */
"/*"			{ BEGIN COMMENT; }
<COMMENT>"*/"	{ BEGIN INITIAL; }
<COMMENT>([^*]|\n)+|.	{}
<COMMENT><<EOF>>	{ printf("%s:%d:unterminated comment\n", 
		curfilename, yylineno); return 0; }
	/* C++注释 */
"//".*\n		{}

	/* 声明关键字 */
_Bool		|
_Complex	|
_Imaginary	|
auto		|
char		|
const		|
double		|
enum		|
extern		|
float		|
inline		|
int			|
long		|
register	|
restrict	|
short		|
signed		|
static		|
struct		|
typedef		|
union		|
unsigned	|
void		|
volatile	{ defining = 1; }

	/* 关键字 */
break
case
continue
default
do
else
for
goto
if
return
sizeof
switch
while
	/* 常量 */
	/* 整数 */
0[0-7]*{ILEN}?
[1-9[0-9]*{ILEN}?
0[Xx][0-9a-fA-F]+{ILEN}?

	/* 十进制浮点 */
([0-9]*\.[0-9]+|[0-9]+\.){EXP}?[flFL]?
[0-9]+{EXP}[flFL]?

	/* 十六进制浮点 */
0[Xx]([0-9a-fA-F]*\.[0-9a-fA-F]+|[0-9a-fA-F]+\.?)[Pp][-+]?[0-9]+[flFL]?

	/* 字符常量 */
\'([^'\\]|\\['"?\\abfnrtv]|\\[0-7]{1,3}\\[Xx][0-9a-fA-F]+|{UCN})+\'

	/* 字符串常量 */
L?\"([^"\\]|\\['"?\\abfnrtv]|\\[0-7]{1,3}\\[Xx][0-9a-fA-F]+|{UCN})*\"

	/* 标点符号 */
"{"|"<%"|";"	{ defining = 0; }

"["|"]"|"("|")"|"{"|"}"|"."|"->"
"++"|"--"|"&"|"*"|"+"|"-"|"~"|"!"
"/"|"%"|"<<"|">>"|"<"|">"|"<="|">="|"=="|"!="|"^"|"|"|"&&"|"||"
"?"|":"|";"|"..."
"="|"*="|"/="|"%="|"+="|"-="|"<<="|">>="|"&="|"^="|"|="
","|"#"|"##"
"<:"|":>"|"%>"|"%:"|"%:%:"

	/* 标识符 */
([_a-zA-Z]|{UCN})([_a-zA-Z0-9]|{UCN})*	{ addref(yylineno, curfilename, yytext, defining); }

	/* 空白字符 */
[ \t\n]+

	/* 续航符 */
\\$

	/* 预处理 */
#\s*if.*\n
#\s*else.*\n
#\s*endif.*\n
#\s*define.*\n
#\s*line.*\n

	/* 识别包含文件 */
^#[ \t]*include[ \t]*[\"<]	{ BEGIN IFILE;}
<IFILE>[^>\"]+				{
	{
		int c;
		while((c=input()) &&c != '\n');
	}
	newfile(strdup(yytext));
	BEGIN INITIAL;
}

<IFILE>.|\n					{
	fprintf(stderr, "%s:%d bad include line\n",
			curfilename, yylineno);
	BEGIN INITIAL;
}

<<EOF>>				{ if(!popfile()) yyterminate(); }

.	{
	printf("%s:%d: Mystery character '%s'\n", curfilename, yylineno, yytext);
}
%%

int main(int argc, char **argv)
{
	int i;
	if(argc < 2)
	{ 
		fprintf(stderr, "need filename");
		return -1;
	}

	for(i=1; i<argc; i++)
	{
		if(newfile(argv[i]))
			yylex();
	}
	printrefs();
	return 0;
}

int symhash(const char *word)
{
	unsigned int hash = 0;
	unsigned int c;
	while(c = *word++) hash = hash*9^tolower(c);
	return abs(hash);
}

struct symbol *lookup(char* sym)
{
	size_t scount = NHASH;
	int hash = symhash(sym)%NHASH;
	struct symbol *sp = &symtab[hash];
	while(scount-- >= 0)
	{
		if(!sp->name) 
		{
			sp->name = strdup(sym);
			sp->reflist = 0;
			return sp;
		}
		if(!strcasecmp(sp->name, sym)) return sp;
		//尝试下一个条目
		if(++sp >= symtab + NHASH) sp = symtab;
	}
	//所有条目都试过了,符号表已满
	fprintf(stderr, "symbol table overflow\n");
	fprintf(yyout, "symbol table overflow\n");
	abort();
	return NULL;
}

void addref(int lineno, char *filename, char *word, int flags)
{
	struct ref *r;
	struct symbol *sp = lookup(word);

	//不用复制相同行的文件
	if(sp->reflist &&
			sp->reflist->lineno == lineno &&
			sp->reflist->filename == filename) return;

	r = malloc(sizeof(struct ref));
	if(!r)
	{
		fprintf(stderr, "out of memory addref()");
		fprintf(yyout, "out of memory addref()");
		abort();
	}

	r->next = sp->reflist;
	r->lineno = lineno;
	r->filename = filename;
	r->flags = flags;

	sp->reflist = r;
}

int symcompare(const void *xa, const void *xb)
{
	const struct symbol *a = xa;
	const struct symbol *b = xb;
	if(!a || !a->name)
	{
		if(!b || !b->name) return 0;
		return 1;
	}
	if(!b || !b->name) return -1;
	return strcmp(a->name, b->name);
}

void printrefs() 
{
	struct symbol *sp;
	fprintf(yyout, "---\n");
	//对符号进行排序
	qsort( symtab, NHASH, sizeof(struct symbol), symcompare);
	for(sp=symtab; sp->name; sp++)
	{
		//前一个打印文件的文件名,用来跳过重复的文件
		char *prevfile = NULL;
		//翻转引用列表
		struct ref *rp = sp->reflist;
		struct ref *rpp = 0;	//前一个引用
		struct ref *rpn;		//后一个引用

		do{
			rpn = rp->next;
			rp->next = rpp;
			rpp = rp;
			rp = rpn;
		}while(rp);

		//打印单词和它的引用
		fprintf(yyout, "%10s", sp->name);
		for(rp = rpp; rp; rp = rp->next)
		{
			if(rp->filename == prevfile)
			{
				fprintf(yyout, " %d", rp->lineno);
			}
			else
			{
				fprintf(yyout, " %s:%d", rp->filename, rp->lineno);
				prevfile = rp->filename;
			}
			if(rp->flags & 01) printf("*");
		}
		fprintf(yyout, "\n");
	}
}

int newfile(char *fn)
{
	FILE *f = fopen(fn, "r");
	struct bufstack *bs = malloc(sizeof(struct bufstack));
	if(!f)
	{
		perror(fn);
		return 0;
	}
	if(!bs)
	{
		fprintf(stderr, "out of memory!\n");
		exit(1);
	}

	if(curbs) curbs->lineno = yylineno;
	bs->prev = curbs;
	bs->f = f;
	bs->lineno = 0;
	bs->filename = fn;
	bs->bs = yy_create_buffer(f, YY_BUF_SIZE);

	yy_switch_to_buffer(bs->bs);

	curbs = bs;
	yylineno = 1;
	curfilename = fn;
	return 1;
}

int popfile(void)
{
	struct bufstack *bs = curbs;
	struct bufstack *prevbs;

	if(!bs) return 0;
	//删除当前文件信息
	yy_delete_buffer(bs->bs);
	fclose(bs->f);
	//切换回上一个文件
	prevbs = bs->prev;
	//free(bs->filename);
	free(bs);

	if(!prevbs) return 0;
	yy_switch_to_buffer(prevbs->bs);
	curbs = prevbs;
	yylineno = curbs->lineno;
	curfilename = curbs->filename;
	return 1;
}
