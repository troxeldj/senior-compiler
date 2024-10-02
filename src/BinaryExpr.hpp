#ifndef __BINARY_EXPR_HPP
#define __BINARY_EXPR_HPP
#include <memory>
#include <optional>
#include "Expr.hpp"
#include "Token.hpp"

class BinaryExpr : public Expr {
  std::unique_ptr<Expr> left;
  Token operate;
  std::unique_ptr<Expr> right;

  BinaryExpr();
  
public:
  BinaryExpr(std::unique_ptr<Expr>&, std::optional<Token>, std::unique_ptr<Expr>&);

  float getValue() override;
};

#endif