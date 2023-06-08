#include "SourceFile.h"

#include "ast/ASTNodes.h"
#include "lexer/Lexer.h"
#include "parser/Parser.h"

void SourceFile::parse() {
  Lexer lexer(this);
  Parser parser(this, lexer);
  ASTEntryNode *ast = parser.parse();
}
