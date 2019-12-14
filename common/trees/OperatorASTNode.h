#ifndef OPERATORASTNODE_H
#define OPERATORASTNODE_H
#include "ASTNode.h"

enum class opType
{
    Assignop = 1,   // =
    Relop = 2,      // < > <= >=
    Plus = 3,       // +
    Minus = 4,      // -
    Times = 5,      // *
    Div = 6,        // /
    Mod = 7,        // %
    Power = 8,      // ^
    And = 9,        // &&
    Or = 10,        // ||
    Negative = 11,  // ???
    Not = 12,       // !
    SingalAnd = 13, // ???
};

class OperatorASTNode : public AbstractASTNode
{
private:
    opType type;

public:
    OperatorASTNode(char *content, opType type);
    void printInfo(int depth);
    inline opType getType() { return this->type; }
};
#endif
