#ifndef SYMBOL_H
#define SYMBOL_H
#include <string>
#include <unordered_map>
#include <vector>
#define INT_OFFSET 4
enum class symbolType
{
    unset = -1,
    integer = 0,
    function = 1,
    pointer = 2,
    boolean = 3,
    Void = 4
};

class symbol
{
private:
    std::string idName;
    symbolType idType;
    int offset;
    int index;

public:
    symbol();
    symbol(std::string idName, symbolType idType);
    const std::string getIdName();
    inline int getOffset() { return offset; }
    inline int getIndex() { return index; }
    inline void setOffset(int offset) { this->offset = offset; }
    inline void setIndex(int index) { this->index = index; }
    symbolType &getIdType();
};

class SymbolTable
{
private:
    std::unordered_map<std::string, symbol *> symbolHashTable;
    // 只在根作用域下被初始化，用于按照索引值搜索符号
    std::vector<symbol *> *symbolArray;
    SymbolTable *parentTable;
    SymbolTable *childTable;
    SymbolTable *peerTable;
    // 根作用域保存该作用域下总符号数目
    int symbolItemCount;
    // 当前作用域的总偏移量
    int totalOffset;
    // 如果当前作用域是函数，则为true，否则为false
    bool isFunctionTable;
    // 根作用域指针
    SymbolTable *baseTable;
    symbol *findInThisTable(const std::string name);
    SymbolTable(SymbolTable *parent, bool isFun);
    int addSymbol(symbol *symbol);

public:
    // Judge the symbol is successfully added.
    static const int SUCCESS = 0;
    static const int FAIL = -1;
    // 如果当前作用域是函数，isFun则为true，否则为false
    SymbolTable(bool isFun);
    // If success, return SUCCESS = 0, else return FAILED = -1.
    int addSymbol(std::string idName, symbolType idType);
    // Create child symbol table, set peer table automatically
    SymbolTable *createChildTable(bool isFun);
    // If not found, return NULL marco.
    symbol *findSymbol(const std::string name);
    inline void setChild(SymbolTable *child) { this->childTable = child; };
    inline void setParent(SymbolTable *parent) { this->parentTable = parent; };
    inline SymbolTable *getParent() { return this->parentTable; };
    inline SymbolTable *getChild() { return this->childTable; };
    inline SymbolTable *getPeer() { return this->peerTable; }
};

#endif // !SYMBOL_H
