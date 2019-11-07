#include "DefVarASTNode.h"

DefVarASTNode::DefVarASTNode(char* content,IdentifierASTNode* value)
    : AbstractASTNode(content, ASTNodeType::defVar)
{
    this->addChildNode(id);
}

void DefVarASTNode::printInfo()
{
    std::cout << "Variation define." << this->content;
}