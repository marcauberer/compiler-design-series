#pragma once

#include <any>

// Forward declarations
class ASTNode;
class ASTEntryNode;
class ASTStmtNode;
class ASTDeclStmtNode;
class ASTAdditiveExprNode;
class ASTMultiplicativeExprNode;
class ASTAtomicExprNode;
class ASTConstantNode;
class ASTPrintCallNode;
class ASTDataTypeNode;

class ASTVisitor {
public:
  // General visitor method
  std::any visit(ASTNode *node);
  std::any visitChildren(ASTNode *node);

  // Visitor methods
  virtual std::any visitEntry(ASTEntryNode *node) = 0;
  virtual std::any visitStmt(ASTStmtNode *node) = 0;
  virtual std::any visitDeclStmt(ASTDeclStmtNode *node) = 0;
  virtual std::any visitAdditiveExpr(ASTAdditiveExprNode *node) = 0;
  virtual std::any visitMultiplicativeExpr(ASTMultiplicativeExprNode *node) = 0;
  virtual std::any visitAtomicExpr(ASTAtomicExprNode *node) = 0;
  virtual std::any visitCosntant(ASTConstantNode *node) = 0;
  virtual std::any visitPrintCall(ASTPrintCallNode *node) = 0;
  virtual std::any visitDataType(ASTDataTypeNode *node) = 0;
};
