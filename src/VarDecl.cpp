#include "VarDecl.hpp"

VarDecl::VarDecl() {}

std::string VarDecl::getName() {
  return this->name;
}

std::unique_ptr<Expr> VarDecl::getExpr() {
  return std::move(this->expr);
}

VarDecl::VarDecl(std::string name, std::unique_ptr<Expr> expr) : 
  name{name}, expr{std::move(expr)} {}

VarDecl::VarDecl(std::string name, std::string dataType, std::unique_ptr<Expr> expr) : 
  name{name}, dataType{dataType}, expr{std::move(expr)} {}

std::any VarDecl::getValue() {
  return this->expr->getValue();
}

void VarDecl::accept(Visitor* vis) {
  vis->visitVarDecl(this);
}