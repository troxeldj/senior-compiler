#ifndef __LITERAL_HPP
#define __LITERAL_HPP

#include "Token.hpp"
#include "Expr.hpp"
#include <optional>
class Literal : public Expr {
  private:
  Token tok;
  std::string type;
  
  Literal();

  public:
  Literal(std::optional<Token> tok);

  std::string getType();

  float getValue() override;
};
#endif