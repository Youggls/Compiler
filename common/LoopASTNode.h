#ifndef LOOPASTNODE_H
#define LOOPASTNODE_H
#include "ASTNode.h"

enum class LoopType {
    _for,
    _whileS
};

class LoopASTNode : public AbstractASTNode
{
private:
    // Type of Loop, for or while.
    LoopType loopType;
public:
    LoopASTNode(char* content, LoopType type);
    void printInfo();
};
#endif // !LOOPASTNODE_H