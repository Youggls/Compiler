#include "DefFunASTNode.h"
#include "DefVarASTNode.h"
#include <cstring>
DefFunASTNode::DefFunASTNode(char* content, AbstractASTNode* argList, AbstractASTNode* funcBody)
    :AbstractASTNode(content, ASTNodeType::defFunc)
{
    this->argList = argList;
    this->addChildNode(funcBody);
}

void DefFunASTNode::printInfo(int depth)
{
    std::cout << "Function define. Name:" << this->content << std::endl;
    std::cout << " ";
    for (int i = 0; i < depth + 1; i++) std::cout << " ";
    std::cout << "Retrun type: ";
    if (this->revType == symbolType::integer) std::cout << "int";
    else if (this->revType == symbolType::Void) std::cout << "void";
    std::cout << std::endl;
    AbstractASTNode* var = (AbstractASTNode*)this->argList;
    while (var != NULL) {
        AbstractASTNode::__printTree(var, depth + 1);
        var = var->getPeer();
    }
}

void DefFunASTNode::setRevType(char* type)
{
    if (strcmp(type, "int") == 0) {
        this->revType = symbolType::integer;
    } else if (strcmp(type, "void") == 0) {
        this->revType = symbolType::Void;
    }
}
