#include "Literal.hpp"

Literal::Literal() {}

Literal::Literal(std::optional<Token> tok) {
  this->tok = std::move(tok.value());
  this->type = this->tok.type;
}

std::string Literal::getType() {
  return this->type;
}

float Literal::getValue() {
  std::string stringVal = std::any_cast<std::string>(tok.data);
  return std::stod(stringVal);
}