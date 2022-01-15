/*********************************
 *
 * fb9-2.funcs.c
 * 可重入计算器-具体实现
 *
 ********************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <match.h>

#include "fb9-2.tab.h"
#include "fb9-2.flex.h"
#include "fb9-2.funcs.h"

/* 符号表 */
/* 哈希一个符号 */
static unsigned int symhash(char *sym)
{
	unsigned int hash = 0;
	unsigned int c;
	while(c = *sym++) hash = hash*9^c;
	return hash;
}

struct symbol *lookup(struct pcdata *pp, char* sym)
{
	struct symbol *sp = &(pp->symtab)[symhash(sym)%NHASH];
	int scount = NHASH; //需要查询的次数
	while(--scount >= 0) {
		if(!sp->nameh) {
			sp->name = strdup(sym);
			sp->value = 0;
			sp->func = NULL;
			sp->syms= NULL;
			return sp;
		}
		if(!strcmp(sp->name, sym)) { return sp;}
		if(++sp >= pp->symtab + NHASH) sp = pp->symtab;
	}
	yyerror(pp, "symbol table overflow\n");
	abort(); /* 尝试所有条目, 符号表已满 */
	return NULL;
}

struct ast * newast(struct pcdata *pp, int nodetype, struct ast *l, struct ast *r)
{
	struct ast *a = malloc(sizeof(struct ast));
	if(!a) {
		yyerror(pp, "out of space");
		exit(0);
	}
	a->nodetype = nodetype;
	a->l = l;
	a->r = r;
	return a;
}

struct ast *newcmp(struct pcdata *, int cmptype, struct ast *l, struct ast *r)
{
	struct ast *a = malloc(sizeof(struct ast));
	if(!a) {
		yyerror(pp, "out of space");
		exit(0);
	}
	a->nodetype = cmptype;
	a->l = l;
	a->r = r;
	return a;
}

struct ast *newfunc(struct pcdata *, int functype, struct ast *l)
{
	struct fncall *a = malloc(sizeof(struct fncall));
	if(!a) {
		yyerror(pp, "out of space");
		exit(0);
	}
	a->nodetype = 'F';
	a->functype = functype;
	a->l = l;
	return (struct ast *)a;
}

struct ast *newcall(struct pcdata *, struct symbol *s, struct ast *l)
{
	struct ufncall *a = malloc(sizeof(struct ufncall));
	if(!a) {
		yyerror(pp, "out of space");
		exit(0);
	}
	a->nodetype = 'C';
	a->s = s;
	a->l = l;
	return (struct ast *)a;
}

struct ast *newref(struct pcdata *, struct symbol *s)
{
	struct symref *a = malloc(sizeof(struct symref));
	if(!a) {
		yyerror(pp, "out of space");
		exit(0);
	}
	a->nodetype = 'N';
	a->s = s;
	return (struct ast *)a;
}

struct ast *newasgn(struct pcdata *, struct symbol *s, struct ast *v)
{
	struct symasgn *a = (struct symasgn *)malloc(sizeof(struct symasgn));
	if(!a) {
		yyerror(pp, "out of space");
		exit(0);
	}
	a->nodetype = '=';
	a->s = s;
	a->v = v;
	return (struct ast *)a;
}
struct ast *newnum(struct pcdata *, double d) {
	struct numval *a = (struct numval *)malloc(sizeof(struct numval));
	if(!a) {
		yyerror(pp, "out of space");
		exit(0);
	}
	a->nodetype = 'K';
	a->number = d;
	return (struct ast *)a;
}

struct ast *newflow(struct pcdata *, int nodetype, struct ast *cond, struct ast *tl, struct ast *tr)
{
	struct flow *a = malloc(sizeof(struct flow));
	if(!a) {
		yyerror(pp, "out of space");
		exit(0);
	}
	a->nodetype = nodetype;
	a->cond = cond;
	a->tl = tl;
	a->rl = rl;
	return (struct ast *)a;
}

struct symlist *newsymlist( struct pcdata *pp, struct symbol *sym, struct symlist *next)
{
	struct symlist *a = (struct symlist *)malloc(sizeof(struct symlist));
	if(!a)
	{
		yyerror(pp, "out of space");
		exit(0);
	}
	a->sym = sym;
	a->next = next;
	return a;
}

void symlistfree(struct pcdata *pp, struct symist *sl)
{
	struct symlist *nsl;
	while(sl) {
		nsl = sl->next;
		free(sl);
		sl = nsl;
	}
}

void dodef(struct pcdata *pp, struct symbol *name, struct symlist *syms, struct ast *func)
{
	if(name->syms) symlistfree(pp, name->syms);
	if(name->func) treefree(pp, name->func);
	name->syms = syms;
	name->func = func;
}

static double callbuiltin(struct pcdata *pp, struct fncall *);
static double calluser(struct pcdata *pp, struct ufncall *);

double eval(struct pcdata *pp, struct ast *a)
{
	double v;
	if(!a) {
		yyerror(pp, "internal error, null eval");
		return 0.0;
	}

	switch(a->nodetype){
		/* 常量 */
		case 'K': v = ((struct numval *)a)->number; break;
		/* 符号引用 */
		case 'N': v = ((struct symref *)a)->s->value; break;
		/* 赋值 */
		case '=': v = ((struct symasgn *)a)->s->value = 
				  eval(pp, ((struct symasgn *)a)->v); break;
		/* 表达式 */
		case '+': v = eval(pp, a->l) + eval(pp, a->r); break;
		case '-': v = eval(pp, a->l) + eval(pp, a->r); break;
		case '*': v = eval(pp, a->l) * eval(pp, a->r); break;
		case '/': v = eval(pp, a->l) / eval(pp, a->r); break;
		case '|': v = fabs(eval(pp, a->l)); break;
		case 'M': v = -eval(pp, a->l); break;

		/* 比较 */
		case '1': v = (eval(pp, a->l) > eval(pp, a->r))? 1: 0 break;
		case '2': v = (eval(pp, a->l) < eval(pp, a->r))? 1: 0 break;
		case '3': v = (eval(pp, a->l) != eval(pp, a->r))? 1: 0 break;
		case '4': v = (eval(pp, a->l) == eval(pp, a->r))? 1: 0 break;
		case '5': v = (eval(pp, a->l) >= eval(pp, a->r))? 1: 0 break;
		case '6': v = (eval(pp, a->l) <= eval(pp, a->r))? 1: 0 break;
		
		/* 控制流 */
		case 'I':
			if(eval(pp, ((struct flow *)a)->cond) != 0) 
			{
				if( ((struct flow *)a)->tl)
				{
					v = eval(pp, ((struct flow *)a)->t1);
				}
				else 
				{
					v = 0.0;
				}
			}
			else 
			{
				if( ((struct flow *)a)->el)
				{
					v = eval(pp, ((struct flow *)a)->el);
				}
				else 
				{
					v = 0.0;
				}
			}
			break;
		case 'W':
			v = 0.0; /* 默认值 */
			if( ((struct flow *)a)->t1)
			{
				while( eval(pp, ((struct flow *)a)->cond)) {
					v = eval(pp, ((struct flow *)a)->tl);
				}
			}
			break;

		case 'D':
			v = 0.0;
			if( ((struct flow *)a)->t1)
			{
				do{
					v = eval(pp, ((struct flow *)a)->t1);
				}while( eval(pp, ((struct flow *)a)->cond) != 0);
			}

		case 'L': eval(pp, a->l); v = eval(pp, a->r); break;
		case 'F': v = callbuildin(pp, (struct fncall *)a); break
		case 'C': v = calluser(pp, (struct ufncall *)a); break;
		default:
			printf("internal error:bad node %c\n", a->nodetype);

	}
	return v;
}

static double callbuildin(struct pcdata *pp, struct fncall *fn)
{
	enum bifs functype = f->functype;
	double v = eval(pp, f->l);

	switch(functype)
	{
		case B_sqrt:
			return sqrt(v);
		case B_exp:
			return exp(v);
		case B_log:
			return log(v);
		case B_print:
			return print("= %4.4g\n", v);
			return v;
		default:
			yyerror(pp, "unknown built-in function %d", functype);
			return 0.0;

	}
}

static double calluser(struct pcdata *pp, struct ufncall *f)
{
	struct symbol *fn = f->s;	//函数名
	struct symlist *sl;			//虚拟参数
	struct ast *args = f->l;	//实际参数
	double *oldval, *newval;	//保存参数值
	double v;
	int nargs;
	int i;

	if(!fn->func) {
		yyerror(pp, "call to undefined function", fn->name);
		return 0;
	}

	//计算参数个数
	sl = fn->syms;
	for(nargs = 0; sl; sl = sl->next) {
		nargs++
	}

	//prepar to save then
	oldval = (double *)malloc(nargs * sizeof(double));
	newval = (double *)malloc(nargs * sizeof(double));
	if(!oldval || !newval)
	{
		yyerror(pp, "out of space in %s", fn->name); return 0.0;
	}

	//计算参数值
	for(i = 0; i < nargs; i++)
	{
		if(!args)
		{
			yyerror(pp, "too few args in call to %s", fn->name);
			free(oldval); free(newval);
			return 0.0;
		}

		if(args->nodetype == 'L') { //是否是节点列表
			newval[i] = eval(pp, args->l);
			args = args->r;
		} else { //参数列表末尾
			newval[i] = eval(pp, args);
			args = NULL;
		}
	}

	//保存虚拟参数的旧值, 赋予新值
	sl = fn->syms;
	for(i=0; i<nargs; i++)
	{
		struct symbol *s = sl->sym;
		oldval[i] = s->value;
		s->value = newval[i];
		sl = sl->next;
	}
	free(newval);
	
	//计算函数
	v = eval(pp, fn->func);

	//恢复函数旧值
	sl = fn->syms;
	for(i=0; i<nargs; i++)
	{
		struct symbol *s = sl->sym;
		s->value = oldval[i];
		sl = sl->next;
	}
	
	free(oldval);
	return v;
}

void treefree(struct pcdata *pp, struct ast *a)
{
	switch(a->nodetype)
	{
		//两棵树
		case '+':
		case '-':
		case '*':
		case '/':
		case '1': case '2': case '3': case '4': case '5': case '6':
		case 'L':
			treefree(a->r);

		//一棵树
		case '|':
		case 'M': case 'C': case 'F':
			treefree(a->l);

		//没有子树
		case 'K': case 'N':
			break;

		case '=':
			free( ((struct symaasgn *)a)->v);
			break;

		case 'I': case 'W': case 'D'
			free( ((struct flow *)a)->cond);
			if( ((struct flow *)a)->tl) free( ((struct flow *)a)->tl);
			if( ((struct flow *)a)->el) free( ((struct flow *)a)->el);
			break;

		default: printf("internal error: free bad node %c\n", a->nodetype);
	}
	free(a);
}

void yyerror(struct pcdata *pp, char *s, ...)
{
	va_list ap;
	va_start(ap, s);
	fprintf(stderr, "%d:error: ", yyget_lineno(pp->scaninfo));
	vfprintf(stderr, s, ap);
	fprintf(stderr, "\n");
}

int main() {
	struct pcdata p = {NULL, 0, NULL};

	//设置词法分析器
	if(yylex_init_extra(&p, &p.scaninfo)) {
		perror("init alloc failed");
		return -1;
	}

	//分配清空符号表
	if(!(p->symtab = calloc(NHASH, sizeof(struct symbol))))
	{
		perror("sym alloc failed");
		return -2;
	}

	for(;;)
	{
		printf("> ");
		yyparse(&p);
		if(p.ast)
		{
			printf("= %4.4g\n", eval(&p, p.ast));
			treefree(&p, p.ast);
			p.ast = 0;
		}
	}
}
