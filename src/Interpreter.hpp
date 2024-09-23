#ifndef __INTERPRETER_HPP
#define __INTERPRETER_HPP
#include <stdio.h>
#include <memory>
#include "ParserTypes.hpp"

class Interpreter {
  std::unique_ptr<Expr> ast;
public:
  Interpreter(std::unique_ptr<Expr> ast) : ast(std::move(ast)) {}
  std::unique_ptr<Expr>& getAst() {
    return this->ast;
  }

  float interpretProgram() {
    return this->ast->getValue();
  }
};

#endif