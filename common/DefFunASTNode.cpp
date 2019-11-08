#include "DefFunASTNode.h"

DefFunASTNode::DefFunASTNode(char* content, AbstractASTNode* argList, AbstractASTNode* funcBody)
    :AbstractASTNode(content, ASTNodeType::defFunc)
{
    this->argList = argList;
    this->addChildNode(funcBody);
}

void DefFunASTNode::printInfo()
{
    std::cout << "Function define." << this->content;
}
