#include "StmtASTNode.h"

StmtAstNode::StmtAstNode() : AbstractASTNode(ASTNodeType::stmt) {

}

void StmtAstNode::printInfo() {
    std::cout<<"Stmt, "<<std::endl;
}
