#include "CallFunASTNode.h"

CallFunASTNode::CallFunASTNode(char* content, AbstractASTNode* varList) :
    AbstractASTNode(content, ASTNodeType::callFunc)
{
    this->varList = varList;
}

void CallFunASTNode::printInfo(int depth)
{
    std::cout << "Call Function." << this->content << std::endl;
    AbstractASTNode::__printTree(this->varList, depth + 1);
}
