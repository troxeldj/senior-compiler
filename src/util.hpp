#ifndef _UTIL_INCLUDE
#define _UTIL_INCLUDE
#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>

void runShell(void) {
  std::string line = "";

  while(line != "exit" and line != "quit") {
    std::cout << "> ";
    std::cin >> line;
  }
  std::cout << "Bye\n";
  exit(0);
}

    
std::string fileContentsToString(std::string filePath) {
  
  std::ifstream t(filePath);
  std::stringstream buffer;
  buffer << t.rdbuf();

  return buffer.str();
}

bool isDigitOrDot(char c) {
  return isdigit(c) || c == '.';
}

#endif
