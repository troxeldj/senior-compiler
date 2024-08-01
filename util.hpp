#ifndef _UTIL_INCLUDE
#define _UTIL_INCLUDE
#include <iostream>
#include <fstream>
#include <iterator>
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
  std::string retVal = "";
  std::ifstream file(filePath);

  if(!file.is_open()) {
    throw std::runtime_error("Unable to open file " + filePath);
  }
  std::string line = "";
  while(std::getline(file, line)) {
    std::cout << line << retVal << "\n";
  }
  


  file.close();
  return retVal;

}

#endif
