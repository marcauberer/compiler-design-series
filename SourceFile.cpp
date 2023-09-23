#include "SourceFile.h"

#include <cassert>

#include "ast/ASTNodes.h"
#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "typechecker/TypeChecker.h"
#include "symboltable/SymbolTableBuilder.h"

void SourceFile::parse() {
  Lexer lexer(this);
  Parser parser(this, lexer);
  ast = parser.parse();
}

void SourceFile::createSymbolTable() {
  SymbolTableBuilder symbolTableBuilder(this);
  assert(ast != nullptr);
  symbolTableBuilder.visit(ast);
}

void SourceFile::typeCheck() {
  TypeChecker typeChecker(this);
  assert(ast != nullptr);
  typeChecker.visit(ast);
}