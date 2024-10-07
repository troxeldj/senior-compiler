#ifndef IDENTIFIER_HPP
#define IDENTIFIER_HPP
#include <string>
#include <memory>
# include <any>
#include "Expr.hpp" 
#include "Visitor.hpp"
#include "VarType.hpp"
class Identifier : public Expr {
public:
  VarType type;
  std::string name;
  std::any value;

  Identifier(VarType type, std::string name, std::unique_ptr<Expr> value) : name(name), type(type), value(value.get()->getValue()) {}
  std::string getName();

  void accept(Visitor* vis) override;
  std::any getValue() override;
};

#endif