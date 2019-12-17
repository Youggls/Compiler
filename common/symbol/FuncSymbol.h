#ifndef FUNCSYMBOL_H
#define FUNCSYMBOL_H
#include <unordered_map>
#include <list>
#include "../trees.h"

class FuncSymbol {
private:
    std::string funcName;
    // By arg to override.
    // For example, if a function is defined as void test(int a, int b)
    // The keyName of it is test_i_i
    // If a fucntion is defined as void test()
    // The keyName of it is test
    std::string keyName;
    std::vector<symbolType> typeList;
    int totalArgOffset;
    symbolType revType;
public:
    FuncSymbol(AbstractASTNode* fun);
    FuncSymbol(std::string funcName, std::vector<symbolType> typeList, symbolType rev);
    bool operator== (const FuncSymbol& another);
    inline std::string getKeyName() { return this->keyName; }
    inline std::string getFunName() { return this->funcName; }
    inline int getTotalArgOffset() { return this->totalArgOffset; }
};

class FuncTable {
private:
    std::unordered_map<std::string, FuncSymbol*> funcHashTable;
    static int num;
public:
    FuncTable();
    bool addFunction(FuncSymbol* func);
    bool addFunction(AbstractASTNode* func);
    FuncSymbol* findFunction(std::string keyName);
};

#endif