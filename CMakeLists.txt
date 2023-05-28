project(MathExprLang)

set(SOURCES
  main.cpp
  SourceFile.cpp
  SourceFile.h
  CompilePhase.h
  reader/Reader.cpp
  reader/Reader.h
  lexer/Lexer.cpp
  lexer/Lexer.h
  parser/Parser.cpp
  parser/Parser.h)

add_executable(mathexpr ${SOURCES})
