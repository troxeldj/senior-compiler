#ifndef _TOKEN_INCLUDE
#define _TOKEN_INCLUDE

#include "tokentype.hpp"
#include <any>
#include <variant>

class Token
{
public:
  TokenType type;
  std::any data;
  // Constructor
  Token() = default;
  Token(TokenType type, std::any data)
  {
    this->type = type;
    this->data = data;
  }

  bool isNumberToken()
  {
    return this->type == TokenType::INT || this->type == TokenType::FLOAT;
  }

  bool isOperatorToken()
  {
    return this->type == TokenType::PLUS || this->type == TokenType::MINUS || this->type == TokenType::DIVIDE || this->type == TokenType::MULTIPLY;
  }

  bool isFactToken() {
    return this->type == TokenType::PLUS || this->type == TokenType::MINUS;
  }

  bool isParenToken() {
    return this->type == TokenType::LPAREN || this->type == TokenType::RPAREN;
  }
};

#endif
