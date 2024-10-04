#ifndef __VISITOR_HPP
#define __VISITOR_HPP

#include <memory>

class BinaryExpr;
class UnaryExpr;
class Literal;
class VarDecl;

class Visitor {
public:
  virtual void visitBinaryExpr(BinaryExpr*) = 0;
  virtual void visitUnaryExpr(UnaryExpr*) = 0;
  virtual void visitLiteral(Literal*) = 0;
  virtual void visitVarDecl(VarDecl* varDecl) = 0;
};

#endif