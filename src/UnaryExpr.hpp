#ifndef __UNARY_EXPR_HPP
#define __UNARY_EXPR_HPP
#include <memory>
#include <optional>
#include "Token.hpp"
#include "Expr.hpp"

class UnaryExpr : public Expr {
  private:
  Token operate;
  std::unique_ptr<Expr> left;
  UnaryExpr() {}

  public:
  UnaryExpr(std::optional<Token>, std::unique_ptr<Expr>&);
  float getValue() override;
};

#endif