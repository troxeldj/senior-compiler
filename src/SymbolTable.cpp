#include "SymbolTable.hpp"

SymbolTable::SymbolTable() {
  table = std::map<std::string, std::unique_ptr<Expr>>();
}

void SymbolTable::add(std::string name, std::unique_ptr<Expr> expr) {
  table[name] = std::move(expr);
}

bool SymbolTable::isInTable(std::string name) {
  return table.find(name) != table.end();
}

void SymbolTable::remove(std::string name) {
  if(!isInTable(name)) {
    return;
  }
  table.erase(name);
}