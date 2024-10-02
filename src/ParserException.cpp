#include "ParserException.hpp"

ParserException::ParserException(std::string message) {
  this->message = message;
}

ParserException::ParserException() = delete;