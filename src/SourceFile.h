#pragma once

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

#include "symboltable/SymbolTable.h"

class SourceFile {
public:
  // Constructor
  SourceFile(const std::filesystem::path &filePath);

  // Public methods
  void parse();
  void createSymbolTable();
  void typeCheck();
  void generateIR();

  // Public members
  std::filesystem::path filePath;
  SymbolTable symbolTable;
  std::vector<std::unique_ptr<ASTNode>> astNodes;
  llvm::LLVMContext context;
  std::unique_ptr<llvm::Module> llvmModule;

private:
  // Private members
  ASTEntryNode *ast = nullptr;
};