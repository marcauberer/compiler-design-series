#pragma once

#include "../CompilerPass.h"
#include "../ast/ASTNodes.h"
#include "../ast/ASTVisitor.h"

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Target/TargetMachine.h>

struct LLVMExprResult {
  llvm::Value *value = nullptr;
  SymbolTableEntry *entry = nullptr;
};

class IRGenerator : private CompilerPass, public ASTVisitor {
public:
  // Constants
  explicit IRGenerator(SourceFile *sourceFile)
      : CompilerPass(sourceFile), context(sourceFile->context), llvmModule(sourceFile->llvmModule.get()) {}

  // Public methods
  std::any visitEntry(ASTEntryNode *node) override;
  std::any visitDeclStmt(ASTDeclStmtNode *node) override;
  std::any visitAdditiveExpr(ASTAdditiveExprNode *node) override;
  std::any visitMultiplicativeExpr(ASTMultiplicativeExprNode *node) override;
  std::any visitAtomicExpr(ASTAtomicExprNode *node) override;
  std::any visitConstant(ASTConstantNode *node) override;
  std::any visitPrintCall(ASTPrintCallNode *node) override;
  std::any visitDataType(ASTDataTypeNode *node) override;

private:
  // Private members
  llvm::LLVMContext &context;
  llvm::IRBuilder<> builder = llvm::IRBuilder<>(context);
  llvm::Module *llvmModule;
  llvm::BasicBlock *entryBlock;

  // Private methods
  llvm::Value *insertAlloca(llvm::Type *llvmType, const std::string &varName = "");
  llvm::Function *getPrintfFct();
  llvm::Function *getFunction(const char *funcName, llvm::Type *returnType, llvm::ArrayRef<llvm::Type *> args, bool varArg) const;
};