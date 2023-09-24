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
  typechecker/TypeChecker.h
  irgenerator/IRGenerator.cpp
  irgenerator/IRGenerator.h
  iroptimizer/IROptimizer.cpp
  iroptimizer/IROptimizer.h
  objectemitter/ObjectEmitter.cpp
  objectemitter/ObjectEmitter.h)

add_executable(mathexpr ${SOURCES})

target_link_libraries(mathexpr ${LLVM_LIBS})
add_library(mathexprlib STATIC ${SOURCES})

# Add additional definitions
IF (WIN32)
    ADD_DEFINITIONS(-DOS_WINDOWS)
ELSE()
    ADD_DEFINITIONS(-DOS_UNIX)
ENDIF()