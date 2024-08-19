#ifndef PARSER_HPP
#define PARSER_HPP
#include <vector>
#include <optional>
#include "token.hpp"
#include <stdexcept>

#define TokExpr std::variant<std::optional<Token>, Expr>


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

class Expr{};


class BinaryExpr : public Expr {
public:
  TokExpr left;
  TokExpr operate;
  TokExpr right;

  BinaryExpr(TokExpr left, TokExpr operate, TokExpr right) : Expr() {
    this->left = left;
    this->operate = operate;
    this->right = right;
  } 
};


class UnaryExpr : public Expr {
public:
  TokExpr left;
  TokExpr operate;

  UnaryExpr(TokExpr left, TokExpr operate) : Expr() {
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

  bool isBinaryOp() {
    return currentToken() && currentToken()->isNumberToken() && peek(1) && peek(1)->isOperatorToken() && peek(2) && peek(2)->isNumberToken();
  }

  bool isUnaryOp() {
    return currentToken() && currentToken()->isOperatorToken() && peek(1) && peek(1)->isNumberToken();
  }

  std::optional<Token> currentToken() {
    return this->tokens[this->curIndex];
  }

  TokExpr parseProgram() 
  {
    // check for valid expression
    TokExpr expr;

    expr = parseExpr();
    return expr;
  }

  TokExpr parseBinaryExpr() {
    TokExpr left = parseFact();
    TokExpr operate;
    TokExpr right; 
    bool needsOp = false;

    if(hasNextToken() && (currentToken()->type == TokenType::PLUS || currentToken()->type == TokenType::MINUS)){
      needsOp = true;
      operate = consume();
      right = parseFact();
    }

    if(!needsOp) {
      return left; 
    }
    return BinaryExpr(left, operate, right);
  }

  TokExpr parseUnaryExpr() {
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

  TokExpr parseExpr() {
    if(isBinaryOp()) {
      return parseBinaryExpr();
    } else if(isUnaryOp()) {
      return parseUnaryExpr();
    } else {
      throw ParserException("Expected Expression.");
    }
  }

  bool checkToken(std::optional<Token> tok, TokenType tType) {
    return tok != std::nullopt && tok->type == tType;
  }

  std::variant<std::optional<Token>, Expr> parseFact() {
    TokExpr left = parseParen();
    TokExpr operate = std::nullopt;
    TokExpr right = std::nullopt;
    bool needsOp = false;

    if(hasNextToken() && (currentToken()->type == TokenType::DIVIDE || currentToken()->type == TokenType::MULTIPLY)){
      needsOp = true;
      operate = consume();
      right = parseParen();
    }
    if(!needsOp) {
      return left;
    }
    return BinaryExpr(left, operate, right);
  }

  TokExpr parseParen() {
    bool isExpr = false;
    TokExpr retVal; 
    if(currentToken()->isParenToken()) {
      isExpr = true;
      consume();
      retVal = parseExpr();
      if(currentToken()->type != TokenType::RPAREN) {
        throw ParserException("Expected closing paren.");
      }
    } else {
      retVal = parseTerm();
    }
    return retVal; 
  }

  std::optional<Token> parseTerm() {
    return consume();
  }

  
};



#endif