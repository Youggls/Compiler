#ifndef ASTNODE_H
#define ASTNODE_H
#include <iostream>

enum class ASTNodeType {

};

class AbstractASTNode
{
private:
	ASTNodeType nodeType;
	std::string content;
	AbstractASTNode* parent;
	AbstractASTNode* peer;
	AbstractASTNode* child;
public:
	AbstractASTNode();
	AbstractASTNode(char* content);
	void addChildNode(AbstractASTNode* node);
	void addPeerNode(AbstractASTNode* node);
	AbstractASTNode* getLastPeerNode();
};
#endif
