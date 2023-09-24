#pragma once

#include "../CompilerPass.h"
#include "../ast/ASTVisitor.h"

#include <llvm/Target/TargetMachine.h>

struct ExecResult {
  std::string output;
  int exitCode;
};

class ObjectEmitter : private CompilerPass {
public:
  // Constructors
  ObjectEmitter(SourceFile *sourceFile, llvm::TargetMachine *targetMachine)
      : CompilerPass(sourceFile), llvmModule(*sourceFile->llvmModule), targetMachine(targetMachine) {}

  // Public methods
  void emit() const;
  void link() const;

private:
  // Private members
  llvm::Module &llvmModule;
  llvm::TargetMachine *targetMachine;

  // Private methods
  ExecResult exec(const std::string &cmd) const;
};