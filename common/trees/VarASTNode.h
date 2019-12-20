#ifndef ASSIGNVARASTNODE_H
#define ASSIGNVARASTNODE_H
#include "ASTNode.h"
#include "LiteralASTNode.h"

class VarASTNode : public AbstractASTNode
{
private:
    std::string structMember;
public:
    inline void setStructMember(std::string member) {
        this->structMember = member;
    }
    VarASTNode(char *content, AbstractASTNode *value = NULL);
    void printInfo(int depth);
};

#endif
