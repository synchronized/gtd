/*******************************************
 *
 * aimless.gencode.cpp
 * 简易计算机语言-代码生成器实现
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
#include "aimless.tab.h"

/* Compile the AST into a module */
void CodeGenContext::generateCode(NBLOCK& root)
{
	std::cout << "Generating code..." << std::endl;
	/* Create the top level interpreter 
	 * function to call as entry 
	 */
	std::vector<const type*> argTypes;
	FunctionType *ftype = 
		FunctionType::get(Type::VoidTy, argTypes, false);
	mainFunction = 
		Function::Create(ftype, 
				GlobalValue::InternalLinkage, "main", module);
	BasicBlock *bblock = 
		BasicBlock::Create("entry", mainFunction, 0);

	/* Push a new variable/block context */
	pushBlock(bblock);
	/* emit bytecode for the toplevel block */
	root.codeGen(*this);
	ReturnInst::Create(bblock);
	popBlock();

	/*
	 * Print the bytecode in a human-readable format 
	 * to see if our program compiled properly
	 */
	std::cout  << "Code is generated." << std::endl;
	PassManager pm;
	pm.add(createPrintModulePass(&outs()));
	pm.run(*module);
}

/* Execute the AST by running the main function */
GenericValue CodeGenContext::runCode() {
	std::cout << "Running code..." << std::endl;
	ExistingModuleProvider *mp = 
		new ExistingModuleProvider(module);
	ExecutionEngine *ee = ExecutionEngine::create(mp, false);
	vector<genericvalue> noargs;
	GenericValue v = ee->runFunction(mainFunction, noargs);
	std::cout << "Code was run.\n";
	return v;
}

/* Returns an LLVM type based on the identifier */
static const Type *typeOf(const NIdentifier& type)
{
	if(type.name.compare("int") == 0)
	{
		return Type::Int64Ty;
	}
	else if(type.name.compare("double") == 0)
	{
		return Type::FP128Ty;
	}
	return Type::VoidTy;
}

/* -- Code Generation -- */
Value* NInteger::codeGen(CodeGenContext& context)
{
	std::cout << "Creating integer: " 
		<< value << std::endl;
	return ConstantInt::get(Type::Int64Ty, value, true);
}

Value* NDouble::codeGen(CodeGenContext& context)
{
	std::cout << "Creating double: " 
		<< value << std::endl;
	return ConstantFP::get(Type::FP128Ty, value);
}

Value* NIdentifier::codeGen(CodeGenContext& context)
{
	std::cout << "Creating identifier reference: " 
		<< name << std::endl;
	if(context.locals().find(name) == context.locals().end())
	{
		std::cerr << "undeclared variable" << name << std::endl;
		return NULL;
	}
	return new LoadInst(context.locals()[name], "", false, 
			context.currentBlock());
}

Value* NMethodCall::codeGen(CodeGenContext& context)
{
	std::cout << "Creating method call: " << id.name << std::endl;
	Function *function = context.module->getFunction(id.name.c_str());
	if(function == NULL) {
		std::cerr << "nosuch function " << id.name << std::endl;
		return NULL;
	}
	std::vector<value *> args;
	ExpressionList::const_iterator it;
	if(it = arguments.begin(); it != arguments.end(); it++)
	{
		args.push_back((**it).codeGen(context));
	}
	CallInst *call = 
		CallInst::Create(function, args.begin(), args.end(), "", 
				context.currentBlock());
	return call;
}

Value* NBinaryOperator::codeGen(CodeGenContext& context)
{
	std::cout << "Creating binary operation " 
		<< op << std::endl;
	Instruction::BinaryOps instr;
	switch(op) {
		case '+': instr = Instruction::Add; break;
		case '-': instr = Instruction::Sub; break;
		case '*': instr = Instruction::Mul; break;
		case '/': instr = Instruction::SDiv; break;
		default:
				  return NULL;
	}
	return BinaryOperator::Create(instr, 
			lhs.codeGen(context), 
			rhs.codeGen(context), "", 
			context.currentBlock());
}

Value* NAssignment::codeGen(CodeGenContext& context)
{
	std::cout << "Creating assignment for " << lhs.name << std::endl;
	if(context.loads().find(lhs.name) == context.locals().end()) {
		std::cerr << "undeclared variable " << lhs.name << std::endl;
		return NULL;
	}
	return newStoreInst(rhs.codeGen(context), 
			context.locals()[lhs.name], false, 
			context.currentBlock());
}

Value* NBlock::codeGen(CodeGenContext& context)
{
	std::cout << "Creaing block" << std::endl;
	StatementList::const_iterator it;
	Value *last = NULL;
	for (it = statements.begin(); it != statements.end(); it++) {
		std::cout << "Generating code for " 
			<< typeid(**it).name() << std::endl;
		last = (**it).codeGen(context);
	}
	return last;
}

Value* NExpressionStatment::codeGen(CodeGenContext& context)
{
	std::cout << "Generating code for " 
		<< typeid(expression).name() << std::endl;
	return expression.codeGen(context);
}

Value* NVariableDeclaration::codeGen(CodeGenContext& context)
{
	std::cout << "Creating variable declaration " 
		<< type.name << " " << id.name << std::endl;
	AllocaInst *alloc = 
		new AllocaInst(typeOf(type), id.name.c_str(), 
				context.currentBlock());
	context.locals()[id.name] = alloc;
	if(assignmentExpr != NULL) {
		NAssignment assn(id, *assignmentExpr);
		assn.codeGen(context);
	}
	return alloc;
}

Value* NFunctionDeclaration::codeGen(CodeGenContext& context)
{
	std::vector<const type*> argTypes;
	VariableList::const_iterator it;
	for(it = arguments.begin(); it != arguments.end(); it++) {
		argTypes.push_back(typeOf((**it).type));
	}
	FunctionType *ftype = FunctionType::get(typeOf(type), argTypes, false);
	Function *function = 
		Function::Create(ftype, GlobalValue::InternalLinkage, 
				id.name.c_str(), context.module);
	BasicBlock *bblock = BasicBlock::Create("entry", function, 0);

	context.pushBlock(bblock);

	for(it = arguments.begin(); it != arguments.end(); it++)
	{
		(**it).codeGen(context);
	}

	block.codeGen(context);
	ReturnInst::Create(bblock);

	context.popBlock();
	std::cout << "Creating function: " << id.name << endl;
	return function;
}

