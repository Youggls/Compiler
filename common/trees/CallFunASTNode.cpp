#include "CallFunASTNode.h"
#include "VarASTNode.h"
CallFunASTNode::CallFunASTNode(char *content, AbstractASTNode *varList)
    : AbstractASTNode(content, ASTNodeType::callFunc)
{
    this->varList = varList;
    if (varList != NULL) {
        varList->setParent(this);
    }
}

void CallFunASTNode::printInfo(int depth) {
    std::cout << "Call Function." << this->content << std::endl;
    AbstractASTNode *var = this->varList;
    while (var != NULL) {
        AbstractASTNode::__printTree(var, depth + 1);
        var = var->getPeer();
    }
}
