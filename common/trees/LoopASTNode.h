#ifndef LOOPASTNODE_H
#define LOOPASTNODE_H
#include "ASTNode.h"

enum class LoopType
{
    _for,
    _while
};

class LoopASTNode : public AbstractASTNode
{
private:
    // Type of Loop, for or while.
    LoopType loopType;
    AbstractASTNode *cond;
    AbstractASTNode *dec;
    AbstractASTNode *action;

public:
    LoopASTNode(char *content, LoopType type, AbstractASTNode *body, AbstractASTNode *condition);
    LoopASTNode(char *content, LoopType type, AbstractASTNode *body, AbstractASTNode *dec, AbstractASTNode *condition, AbstractASTNode *action);
    void printInfo(int depth);
    inline LoopType getType() { return this->loopType; }
    inline AbstractASTNode *getCond() { return this->cond; }
    inline AbstractASTNode *getDec() { return this->dec; }
    inline AbstractASTNode *getAction() { return this->action; }
};
#endif // !LOOPASTNODE_H
