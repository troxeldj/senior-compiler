#include "Lexer.hpp"
#include "util.hpp"

Lexer::Lexer(std::string fileContents) {
  this->fileContents = fileContents;
  this->contLength = fileContents.length();
  this->cur_index = 0;
}

bool Lexer::isAtEnd(void) {
  return this->cur_index >= this->contLength;
}

char Lexer::peek(void) {
  if(isAtEnd()) {
    return '\0';
  }
  return this->fileContents.at(this->cur_index);
}

char Lexer::consume() {
  if(isAtEnd()) {
    return '\0'; 
  }
  return this->fileContents.at(this->cur_index++);
}

std::vector<std::optional<Token>> Lexer::getTokens() {
  return this->tokens;
}

void Lexer::makeTokens() {
  char curChar = consume();
  if(curChar == '\0') {
    throw std::runtime_error("Empty buffer");
  }
  while(cur_index <= contLength) {
    std::optional<Token> token = makeToken(curChar);
    if(token != std::nullopt) {
      tokens.push_back(token);
    }
    if(cur_index == contLength) {
      curChar = peek();
      cur_index++;
    } else {
      curChar = consume();
    }
  }
  tokens.push_back(Token(TokenType::_EOF, ""));
}

std::optional<Token> Lexer::makeNumber(char currChar) {
  std::string numberString = "";
  bool hasDot = false;
  numberString.push_back(currChar);
  while(!isAtEnd() && isDigitOrDot(peek())) {
    if(cur_index == contLength) {
      currChar = peek();
    } else {
      currChar = consume();
    }
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

std::string Lexer::makeWord(char currChar) {
  if(currChar == '"') {
    currChar = consume();
  }
  std::string retVal = "";
  retVal.push_back(currChar);
  while(!isAtEnd() && isalnum(peek())) {
    if(currChar == '"') {
      consume();
      continue;
    }
    currChar = consume();
    retVal.push_back(currChar);
  }
  return retVal;
}

std::optional<Token> Lexer::makeToken(char currChar) {
  // Whitespace
  if(currChar == '\n' || currChar == '\t' || currChar == ' ') {
      return std::nullopt;
  // Numbers
  } else if (isdigit(currChar)) {
    return makeNumber(currChar);
  // Math operators
  } else if (currChar == '+') {
    return Token(TokenType::PLUS, "+");
  } else if (currChar == '-') {
    return Token(TokenType::MINUS, "-");
  } else if (currChar == '*') {
    return Token(TokenType::MULTIPLY, "*");
  } else if (currChar == '/') {
    return Token(TokenType::DIVIDE, "/");
  } else if (currChar == '(') {
    return Token(TokenType::LPAREN, currChar);
  } else if (currChar == ')') {
    return Token(TokenType::RPAREN, currChar);
  } else if (currChar == '[') {
    return Token(TokenType::LBRACKET, currChar);
  } else if (currChar == ']') {
    return Token(TokenType::RBRACKET, currChar);
  } else if (currChar == '{') {
    return Token(TokenType::LBRACE, currChar);
  } else if (currChar == '}') {
    return Token(TokenType::RBRACE, currChar);
  } else if (currChar == '=') {
    return Token(TokenType::EQUAL, "");
  } else if(currChar == '"') {
    std::string word = makeWord(currChar);
    if(currChar != '"') {
      throw std::runtime_error("Expected closing paren");
    }
    consume(); //consume closing "
    return Token(TokenType::STRING, word);
    // Keywords and Identifiers
    } else if(isalpha(currChar)) {
      std::string word = makeWord(currChar);
      if(isKeyword(word)) {
        return Token(TokenType::KEYWORD, word);
      }
      return Token(TokenType::IDENTIFIER, word);
  } else {
    throw std::runtime_error("Unexpected Token.");
  }
}

void Lexer::addToken(TokenType type, std::any data) {
  Token tok = Token(type, data);
  this->tokens.push_back(tok);
} 