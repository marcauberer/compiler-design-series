#include "ASTVisitor.h"

#include "../ast/ASTNodes.h"

std::any ASTVisitor::visit(ASTNode *node) { return node->accept(this); }

std::any ASTVisitor::visitChildren(ASTNode *node) {
  for (ASTNode *child : node->children)
    if (child != nullptr)
      child->accept(this);
  return nullptr;
}