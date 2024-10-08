#ifndef __LEXER_HPP
#define __LEXER_HPP

#include <iostream>
#include <stdexcept>
#include <vector>
#include <optional>
#include "Token.hpp"


class Lexer {
  std::string fileContents;
  std::vector<Token> tokens;
  int cur_index;
  int contLength;

public:
  // Constructor
  Lexer(std::string);

  bool isAtEnd();
  char peek();
  void makeTokens();
  char consume();

  Token makeNumber(char);
  std::string makeWord(char);
  Token makeToken(char);

  void addToken(TokenType, std::any);
  std::vector<Token>& getTokens();
};

#endif