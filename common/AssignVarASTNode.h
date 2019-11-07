#ifndef ASSIGNVARASTNODE_H
#define ASSIGNVARASTNODE_H
#include "ASTNode.h"
#include "LiteralASTNode.h"
#include "IdentifierASTNode.h"
class AssignVarASTNode : public AbstractASTNode
{
private:
    IdentifierASTNode* id;
    LiteralASTNode* value;

public:
    AssignVarASTNode(char* content, IdentifierASTNode* id, LiteralASTNode* value);
    void printInfo();
};

#endif