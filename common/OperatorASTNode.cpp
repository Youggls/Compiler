#include "OperatorASTNode.h"

OperatorASTNode::OperatorASTNode(char* content, opType type) 
    : AbstractASTNode(content, ASTNodeType::op) {
    this->type = type;
}

void OperatorASTNode::printInfo() {
    std::cout <<"Operator: \"" << this->content << "\"" << std::endl;
}
