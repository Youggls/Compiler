#ifndef DEFVARASTNODE_H
#define DEFVARASTNODE_H
#include "ASTNode.h"
#include "IdentifierASTNode.h"
class DefVarASTNode : public AbstractASTNode
{
private:
    IdentifierASTNode* id;
public:
    DefVarASTNode(char* content, IdentifierASTNode* id);
    void printInfo();
};

#endif