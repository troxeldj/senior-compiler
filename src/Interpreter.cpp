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

void Interpreter::interpretProgram() {
  for (std::unique_ptr<Expr>& expr : expressions) {
    expr->accept(this);
  }
}