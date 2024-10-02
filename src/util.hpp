#ifndef __UTIL_HPP
#define __UTIL_HPP

#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>

void runShell();
std::string fileContentsToString(std::string);
bool isDigitOrDot(char);
bool isKeyword(std::string);
bool isDataType(std::string);

#endif