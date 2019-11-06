#ifndef OPERATORASTNODE_H
#define OPERATORASTNODE_H
#include "ASTNode.h"

enum class opType {
    Assignop = 1,
    Relop = 2,
    plus = 3,
    minus = 4,
    times = 5,
    div = 6,
    mod = 7,
    power = 8
};

class OperatorASTNode:public AbstractASTNode {
private:
    opType type;
public: 
    OperatorASTNode(char* content, opType type);
    void printInfo();
};
#endif
