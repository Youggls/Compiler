#include "VarASTNode.h"

VarASTNode::VarASTNode(char* content, AbstractASTNode* value)
    : AbstractASTNode(content, ASTNodeType::assignVar)
{
    this->addChildNode(value);
}

void VarASTNode::printInfo()
{
    std::cout << "Variation " << this->content << std::endl;
}
