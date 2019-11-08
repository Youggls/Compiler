#ifndef FUNCASTNODE_H
#define FUNCASTNODE_H
#include "ASTNode.h"

class DefFunASTNode : public AbstractASTNode
{
private:
    // 记录参数列表
    AbstractASTNode* argList;
public:
    // argList是参数列表，funcBody是函数体
    DefFunASTNode(char* content, AbstractASTNode* argList, AbstractASTNode* funcBody);
    // 通过 AbstractASTNode 继承
    void printInfo();
};

#endif // !FUNCASTNODE_H
