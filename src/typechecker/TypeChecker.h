#pragma once

#include "../CompilerPass.h"
#include "../ast/ASTVisitor.h"
#include "../symboltable/SymbolTableEntry.h"
#include "../symboltable/SymbolType.h"

struct ExprResult {
  SymbolType type;
  SymbolTableEntry *entry = nullptr;
};

class TypeChecker : private CompilerPass, public ASTVisitor {
public:
  // Constructor
  explicit TypeChecker(SourceFile *sourceFile) : CompilerPass(sourceFile) {}

  // Public methods
  std::any visitDeclStmt(ASTDeclStmtNode *node) override;
  std::any visitAdditiveExpr(ASTAdditiveExprNode *node) override;
  std::any visitMultiplicativeExpr(ASTMultiplicativeExprNode *node) override;
  std::any visitAtomicExpr(ASTAtomicExprNode *node) override;
  std::any visitConstant(ASTConstantNode *node) override;
  std::any visitDataType(ASTDataTypeNode *node) override;
};