#include "IRGenerator.h"

#include <cassert>

#include <llvm/IR/Verifier.h>
#include <llvm/TargetParser/Host.h>

std::any IRGenerator::visitEntry(ASTEntryNode *node) {
  // Attach information to the module
  llvmModule->setTargetTriple(llvm::sys::getDefaultTargetTriple());
  llvmModule->setDataLayout(sourceFile->targetMachine->createDataLayout());

  // Create main function
  llvm::Type *returnType = builder.getInt32Ty();
  llvm::FunctionType *fctType = llvm::FunctionType::get(returnType, {}, false);
  llvm::Function *fct = llvm::Function::Create(fctType, llvm::Function::ExternalLinkage, "main", llvmModule);
  fct->setDSOLocal(true);

  // Add function attributes
  fct->addFnAttr(llvm::Attribute::NoInline);
  fct->addFnAttr(llvm::Attribute::NoUnwind);
  /*if (cliOptions.optLevel == OptLevel::O0)
    fct->addFnAttr(llvm::Attribute::OptimizeNone);
  else if (cliOptions.optLevel >= OptLevel::Os)
    fct->addFnAttr(llvm::Attribute::OptimizeForSize);*/
  fct->addFnAttr(llvm::Attribute::getWithUWTableKind(context, llvm::UWTableKind::Default));

  // Create entry block
  entryBlock = llvm::BasicBlock::Create(context);
  fct->insert(fct->end(), entryBlock);
  builder.SetInsertPoint(entryBlock);

  // Visit program
  visitChildren(node);

  // Always return with exit code 0
  builder.CreateRet(builder.getInt32(0));

  // Verify function
  std::string output;
  llvm::raw_string_ostream oss(output);
  if (llvm::verifyFunction(*fct, &oss))
    throw std::runtime_error("Invalid main function");

  return nullptr;
}

std::any IRGenerator::visitDeclStmt(ASTDeclStmtNode *node) {
  // Get variable entry
  SymbolTableEntry *varEntry = node->varEntry;
  assert(varEntry != nullptr);
  const SymbolType &varSymbolType = varEntry->type;

  // Allocate variable
  llvm::Type *llvmType = varSymbolType.toLLVMType(context);
  llvm::Value *varAddress = insertAlloca(llvmType, varEntry->name + ".addr");
  varEntry->address = varAddress;

  // Visit rhs
  auto initValue = std::any_cast<LLVMExprResult>(visit(node->additiveExpr()));
  assert(initValue.value != nullptr);

  // Store the rhs value to the allocated address
  builder.CreateStore(initValue.value, varAddress);

  return LLVMExprResult{.value = initValue.value, .entry = varEntry};
}

std::any IRGenerator::visitAdditiveExpr(ASTAdditiveExprNode *node) {
  // Check if only one operand is present -> loop through
  if (node->operands().size() == 1)
    return visit(node->operands().front());

  // It is an additive expression
  // Evaluate first operand
  ASTMultiplicativeExprNode *lhsNode = node->operands().at(0);
  SymbolType lhsSTy = lhsNode->getEvaluatedSymbolType();
  auto lhs = std::any_cast<LLVMExprResult>(visit(lhsNode));

  // Evaluate second operand
  ASTMultiplicativeExprNode *rhsNode = node->operands().at(1);
  SymbolType rhsSTy = rhsNode->getEvaluatedSymbolType();
  auto rhs = std::any_cast<LLVMExprResult>(visit(rhsNode));

  assert(lhsSTy == rhsSTy);
  assert(node->op != ASTAdditiveExprNode::OP_NONE);

  llvm::Value *resultValue = nullptr;
  if (node->op == ASTAdditiveExprNode::OP_PLUS) {
    if (lhsSTy.is(TY_INT)) {
      resultValue = builder.CreateAdd(lhs.value, rhs.value);
    } else if (lhsSTy.is(TY_DOUBLE)) {
      resultValue = builder.CreateFAdd(lhs.value, rhs.value);
    }
  } else if (node->op == ASTAdditiveExprNode::OP_MINUS) {
    if (lhsSTy.is(TY_INT)) {
      resultValue = builder.CreateSub(lhs.value, rhs.value);
    } else if (lhsSTy.is(TY_DOUBLE)) {
      resultValue = builder.CreateFSub(lhs.value, rhs.value);
    }
  }
  assert(resultValue != nullptr);

  return LLVMExprResult{.value = resultValue};
}

std::any IRGenerator::visitMultiplicativeExpr(ASTMultiplicativeExprNode *node) {
  // Check if only one operand is present -> loop through
  if (node->operands().size() == 1)
    return visit(node->operands().front());

  // It is an multiplicative expression
  // Evaluate first operand
  ASTAtomicExprNode *lhsNode = node->operands().at(0);
  SymbolType lhsSTy = lhsNode->getEvaluatedSymbolType();
  auto lhs = std::any_cast<LLVMExprResult>(visit(lhsNode));

  // Evaluate second operand
  ASTAtomicExprNode *rhsNode = node->operands().at(1);
  SymbolType rhsSTy = rhsNode->getEvaluatedSymbolType();
  auto rhs = std::any_cast<LLVMExprResult>(visit(rhsNode));

  assert(lhsSTy == rhsSTy);
  assert(node->op != ASTMultiplicativeExprNode::OP_NONE);

  llvm::Value *resultValue = nullptr;
  if (node->op == ASTMultiplicativeExprNode::OP_MUL) {
    if (lhsSTy.is(TY_INT)) {
      resultValue = builder.CreateMul(lhs.value, rhs.value);
    } else if (lhsSTy.is(TY_DOUBLE)) {
      resultValue = builder.CreateFMul(lhs.value, rhs.value);
    }
  } else if (node->op == ASTMultiplicativeExprNode::OP_DIV) {
    if (lhsSTy.is(TY_INT)) {
      resultValue = builder.CreateSDiv(lhs.value, rhs.value);
    } else if (lhsSTy.is(TY_DOUBLE)) {
      resultValue = builder.CreateFDiv(lhs.value, rhs.value);
    }
  }
  assert(resultValue != nullptr);

  return LLVMExprResult{.value = resultValue};
}

std::any IRGenerator::visitAtomicExpr(ASTAtomicExprNode *node) {
  // If constant
  if (node->constant())
    return visit(node->constant());

  // Check if sub expr within parentheses
  if (node->additiveExpr())
    return visit(node->additiveExpr());

  // Get the referenced variable entry
  SymbolTableEntry *varEntry = node->referencedEntry;
  assert(varEntry != nullptr);
  assert(varEntry->address != nullptr);

  // Load the vaue
  llvm::Type *llvmType = varEntry->type.toLLVMType(context);
  llvm::Value *loadedValue = builder.CreateLoad(llvmType, varEntry->address, varEntry->name);

  return LLVMExprResult{.value = loadedValue, .entry = varEntry};
}

std::any IRGenerator::visitConstant(ASTConstantNode *node) {
  llvm::Constant *constValue = nullptr;
  if (node->type == ASTConstantNode::TYPE_INT)
    constValue = builder.getInt32(node->compileTimeVaue.intValue);
  else if (node->type == ASTConstantNode::TYPE_DOUBLE)
    constValue = llvm::ConstantFP::get(context, llvm::APFloat(node->compileTimeVaue.doubleValue));
  else
    assert(false && "IRGenerator - Constant fall-through");
  return LLVMExprResult{.value = constValue};
}

std::any IRGenerator::visitPrintCall(ASTPrintCallNode *node) {
  auto arg = std::any_cast<LLVMExprResult>(visit(node->arg()));
  SymbolType &argType = arg.entry->type;

  // Create template string
  const std::string templateString = argType.is(TY_INT) ? "%d\n" : "%f\n";
  llvm::Constant *templateStringConstant = builder.CreateGlobalStringPtr(templateString, "print.str", 0, llvmModule);

  // Call printf function
  llvm::Function *printfFct = getPrintfFct();
  llvm::CallInst *returnValue = builder.CreateCall(printfFct, {templateStringConstant, arg.value});

  return LLVMExprResult{.value = returnValue};
}

std::any IRGenerator::visitDataType(ASTDataTypeNode *node) {
  // Retrieve symbol type
  SymbolType symbolType = node->getEvaluatedSymbolType();
  assert(!symbolType.is(TY_INVALID));
  return symbolType.toLLVMType(context);
}

std::string IRGenerator::getIRString() const {
  std::string output;
  llvm::raw_string_ostream oss(output);
  llvmModule->print(oss, nullptr);
  return oss.str();
}

llvm::Value *IRGenerator::insertAlloca(llvm::Type *llvmType, const std::string &varName) {
  // Save insert point
  llvm::BasicBlock *currentBlock = builder.GetInsertBlock();
  builder.SetInsertPoint(entryBlock);
  // Allocate
  llvm::AllocaInst *allocaInst = builder.CreateAlloca(llvmType, nullptr, varName);
  // Restore old insert point
  builder.SetInsertPoint(currentBlock);
  return allocaInst;
}

llvm::Function *IRGenerator::getPrintfFct() {
  llvm::Function *printfFct = getFunction("printf", builder.getInt32Ty(), builder.getInt8PtrTy(), true);
  // Set attributes
  printfFct->addFnAttr(llvm::Attribute::NoFree);
  printfFct->addFnAttr(llvm::Attribute::NoUnwind);
  printfFct->addParamAttr(0, llvm::Attribute::NoCapture);
  printfFct->addParamAttr(0, llvm::Attribute::NoUndef);
  printfFct->addParamAttr(0, llvm::Attribute::ReadOnly);
  printfFct->addRetAttr(llvm::Attribute::NoUndef);
  return printfFct;
}

llvm::Function *IRGenerator::getFunction(const char *funcName, llvm::Type *returnType, llvm::ArrayRef<llvm::Type *> args,
                                         bool varArg) const {
  // Check if function already exists in the current module
  llvm::Function *fct = llvmModule->getFunction(funcName);
  if (fct != nullptr)
    return fct;

  // Add function to the current module
  llvm::FunctionType *opFctTy = llvm::FunctionType::get(returnType, args, varArg);
  llvmModule->getOrInsertFunction(funcName, opFctTy);
  return llvmModule->getFunction(funcName);
}