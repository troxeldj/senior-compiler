#include "Interpreter.hpp"
#include "util.hpp"
#include "ParserTypes.hpp"

void Interpreter::visitBinaryExpr(BinaryExpr* binaryExpr) {
  printAny(binaryExpr->getValue());
}

void Interpreter::visitUnaryExpr(UnaryExpr* unaryExpr) {
  printAny(unaryExpr->getValue());
}

void Interpreter::visitLiteral(Literal* literal) {
  printAny(literal->getValue());
}

void Interpreter::visitVarDecl(VarDecl* varDecl) {
  printAny(varDecl->getValue());
}

void Interpreter::visitIdentifier(Identifier* ident) {
  //if already in symbol table, update value
  if (symbolTable.isInTable(ident->getName())) {
    if(ident->value->getValue().type() != symbolTable.getTable()[ident->getName()].type()) {
      throw std::runtime_error("Type mismatch");
    }
  }
  // add to symbol table
  symbolTable.add(ident->getName(), std::move(ident->value->getValue()));
}

void Interpreter::interpretProgram() {
  for (std::unique_ptr<Expr>& expr : expressions) {
    expr->accept(this);
  }
}