#include "ASTVisitor.h"

#include "../ast/ASTNodes.h"

std::any ASTVisitor::visit(ASTNode *node) { return node->accept(this); }

std::any ASTVisitor::visitChildren(ASTNode *node) {
  for (ASTNode *child : node->children)
    if (child != nullptr)
      child->accept(this);
  return nullptr;
}

std::any ASTVisitor::visitEntry(ASTEntryNode *node) { return visitChildren(node); };

std::any ASTVisitor::visitStmt(ASTStmtNode *node) { return visitChildren(node); };

std::any ASTVisitor::visitDeclStmt(ASTDeclStmtNode *node) { return visitChildren(node); };

std::any ASTVisitor::visitAdditiveExpr(ASTAdditiveExprNode *node) { return visitChildren(node); };

std::any ASTVisitor::visitMultiplicativeExpr(ASTMultiplicativeExprNode *node) { return visitChildren(node); };

std::any ASTVisitor::visitAtomicExpr(ASTAtomicExprNode *node) { return visitChildren(node); };

std::any ASTVisitor::visitConstant(ASTConstantNode *node) { return visitChildren(node); };

std::any ASTVisitor::visitPrintCall(ASTPrintCallNode *node) { return visitChildren(node); };

std::any ASTVisitor::visitDataType(ASTDataTypeNode *node) { return visitChildren(node); };
