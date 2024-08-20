#ifndef PARSER_HPP
#define PARSER_HPP
#include <vector>
#include <optional>
#include "token.hpp"
#include <stdexcept>

#define ParserTypes std::variant<UnaryExpr, BinaryExpr, Literal>


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

class Expr{
  public:

  std::optional<Token> left;
  std::optional<Token> operate;
  std::optional<Token> right;

  Expr() = default;
  Expr(std::optional<Token> left) {
    this->left = left;
    this->operate = std::nullopt;
    this->right = std::nullopt;
  }
  Expr(std::optional<Token> left, std::optional<Token> operate) {
    this->left = left;
    this->operate = operate;
    this->right = std::nullopt;
  }

  Expr(std::optional<Token> left, std::optional<Token> operate, std::optional<Token> right) {
    this->left = left;
    this->operate = operate;
    this->right = right;
  }
};

class Literal : public Expr {
  public:

  Literal(std::optional<Token> tok) : Expr(tok) {
  }
};

class Statement{};


class BinaryExpr : public Expr {
public:

  Expr left;
  std::optional<Token> operate;
  Expr right;  

  BinaryExpr(std::optional<Token> left, std::optional<Token> operate, std::optional<Token> right) : Expr (left, operate, right) {
  }


  BinaryExpr(Expr left, std::optional<Token> operate, Expr right) {
    this->left = left;
    this->operate = operate;
    this->right = right;
  }
};


class UnaryExpr : public Expr {
public:
  Expr left;
  std::optional<Token> operate;

  UnaryExpr(std::optional<Token> left, std::optional<Token> operate) : Expr(left, operate)  {

  }

  UnaryExpr(Expr left, std::optional<Token> operate) {
    this->left = left;
    this->operate = operate;
  }
};

class NumLit : public Expr {
public:
  std::optional<Token> tok;
  NumLit(std::optional<Token> tok) : Expr() {
    this->tok = tok;
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

  bool isBinaryOp() {
    return currentToken() && currentToken()->isNumberToken() && peek(1) && peek(1)->isOperatorToken() && peek(2) && peek(2)->isNumberToken();
  }

  bool isUnaryOp() {
    return currentToken() && currentToken()->isOperatorToken() && peek(1) && peek(1)->isNumberToken();
  }

  std::optional<Token> currentToken() {
    return this->tokens[this->curIndex];
  }

  Expr parseProgram() {
    return parseExpr();
  }

  Expr parseExpr() {
    if(isBinaryOp())
      return parseBinaryExpr();
    else if (isUnaryOp())
      return parseUnaryExpr();
    else
      throw ParserException("Expected Expr");
  }

  UnaryExpr parseUnaryExpr() {
    std::optional<Token> operate = consume();
    Expr left = parseFact();
    return UnaryExpr(left, operate);
  }

  Expr parseBinaryExpr() {
      Expr left = parseFact();
      if(currentToken()->isPlusMinus()) {
        std::optional<Token> operate = consume();
        Expr right = parseFact();
        return BinaryExpr(left, operate, right);
      }
      return left;
  }

  Expr parseFact() {
   Expr left = parseParen(); 
   if(currentToken()->isMulDiv()) {
    std::optional<Token> operate = consume();
    Expr right = parseParen();
    return BinaryExpr(left, operate, right);
   }
   return left;
  }

  Expr parseParen() {
    Expr retExpr;
    if(currentToken()->type == TokenType::LPAREN) {
      retExpr = parseExpr();
      return retExpr;
    }
   std::optional<Token> term = parseTerm();
   return Literal(term);
  }

  std::optional<Token> parseTerm() {
    if(currentToken() == std::nullopt || !currentToken()->isNumberToken()) {
      throw ParserException("Expected Number.");
    }
    return consume();
  }
};

#endif