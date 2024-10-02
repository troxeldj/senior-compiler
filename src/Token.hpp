#ifndef __TOKEN_HPP
#define __TOKEN_HPP

#include <any>
#include <variant>
#include "TokenType.hpp"

class Token
{

  public:
  TokenType type;
  std::any data;
  // Constructor
  Token(){}
  Token(TokenType, std::any);
  Token(const Token&);

  bool isNumberToken();
  bool isOperatorToken();
  bool isPlusMinus();
  bool isMulDiv();
  bool isParenToken();
};

#endif