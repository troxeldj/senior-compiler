#include <stdexcept>
#include "UnaryExpr.hpp"

UnaryExpr::UnaryExpr(std::optional<Token> operate, std::unique_ptr<Expr> &left) {
  this->left = std::move(left);
  this->operate = operate.value();
}

std::any UnaryExpr::getValue() {
  std::any expVal = left->getValue();
  if(expVal.type() == typeid(int)) {
    int intVal = std::any_cast<int>(expVal);
    if(operate.type == TokenType::MINUS)
      return -intVal;
    else
      return intVal;
  } else if(expVal.type() == typeid(float)) {
    float floatVal = std::any_cast<float>(expVal);
    if(operate.type == TokenType::MINUS)
      return -floatVal;
    else
      return floatVal;
  } else if (expVal.type() == typeid(std::string)) {
    return std::any_cast<std::string>(expVal);
  } else {
    throw std::runtime_error("Invalid UnaryExpression Value");
  }
}

void UnaryExpr::accept(Visitor* vis) {
  vis->visitUnaryExpr(this);
}