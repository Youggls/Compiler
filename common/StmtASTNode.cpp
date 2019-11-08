#include "StmtASTNode.h"

StmtAstNode::StmtAstNode() : AbstractASTNode(ASTNodeType::stmt) {

    void StmtASTNode::printInfo() {
        if (this->type == StmtType::compStmt) {
            std::cout << "Comp Stmt" << std::endl;
        }
        else if (this->type == StmtType::defStmt) {
            std::cout << "Def Stmt" << std::endl;
        }
        else if (this->type == StmtType::expStmt) {
            std::cout << "Exp Stmt" << std::endl;
        }
    }
