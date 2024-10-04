#ifndef __BINARY_EXPR_HPP
#define __BINARY_EXPR_HPP
#include <any>
#include <memory>
#include <optional>
#include "Expr.hpp"
#include "Token.hpp"
#include "Visitor.hpp"

class BinaryExpr : public Expr {
  std::unique_ptr<Expr> left;
  Token operate;
  std::unique_ptr<Expr> right;

  BinaryExpr();
  
public:
  BinaryExpr(std::unique_ptr<Expr>&, std::optional<Token>, std::unique_ptr<Expr>&);

  std::any getValue() override;
  void accept(Visitor*) override;
};

#endif