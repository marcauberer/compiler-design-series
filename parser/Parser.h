#pragma once

#include "../CompilePhase.h"
#include "../lexer/Lexer.h"

class Parser : public CompilePhase {
public:
  // Constructor
  Parser(SourceFile *sourceFile, Lexer &lexer)
      : CompilePhase(sourceFile), lexer(lexer) {}

private:
  // Private members
  Lexer &lexer;
};
