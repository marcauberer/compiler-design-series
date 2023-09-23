#pragma once

#include <string>
#include <memory>
#include <vector>

#include "symboltable/SymbolTable.h"

class SourceFile {
public:
  // Constructor
  SourceFile(const std::string &filePath) : filePath(filePath), symbolTable(this) {}

  // Public methods
  void parse();
  void createSymbolTable();
  void typeCheck();

  // Public members
  std::string filePath;
  SymbolTable symbolTable;
  std::vector<std::unique_ptr<ASTNode>> astNodes;

private:
  // Private members
  ASTEntryNode *ast = nullptr;
};