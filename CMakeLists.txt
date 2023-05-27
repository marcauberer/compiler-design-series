project(MathExprLang)

set(SOURCES
  main.cpp
  SourceFile.cpp
  SourceFile.h
  CompilePhase.h
  lexer/Lexer.cpp
  lexer/Lexer.h)

add_executable(mathexpr ${SOURCES})
