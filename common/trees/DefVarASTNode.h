#ifndef DEFVARASTNODE_H
#define DEFVARASTNODE_H
#include "ASTNode.h"
#include "IdentifierASTNode.h"
#include "../symbol/symbol.h"

class DefVarASTNode : public AbstractASTNode
{
private:
    symbolType type;
    int arrayLength;

public:
    DefVarASTNode(char *content, AbstractASTNode *value = NULL);
    inline symbolType getSymbolType() { return this->type; }
    inline void setArrayType() { this->type = symbolType::Array; }
    void setAllType(char *type);
    void setArrayLength(char *length);
    void printInfo(int depth);
};

#endif
