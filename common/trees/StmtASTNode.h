#ifndef STMTASTNODE_H
#define STMTASTNODE_H
#include "ASTNode.h"

enum class StmtType
{
    compStmt = 1,
    expStmt = 2,
    defStmt = 3,
    returnStmt = 4,
};

class StmtASTNode : public AbstractASTNode
{
private:
    StmtType type;

public:
    inline StmtType getStmtType(){ return this->type;}
    StmtASTNode(StmtType type);
    void printInfo(int depth);
};

#endif
