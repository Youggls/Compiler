#include "IdentifierASTNode.h"

IdentifierASTNode::IdentifierASTNode(char *content) : AbstractASTNode(content, ASTNodeType::identifier)
{
}

void IdentifierASTNode::printInfo(int depth)
{
    std::cout << "Identifier: " << this->getValue() << std::endl;
}

int IdentifierASTNode::getValue()
{
    return std::stoi(this->content);
}
