/**************************************
 *
 * fb9-1.l
 * 数字统计-词法分析器
 *
 *************************************/

%define api.pure
%parse-param { struct pureparse *pp }

%{
	/* 语法分析器中生成的调用 */

#define YYLEX_PARAM pp->scaninfo
%}


%%
	/* 语法分析器重生成的调用 */
token = yylex(YYSTYPE *yylvalp, pp->scaninfo);
token = yylex(YYSTYPE *yylvalp, YYLTYPE *yylocp, pp->scaninfo);

yyerror(struct pureparse *pp, "Syntax error");
yyerror(YYLTYPE &yyllocp, struct pureparse *pp, "Syntax error");

%%


