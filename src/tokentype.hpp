#ifndef _TOKENTYPE_INCLUDE
#define _TOKENTYPE_INCLUDE

std::vector<std::string> KEYWORDS = {"int", "float", "string", "for", "const", "func"};
std::vector<std::string> DATATYPES = {"int", "float", "string"};

bool isKeyword(std::string word) {
  for(std::string& kWord : KEYWORDS) {
    if(word == kWord) {
      return true;
    }
  }
  return false;
}

bool isDataType(std::string word) {
  for (std::string& dType : DATATYPES) {
    if(dType == word) {
      return true;
    }
  }
  return false;
}


enum TokenType {
  //  Parens, braces, brackets
  LPAREN,
  RPAREN,
  LBRACKET, // [
  RBRACKET, // ]
  LBRACE, // {
  RBRACE, // }
 
  // Operators
  PLUS,
  MINUS,
  MULTIPLY,
  DIVIDE,
  EQUAL,

  // Other
  NEWLINE,
  IDENTIFIER,
  FLOAT,
  INT,
  STRING,
  _EOF,
  KEYWORD,
};


#endif
