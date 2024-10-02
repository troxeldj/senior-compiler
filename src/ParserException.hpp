#ifndef __PARSER_EXCEPT_HPP
#define __PARSER_EXCEPT_HPP

#include <exception>
#include <string>
class ParserException : public std::exception {
  public:
  std::string message;
  ParserException(std::string);
  ParserException();
};

#endif