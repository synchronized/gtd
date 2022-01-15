/*******************************************
 *
 * aimless.ast.cpp
 * 简易计算机语言-抽象语法树实现
 *
 * 基本语法:
 * int do_math(int a) {  
 * 	int x = a * 5 + 3
 * } 
 * do_math(10)
 *
 ******************************************/

#include "aimless.ast.h"
#include "aimless.gencode.h"

void NInteger::codeGen(CodeGenContext& context)
{
	std::cout << "Creating integer: " << value << std::endl;
}

void NDouble::codeGen(CodeGenContext& context)
{
	std::cout << "Creating double: " << value << std::endl;
}

void NIdentifier::codeGen(CodeGenContext& context)
{
	std::cout << "Creating identifier reference: " << name << std::endl;
	if(context
}
