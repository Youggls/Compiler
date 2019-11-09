#include "ExpASTNode.h"

ExpASTNode::ExpASTNode() :AbstractASTNode(ASTNodeType::exp) {

}

void ExpASTNode::printInfo(int depth) {
    std::cout << "Expr, " << std::endl;
}
