#ifndef DEFVARASTNODE_H
#define DEFVARASTNODE_H
#include "ASTNode.h"
#include "IdentifierASTNode.h"
#include "../symbol/symbol.h"

class DefVarASTNode : public AbstractASTNode
{
private:
    symbolType type;

public:
    DefVarASTNode(char *content, AbstractASTNode *value = NULL);
    inline symbolType getSymbolType() { return this->type; }
    void setAllType(char *type);
    void printInfo(int depth);
};

#endif