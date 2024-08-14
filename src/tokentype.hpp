#ifndef _TOKENTYPE_INCLUDE
#define _TOKENTYPE_INCLUDE

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

  // Other
  NEWLINE,
  IDENTIFIER,
  FLOAT,
  INT,
  _EOF,
  KEYWORD,
};


#endif
