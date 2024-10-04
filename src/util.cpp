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

bool isInt(std::any& anyVal) {
  return anyVal.type() == typeid(int);
}
bool isFloat(std::any& anyVal) {
  return anyVal.type() == typeid(float);
}
bool isString(std::any& anyVal) {
  return anyVal.type() == typeid(std::string);
}

int anyToInt(std::any& anyVal) {
  return std::any_cast<int>(anyVal);
}

float anyToFloat(std::any& anyVal) {
  return std::any_cast<float>(anyVal);
}

std::string anyToString(std::any& anyVal) {
  return std::any_cast<std::string>(anyVal);
}

std::string repeatString(int numTimes, std::string strn) {
  for(int i = 0; i < numTimes; i++) {
    strn += strn; 
  }
  return strn;
}

void printAny(const std::any val) {
  if (val.type() == typeid(int)) {
      std::cout << std::any_cast<int>(val) << std::endl;
  } else if (val.type() == typeid(float)) {
      std::cout << std::any_cast<float>(val) << std::endl;
  } else if (val.type() == typeid(std::string)) {
      std::cout << std::any_cast<std::string>(val) << std::endl;
  } else {
      std::cout << "Unknown type" << std::endl;
  }
}