#pragma once

#include <llvm/Analysis/AliasAnalysis.h>
#include <llvm/Analysis/CGSCCPassManager.h>
#include <llvm/Analysis/LoopAnalysisManager.h>
#include <llvm/Passes/OptimizationLevel.h>
#include <llvm/Passes/PassBuilder.h>

#include "../CompilerPass.h"
#include "../SourceFile.h"

class IROptimizer : private CompilerPass {
public:
  // Constructors
  IROptimizer(SourceFile *sourceFile, llvm::TargetMachine *targetMachine)
      : CompilerPass(sourceFile), llvmModule(sourceFile->llvmModule.get()), targetMachine(targetMachine) {}

  // Public methods
  void prepare();
  void optimize();
  [[nodiscard]] std::string getIRString() const;

private:
  // Private members
  llvm::LoopAnalysisManager loopAnalysisMgr;
  llvm::FunctionAnalysisManager functionAnalysisMgr;
  llvm::CGSCCAnalysisManager cgsccAnalysisMgr;
  llvm::ModuleAnalysisManager moduleAnalysisMgr;
  std::unique_ptr<llvm::PassBuilder> passBuilder;
  llvm::Module *llvmModule;
  llvm::TargetMachine *targetMachine;
};