#include "Parser.hpp"
#include "ParserTypes.hpp"
#include "util.hpp"

  Parser::Parser(std::vector<std::optional<Token>> tokens)
  {
    this->tokens = tokens;
    curIndex = 0;
    tokLen = tokens.size();
  }

  Parser::~Parser() = default;

  bool Parser::hasNextToken() {
    return (this->curIndex + 1) < this->tokLen;
  }

  bool Parser::isAtEnd() {
    return this->curIndex >= (tokLen - 1);
  }

  std::optional<Token> Parser::consume() {
    if (isAtEnd())
    {
      return std::nullopt;
    }
    return this->tokens[this->curIndex++];
  }

  std::optional<Token> Parser::peek(int num = 1) {
    if (this->curIndex + num >= this->tokLen)
    {
      return std::nullopt;
    }
    return this->tokens[this->curIndex + num];
  }

  void Parser::consumeParens() {
    while(currentToken().value().type == TokenType::LPAREN)
      consume();
  }

  bool Parser::isBinaryOp() {
    consumeParens();
    return (
      (currentToken().has_value() && currentToken().value().isNumberToken()) && 
      (peek(1).has_value() && peek(1)->isOperatorToken()) &&
      (peek(2).has_value() && peek(2)->isNumberToken())
    );
  }

  bool Parser::isUnaryOp() {
    consumeParens();
    return (
      (currentToken().has_value() && currentToken().value().isOperatorToken()) &&
      (peek(1).has_value() && peek(1).value().isNumberToken())
    );
  }

  bool Parser::isNewline() {
    return currentToken().value().type == TokenType::NEWLINE;
  }

  bool Parser::isVarDecl() {
    return (
      (
        currentToken().has_value()
        && currentToken().value().type == TokenType::KEYWORD
        && isDataType(std::any_cast<std::string>(currentToken().value().data))
      ) 
      && (peek(1).has_value() && peek(1).value().type == IDENTIFIER)
      && (peek(2).has_value() && peek(2).value().type == EQUAL)
      && peek(3).has_value()
    );
  }

  bool Parser::isTerm() {
    if(currentToken().value().isNumberToken()) return true;
    return false;
  }

  bool Parser::isString() {
    if(currentToken().has_value() && currentToken().value().type == TokenType::STRING) 
      return true;
    return false;
  }

  std::optional<Token> Parser::currentToken() {
    return this->tokens[this->curIndex];
  }

  std::vector<std::unique_ptr<Expr>> Parser::parseProgram() {
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

  std::unique_ptr<Expr> Parser::parseExpr() {
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

  std::unique_ptr<Expr> Parser::parseBinaryExpr() {
    std::unique_ptr<Expr> left = parseFact();
    while(currentToken().value().isPlusMinus()) {
      Token operate = consume().value();
      std::unique_ptr<Expr> right = parseFact();
      left = std::make_unique<BinaryExpr>(left, operate, right);
    }
    return left;
  }

  std::unique_ptr<Expr> Parser::parseUnaryExpr() {
    if(!currentToken().value().isOperatorToken()) {
      throw ParserException("Expected Operator");
    }
    Token operate = consume().value();
    std::unique_ptr<Expr> left = parseTerm();
    return std::make_unique<UnaryExpr>(operate, left);
  }

  std::unique_ptr<Expr> Parser::parseVarDecl() {
    std::string dataType = std::any_cast<std::string>(consume().value().data);
    std::string identName = std::any_cast<std::string>(consume().value().data);
    // consume =
    consume();
    return std::make_unique<VarDecl>(identName, dataType, std::move(parseExpr()));
  }

  std::unique_ptr<Expr> Parser::parseFact() {
    std::unique_ptr<Expr> left = parseParen();
    while(currentToken()->isMulDiv()) {
      Token operate = consume().value();
      std::unique_ptr<Expr> right = parseParen();
      left = std::make_unique<BinaryExpr>(BinaryExpr(left, operate, right));
    }
    return left;
  }

  std::unique_ptr<Expr> Parser::parseParen() {
    // parenthesized expr
    while(currentToken()->type == TokenType::LPAREN) {
      // consume l paren 
      consume();
      std::unique_ptr<Expr> expr = parseExpr();
      if(currentToken().value().type != TokenType::RPAREN) {
        throw ParserException("Expected right paren token");
      }
    }
    return parseTerm();
  }

  std::unique_ptr<Expr> Parser::parseTerm() {
    if(!currentToken()->isNumberToken()) {
      throw ParserException("Expected Number");
    }
    std::optional<Token> curTok = consume();
    Literal retLit = Literal(curTok);
    return std::make_unique<Literal>(retLit);
  }