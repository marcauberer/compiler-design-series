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
  virtual std::any visitEntry(ASTEntryNode *node);
  virtual std::any visitStmt(ASTStmtNode *node);
  virtual std::any visitDeclStmt(ASTDeclStmtNode *node);
  virtual std::any visitAdditiveExpr(ASTAdditiveExprNode *node);
  virtual std::any visitMultiplicativeExpr(ASTMultiplicativeExprNode *node);
  virtual std::any visitAtomicExpr(ASTAtomicExprNode *node);
  virtual std::any visitConstant(ASTConstantNode *node);
  virtual std::any visitPrintCall(ASTPrintCallNode *node);
  virtual std::any visitDataType(ASTDataTypeNode *node);
};
