#pragma once

#include <string>

class SourceFile {
public:
  // Constructor
  SourceFile(const std::string &filePath) : filePath(filePath) {}

  // Public methods
  void runLexer();

  // Public members
  std::string filePath;
};