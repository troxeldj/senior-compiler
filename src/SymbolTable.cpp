#include "SymbolTable.hpp"
#include <stdexcept>
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

std::any SymbolTable::get(std::string name) {
  if(!isInTable(name)) {
    throw std::runtime_error("Variable " + name + " not found");
  }
  return table[name];
}

void SymbolTable::remove(std::string name) {
  if(!isInTable(name)) {
    return;
  }
  table.erase(name);
}