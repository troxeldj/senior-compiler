#ifndef __UTIL_HPP
#define __UTIL_HPP
#include <any>
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

bool isInt(std::any&);
bool isFloat(std::any&);
bool isString(std::any&);

int anyToInt(std::any&);  
float anyToFloat(std::any&);
std::string anyToString(std::any&);

std::string repeatString(int, std::string);

void printAny(std::any);


#endif