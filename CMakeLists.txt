cmake_minimum_required(VERSION 3.17)
project(MathExprLang)
set(CMAKE_CXX_STANDARD 20)

# Enable pedantic mode and treat warnings as errors
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(
        -Wall               # Enable most common warnings
        -Wextra             # Enable extra warnings
        -pedantic           # Enable pedantic mode
        -Werror             # Treat warnings as errors
    )
endif()

set(SOURCES
  main.cpp
  CompilerPass.h
  SourceFile.cpp
  SourceFile.h
  reader/CodeLoc.cpp
  reader/CodeLoc.h
  reader/Reader.cpp
  reader/Reader.h
  lexer/Lexer.cpp
  lexer/Lexer.h
  ast/ASTNodes.h
  ast/ASTVisitor.cpp
  ast/ASTVisitor.h
  parser/Parser.cpp
  parser/Parser.h
  symboltable/SymbolType.cpp
  symboltable/SymbolType.h
  symboltable/SymbolTableEntry.cpp
  symboltable/SymbolTableEntry.h
  symboltable/SymbolTable.cpp
  symboltable/SymbolTable.h
  symboltable/SymbolTableBuilder.cpp
  symboltable/SymbolTableBuilder.h
  typechecker/TypeChecker.cpp
  typechecker/TypeChecker.h)

add_executable(mathexpr ${SOURCES})
