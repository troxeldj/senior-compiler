#ifndef __SIM_INTERPRETER_HPP
#define __SIM_INTERPRETER_HPP

#include <iostream>
#include <stdio.h>
#include <memory>
#include <vector>
#include "SymbolTable.hpp"
#include "Visitor.hpp"

class SimpleInterpreter {
  std::vector<std::unique_ptr<Expr>> expressions;
  SymbolTable table;

public:

  SimpleInterpreter();

  ~SimpleInterpreter(){}

  SimpleInterpreter(std::vector<std::unique_ptr<Expr>>);

  void interpretProgram();
};

#endif