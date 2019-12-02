#ifndef FUNCASTNODE_H
#define FUNCASTNODE_H
#include "ASTNode.h"
#include "../symbol/symbol.h"

class DefFunASTNode : public AbstractASTNode
{
private:
    // 记录参数列表
    AbstractASTNode* argList;
    symbolType revType;
public:
    // argList是参数列表，funcBody是函数体
    DefFunASTNode(char* content, AbstractASTNode* argList, AbstractASTNode* funcBody);
    inline void setFunBody(AbstractASTNode* body) {this->addChildNode(body);}
    inline AbstractASTNode* getArgList() { return this->argList; }
    void setRevType(char*);
    // 通过 AbstractASTNode 继承
    void printInfo(int depth);
};

#endif // !FUNCASTNODE_H
