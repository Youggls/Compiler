#include "SelectASTNode.h"

SelectASTNode::SelectASTNode(char *content, SelectType type, AbstractASTNode *body,
                             AbstractASTNode *cond, AbstractASTNode *elseStmt)
    : AbstractASTNode(content, ASTNodeType::select)
{
    this->selectType = type;
    this->body = body;
    this->body->setParent(this);
    this->condition = cond;
    this->condition->setParent(this);
    this->elseStmt = elseStmt;
    if (elseStmt) {
        this->elseStmt->setParent(this);
    }
}

void SelectASTNode::printInfo(int depth)
{
    if (this->selectType == SelectType::_if)
    {
        std::cout << "IF" << std::endl;
        AbstractASTNode::__printTree(this->condition, depth + 1);
        AbstractASTNode::__printTree(this->body, depth + 1);
        if (this->elseStmt != NULL)
        {
            for (int i = 0; i < depth; i++)
                std::cout << " ";
            std::cout << "ELSE" << std::endl;
            AbstractASTNode::__printTree(this->elseStmt, depth + 1);
        }
    }
}
