#pragma once

#include <stack>
#include <memory>

#include "../CompilerPass.h"
#include "../ast/ASTNodes.h"
#include "../lexer/Lexer.h"

class Parser : public CompilerPass {
public:
  // Constructor
  Parser(SourceFile *sourceFile, Lexer &lexer)
      : CompilerPass(sourceFile), lexer(lexer) {}

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

  // Private methods
  template <typename T> T *createNode();
  template <typename T> T *concludeNode(T *node);
};
