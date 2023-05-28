#pragma once

#include <fstream>
#include <iostream>

struct CodeLoc {
  uint64_t line;
  uint64_t column;

  [[nodiscard]] std::string print() const;
};

class Reader {
public:
  // Constructors
  explicit Reader(const char *filePath);

  // Public methods
  char getChar() const;
  CodeLoc getCodeLoc() const;
  void advance();
  void expect(char c);

private:
  // Private members
  std::ifstream input;
  char curChar = '\0';
  CodeLoc curCodeLoc{1ull, 0ull};
};