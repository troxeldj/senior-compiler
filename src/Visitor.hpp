#ifndef __VISITOR_HPP
#define __VISITOR_HPP
#include <memory>
#include "ParserTypes.hpp"


class Visitor {
  virtual void visitBinaryExpr(std::unique_ptr<BinaryExpr> binaryExpr) = 0;
  virtual void visitUnaryExpr(std::unique_ptr<UnaryExpr> unaryExpr) = 0;
  virtual void visitLiteral(std::unique_ptr<UnaryExpr> Literal) = 0;
  virtual void visitVarDecl(std::unique_ptr<VarDecl> varDecl) = 0;
};

#endif