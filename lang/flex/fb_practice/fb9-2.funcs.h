/*********************************
 *
 * fb9-2.funcs.h
 * 可重入计算器头文件
 *
 ********************************/

#ifndef _FB92_FUNCS_H_
#define _FB92_FUNCS_H_

/* 分析数据 */
struct pcdata {
	yyscan_t scaninfo;		// 词法分析器上下文
	struct symbol *symtab;	// 本次分析的符号
	struct ast *ast;		// 最近分析的抽象语法树
};

/* 符号表 */
struct symbol {				// 变量名
	char *name;
	double value;
	struct ast *func;		// 函数的抽象语法树
	struct symlist *syms;	// 虚拟参数列表
};

/* 固定大小的简单符号表 */
#define NHASH 9997
struct symbol symtab[NHASH];

struct symbol *lookup(struct pcdata *, char *);

/* 针对参数列表的符号列表 */
struct symlist {
	struct symbol *sym;
	struct symlist *next;
};

struct symlist *newsymlist(struct pcdata *, struct symbol *sym, struct symlist *next);
void symlistfree(struct pcdata *, struct symlist *sl);

/* 节点类型
 * + - * /
 * 0-7 为比较操作符, 位编码: 04 等于, 02 小于, 01 大于
 * M 弹幕符号
 * L 语句列表
 * I IF语句
 * W WHILE语句
 * N 符号引用
 * = 复制
 * S 符号列表
 * F 内置函数调用
 * C 用户函数调用
 */
enum bifs { /* 内置函数 */
	B_sqrt = 1,
	B_exp,
	B_log,
	B_print
};

/* 抽象语法树中的节点 */
/* 所有节点都有共同的初始nodetype */
struct ast{
	int nodetype;
	struct ast *l;
	struct ast *r;
};

struct fncall { 		//内置函数
	int nodetype; 		//类型F
	struct ast *l;
	enum bifs functype;
};

struct ufncall { 		//用户自定义函数
	int nodetype; 		//类型C
	struct ast *l; 		//参数列表
	struct symbol *s;
};

struct flow {
	int nodetype; 		//类型I或者W
	struct ast *cond; 	//条件
	struct ast *tl;		//then分支或者do语句
	struct ast *el;		//可选的else分支
};

struct numval {
	int nodetype; 		//类型K
	double number;
};

struct symref {
	int nodetype;		//类型N
	struct symbol *s;
};

struct symasgn {
	int nodetype;		//类型=
	struct symbol *s;
	struct ast *v;		//值
};

/* 构造一个抽象语法树 */
struct ast *newast(struct pcdata *, int nodetype, struct ast *l, struct ast *r);
struct ast *newcmp(struct pcdata *, int cmptype, struct ast *l, struct ast *r);
struct ast *newfunc(struct pcdata *, int functype, struct ast *l);
struct ast *newcall(struct pcdata *, struct symbol *s, struct ast *l);
struct ast *newref(struct pcdata *, struct symbol *s);
struct ast *newasgn(struct pcdata *, struct symbol *s, struct ast *v);
struct ast *newnum(struct pcdata *, double d);
struct ast *newflow(struct pcdata *, int nodetype, struct ast *cond, struct ast *tl, struct ast *tr);

/* 定义函数 */
void dodef(struct pcdata *, struct symbol *name, struct symlist *syms, struct ast *stmts);

/* 计算抽象语法树 */
double eval(struct pcdata *, struct ast *);

/* 删除和释放抽象语法树 */
void treefree(struct pcdata *, struct ast *);

/* 于词法分析器的接口 */
void yyerror(struct pcdata *pp, char *s, ...);

#endif //_FB92_FUNCS_H_
