#ifndef __VARDECL_HPP
#define __VARDECL_HPP
#include <string>
#include <memory>
#include "Expr.hpp"

class VarDecl : public Expr {
  std::string name;
  std::string dataType;
  std::unique_ptr<Expr> expr;

  VarDecl();

public:
  float getValue() override;

  std::string getName();

  std::unique_ptr<Expr> getExpr();

  VarDecl(std::string, std::unique_ptr<Expr>);

  VarDecl(std::string, std::string, std::unique_ptr<Expr>);
};

#endif