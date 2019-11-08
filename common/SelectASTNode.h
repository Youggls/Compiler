#ifndef SELECTASTNODE_H
#define SELECTASTNODE_H
#include "ASTNode.h"
#include "StmtASTNode.h"

enum class SelectType {
    _if,
    _else,
    _else_if
};
class SelectASTNode : public AbstractASTNode
{
private:
    // if & else if contain 2/3 child node, qulification statement and 'else'/'else if' node(optional)
    SelectType selectType;
public:
    SelectASTNode(char* content, SelectType type);
    void printInfo();
};
#pragma once
#endif // !SELECTASTNODE_H