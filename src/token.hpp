#ifndef _TOKEN_INCLUDE
#define _TOKEN_INCLUDE

#include <any>
#include <variant>
#include "tokentype.hpp"

class Token
{

  public:
  TokenType type;
  std::any data;
  // Constructor
  Token(){}
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

  bool isPlusMinus() {
    return this->type == TokenType::PLUS || this->type == TokenType::MINUS;
  }

  bool isMulDiv() {
    return this->type == TokenType::DIVIDE || this->type == TokenType::MULTIPLY;
  }

  bool isParenToken() {
    return this->type == TokenType::LPAREN || this->type == TokenType::RPAREN;
  }
};

#endif