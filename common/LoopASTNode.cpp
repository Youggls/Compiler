#include "LoopASTNode.h"

LoopASTNode::LoopASTNode(char* content, LoopType type): AbstractASTNode(content, ASTNodeType::loop)
{
	this->loopType = type;
}

void LoopASTNode::printInfo()
{
	if (this->loopType == LoopType.forLoop) 
	{
		std::cout << "Loop: \" for   \"" << std::endl;
	}
	else 
	{
		std::cout << "Loop: \" while \"" << std::endl;
	}
}
