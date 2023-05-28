#include "Reader.h"

#include <cassert>

Reader::Reader(const char *filePath) {
  input = std::ifstream(filePath);
  assert(input.is_open());

  // Read first character
  advance();
}

/**
 * @brief Get the previously read character
 *
 * @return char Last character
 */
char Reader::getChar() const { return curChar; }

/**
 * @brief Get the code location of the previously read character
 *
 * @return CodeLoc Code location
 */
CodeLoc Reader::getCodeLoc() const { return curCodeLoc; }

/**
 * @brief Advance the reader by one character
 */
void Reader::advance() {
  input.get(curChar);
  if (curChar == '\n') {
    curCodeLoc.line++;
    curCodeLoc.column = 0;
  }
  curCodeLoc.column++;
}

/**
 * @brief Advance the reader by one character and check if this char equals the
 * expected
 *
 * @param c Expected char
 */
void Reader::expect(char c) {
  advance();
  assert(curChar == c);
}