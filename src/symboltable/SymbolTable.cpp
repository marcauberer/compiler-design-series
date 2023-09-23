#include "SymbolTable.h"

SymbolTableEntry *SymbolTable::insert(const std::string &name, ASTNode *declNode) {
  symbols.insert({name, SymbolTableEntry(name, SymbolType(TY_INVALID), declNode)});
  return &symbols.at(name);
}

SymbolTableEntry *SymbolTable::lookup(const std::string &name) {
  if (symbols.find(name) != symbols.end())
    return &symbols.at(name);
  return nullptr;
}