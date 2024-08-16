#ifndef PARSER_HPP
#define PARSER_HPP
#include <vector>
#include <optional>
#include "token.hpp"
#include <stdexcept>

#define Expr std::variant<BinaryExpr, UnaryExpr>

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


class BinaryExpr {
public:
  std::optional<Token> left;
  std::optional<Token> operate;
  std::optional<Token> right;

  BinaryExpr(std::optional<Token> &left, std::optional<Token> operate, std::optional<Token> right) {
    this->left = left;
    this->operate = operate;
    this->right = right;
  } 
};


class UnaryExpr {
public:
  std::optional<Token> left;
  std::optional<Token> operate;

  UnaryExpr(std::optional<Token> left, std::optional<Token> operate) {
    this->left = left;
    this->operate = operate;
  }
};


class Parser
{
private:
  std::vector<std::optional<Token>> tokens;
  int curIndex;
  int tokLen;

public:
  Parser(std::vector<std::optional<Token>> tokens)
  {
    this->tokens = tokens;
    curIndex = 0;
    tokLen = tokens.size();
  }


  bool hasNextToken() {
    return (this->curIndex + 1) < this->tokLen;
  }


  bool isAtEnd()
  {
    return this->curIndex >= tokLen;
  }

  std::optional<Token> consume()
  {
    if (isAtEnd())
    {
      return std::nullopt;
    }
    return this->tokens[this->curIndex++];
  }

  std::optional<Token> peek(int num = 1)
  {
    if (this->curIndex + num >= this->tokLen)
    {
      return std::nullopt;
    }
    return this->tokens[this->curIndex + num];
  }

  std::optional<Token> currentToken() {
    return this->tokens[this->curIndex];
  }


  Expr parseProgram()
  {
    while(!isAtEnd()) {

    }
  }
  

  BinaryExpr parseBinaryExpr() {
    std::optional<Token> left = consume();
    if(!hasNextToken() || !left->isNumberToken()) {
      throw ParserException("Expected number");
    }
    std::optional<Token> operate = consume();
    std::optional<Token> right = consume();
    if(!right->isNumberToken()) {
      throw ParserException("Expected number");
    }

    return BinaryExpr(left, operate, right);
  }

  UnaryExpr parseUnaryExpr() {
    std::optional<Token> left = consume();
    if(!hasNextToken() || !left->isOperatorToken()) {
      throw ParserException("Expected operator");
    }
    std::optional<Token> operate = consume();
    if(!hasNextToken() || !operate->isNumberToken()) {
      throw ParserException("Expected number");
    }

    return UnaryExpr(left, operate);
  }
};



#endif