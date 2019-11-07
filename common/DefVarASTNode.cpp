#include "DefVarASTNode.h"
#include <cstring>
DefVarASTNode::DefVarASTNode(char* content, AbstractASTNode* value)
    : AbstractASTNode(content, ASTNodeType::defVar)
{
    this->type = VarType::unset;
    this->addChildNode(value);
}

void DefVarASTNode::printInfo()
{
    std::cout << "Variation define.";
    if (type == VarType::integer) std::cout << "integer ";
    std::cout << this->content << std::endl;
    // Need to fix indent
    if (this->getChild() != NULL) this->getChild()->printInfo();
}

void DefVarASTNode::setAllType(char* type) {
    VarType varType;
    if (strcmp(type, "int") == 0) {
        varType = VarType::integer;
    }
    this->type = varType;
    DefVarASTNode* peer = (DefVarASTNode*)this->getPeer();
    while (peer != NULL) {
        peer->type = varType;
        peer = (DefVarASTNode*)peer->getPeer();
    }
}
