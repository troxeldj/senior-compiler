#ifndef _TOKEN_INCLUDE
#define _TOKEN_INCLUDE

#include "tokentype.hpp"
#include <any>
#include <variant>


class Token {
public: 
  TokenType type;
  std::any data;
  // Constructor
  Token(TokenType type, std::any data) {
    this->type = type;
    this->data = data;
  }
};

#endif
