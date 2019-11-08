#include "IdentifierASTNode.h"

IdentifierASTNode::IdentifierASTNode(char *content) : AbstractASTNode(content, ASTNodeType::identifier)
{
}

void IdentifierASTNode::printInfo()
{
    std::cout << "Encounter an identifier: " << this->getValue() << std::endl;
}

int IdentifierASTNode::getValue()
{
    return std::stoi(this->content);
}
