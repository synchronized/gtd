/*******************************************
 *
 * aimless.y
 * 简易计算机语言-主函数
 *
 * 基本语法:
 * int do_math(int a) {  
 * 	int x = a * 5 + 3
 * } 
 * do_math(10)
 *
 ******************************************/

#include <iostream>
#include "aimless.h"

extern NBlock* programBlock;
extern int yyparse();

int main(int argc, char **argv)
{
	yyparse();
	std::cout << programBlock << std::endl;
	return 0;
}
