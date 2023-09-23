#include "SymbolType.h"

#include <algorithm>
#include <cassert>

bool SymbolType::is(SymbolSuperType superType) const { return this->superType == superType; }

bool SymbolType::isOneOf(const std::initializer_list<SymbolSuperType> &superTypes) const {
  const SymbolSuperType &superType = this->superType;
  return std::any_of(superTypes.begin(), superTypes.end(), [&superType](int type) { return type == superType; });
}

std::string SymbolType::getName() const {
  if (superType == TY_INT)
    return "int";
  else if (superType == TY_DOUBLE)
    return "double";
  else
    assert(false && "Unknown super type");
}

bool operator==(const SymbolType &lhs, const SymbolType &rhs) { return lhs.superType == rhs.superType; }

bool operator!=(const SymbolType &lhs, const SymbolType &rhs) { return !(lhs == rhs); }
