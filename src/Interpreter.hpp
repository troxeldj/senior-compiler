#ifndef __INTERPRETER_HPP
#define __INTERPRETER_HPP
#include <iostream>
#include <stdio.h>
#include <memory>
#include <vector>
#include "Visitor.hpp"
#include "Expr.hpp"

class BinaryExpr;
class UnaryExpr;
class Literal;
class VarDecl;

class Interpreter : public Visitor {
  std::vector<std::unique_ptr<Expr>> expressions;
public:
  Interpreter(std::vector<std::unique_ptr<Expr>> expressions) : expressions{std::move(expressions)} {}
  ~Interpreter() {};

  void visitBinaryExpr(BinaryExpr*) override;
  void visitUnaryExpr(UnaryExpr*) override;
  void visitLiteral(Literal*) override;
  void visitVarDecl(VarDecl*) override;

  void interpretProgram();
};

#endif