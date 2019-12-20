#include "DefVarASTNode.h"
#include <cstring>
DefVarASTNode::DefVarASTNode(char *content, AbstractASTNode *value)
    : AbstractASTNode(content, ASTNodeType::defVar)
{
    this->type = symbolType::unset;
    this->addChildNode(value);
}
DefVarASTNode::DefVarASTNode(char* structTypeName, char* structIdName)
    : AbstractASTNode(structIdName, ASTNodeType::defVar)
{
    this->type = symbolType::Struct;
    this->structType = structTypeName;
}

void DefVarASTNode::printInfo(int depth)
{
    std::cout << "Variation define.";
    if (type == symbolType::integer)
        std::cout << "integer ";
    else if (type == symbolType::pointer)
        std::cout << "pointer ";
    else if (type == symbolType::Array)
        std::cout << "array ";
    else if (type == symbolType::Struct)
        std::cout << "struct " << this->structType << " ";
    std::cout << this->content << std::endl;
}

void DefVarASTNode::setAllType(char *type)
{
    symbolType varType;
    if (strcmp(type, "int") == 0)
    {
        varType = symbolType::integer;
    }
    else if (strcmp(type, "void") == 0)
    {
        varType = symbolType::Void;
    }
    else if (strcmp(type, "integer pointer") == 0)
    {
        varType = symbolType::pointer;
    }
    else if (strcmp(type, "struct") == 0)
    {
        varType = symbolType::Struct;
    }
    else if (strcmp(type, "array") == 0) {
        varType = symbolType::Array;
    }
    if (this->type == symbolType::unset) {
        this->type = varType;
    }
    DefVarASTNode *peer = (DefVarASTNode *)this->getPeer();
    while (peer != NULL)
    {
        if (peer->type == symbolType::unset) {
            peer->type = varType;
        }
        peer = (DefVarASTNode *)peer->getPeer();
    }
}

void DefVarASTNode::setArrayLength(char *length) {
    this->arrayLength = atoi(length);
}
