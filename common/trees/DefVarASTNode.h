#ifndef DEFVARASTNODE_H
#define DEFVARASTNODE_H
#include "ASTNode.h"
#include "IdentifierASTNode.h"
enum class VarType {
    unset = 0,
    integer = 1,
    integerPointer = 2,
    Void = 3
};

class DefVarASTNode : public AbstractASTNode
{
private:
    VarType type;
public:
    DefVarASTNode(char* content, AbstractASTNode* value=NULL);
    void setAllType(char* type);
    void printInfo(int depth);
};

#endif