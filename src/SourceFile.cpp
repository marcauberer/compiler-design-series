#include "SourceFile.h"

#include <cassert>

#include "ast/ASTNodes.h"
#include "irgenerator/IRGenerator.h"
#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "symboltable/SymbolTableBuilder.h"
#include "typechecker/TypeChecker.h"

SourceFile::SourceFile(const std::filesystem::path &filePath) : filePath(filePath), symbolTable(this) {
  // Create LLVM module for this source file
  llvmModule = std::make_unique<llvm::Module>(filePath.filename().string(), context);
}

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

void SourceFile::generateIR() {
  IRGenerator irGenerator(this);
  assert(ast != nullptr);
  irGenerator.visit(ast);
}