#pragma once

#include <string>

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
  SymbolType type;
  ASTNode *declNode;
};