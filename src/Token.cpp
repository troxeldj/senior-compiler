#include <any>
#include <variant>
#include "Token.hpp"

  Token::Token(TokenType tType, std::any data) {
    this->type = tType;
    this->data = data;
  }

  Token::Token(const Token& other) {
    this->data = other.data;
    this->type = other.type;
  }

  bool Token::isNumberToken() {
    return this->type == TokenType::INT || this->type == TokenType::FLOAT;
  }

  bool Token::isOperatorToken() {
    return this->type == TokenType::PLUS || this->type == TokenType::MINUS || this->type == TokenType::DIVIDE || this->type == TokenType::MULTIPLY;
  }

  bool Token::isPlusMinus() {
    return this->type == TokenType::PLUS || this->type == TokenType::MINUS;
  }

  bool Token::isMulDiv() {
    return this->type == TokenType::DIVIDE || this->type == TokenType::MULTIPLY;
  }

  bool Token::isParenToken() {
    return this->type == TokenType::LPAREN || this->type == TokenType::RPAREN;
  }
