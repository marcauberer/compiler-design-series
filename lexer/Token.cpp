#include "Token.h"

std::string CodeLoc::print() const {
  return "L" + std::to_string(line) + "C" + std::to_string(column);
}
