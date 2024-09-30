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
  bool isVarDecl(std::unique_ptr<Expr> &expr) {
    return dynamic_cast<VarDecl*>(expr.get());
  }

  bool isLiteral(std::unique_ptr<Expr> &expr) {
    return dynamic_cast<Literal*>(expr.get());
  }

  void interpretProgram() {
    for(auto &expr : expressions) {
      // if expr is a varDecl add to symbol table
      if(isVarDecl(expr)) {
        VarDecl *varDecl = dynamic_cast<VarDecl*>(expr.get());
        table.add(varDecl->getName(), std::move(varDecl->getExpr()));
      }
      else if(isLiteral(expr)) {
        Literal *lit = dynamic_cast<Literal*>(expr.get());
        if(lit->getToken().type == TokenType::IDENTIFIER) {
          if(table.isInTable(lit->getToken().data.emplace<std::string>())) {
            std::cout << table.get(lit->getToken().data.emplace<std::string>()) << std::endl;
          }
          else {
            std::cout << "Variable " + lit->getToken().data.emplace<std::string>() + " not found" << std::endl;
          }
        }
      }
      else {
        std::cout << expr->getValue() << std::endl;
      }
      expr->getValue();
    }
  }
};

#endif