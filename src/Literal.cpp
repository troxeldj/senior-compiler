#include <stdexcept>
#include "Literal.hpp"

Literal::Literal() {}

Literal::Literal(std::optional<Token> tok) {
  this->tok = std::move(tok.value());
  this->type = this->tok.type;
}

std::string Literal::getType() {
  return this->type;
}

std::any Literal::getValue() {
  if(this->tok.type == TokenType::FLOAT) {
    return std::any_cast<float>(this->tok.data);
  } else if (this->tok.type == TokenType::STRING) {
    return std::any_cast<std::string>(this->tok.data);
  } else if(this->tok.type == TokenType::STRING) {
   return std::any_cast<int>(this->tok.data);
  } else {
    throw std::runtime_error("Invalid Literal value");
  }
}

void Literal::accept(Visitor* vis) {
  vis->visitLiteral(this);
}