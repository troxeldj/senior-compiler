#include "util.hpp"
#include "TokenType.cpp"
#include "Keywords.hpp"

void runShell() {
  std::string line = "";

  while(line != "exit" and line != "quit") {
    std::cout << "> ";
    std::cin >> line;
  }
  std::cout << "Bye\n";
  exit(0);
}

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

std::string fileContentsToString(std::string filePath) {
  
  std::ifstream t(filePath);
  std::stringstream buffer;
  buffer << t.rdbuf();

  return buffer.str();
}

bool isDigitOrDot(char c) {
  return isdigit(c) || c == '.';
}