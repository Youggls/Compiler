#ifndef STRUCTSYMBOL_H
#define STRUCTSYMBOL_H
#include <unordered_map>
#include <list>
#include "../trees.h"
#include "symbol.h"

class structSymbol : public symbol {
    std::unordered_map<std::string, int>offsetTable;
    int totalOffsets;
public:
    structSymbol();
    structSymbol(std::string name, AbstractASTNode * node);
    inline std::string getStructName() { return this->idName; }
    inline int getTotalOffsets() { return this->totalOffsets; }
    int insert(std::string name, int offset);
};


class StructTable {
private:
    std::unordered_map<std::string, structSymbol*> structHashTable;
    static int num;
public:
    StructTable();
    bool addStruct(structSymbol* func);
    structSymbol* findStruct(std::string keyName);
};

#endif
