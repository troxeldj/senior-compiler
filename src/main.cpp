#include <iostream>
#include "util.hpp"

int main(int argc, char* argv[]) {
  int numOfArgs = argc;
  
  if(numOfArgs == 1) {
    runShell();
  }
  else {
    std::string filePath = argv[1];
    std::string fileContents = "";
    try {
      fileContents = fileContentsToString(filePath); 
      std::cout << fileContents << "\n";
    } catch (std::exception& ex){
      std::cout << "Unable to open file " + filePath + "\n";
      std::cout << ex.what();
    }
    return 0;
  }
}
