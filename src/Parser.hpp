#ifndef PARSER_HPP
#define PARSER_HPP
#include <vector>
#include <optional>
#include "token.hpp"
#include <stdexcept>

class Expr {
  std::optional<Token> token;
  public:
    Expr(std::optional<Token> token) {
      this->token = token;
    }
};

class BinaryExpr : public Expr {
  std::optional<Expr> left;
  std::optional<Expr> right;
  public:
    BinaryExpr(std::optional<Token> token, std::optional<Expr> left, std::optional<Expr> right) : Expr(token) {
      this->left = left;
      this->right = right;
    }
};

class UnaryExpr : public Expr {
  std::optional<Expr> expr;
  public:
    UnaryExpr(std::optional<Token> token, std::optional<Expr> expr) : Expr(token) {
      this->expr = expr;
    }
};

class Parser
{
private:
  std::vector<std::optional<Token>> tokens;
  int cur_index;
  int tokLen;

  bool isAtEnd(void)
  {
    return this->cur_index >= this->tokLen;
  }

  std::optional<Token> peek(void)
  {
    if (isAtEnd())
    {
      return std::nullopt;
    }
    return this->tokens.at(this->cur_index);
  }

  std::optional<Token> consume(void)
  {
    if (isAtEnd())
    {
      return std::nullopt;
    }
    return this->tokens.at(this->cur_index++);
  }

public:
  Parser(std::vector<std::optional<Token>> tokens)
  {
    this->tokens = tokens;
    this->cur_index = 0;
    this->tokLen = tokens.size();
  }

  std::optional<Expr> parse(void)
  {
    return expression();
  }

  std::optional<Expr> expression(void)
  {
    if (peek() == std::nullopt)
    {
      return std::nullopt;
    }
    std::optional<Expr> left = term();
    while (peek() != std::nullopt && (peek()->type == TokenType::PLUS || peek()->type == TokenType::MINUS))
    {
      std::optional<Token> op = consume();
      std::optional<Expr> right = term();
      left = std::make_optional<Expr>(BinaryExpr(op, left, right));
    }
    return left;
  }

  std::optional<Expr> term(void)
  {
    if (peek() == std::nullopt)
    {
      return std::nullopt;
    }
    std::optional<Expr> left = factor();
    while (peek() != std::nullopt && (peek()->type == TokenType::MULTIPLY || peek()->type == TokenType::DIVIDE))
    {
      std::optional<Token> op = consume();
      std::optional<Expr> right = factor();
      left = std::make_optional<Expr>(BinaryExpr(op, left, right));
    }
    return left;
  }

  std::optional<Expr> factor(void)
  {
    if (peek() == std::nullopt)
    {
      return std::nullopt;
    }
    std::optional<Token> tok = consume();
    if (tok->type == TokenType::INT || tok->type == TokenType::FLOAT)
    {
      return std::make_optional<Expr>(UnaryExpr(tok, std::nullopt));
    }
    else if (tok->type == TokenType::LPAREN)
    {
      std::optional<Expr> expr = expression();
      if (consume()->type != TokenType::RPAREN)
      {
        throw std::runtime_error("Expected closing parenthesis");
      }
      return expr;
    }
    else
    {
      throw std::runtime_error("Unexpected token");
    }
  }


};
#endif