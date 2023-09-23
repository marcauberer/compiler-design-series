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

  return EXIT_SUCCESS;
}
