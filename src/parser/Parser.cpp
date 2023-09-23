#include "Parser.h"

#include <assert.h>

ASTEntryNode *Parser::parse() {
  ASTEntryNode *entryNode = createNode<ASTEntryNode>();

  while (lexer.getToken().type != TOK_EOF) {
    parseStmt();
  }

  return concludeNode(entryNode);
}

ASTStmtNode *Parser::parseStmt() {
  ASTStmtNode *stmtNode = createNode<ASTStmtNode>();

  // SELECT(stmt) = { TOK_TYPE_INT, TOK_TYPE_DOUBLE, TOK_PRINT }
  const TokenType curTok = lexer.getToken().type;

  if (curTok == TOK_TYPE_INT || curTok == TOK_TYPE_DOUBLE) // TOK_TYPE_INT, TOK_TYPE_DOUBLE -> declStmt
    parseDeclStmt();
  else if (curTok == TOK_PRINT) // TOK_PRINT -> printCall
    parsePrintCall();

  lexer.expect(TOK_SEMICOLON);

  return concludeNode(stmtNode);
}

ASTDeclStmtNode *Parser::parseDeclStmt() {
  ASTDeclStmtNode *declStmtNode = createNode<ASTDeclStmtNode>();

  // Parse
  parseDataType();
  const Token &token = lexer.getToken();
  declStmtNode->varName = token.text;
  lexer.expect(TOK_IDENTIFIER);
  lexer.expect(TOK_ASSIGN);
  parseAdditiveExpr();

  return concludeNode(declStmtNode);
}

ASTAdditiveExprNode *Parser::parseAdditiveExpr() {
  ASTAdditiveExprNode *additiveExprNode = createNode<ASTAdditiveExprNode>();

  // Parse first operand
  parseMultiplicativeExpr();

  const TokenType curTok = lexer.getToken().type;
  if (curTok == TOK_PLUS || curTok == TOK_MINUS) {
    // Parse operator
    if (curTok == TOK_PLUS) {
      additiveExprNode->op = ASTAdditiveExprNode::OP_PLUS;
    } else if (curTok == TOK_MINUS) {
      additiveExprNode->op = ASTAdditiveExprNode::OP_MINUS;
    }
    lexer.expectOneOf({TOK_PLUS, TOK_MINUS});

    // Parse second operand
    parseMultiplicativeExpr();
  }

  return concludeNode(additiveExprNode);
}

ASTMultiplicativeExprNode *Parser::parseMultiplicativeExpr() {
  ASTMultiplicativeExprNode *additiveExprNode = createNode<ASTMultiplicativeExprNode>();

  // Parse first operand
  parseAtomicExpr();

  const TokenType curTok = lexer.getToken().type;
  if (curTok == TOK_MUL || curTok == TOK_DIV) {
    // Parse operator
    if (curTok == TOK_MUL) {
      additiveExprNode->op = ASTMultiplicativeExprNode::OP_MUL;
    } else if (curTok == TOK_DIV) {
      additiveExprNode->op = ASTMultiplicativeExprNode::OP_DIV;
    }
    lexer.expectOneOf({TOK_MUL, TOK_DIV});

    // Parse second operand
    parseAtomicExpr();
  }

  return concludeNode(additiveExprNode);
}

ASTAtomicExprNode *Parser::parseAtomicExpr() {
  ASTAtomicExprNode *atomicExprNode = createNode<ASTAtomicExprNode>();

  // SELECT(atomicExpr) = { TOK_INT_LIT, TOK_DOUBLE_LIT, TOK_IDENTIFIER, TOK_LPAREN }
  const TokenType curTok = lexer.getToken().type;

  if (curTok == TOK_INT_LIT || curTok == TOK_DOUBLE_LIT) { // TOK_INT_LIT, TOK_DOUBLE_LIT -> constant
    parseConstant();
  } else if (curTok == TOK_IDENTIFIER) { // TOK_IDENTIFIER
    atomicExprNode->referencedVariableName = lexer.getToken().text;
    lexer.expect(TOK_IDENTIFIER); // Consume IDENTIFIER
  } else if (curTok == TOK_LPAREN) { // TOK_LPAREN
    lexer.expect(TOK_LPAREN); // Consume LPAREN
    parseAdditiveExpr();
    lexer.expect(TOK_RPAREN); // Consume RPAREN
  }

  return concludeNode(atomicExprNode);
}

ASTConstantNode *Parser::parseConstant() {
  ASTConstantNode *constantNode = createNode<ASTConstantNode>();

  const Token &curTok = lexer.getToken();
  if (curTok.type == TOK_INT_LIT) {
    constantNode->type = ASTConstantNode::TYPE_INT;
    constantNode->compileTimeVaue.intValue = std::stoi(curTok.text);
  } else if (curTok.type == TOK_DOUBLE_LIT) {
    constantNode->type = ASTConstantNode::TYPE_DOUBLE;
    constantNode->compileTimeVaue.doubleValue = std::stod(curTok.text);
  }
  lexer.expectOneOf({TOK_INT_LIT, TOK_DOUBLE_LIT});

  return concludeNode(constantNode);
}

ASTPrintCallNode *Parser::parsePrintCall() {
  ASTPrintCallNode *printCallNode = createNode<ASTPrintCallNode>();

  // Parse
  lexer.expect(TOK_PRINT);
  lexer.expect(TOK_LPAREN);
  parseAdditiveExpr();
  lexer.expect(TOK_RPAREN);

  return concludeNode(printCallNode);
}

ASTDataTypeNode *Parser::parseDataType() {
  ASTDataTypeNode *dataTypeNode = createNode<ASTDataTypeNode>();

  const TokenType curTok = lexer.getToken().type;
  if (curTok == TOK_TYPE_INT) {
    dataTypeNode->type = ASTDataTypeNode::TYPE_INT;
  } else if (curTok == TOK_TYPE_DOUBLE) {
    dataTypeNode->type = ASTDataTypeNode::TYPE_DOUBLE;
  }
  lexer.expectOneOf({TOK_TYPE_INT, TOK_TYPE_DOUBLE});

  return concludeNode(dataTypeNode);
}

template <typename T> T *Parser::createNode() {
  ASTNode *parent = nullptr;
  if constexpr (!std::is_same_v<T, ASTEntryNode>)
    parent = parentStack.top();

  // Create the new node
  sourceFile->astNodes.push_back(std::make_unique<T>(parent, lexer.getCodeLoc()));
  T *node = static_cast<T *>(sourceFile->astNodes.back().get());

  // If this is not the entry node, we need to add the new node to its parent
  if constexpr (!std::is_same_v<T, ASTEntryNode>)
    parent->addChild(node);

  // This node is the parent for its children
  parentStack.push(node);

  return node;
}

template <typename T> T *Parser::concludeNode(T *node) {
  // This node is no longer the parent for its children
  assert(parentStack.top() == node);
  parentStack.pop();

  return node;
}