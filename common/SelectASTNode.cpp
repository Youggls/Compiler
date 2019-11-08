#include "SelectASTNode.h"

SelectASTNode::SelectASTNode(char* content, SelectType type) : AbstractASTNode(content, ASTNodeType::select)
{
    this->selectType = type;
}

void SelectASTNode::printInfo()
{
    std::cout << "Select: \"" << this->content << "   \"" << std::endl;
}
