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
    return this->curIndex >= (tokLen - 1);
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

  void consumeParens() {
    while(currentToken()->type == TokenType::LPAREN)
      consume();
  }

  bool isBinaryOp() {
    consumeParens();
    return (
      (currentToken() && currentToken()->isNumberToken()) && 
      (peek(1) && peek(1)->isOperatorToken()) &&
      (peek(2) && peek(2)->isNumberToken())
    );
  }

  bool isUnaryOp() {
    consumeParens();
    return (
      (currentToken() && currentToken()->isOperatorToken()) &&
      (peek(1) && peek(1)->isNumberToken())
    );
  }

  bool isNewline() {
    return currentToken()->type == TokenType::NEWLINE;
  }

  bool isVarDecl() {
    return (
      (
        currentToken() 
        && currentToken()->type == TokenType::KEYWORD
        && isDataType(std::any_cast<std::string>(currentToken()->data))
      ) 
      && (peek(1) && peek(1)->type == IDENTIFIER)
      && (peek(2) && peek(2)->type == EQUAL)
      && peek(3)
    );
  }

  bool isTerm() {
    if(currentToken()->isNumberToken()) return true;
    return false;
  }

  bool isString() {
    if(currentToken() && currentToken()->type == TokenType::STRING) 
      return true;
    return false;
  }

  std::optional<Token> currentToken() {
    return this->tokens[this->curIndex];
  }

  std::vector<std::unique_ptr<Expr>> parseProgram() {
    std::vector<std::unique_ptr<Expr>> retVec;
    while(!isAtEnd()) {
      std::unique_ptr<Expr> expr = parseExpr();
      if(expr == nullptr) {
        consume();
        continue;
      }
      retVec.emplace_back(std::move(expr));
    }
    return retVec;
  }

  std::unique_ptr<Expr> parseExpr() {
    std::unique_ptr<Expr> retExpr;
    if(isBinaryOp()) {
      retExpr = parseBinaryExpr();
    } else if (isUnaryOp()) {
      retExpr = parseUnaryExpr();
    } else if (isVarDecl()) {
      retExpr = parseVarDecl();
    } else if (isNewline()) {
      return nullptr;
    } else if (isTerm()) {
      retExpr = parseTerm();
    } else if (isString()) {
      retExpr = std::make_unique<Literal>(consume());
    } else {
      throw ParserException("Expected Expression.");
    }

    while (currentToken()->type == TokenType::RPAREN) {
      consume(); 
    }
    
    return retExpr;
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

  std::unique_ptr<Expr> parseVarDecl() {
    std::string dataType = std::any_cast<std::string>(consume()->data);
    std::string identName = std::any_cast<std::string>(consume()->data);
    // consume =
    consume();
    return std::make_unique<VarDecl>(identName, dataType, std::move(parseExpr()));
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