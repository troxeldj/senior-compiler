#include <iostream>
#include <stdexcept>
#include <vector>
#include "token.hpp"
#include "tokentype.hpp"


class Lexer {
private:
  std::string fileContents;
  std::vector<Token> tokens;
  int cur_index;
  int contLength;
public:
  // Constructor
  Lexer(std::string fileContents) {
    this->fileContents = fileContents;
    this->contLength = fileContents.length();
    this->cur_index = 0;
  }

  bool isAtEnd(void) {
    return this->cur_index >= this->contLength;
  }

  char peek(void) {
    if(isAtEnd()) {
      return '\0';
    }
    if(this->cur_index + 1 < this->contLength) {
      this->fileContents.at(this->cur_index);
    }
    // Not another character left
    return '\0'; 
  }

  char consume(void) {
    if(isAtEnd()) {
      return '\0'; 
    }
    return this->fileContents.at(this->cur_index++);
  }

  std::vector<Token> getTokens(void) {
    return this->tokens;
  }
  
  void makeTokens(void) {
    char curChar = consume();
    if(curChar == '\0') {
      throw std::runtime_error("Empty buffer");
    }
    while(!isAtEnd()) {
      break;
    }
  }

  void addToken(TokenType type, std::any data) {
    Token tok = Token(type, data);
    this->tokens.push_back(tok);
  } 
};
