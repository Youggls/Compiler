#ifndef DEFVARASTNODE_H
#define DEFVARASTNODE_H
#include "ASTNode.h"
#include "../symbol/symbol.h"

class DefVarASTNode : public AbstractASTNode
{
private:
    symbolType type;
    int arrayLength;
    std::string structType;

public:
    DefVarASTNode(char *content, AbstractASTNode *value = NULL);
    DefVarASTNode(char *structTypeName, char *structIdName);
    inline symbolType getSymbolType() { return this->type; }
    inline std::string getStructType() { return this->structType; }
    inline void setArrayType() { this->type = symbolType::Array; }
    inline int getArrayLength() { return this->arrayLength; }
    void setAllType(char *type);
    void setArrayLength(char *length);
    void printInfo(int depth);
};

#endif
