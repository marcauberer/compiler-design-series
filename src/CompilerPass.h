#pragma once

#include "SourceFile.h"

class CompilerPass {
public:
  // Constructors
  explicit CompilerPass(SourceFile *sourceFile) : sourceFile(sourceFile) {}

protected:
  // Protected members
  SourceFile *sourceFile;
};