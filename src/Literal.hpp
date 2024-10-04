#ifndef __LITERAL_HPP
#define __LITERAL_HPP

#include <optional>
#include "Token.hpp"
#include "Expr.hpp"
#include "Visitor.hpp"

class Literal : public Expr {
  private:
  Token tok;
  std::string type;
  
  Literal();

  public:
  Literal(std::optional<Token> tok);

  std::string getType();

  std::any getValue() override;
  void accept(Visitor*) override;
};
#endif