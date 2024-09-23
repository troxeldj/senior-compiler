#ifndef PARSER_HPP
#define PARSER_HPP
#include <vector>
#include <optional>
#include <stdexcept>
#include <memory>
#include "token.hpp"
#include "ParserTypes.hpp"

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

  bool isTerm() {
    return (currentToken()->type == TokenType::INT || currentToken()->type == TokenType::FLOAT) && (peek() == std::nullopt || peek()->type == TokenType::_EOF);
  }

  std::optional<Token> currentToken() {
    return this->tokens[this->curIndex];
  }

  std::unique_ptr<Expr> parseProgram() {
    return parseExpr();
  }

  std::unique_ptr<Expr> parseExpr() {
    // Consume initial parenthesis
    while(currentToken() && currentToken()->type == LPAREN) {
      consume();
    }

    if(isBinaryOp()) {
      return parseBinaryExpr();
    } else if (isUnaryOp()) {
      return parseUnaryExpr();
    } else if (isTerm()) {
    return parseTerm();
    } else {
      throw ParserException("Expected Expression.");
    }
  }


  std::unique_ptr<Expr> parseBinaryExpr() {
    std::unique_ptr<Expr> left = parseFact();
    while(currentToken()->isPlusMinus()) {
      Token operate = consume().value();
      std::unique_ptr<Expr> right = parseFact();
      left = std::make_unique<BinaryExpr>(left, operate, right);
    }
    return left;
  }

  std::unique_ptr<Expr> parseUnaryExpr() {
    if(!currentToken()->isOperatorToken()) {
      throw ParserException("Expected Operator");
    }
    Token operate = consume().value();
    std::unique_ptr<Expr> left = parseTerm();
    return std::make_unique<UnaryExpr>(operate, left);
  }

  std::unique_ptr<Expr> parseFact() {
    std::unique_ptr<Expr> left = parseParen();
    while(currentToken()->isMulDiv()) {
      Token operate = consume().value();
      std::unique_ptr<Expr> right = parseParen();
      left = std::make_unique<BinaryExpr>(BinaryExpr(left, operate, right));
    }
    return left;
  }

  std::unique_ptr<Expr> parseParen() {
    // parenthesized expr
    while(currentToken()->type == TokenType::LPAREN) {
      // consume l paren 
      consume();
      std::unique_ptr<Expr> expr = parseExpr();
      if(currentToken()->type != TokenType::RPAREN) {
        throw ParserException("Expected right paren token");
      }
    }
    return parseTerm();
  }

  std::unique_ptr<Expr> parseTerm() {
    if(!currentToken()->isNumberToken()) {
      throw ParserException("Expected Number");
    }
    std::optional<Token> curTok = consume();
    Literal retLit = Literal(curTok);
    return std::make_unique<Literal>(retLit);
  }
};

#endif