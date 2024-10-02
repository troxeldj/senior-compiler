#include "BinaryExpr.hpp"
#include "ParserException.hpp"

BinaryExpr::BinaryExpr(std::unique_ptr<Expr> &left, std::optional<Token> operate, std::unique_ptr<Expr> &right) {
  this->left = std::move(left);
  this->operate = operate.value();
  this->right = std::move(right);
}

float BinaryExpr::getValue() {
  switch(operate.type) {
    case TokenType::PLUS:
      return this->left->getValue() + this->right->getValue();
      break;
    case TokenType::MINUS:
      return this->left->getValue() - this->right->getValue();
      break;
    case TokenType::MULTIPLY:
      return this->left->getValue() * this->right->getValue();
      break;
    case TokenType::DIVIDE:
      return this->left->getValue() / this->right->getValue();
      break;
    default:
      throw ParserException("Invalid Operator Token");
      break;
  }
}