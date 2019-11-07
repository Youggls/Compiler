#include "AssignVarASTNode.h"

AssignVarASTNode::AssignVarASTNode(char* content, IdentifierASTNode* id, LiteralASTNode* value)
    : AbstractASTNode(content, ASTNodeType::assignVar)
{
    this->addChildNode(id);
    this->addChildNode(value);
}

void AssignVarASTNode::printInfo()
{
    std::cout << "Variation assign." << this->content;
}
