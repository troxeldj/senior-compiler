#ifndef __INTERPRETER_HPP
#define __INTERPRETER_HPP
#include <stdio.h>
#include <memory>
#include <vector>
#include "ParserTypes.hpp"
#include "Visitor.hpp"

class Interpreter : public Visitor {
  std::vector<std::unique_ptr<Expr>> expressions;
public:
  Interpreter(std::vector<std::unique_ptr<Expr>> expressions) : expressions{std::move(expressions)} {}
  ~Interpreter() {};

  void visitBinaryExpr(std::unique_ptr<BinaryExpr> binaryExpr) override {

  }

  void visitUnaryExpr(std::unique_ptr<UnaryExpr> unaryExpr) override {

  }

  void visitLiteral(std::unique_ptr<Literal> Literal) {
  }

  void visitVarDecl(std::unique_ptr<VarDecl> varDecl) {

  }

private:
  Interpreter() {}
};

#endif