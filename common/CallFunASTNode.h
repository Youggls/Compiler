#ifndef CALLFUNASTNODE_H
#define CALLFUNASTNODE_H
#include "ASTNode.h"
class CallFunASTNode :public AbstractASTNode
{
private:
	// 记录参数列表
	AbstractASTNode* varList;
public:
	CallFunASTNode(char* content, AbstractASTNode* varList);
	// ͨ通过 AbstractASTNode 继承
	void printInfo();
};
#endif // !CALLFUNASTNODE_H
