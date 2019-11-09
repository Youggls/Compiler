#include "StmtASTNode.h"

StmtASTNode::StmtASTNode(StmtType type) : AbstractASTNode(ASTNodeType::stmt) {
    this->type = type;
}

void StmtASTNode::printInfo(int depth) {
    if (this->type == StmtType::compStmt) {
        std::cout << "Comp Stmt" << std::endl;
    }
    else if (this->type == StmtType::defStmt) {
        std::cout << "Def Stmt" << std::endl;
    }
    else if (this->type == StmtType::expStmt) {
        std::cout << "Exp Stmt" << std::endl;
    }
    else if (this->type == StmtType::returnStmt) {
        std::cout << "Return Stmt" << std::endl;
    }
}
