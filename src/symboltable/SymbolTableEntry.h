#pragma once

#include <string>

#include <llvm/IR/Value.h>

#include "../symboltable/SymbolType.h"

// Forward declarations
class ASTNode;

class SymbolTableEntry {
public:
  // Constructors
  SymbolTableEntry(std::string name, SymbolType type, ASTNode *declNode)
      : name(std::move(name)), type(std::move(type)), declNode(declNode) {}

  // Public members
  const std::string name;
  SymbolType type = SymbolType(TY_INVALID);
  ASTNode *declNode;
  llvm::Value *address;
};