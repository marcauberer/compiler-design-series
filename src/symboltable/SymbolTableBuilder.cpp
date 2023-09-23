#include "SymbolTableBuilder.h"

#include <stdexcept>

std::any SymbolTableBuilder::visitDeclStmt(ASTDeclStmtNode *node) {
  const std::string &name = node->varName;
  SymbolTable &table = sourceFile->symbolTable;

  // Check if the variable was already declared
  if (table.lookup(name))
    throw std::runtime_error("Re-declaration of variable '" + name + "'");

  // Add to symbol table
  table.insert(name, node);

  return nullptr;
}