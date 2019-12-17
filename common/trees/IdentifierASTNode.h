#ifndef IDENTIFIERASTNODE_H
#define IDENTIFIERASTNODE_H
#include "ASTNode.h"
class IdentifierASTNode : public AbstractASTNode
{
public:
    IdentifierASTNode(char *content);
    void printInfo(int depth);
    int getValue();
};
#endif
