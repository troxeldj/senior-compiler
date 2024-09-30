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
  std::string type;
  Literal() {}

  public:
  Literal(std::optional<Token> tok) {
    this->tok = std::move(tok.value());
    this->type = this->tok.type;
  }

  std::string getType() {
    return this->type;
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

class VarDecl : public Expr {
  std::string name;
  std::string dataType;
  std::unique_ptr<Expr> expr;

  VarDecl() {}

  public:
  float getValue() override { 
  }

  std::string getName() {
    return this->name;
  }

  std::unique_ptr<Expr> getExpr() {
    return std::move(this->expr);
  }

  VarDecl(std::string name, std::unique_ptr<Expr> expr) : 
    name{name}, expr{std::move(expr)} {}

  VarDecl(std::string name, std::string dataType, std::unique_ptr<Expr> expr) : 
    name{name}, dataType{dataType}, expr{std::move(expr)} {}
};

#endif