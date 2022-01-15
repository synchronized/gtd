/*******************************************
 *
 * aimless.gencode.h
 * 简易计算机语言-代码生成器头文件
 *
 * 基本语法:
 * int do_math(int a) {  
 * 	int x = a * 5 + 3
 * } 
 * do_math(10)
 *
 ******************************************/

#include <stack>
#include <llvm/Module.h>
#include <llvm/Function.h>
#include <llvm/PassManager.h>
#include <llvm/CallingConv.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Assembly/PrintModulePass.h>
#include <llvm/Support/IRBuilder.h>
#include <llvm/ModuleProvider.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

class NBlock;

class CodeGenBlock {
public:
	BasicBlock *block;
	std::map<std::string, Value *> locals;
};

class CodeGenContext {
	std::stack<CodeGenBlock *> blocks;
	Function *mainFunction;

public:
	Module *module;
	CodeGenContext() { module = new Module("main"); }

	void generateCode(NBlock& root);
	GenericValue runCode();
	std::map<std::string, Value*>& locals() { return blocks.top()->blocks; }
	BasicBlock *currentBlock() { return blocks.top()->block; }
	void pushBlock(BasicBlock *block) { 
		blocks.push(new CodeGenBlock()); 
		blocks.top()->block = block;
	}
	void popBlock() { 
		CodeGenBlock *top = blocks.top(); 
		blocks.pop();
		delete top;
	}
};

