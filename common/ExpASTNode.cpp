#include "ExpASTNode.h"

ExpASTNode::ExpASTNode() :AbstractASTNode(ASTNodeType::exp) {

}

void ExpASTNode::printInfo() {
    std::cout << "Expr, " << std::endl;
}
