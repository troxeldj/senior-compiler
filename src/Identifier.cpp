#include "Identifier.hpp"

std::string Identifier::getName() {
  return this->name;
}

void Identifier::accept(Visitor* vis) {
  vis->visitIdentifier(this);
}

std::any Identifier::getValue() {
  return std::move(this->value->getValue());
}