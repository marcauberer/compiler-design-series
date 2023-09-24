#include "IROptimizer.h"

#include <llvm/Transforms/IPO/AlwaysInliner.h>

void IROptimizer::prepare() {
  passBuilder = std::make_unique<llvm::PassBuilder>(targetMachine);

  functionAnalysisMgr.registerPass([&] { return passBuilder->buildDefaultAAPipeline(); });

  passBuilder->registerModuleAnalyses(moduleAnalysisMgr);
  passBuilder->registerCGSCCAnalyses(cgsccAnalysisMgr);
  passBuilder->registerFunctionAnalyses(functionAnalysisMgr);
  passBuilder->registerLoopAnalyses(loopAnalysisMgr);
  passBuilder->crossRegisterProxies(loopAnalysisMgr, functionAnalysisMgr, cgsccAnalysisMgr, moduleAnalysisMgr);
}

void IROptimizer::optimize() {
  assert(passBuilder != nullptr);

  // Run passes
  llvm::OptimizationLevel llvmOptLevel = llvm::OptimizationLevel::O2; // Adjust here, if you want to change to optmization level
  llvm::ModulePassManager modulePassMgr = passBuilder->buildPerModuleDefaultPipeline(llvmOptLevel);
  modulePassMgr.addPass(llvm::AlwaysInlinerPass());
  modulePassMgr.run(*llvmModule, moduleAnalysisMgr);
}

std::string IROptimizer::getIRString() const {
  std::string output;
  llvm::raw_string_ostream oss(output);
  llvmModule->print(oss, nullptr);
  return oss.str();
}