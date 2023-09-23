#pragma once

#include "../CompilerPass.h"
#include "../reader/Reader.h"
#include "Token.h"

class Lexer : public CompilerPass {
public:
  // Constructor
  explicit Lexer(SourceFile *sourceFile);

  // Public methods
  const Token &getToken() const;
  void advance();
  void expect(TokenType expectedType);
  void expectOneOf(const std::initializer_list<TokenType> &expectedTypes);
  bool isEOF() const;
  CodeLoc getCodeLoc() const;

private:
  // Private members
  Reader reader = Reader(sourceFile->filePath.c_str());
  Token curTok = Token(TOK_INVALID);

  // Private methods
  Token consumeToken();
  Token consumeNumber();
  Token consumeKeywordOrIdentifier();
  Token consumeSemicolon();
};
