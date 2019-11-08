#ifndef ASTNODE_H
#define ASTNODE_H
#include <iostream>

enum class ASTNodeType {
    defFunc = 1,
    callFunc = 2,
    literal = 3,
    op = 4,         //包含 assignop ， relop， +， -， *， /， %
    exp = 5,
    stmt = 6,
    defVar,
    assignVar,
    identifier,
    loop,
    select
};

class AbstractASTNode
{
private:
    ASTNodeType nodeType;
    AbstractASTNode* parent;
    AbstractASTNode* peer;
    AbstractASTNode* child;
    static void __printTree(AbstractASTNode* node, int depth);
protected:
    std::string content;
    inline AbstractASTNode* getChild() { return this->child; }
    inline AbstractASTNode* getPeer() { return this->peer; }

public:
    AbstractASTNode();
    AbstractASTNode(ASTNodeType nodetype);
    AbstractASTNode(char* content, ASTNodeType nodeType);
    void addChildNode(AbstractASTNode* node);
    void addPeerNode(AbstractASTNode* node);
    AbstractASTNode* getLastPeerNode();
    void printTree();
    virtual void printInfo() = 0;
};
#endif
