#pragma once

#include "SourceFile.h"

class CompilePhase {
public:
  // Constructors
  explicit CompilePhase(SourceFile *sourceFile) : sourceFile(sourceFile) {}

protected:
  // Protected members
  SourceFile *sourceFile;
};