#include "TypeChecker.h"

#include <cassert>
#include <stdexcept>

std::any TypeChecker::visitDeclStmt(ASTDeclStmtNode *node) {
  // Check that the lhs type matches the rhs type
  auto dataType = std::any_cast<SymbolType>(visit(node->dataType()));
  auto initValue = std::any_cast<ExprResult>(visit(node->additiveExpr()));
  if (initValue.type != dataType)
    throw std::runtime_error(node->codeLoc.print() + ": Cannot assign an " + initValue.type.getName() + " value to " +
                             dataType.getName() + " variable");

  // Update type of symbol table entry
  SymbolTableEntry *varEntry = sourceFile->symbolTable.lookup(node->varName);
  assert(varEntry != nullptr);
  varEntry->type = dataType;

  return ExprResult{dataType, varEntry};
}

std::any TypeChecker::visitAdditiveExpr(ASTAdditiveExprNode *node) {
  // Check if at least one additive operator is applied
  if (node->children.size() == 1)
    return visit(node->operands().front());

  // Check that the operands have the same type
  auto lhs = std::any_cast<ExprResult>(visit(node->operands().at(0)));
  auto rhs = std::any_cast<ExprResult>(visit(node->operands().at(1)));
  if (lhs.type != rhs.type)
    throw std::runtime_error(node->codeLoc.print() + ": Cannot apply + operator on " + lhs.type.getName() + " and " +
                             rhs.type.getName());

  return ExprResult{lhs.type};
}

std::any TypeChecker::visitMultiplicativeExpr(ASTMultiplicativeExprNode *node) {
  // Check if at least one additive operator is applied
  if (node->children.size() == 1)
    return visit(node->operands().front());

  // Check that the operands have the same type
  auto lhs = std::any_cast<ExprResult>(visit(node->operands().at(0)));
  auto rhs = std::any_cast<ExprResult>(visit(node->operands().at(1)));
  if (lhs.type != rhs.type)
    throw std::runtime_error(node->codeLoc.print() + ": Cannot apply * operator on " + lhs.type.getName() + " and " +
                             rhs.type.getName());

  return ExprResult{lhs.type};
}

std::any TypeChecker::visitAtomicExpr(ASTAtomicExprNode *node) {
  // Check if constant
  if (node->constant())
    return visit(node->constant());

  // Check if sub expr within parentheses
  if (node->additiveExpr())
    return visit(node->additiveExpr());

  // Identifier (variable access)
  const std::string &name = node->referencedVariableName;
  assert(!name.empty());
  node->referencedEntry = sourceFile->symbolTable.lookup(name);
  if (!node->referencedEntry)
    throw std::runtime_error(node->codeLoc.print() + ": Referenced undefined variable '" + name + "'");
  const SymbolType &varType = node->referencedEntry->type;
  assert(!varType.is(TY_INVALID));

  return ExprResult{varType, node->referencedEntry};
}

std::any TypeChecker::visitConstant(ASTConstantNode *node) {
  if (node->type == ASTConstantNode::TYPE_INT)
    return ExprResult{SymbolType(TY_INT)};
  if (node->type == ASTConstantNode::TYPE_DOUBLE)
    return ExprResult{SymbolType(TY_DOUBLE)};
  assert(false && "TypeChecker - Constant fall-through");
  return nullptr;
}

std::any TypeChecker::visitDataType(ASTDataTypeNode *node) {
  if (node->type == ASTDataTypeNode::TYPE_INT)
    return SymbolType(TY_INT);
  if (node->type == ASTDataTypeNode::TYPE_DOUBLE)
    return SymbolType(TY_DOUBLE);
  assert(false && "TypeChecker - DataType fall-through");
  return nullptr;
}