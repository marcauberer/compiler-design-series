#pragma once

#include <cstdint>
#include <string>

#include "../reader/Reader.h"

enum TokenType {
  TOK_INVALID,
  TOK_INT_LIT,
  TOK_DOUBLE_LIT,
  TOK_IDENTIFIER,
  TOK_TYPE_INT,
  TOK_TYPE_DOUBLE,
  TOK_PRINT,
  TOK_ASSIGN,
  TOK_PLUS,
  TOK_MINUS,
  TOK_MUL,
  TOK_DIV,
  TOK_LPAREN,
  TOK_RPAREN,
  TOK_SEMICOLON,
  TOK_EOF
};

struct Token {
  TokenType type;
  std::string text;
  CodeLoc codeLoc;

  explicit Token(TokenType type) : type(type) {}
  Token(TokenType type, const std::string &text, const CodeLoc &codeLoc) : type(type), text(text), codeLoc(codeLoc) {}
  Token(const Token &) = delete;
};
