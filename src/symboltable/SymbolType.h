#pragma once

#include <string>
#include <initializer_list>

enum SymbolSuperType {
  TY_INVALID,
  TY_INT,
  TY_DOUBLE,
};

class SymbolType {
public:
  // Constructor
  explicit SymbolType(SymbolSuperType superType) : superType(superType) {}

  // Public methods
  [[nodiscard]] bool is(SymbolSuperType superType) const;
  [[nodiscard]] bool isOneOf(const std::initializer_list<SymbolSuperType> &superTypes) const;
  [[nodiscard]] std::string getName() const;

  // Overloaded operators
  friend bool operator==(const SymbolType &lhs, const SymbolType &rhs);
  friend bool operator!=(const SymbolType &lhs, const SymbolType &rhs);

private:
  // Private members
  SymbolSuperType superType;
};