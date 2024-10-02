#include "SimpleInterpreter.hpp"

SimpleInterpreter::SimpleInterpreter() {}

SimpleInterpreter::SimpleInterpreter(std::vector<std::unique_ptr<Expr>> expressions) {
  this->expressions = std::move(expressions);
}

void SimpleInterpreter::interpretProgram() {
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