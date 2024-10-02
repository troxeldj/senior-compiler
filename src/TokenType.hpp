#ifndef __TOKENTYPE_HPP
#define __TOKENTYPE_HPP
#include <vector>
#include <string>

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