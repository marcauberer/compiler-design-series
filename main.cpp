#include "SourceFile.h"

#include <iostream>

/**
 * @brief Entry point to the MathExpr compiler
 *
 * @param argc Argument count
 * @param argv Argument values
 * @return int Exit code
 */
int main(int argc, char **argv) {
  SourceFile mainSourceFile("./test.mathexpr");
  std::cout << "Parsing ..." << std::endl;
  mainSourceFile.parse();
  std::cout << "Type checking ..." << std::endl;

  return EXIT_SUCCESS;
}
