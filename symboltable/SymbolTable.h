#pragma once

#include <string>
#include <unordered_map>

#include "../ast/ASTNodes.h"
#include "../symboltable/SymbolTableEntry.h"

// Forward declarations
class SourceFile;

class SymbolTable {
public:
  // Constructor
  explicit SymbolTable(SourceFile *sourceFile) : sourceFile(sourceFile) {}

  // Public methods
  SymbolTableEntry *insert(const std::string &name, ASTNode *declNode);
  SymbolTableEntry *lookup(const std::string &name);

private:
  SourceFile *sourceFile;
  std::unordered_map<std::string, SymbolTableEntry> symbols;
};