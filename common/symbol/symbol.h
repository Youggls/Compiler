#ifndef SYMBOL_H
#define SYMBOL_H
#include <string>
#include <unordered_map>
#include <vector>
enum class symbolType {
    unset = -1,
    integer = 0,
    function = 1,
    pointer = 2,
    boolean = 3,
    Void = 4
};

class symbol {
private:
    std::string idName;
    symbolType idType;
public:
    symbol();
    symbol(std::string idName, symbolType idType);
    const std::string getIdName();
    symbolType& getIdType();
};

class SymbolTable {
private:
    std::unordered_map<std::string, symbol*> symbolHashTable;
    SymbolTable* parentTable;
    SymbolTable* childTable;
    symbol* findInThisTable(const std::string name);
public:
    // Judge the symbol is successfully added.
    static const int SUCCESS = 0;
    static const int FAIL = -1;
    SymbolTable();
    // At the same time, set the parent's childTablt pointer as this class.
    SymbolTable(SymbolTable* parent);
    // If success, return SUCCESS, else return FAILED.
    int addSymbol(symbol* symbol);
    // If not found, return NULL marco.
    symbol* findSymbol(const std::string name);
    inline void setChild(SymbolTable* child) { this->childTable = child; };
    inline void setParent(SymbolTable* parent) { this->parentTable = parent; };
    inline SymbolTable* getParent() { return this->parentTable; };
    inline SymbolTable* getChild() { return this->childTable; };
};

#endif // !SYMBOL_H
