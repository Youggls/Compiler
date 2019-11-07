#ifndef ASTNODE_H
#define ASTNODE_H
#include <iostream>

enum class ASTNodeType {
	defFunc = 1,
	callFunc = 2,
    literal = 3,
    op = 4,           //包含 assignop ， relop， +， -， *， /， %
    exp = 5,
    stmt = 6,
	loop
};

class AbstractASTNode
{
private:
	ASTNodeType nodeType;
	AbstractASTNode* parent;
	AbstractASTNode* peer;
	AbstractASTNode* child;
protected:
	std::string content;
public:
	AbstractASTNode();
    AbstractASTNode(ASTNodeType nodetype);
	AbstractASTNode(char* content, ASTNodeType nodeType);
	void addChildNode(AbstractASTNode* node);
	void addPeerNode(AbstractASTNode* node);
	AbstractASTNode* getLastPeerNode();
	virtual void printInfo() = 0;
};
#endif
