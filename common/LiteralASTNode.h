#ifndef LITERAL_H
#define LITERAL_H
#include "ASTNode.h"
class LiteralASTNode : public AbstractASTNode {
public:
    LiteralASTNode(char* content);
    // 通过 AbstractASTNode 继承
    void printInfo(int depth);
    int getValue();
};
#endif
