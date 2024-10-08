#ifndef __SYMBOL_TABLE_HPP
#define __SYMBOL_TABLE_HPP
#include <memory>
#include <any>
#include <map>
#include <string>
#include "ParserTypes.hpp"

class SymbolTable {
private:
  std::map<std::string, std::any> table;
  SymbolTable& operator=(const SymbolTable&) = delete;
  SymbolTable(const SymbolTable&) = delete;
public:
  SymbolTable();

  void add(std::string name, std::any value);
  std::any get(std::string name);
  std::map<std::string, std::any>& getTable();
  bool isInTable(std::string name);
  void remove(std::string name);
};


#endif