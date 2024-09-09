#ifndef __PARSER_TYPES
#define __PARSER_TYPES

#include <iostream>
#include <string>
#include <stdexcept>
#include <optional>
#include "token.hpp"


class ParserException : public std::exception {
  public:
  std::string message;

  ParserException(std::string message) {
    this->message = message;
  }

  const char *what () const throw() {
      return message.c_str(); 
  }
};


class Expr {
  public:
  virtual float getValue(){ return -1;}
};


class UnaryExpr : public Expr {
  private:
  Token operate;
  std::unique_ptr<Expr> left;

  UnaryExpr() {}
  public:
  UnaryExpr(std::optional<Token> operate, std::unique_ptr<Expr> &left) {
    this->left = std::move(left);
    this->operate = operate.value();
  }

  float getValue() override {
    if(operate.type == TokenType::MINUS) {
      return - (left->getValue());
    }
    return left->getValue();
  }
};
class Literal : public Expr {
  private:
  Token tok;

  Literal() {}

  public:
  Literal(std::optional<Token> tok) {
    this->tok = std::move(tok.value());
  }

  float getValue() override {
    std::string stringVal = std::any_cast<std::string>(tok.data);
    return std::stod(stringVal);
  }
};

class BinaryExpr : public Expr {
  private:
  std::unique_ptr<Expr> left;
  Token operate;
  std::unique_ptr<Expr> right;

  BinaryExpr() {}
  
  public:
  BinaryExpr(std::unique_ptr<Expr> &left, std::optional<Token> operate, std::unique_ptr<Expr> &right) {
    this->left = std::move(left);
    this->operate = operate.value();
    this->right = std::move(right);
  }

  float getValue() override {
    switch(operate.type) {
      case TokenType::PLUS:
        return this->left->getValue() + this->right->getValue();
        break;
      case TokenType::MINUS:
        return this->left->getValue() - this->right->getValue();
        break;
      case TokenType::MULTIPLY:
        return this->left->getValue() * this->right->getValue();
        break;
      case TokenType::DIVIDE:
        return this->left->getValue() / this->right->getValue();
        break;
      default:
        throw ParserException("Invalid Operator Token");
        break;
    }
  }
};

#endif