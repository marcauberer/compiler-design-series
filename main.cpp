#include "SourceFile.h"

/**
 * @brief Entry point to the MathExpr compiler
 *
 * @param argc Argument count
 * @param argv Argument values
 * @return int Exit code
 */
int main(int argc, char **argv) {
  SourceFile mainSourceFile("./test.mathexpr");
  mainSourceFile.runLexer();

  return EXIT_SUCCESS;
}
