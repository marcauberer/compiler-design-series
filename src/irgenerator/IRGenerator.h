#pragma once

#include "../CompilerPass.h"
#include "../ast/ASTNodes.h"
#include "../ast/ASTVisitor.h"

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Target/TargetMachine.h>

class IRGenerator : private CompilerPass, public ASTVisitor {
public:
  // Constants
  explicit IRGenerator(SourceFile *sourceFile) : CompilerPass(sourceFile) {}

  // Public methods
  std::any visitStmt(ASTStmtNode *node) override;
  std::any visitDeclStmt(ASTDeclStmtNode *node) override;
  std::any visitAdditiveExpr(ASTAdditiveExprNode *node) override;
  std::any visitMultiplicativeExpr(ASTMultiplicativeExprNode *node) override;
  std::any visitAtomicExpr(ASTAtomicExprNode *node) override;
  std::any visitConstant(ASTConstantNode *node) override;
  std::any visitDataType(ASTDataTypeNode *node) override;

private:
  // Private members
  llvm::LLVMContext context;
  llvm::IRBuilder<> builder = llvm::IRBuilder<>(context);
};