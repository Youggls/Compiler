#ifndef ASSIGNVARASTNODE_H
#define ASSIGNVARASTNODE_H
#include "ASTNode.h"
#include "LiteralASTNode.h"
#include "IdentifierASTNode.h"
class VarASTNode : public AbstractASTNode
{
public:
    VarASTNode(char* content, AbstractASTNode* value=NULL);
    void printInfo();
};

#endif