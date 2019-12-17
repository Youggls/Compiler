#include "OperatorASTNode.h"

OperatorASTNode::OperatorASTNode(char *content, opType type)
    : AbstractASTNode(content, ASTNodeType::op)
{
    this->type = type;
}

void OperatorASTNode::printInfo(int depth)
{
    std::cout << "Operator: " << this->content << "Type is: " << (int)this->type << std::endl;
}
