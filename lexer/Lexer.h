#pragma once

#include "../CompilePhase.h"
#include "../reader/Reader.h"
#include "Token.h"

class Lexer : public CompilePhase {
public:
  // Constructor
  explicit Lexer(SourceFile *sourceFile) : CompilePhase(sourceFile) {}

  // Public methods
  Token getToken() const;
  void advance();
  void expect(TokenType token);

private:
  // Private members
  Reader reader = Reader(sourceFile->filePath.c_str());
  Token curTok;

  // Private methods
  Token consumeToken();
  Token consumeNumber();
  Token consumeKeywordOrIdentifier();
  Token consumeSemicolon();
};
