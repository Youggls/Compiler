#ifndef STMTASTNODE_H
#define STMTASTNODE_H
#include "ASTNode.h"

enum class StmtType {
    compStmt = 1,
    expStmt = 2,
    defStmt = 3,
};

class StmtASTNode : public AbstractASTNode {
private:
    StmtType type;
public:
    StmtASTNode(StmtType type);
    void printInfo();
};

#endif
