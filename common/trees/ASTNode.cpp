#include "ASTNode.h"
#include <typeinfo>

AbstractASTNode::AbstractASTNode()
{
  this->child = NULL;
  this->parent = NULL;
  this->peer = NULL;
  this->content = "Initial stat";
}

AbstractASTNode::AbstractASTNode(ASTNodeType nodeType)
{
  this->child = NULL;
  this->parent = NULL;
  this->peer = NULL;
  this->nodeType = nodeType;
}

AbstractASTNode::AbstractASTNode(char *content, ASTNodeType nodeType)
{
  this->child = NULL;
  this->parent = NULL;
  this->peer = NULL;
  this->content = content;
  this->nodeType = nodeType;
}

void AbstractASTNode::addChildNode(AbstractASTNode *node)
{
  if (node != NULL)
  {
    node->parent = this;
    // 儿子的兄弟也是我的儿子
    AbstractASTNode *peerNode = node->peer;
    // 遍历所有儿子的兄弟，他们的父亲都是我
    while (peerNode != NULL)
    {
      peerNode->parent = this;
      peerNode = peerNode->peer;
    }
  }
  this->child = node;
}

void AbstractASTNode::addPeerNode(AbstractASTNode *node)
{
  if (node != NULL)
    node->parent = this->parent;
  this->peer = node;
}

AbstractASTNode *AbstractASTNode::getLastPeerNode()
{
  AbstractASTNode *t = this;
  while (t->peer != NULL)
  {
    t = t->peer;
  }
  return t;
}

void AbstractASTNode::__printTree(AbstractASTNode *node, int depth)
{
  if (node == NULL)
    return;
  std::cout << (int)node->nodeType << " " << typeid(*node).name() << "  "
            << "\t";
  std::cout << depth;
  for (int i = 0; i < depth; i++)
    std::cout << " ";
  node->printInfo(depth);
  AbstractASTNode *p = node->child;
  while (p != NULL)
  {
    AbstractASTNode::__printTree(p, depth + 1);
    p = p->peer;
  }
}

void AbstractASTNode::printTree()
{
  AbstractASTNode::__printTree(this, 0);
}

RootASTNode::RootASTNode() : AbstractASTNode(ASTNodeType::root)
{
  this->content = "Root";
}

void RootASTNode::printInfo(int depth)
{
  std::cout << this->content << std::endl;
}
