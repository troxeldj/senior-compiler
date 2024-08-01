#include <iostream>
#include <vector>
#include "token.hpp"
#include "tokentype.hpp"


class Lexer {
private:
  std::string fileContents;
  std::vector<Token> tokens;
  int cur_index;
  char cur_char;
  int length;
public:
  // Constructor
  Lexer(std::string fileContents) {
    this->fileContents = fileContents;
    this->length = fileContents.length();
    this->cur
  }

  std::vector<Token> getTokens() {
    return this->tokens;
  }

  void addToken(TokenType type, std::any data) {
    Token tok = Token(type, data);
    this->tokens.push_back(tok);
  } 

};
