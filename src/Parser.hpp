#ifndef __PARSER_HPP
#define __PARSER_HPP

#include <vector>
#include <optional>
#include <stdexcept>
#include <memory>
#include "Token.hpp"
#include "Expr.hpp"

class Parser
{
private:
  std::vector<std::optional<Token>> tokens;
  int curIndex;
  int tokLen;

public:
  Parser(std::vector<std::optional<Token>>);
  ~Parser();
  bool hasNextToken();

  std::optional<Token> consume();
  std::optional<Token> currentToken();
  std::optional<Token> peek(int num);

  bool isAtEnd();

  void consumeParens();

  bool isBinaryOp();
  bool isUnaryOp();
  bool isNewline();
  bool isVarDecl();
  bool isTerm();
  bool isString();


  std::vector<std::unique_ptr<Expr>> parseProgram();
  std::unique_ptr<Expr> parseExpr();
  std::unique_ptr<Expr> parseBinaryExpr();
  std::unique_ptr<Expr> parseUnaryExpr();
  std::unique_ptr<Expr> parseVarDecl();
  std::unique_ptr<Expr> parseFact();
  std::unique_ptr<Expr> parseParen();
  std::unique_ptr<Expr> parseTerm();
};
#endif