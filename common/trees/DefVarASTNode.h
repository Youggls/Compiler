#ifndef DEFVARASTNODE_H
#define DEFVARASTNODE_H
#include "ASTNode.h"
#include "IdentifierASTNode.h"
#include "../symbol.h"

class DefVarASTNode : public AbstractASTNode
{
private:
    symbolType type;
public:
    DefVarASTNode(char* content, AbstractASTNode* value=NULL);
    void setAllType(char* type);
    void printInfo(int depth);
};

#endif