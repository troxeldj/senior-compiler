#ifndef __SIM_INTERPRETER_HPP
#define __SIM_INTERPRETER_HPP
#include <stdio.h>
#include <memory>
#include <vector>
#include "ParserTypes.hpp"
#include "SymbolTable.hpp"

class SimpleInterpreter {
  std::vector<std::unique_ptr<Expr>> expressions;
  SymbolTable table;
  SimpleInterpreter(){}

public:
  explicit SimpleInterpreter(std::vector<std::unique_ptr<Expr>> expressions) {
    this->expressions = std::move(expressions);
  }
  ~SimpleInterpreter() {}

  void interpretProgram() {
    for(auto &expr : expressions) {
      // if expr is a varDecl add to symbol table
      if(dynamic_cast<VarDecl*>(expr.get())) {
        VarDecl *varDecl = dynamic_cast<VarDecl*>(expr.get());
        table.add(varDecl->getName(), std::move(varDecl->getExpr()));
      }
      else {
        std::cout << expr->getValue() << std::endl;
      }
      expr->getValue();
    }
  }
};

#endif