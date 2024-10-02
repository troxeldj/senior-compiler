#include "UnaryExpr.hpp"

UnaryExpr::UnaryExpr(std::optional<Token> operate, std::unique_ptr<Expr> &left) {
  this->left = std::move(left);
  this->operate = operate.value();
}

float UnaryExpr::getValue() {
  if(operate.type == TokenType::MINUS) {
    return - (left->getValue());
  }
  return left->getValue();
}