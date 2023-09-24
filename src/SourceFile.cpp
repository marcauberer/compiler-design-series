#include "SourceFile.h"

#include <cassert>

#include "ast/ASTNodes.h"
#include "irgenerator/IRGenerator.h"
#include "iroptimizer/IROptimizer.h"
#include "lexer/Lexer.h"
#include "objectemitter/ObjectEmitter.h"
#include "parser/Parser.h"
#include "symboltable/SymbolTableBuilder.h"
#include "typechecker/TypeChecker.h"

#include <llvm/MC/TargetRegistry.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/TargetParser/Host.h>
#include <llvm/TargetParser/Triple.h>

SourceFile::SourceFile(const std::filesystem::path &filePath) : filePath(filePath), symbolTable(this) {
  // Initialize the native LLVM target
  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();

  // Search after selected target
  std::string error;
  const std::string targetTriple = llvm::sys::getDefaultTargetTriple();
  const llvm::Target *target = llvm::TargetRegistry::lookupTarget(targetTriple, error);
  if (!target)
    throw std::runtime_error("Selected target was not found: " + error);

  // Create target machine for LLVM
  llvm::TargetOptions opt;
  std::stringstream featureString;
  // Retrieve native CPU name and the supported CPU features
  llvm::StringRef cpuName = llvm::sys::getHostCPUName();
  llvm::StringMap<bool> hostFeatures;
  llvm::sys::getHostCPUFeatures(hostFeatures);
  for (const llvm::StringMapEntry<bool> &feature : hostFeatures) {
    if (featureString.rdbuf()->in_avail() > 0)
      featureString << ",";
    featureString << (feature.second ? "+" : "-") << feature.first().str();
  }

  // Create target machine
  llvm::TargetMachine *targetMachineRaw = target->createTargetMachine(targetTriple, cpuName, featureString.str(), opt, llvm::Reloc::PIC_);
  targetMachine = std::unique_ptr<llvm::TargetMachine>(targetMachineRaw);

  // Create LLVM module for this source file
  llvmModule = std::make_unique<llvm::Module>(filePath.filename().string(), context);
}

void SourceFile::parse() {
  Lexer lexer(this);
  Parser parser(this, lexer);
  ast = parser.parse();
}

void SourceFile::createSymbolTable() {
  SymbolTableBuilder symbolTableBuilder(this);
  assert(ast != nullptr);
  symbolTableBuilder.visit(ast);
}

void SourceFile::typeCheck() {
  TypeChecker typeChecker(this);
  assert(ast != nullptr);
  typeChecker.visit(ast);
}

void SourceFile::generateIR() {
  IRGenerator irGenerator(this);
  assert(ast != nullptr);
  irGenerator.visit(ast);
  std::cout << "Unoptimized IR code: " << irGenerator.getIRString() << std::endl;
}

void SourceFile::optimizeIR() {
  IROptimizer irOptimizer(this, targetMachine.get());
  irOptimizer.prepare();
  irOptimizer.optimize();
  std::cout << "Optimized IR code: " << irOptimizer.getIRString() << std::endl;
}

void SourceFile::emitObject() {
  ObjectEmitter objectEmitter(this, targetMachine.get());
  objectEmitter.emit();
  objectEmitter.link();
}