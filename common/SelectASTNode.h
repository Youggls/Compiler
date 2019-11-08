#ifndef SELECTASTNODE_H
#define SELECTASTNODE_H
#include "ASTNode.h"
#include "StmtASTNode.h"

enum class SelectType {
    _if = 1,
    _else = 2,
    _else_if = 3
};
class SelectASTNode : public AbstractASTNode
{
private:
    AbstractASTNode* condition;
    AbstractASTNode* elseStmt;
    AbstractASTNode* body;
    // if & else if contain 2/3 child node, qulification statement and 'else'/'else if' node(optional)
    SelectType selectType;
public:
    SelectASTNode(char* content, SelectType type, AbstractASTNode* body, AbstractASTNode* condition, AbstractASTNode* elseStmt=NULL);
    void printInfo(int depth);
};
#endif // !SELECTASTNODE_H