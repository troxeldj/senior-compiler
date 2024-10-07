#include "SymbolTable.hpp"

SymbolTable::SymbolTable() {
  table = std::map<std::string, std::any>();
}

void SymbolTable::add(std::string name, std::any value) {
  table[name] = value;
}

bool SymbolTable::isInTable(std::string name) {
  return table.find(name) != table.end();
}

std::map<std::string, std::any>& SymbolTable::getTable() {
  return table;
}

void SymbolTable::remove(std::string name) {
  if(!isInTable(name)) {
    return;
  }
  table.erase(name);
}