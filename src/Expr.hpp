#ifndef __EXPR_HPP
#define __EXPR_HPP
#include <any>
#include "Visitor.hpp"

class Expr {
  public:
  virtual std::any getValue() = 0;
  virtual void accept(Visitor* ) = 0;
};
#endif