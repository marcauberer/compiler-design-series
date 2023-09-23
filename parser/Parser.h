#pragma once

#include <stack>
#include <memory>

#include "../CompilePhase.h"
#include "../ast/ASTNodes.h"
#include "../lexer/Lexer.h"

class Parser : public CompilePhase {
public:
  // Constructor
  Parser(SourceFile *sourceFile, Lexer &lexer)
      : CompilePhase(sourceFile), lexer(lexer) {}

  ASTEntryNode *parse();
  ASTStmtNode *parseStmt();
  ASTDeclStmtNode *parseDeclStmt();
  ASTAdditiveExprNode *parseAdditiveExpr();
  ASTMultiplicativeExprNode *parseMultiplicativeExpr();
  ASTAtomicExprNode *parseAtomicExpr();
  ASTConstantNode *parseConstant();
  ASTPrintCallNode *parsePrintCall();
  ASTDataTypeNode *parseDataType();

private:
  // Private members
  Lexer &lexer;
  std::stack<ASTNode *> parentStack;
  std::vector<std::unique_ptr<ASTNode>> astNodes;

  // Private methods
  template <typename T> T *createNode();
  template <typename T> T *concludeNode(T *node);
};
