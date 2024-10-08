#include "Parser.hpp"
#include "ParserTypes.hpp"
#include "util.hpp"

  Parser::Parser(std::vector<Token>& tokens) : tokens(tokens) {
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

  Token Parser::consume() {
    if (isAtEnd()) {
      throw ParserException("No more tokens to consume.");
    }
    return this->tokens[this->curIndex++];
  }

  Token Parser::peek(int num = 1) {
    if (this->curIndex + num >= this->tokLen) {
      throw ParserException("No more tokens to peek.");
    }
    return this->tokens[this->curIndex + num];
  }

  void Parser::consumeParens() {
    while(currentToken().type == TokenType::LPAREN)
      consume();
  }

  bool Parser::isBinaryOp() {
    consumeParens();
    return (
      (currentToken().isNumberToken()) && 
      (peek(1).isOperatorToken()) &&
      (peek(2).isNumberToken())
    );
  }

  bool Parser::isUnaryOp() {
    consumeParens();
    return (
      (currentToken().isOperatorToken()) &&
      (peek(1).isNumberToken())
    );
  }

  bool Parser::isNewline() {
    return currentToken().type == TokenType::NEWLINE;
  }

  bool Parser::isVarDecl() {
    return (
      (
        currentToken().type == TokenType::KEYWORD
        && isDataType(std::any_cast<std::string>(currentToken().data))
      ) 
      && (peek(1).type == IDENTIFIER)
      && (peek(2).type == EQUAL)
    );
  }

  bool Parser::isTerm() {
    if(currentToken().isNumberToken()) return true;
    return false;
  }

  bool Parser::isString() {
    if(currentToken().type == TokenType::STRING) 
      return true;
    return false;
  }

  Token Parser::currentToken() {
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

    while (currentToken().type == TokenType::RPAREN) {
      consume(); 
    }
    
    return retExpr;
  }

  std::unique_ptr<Expr> Parser::parseBinaryExpr() {
    std::unique_ptr<Expr> left = parseFact();
    while(currentToken().isPlusMinus()) {
      Token operate = consume();
      std::unique_ptr<Expr> right = parseFact();
      left = std::make_unique<BinaryExpr>(left, operate, right);
    }
    return left;
  }

  std::unique_ptr<Expr> Parser::parseUnaryExpr() {
    if(!currentToken().isOperatorToken()) {
      throw ParserException("Expected Operator");
    }
    Token operate = consume();
    std::unique_ptr<Expr> left = parseTerm();
    return std::make_unique<UnaryExpr>(operate, left);
  }

  std::unique_ptr<Expr> Parser::parseVarDecl() {
    std::string dataType = std::any_cast<std::string>(consume().data);
    std::string identName = std::any_cast<std::string>(consume().data);
    // consume =
    consume();
    return std::make_unique<VarDecl>(identName, dataType, std::move(parseExpr()));
  }

  std::unique_ptr<Expr> Parser::parseFact() {
    std::unique_ptr<Expr> left = parseParen();
    while(currentToken().isMulDiv()) {
      Token operate = consume();
      std::unique_ptr<Expr> right = parseParen();
      left = std::make_unique<BinaryExpr>(BinaryExpr(left, operate, right));
    }
    return left;
  }

  std::unique_ptr<Expr> Parser::parseParen() {
    // parenthesized expr
    while(currentToken().type == TokenType::LPAREN) {
      // consume l paren 
      consume();
      std::unique_ptr<Expr> expr = parseExpr();
      if(currentToken().type != TokenType::RPAREN) {
        throw ParserException("Expected right paren token");
      }
    }
    return parseTerm();
  }

  std::unique_ptr<Expr> Parser::parseTerm() {
    if(!currentToken().isNumberToken()) {
      throw ParserException("Expected Number");
    }
    std::optional<Token> curTok = consume();
    Literal retLit = Literal(curTok);
    return std::make_unique<Literal>(retLit);
  }