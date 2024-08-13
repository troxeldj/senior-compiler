#ifndef _TOKEN_INCLUDE
#define _TOKEN_INCLUDE

#include "tokentype.hpp"
#include <any>
#include <variant>


class Token {
private:
  TokenType type;
  std::any data;
public: 
  // Constructor
  Token(TokenType type, std::any data) {
    this->type = type;
    this->data = data;
  }
};

#endif
