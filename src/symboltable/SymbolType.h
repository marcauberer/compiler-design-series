#pragma once

#include <initializer_list>
#include <string>

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

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
  [[nodiscard]] llvm::Type *toLLVMType(llvm::LLVMContext &context) const;

  // Overloaded operators
  friend bool operator==(const SymbolType &lhs, const SymbolType &rhs);
  friend bool operator!=(const SymbolType &lhs, const SymbolType &rhs);

private:
  // Private members
  SymbolSuperType superType;
};