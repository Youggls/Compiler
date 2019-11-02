#include "CallFunASTNode.h"

CallFunASTNode::CallFunASTNode(char* content, AbstractASTNode* varList):
	AbstractASTNode(content, ASTNodeType::callFunc)
{
	this->varList = varList;
}

void CallFunASTNode::printInfo()
{
	std::cout << "Call Function." << this->content;
}
