#include <iostream>
#include <stdexcept>
#include <vector>
#include <optional>
#include "token.hpp"
#include "tokentype.hpp"

class Lexer {
private:
  std::string fileContents;
  std::vector<std::optional<Token>> tokens;
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
      return this->fileContents.at(this->cur_index);
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

  std::vector<std::optional<Token>> getTokens(void) {
    return this->tokens;
  }
  
  void makeTokens(void) {
    char curChar = consume();
    if(curChar == '\0') {
      throw std::runtime_error("Empty buffer");
    }
    while(!isAtEnd()) {
      std::optional<Token> token = makeToken(curChar);
      if(token != std::nullopt) {
        tokens.push_back(token);
      }
    }
    tokens.push_back(Token(TokenType::_EOF, ""));
  }

  std::optional<Token> makeNumber(char currChar) {
    std::string numberString = "";
    bool hasDot = false;
    numberString.push_back(currChar);
    while(!isAtEnd && isDigitOrDot(peek())) {
      currChar = consume();
      // check for decimal
      if(currChar == '.') {
        hasDot = true;
      }
      numberString.push_back(currChar);
    }

    // todo: convert string to int/float
    // need to change Token data to std::variant
    if(hasDot) {
      return Token(TokenType::FLOAT, numberString);
    }
    return Token(TokenType::INT, numberString);
  }

  std::string makeWord(char currChar) {
    std::string retVal = "";
    retVal.push_back(currChar);
    while(!isAtEnd() && isalnum(peek())) {
      currChar = consume();
      retVal.push_back(currChar);
    }
    return retVal;

  }

  bool isKeyword(std::string word) {

  }

  std::optional<Token> makeToken(char currChar) {
    if(currChar == '\n' || currChar == '\t') {
        return std::nullopt;
    } else if (isdigit(currChar)) {
      return makeNumber(currChar);
    } else if(isalpha(currChar)) {
      std::string word = makeWord(currChar);
      if(isKeyword(word)) {
        return Token(TokenType::KEYWORD, word);
      } else {
        return Token(TokenType::IDENTIFIER, word);
      }
    }
  }

  void addToken(TokenType type, std::any data) {
    Token tok = Token(type, data);
    this->tokens.push_back(tok);
  } 
};