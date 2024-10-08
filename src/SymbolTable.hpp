#ifndef __SYMBOL_TABLE_HPP
#define __SYMBOL_TABLE_HPP
#include <memory>
#include <map>
#include <string>
#include "ParserTypes.hpp"

class SymbolTable {
private:
  std::map<std::string, std::unique_ptr<Expr>> table;
  SymbolTable& operator=(const SymbolTable&) = delete;
  SymbolTable(const SymbolTable&) = delete;
public:
  SymbolTable();

  void add(std::string name, std::unique_ptr<Expr> expr);
  bool isInTable(std::string name);
  void remove(std::string name);
};


#endif