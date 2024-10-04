#include "BinaryExpr.hpp"
#include "ParserException.hpp"
#include "util.hpp"

BinaryExpr::BinaryExpr(std::unique_ptr<Expr> &left, std::optional<Token> operate, std::unique_ptr<Expr> &right) {
  this->left = std::move(left);
  this->operate = operate.value();
  this->right = std::move(right);
}

std::any BinaryExpr::getValue() {
  std::any leftVal = left->getValue();
  std::any rightVal = right->getValue();

  if(operate.type == TokenType::PLUS) {
    if(isInt(leftVal) && isInt(rightVal)) {
      return anyToInt(leftVal) + anyToInt(rightVal);
    } else if (isInt(leftVal) && isFloat(rightVal)) {
      return static_cast<float>(anyToInt(leftVal)) + anyToFloat(rightVal);
    } else if (isFloat(leftVal) && isInt(rightVal)) {
      return anyToFloat(leftVal) + static_cast<float>(anyToInt(rightVal));
    } else if(isFloat(leftVal) && isFloat(leftVal)) {
      return anyToFloat(leftVal) + anyToFloat(rightVal);
    } else if (isString(leftVal) + isString(rightVal)) {
      return anyToString(leftVal) + anyToString(rightVal);
    } else {
      throw std::runtime_error("Invalid Operation between operands in BinaryExpr");
    }
  } else if (operate.type == MINUS) {
    if(isInt(leftVal) && isInt(rightVal)) {
      return anyToInt(leftVal) - anyToInt(rightVal);
    } else if (isInt(leftVal) && isFloat(rightVal)) {
      return static_cast<float>(anyToInt(leftVal)) + anyToFloat(rightVal);
    } else if (isFloat(leftVal) && isInt(rightVal)) {
      return anyToFloat(leftVal) - static_cast<float>(anyToInt(rightVal));
    } else if(isFloat(leftVal) && isFloat(leftVal)) {
      return anyToFloat(leftVal) - anyToFloat(rightVal);
    } else if (isString(leftVal) - isString(rightVal)) {
      throw std::runtime_error("Unable to add subtract strings");
    } else {
      throw std::runtime_error("Invalid Operation between operands in BinaryExpr");
    }
  } else if(operate.type == TokenType::MULTIPLY) {
    if(isInt(leftVal) && isInt(rightVal)) {
      return anyToInt(leftVal) * anyToInt(rightVal);
    } else if (isInt(leftVal) && isFloat(rightVal)) {
      return static_cast<float>(anyToInt(leftVal)) * anyToFloat(rightVal);
    } else if (isFloat(leftVal) && isInt(rightVal)) {
      return anyToFloat(leftVal) * static_cast<float>(anyToInt(rightVal));
    } else if(isFloat(leftVal) && isFloat(leftVal)) {
      return anyToFloat(leftVal) * anyToFloat(rightVal);
    } else if (isInt(leftVal) && isString(rightVal)) {
      return repeatString(anyToInt(leftVal), anyToString(rightVal));
    } else if (isString(leftVal) && isInt(rightVal)) {
      return repeatString(anyToInt(rightVal), anyToString(leftVal));
    } else {
      throw std::runtime_error("Invalid Operation between operands in BinaryExpr");
    }
  } else if(operate.type == TokenType::DIVIDE) {
    if(isInt(leftVal) && isInt(rightVal)) {
      return anyToInt(leftVal) / anyToInt(rightVal);
    } else if (isInt(leftVal) && isFloat(rightVal)) {
      return static_cast<float>(anyToInt(leftVal)) / anyToFloat(rightVal);
    } else if (isFloat(leftVal) && isInt(rightVal)) {
      return anyToFloat(leftVal) / static_cast<float>(anyToInt(rightVal));
    } else if(isFloat(leftVal) && isFloat(leftVal)) {
      return anyToFloat(leftVal) / anyToFloat(rightVal);
    } else {
      throw std::runtime_error("Invalid Operation between operands in BinaryExpr");
    }
  } else {
    throw std::runtime_error("Invalid operator in BinaryExpr");
  }
}

void BinaryExpr::accept(Visitor* vis) {
  vis->visitBinaryExpr(this);
}
