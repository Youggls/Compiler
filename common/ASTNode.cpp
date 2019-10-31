#include "ASTNode.h"

AbstractASTNode::AbstractASTNode() {
	this->child = NULL;
	this->parent = NULL;
	this->peer = NULL;
	this->content = "Initial stat";
}

AbstractASTNode::AbstractASTNode(char* content) {
	this->child = NULL;
	this->parent = NULL;
	this->peer = NULL;
	this->content = content;
}

void AbstractASTNode::addChildNode(AbstractASTNode* node) {
	this->child = node;
}

void AbstractASTNode::addPeerNode(AbstractASTNode* node) {
	this->peer = node;
}

AbstractASTNode* AbstractASTNode::getLastPeerNode()
{
	AbstractASTNode* t = this;
	while (t->peer != NULL)
	{
		t = t->peer;
	}
	return t;
}
