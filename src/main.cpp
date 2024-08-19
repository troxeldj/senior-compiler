#include <iostream>
#include "util.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
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
      Lexer lexer = Lexer(fileContents);
      lexer.makeTokens();
      std::vector<std::optional<Token>> tokens = lexer.getTokens();
      Parser parser = Parser(tokens);
      TokExpr ast = parser.parseProgram();
      std::cout << "Parsed successfully\n";
    } catch (std::exception& ex){
      std::cout << "Unable to open file " + filePath + "\n";
      std::cout << ex.what();
    }
    return 0;
  }
}
