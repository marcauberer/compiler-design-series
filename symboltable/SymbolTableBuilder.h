#pragma once

#include "../CompilerPass.h"
#include "../ast/ASTVisitor.h"

class SymbolTableBuilder : private CompilerPass, public ASTVisitor {
public:
  // Constructors
  explicit SymbolTableBuilder(SourceFile *sourceFile) : CompilerPass(sourceFile) {}

  // Public methods
  std::any visitDeclStmt(ASTDeclStmtNode *node) override;
};