#include "SourceFile.h"

/**
 * @brief Entry point to the MathExpr compiler
 *
 * @return int Exit code
 */
int main(void) {
  SourceFile sourceFile("./test.mathexpr");
  std::cout << "Parsing ..." << std::endl;
  sourceFile.parse();
  std::cout << "Create symbol table ..." << std::endl;
  sourceFile.createSymbolTable();
  std::cout << "Type checking ..." << std::endl;
  sourceFile.typeCheck();
  std::cout << "Generating IR code ..." << std::endl;
  sourceFile.generateIR();
  std::cout << "Optimizing IR code ..." << std::endl;
  sourceFile.optimizeIR();
  std::cout << "Emit object file ..." << std::endl;
  sourceFile.emitObject();
  std::cout << "Finished compilation. Executable file emitted." << std::endl;

  return EXIT_SUCCESS;
}
