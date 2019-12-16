#include "InterMediate.h"
#include <typeinfo>
#include <cstdio>
InterMediate::InterMediate(RootASTNode *rootNode)
{
    tempVar.reserve(100);
    this->root = rootNode;
    this->rootTable = new SymbolTable(false);
}

void InterMediate::Generate(AbstractASTNode *node, SymbolTable *symbolTable)
{
    if (node == NULL)
    {
        std::cout << "NULL" << std::endl;
    }
    if (node == NULL)
        return;
    AbstractASTNode *p = node->getChild();
    switch (node->getNodeType())
    {
    case ASTNodeType::defFunc:
    {
        FuncSymbol *func = new FuncSymbol(node);
        this->funcTable.addFunction(func);
        while (p != NULL)
        {
            Generate(p, symbolTable->createChildTable(true));
            p = p->getPeer();
        }
        break;
    }
    case ASTNodeType::callFunc:
    {
        int count = 0;
        AbstractASTNode *var = ((CallFunASTNode *)node)->getVarList();
        std::string addOn = "";
        while (var != NULL)
        {
            count = count + 1;
            Quad *temp;
            if (var->getNodeType() == ASTNodeType::assignVar)
            {
                symbol *arg1 = symbolTable->findSymbol(var->getContent());
                if (arg1 == NULL)
                {
                    std::cout << "\033[31mError: \033[0m"
                              << "value not defined" << std::endl;
                    exit(1);
                }
                temp = new Quad(OpCode::PARAM, arg1, (symbol *)NULL);
                switch (arg1->getIdType())
                {
                case symbolType::integer:
                    addOn = addOn + "_i";
                    break;
                default:
                    break;
                }
            }
            else if (var->getNodeType() == ASTNodeType::literal)
            {
                int arg1 = std::stoi(var->getContent());
                temp = new Quad(OpCode::PARAM, arg1, (symbol *)NULL);
                addOn = addOn + "_i";
            }
            else if (var->getNodeType() == ASTNodeType::op)
            {
                symbol *arg1 = GenerateOp((OperatorASTNode *)var, symbolTable);
                temp = new Quad(OpCode::PARAM, arg1, (symbol *)NULL);
                switch (arg1->getIdType())
                {
                case symbolType::integer:
                    addOn = addOn + "_i";
                    break;
                default:
                    break;
                }
            }
            this->quads.push_back(*temp);
            var = var->getPeer();
        }
        FuncSymbol *funSym = this->funcTable.findFunction(node->getContent() + addOn);
        if (funSym == NULL)
        {
            std::cout << "\033[31mError: \033[0m"
                      << " function is not decleared." << std::endl;
            exit(1);
        }
        symbol *funcSymbol = new symbol(funSym->getKeyName(), symbolType::Void);
        // symbol *funcSymbol = new symbol(funSym->getFunName(), symbolType::Void);
        symbol *tempV = new symbol("Temp" + std::to_string(tempVar.size()), symbolType::integer);
        Quad *temp = new Quad(OpCode::CALL, funcSymbol, count, tempV);
        this->quads.push_back(*temp);
    }
    case ASTNodeType::literal:
    {
        if (node->getParent()->getNodeType() == ASTNodeType::op)
        {
            OperatorASTNode *par = (OperatorASTNode *)node->getParent();
            if (par->getType() == opType::And || par->getType() == opType::Or || par->getType() == opType::Not)
            {
                Quad *trueQuad = new Quad(OpCode::JUMP_GREAT, std::stoi(node->getContent()), 0, (int)NULL);
                Quad *falseQuad = new Quad(OpCode::JUMP, (int)NULL);
                std::list<int> trueL;
                trueL.push_back(quads.size());
                this->quads.push_back(*trueQuad);
                std::list<int> falseL;
                falseL.push_back(quads.size());
                this->quads.push_back(*falseQuad);
                trueList.push(trueL);
                falseList.push(falseL);
            }
        }
        break;
    }
    case ASTNodeType::op:
    {
        if (((OperatorASTNode *)node)->getType() == opType::And || ((OperatorASTNode *)node)->getType() == opType::Or)
        {
            Generate(p, symbolTable);
            signal.push(quads.size());
            Generate(p->getPeer(), symbolTable);
        }
        else if (((OperatorASTNode *)node)->getType() == opType::Not || ((OperatorASTNode *)node)->getType() == opType::Relop)
        {
            while (p != NULL)
            {
                Generate(p, symbolTable);
                p = p->getPeer();
            }
        }
        this->GenerateOp((OperatorASTNode *)node, symbolTable);
        break;
    }
    case ASTNodeType::stmt:
    {
        while (p != NULL)
        {
            Generate(p, this->GenerateStmt((StmtASTNode *)node, symbolTable));
            p = p->getPeer();
        }
        break;
    }
    case ASTNodeType::defVar:
    {
        DefVarASTNode *tempNode = (DefVarASTNode *)node;
        symbolTable->addSymbol(tempNode->getContent(), tempNode->getSymbolType());
        symbol *ppp = symbolTable->findSymbol(tempNode->getContent());
        while (p != NULL)
        {
            Generate(p, symbolTable);
            p = p->getPeer();
        }
        break;
    }
    case ASTNodeType::assignVar:
    {
        if (node->getParent()->getNodeType() == ASTNodeType::op)
        {
            OperatorASTNode *par = (OperatorASTNode *)node->getParent();
            if (par->getType() == opType::And || par->getType() == opType::Or || par->getType() == opType::Not)
            {
                symbol *arg1 = symbolTable->findSymbol(node->getContent());
                Quad *trueQuad = new Quad(OpCode::JUMP_GREAT, arg1, 0, (int)NULL);
                Quad *falseQuad = new Quad(OpCode::JUMP, (int)NULL);
                std::list<int> trueL;
                trueL.push_back(quads.size());
                this->quads.push_back(*trueQuad);
                std::list<int> falseL;
                falseL.push_back(quads.size());
                this->quads.push_back(*falseQuad);
                trueList.push(trueL);
                falseList.push(falseL);
            }
        }
        break;
    }
    case ASTNodeType::loop: // for(1.DefASTNODE, 2.OperatorASTNODE, 3.OperatorASTNODE, 4.StmtASTNODE)
    {
        LoopASTNode *loop = (LoopASTNode *)node;
        if (loop->getType() == LoopType::_for)
        {
            SymbolTable *childTable = symbolTable->createChildTable(false);
            Generate(((LoopASTNode *)node)->getDec(), childTable);
            int start = quads.size();
            Generate(((LoopASTNode *)node)->getCond(), childTable);
            std::list<int> JudgeTrue = trueList.top();
            std::list<int> JudgeFalse = falseList.top();
            trueList.pop();
            falseList.pop();
            backpatch(&JudgeTrue, JudgeTrue.back() + 2);
            while (p != NULL)
            {
                Generate(p, childTable);
                p = p->getPeer();
            }
            Generate(((LoopASTNode *)node)->getAction(), childTable);

            Quad *temp = new Quad(OpCode::JUMP, start);
            this->quads.push_back(*temp);
            int end = quads.size();
            backpatch(&JudgeFalse, end);
        }
        else if (loop->getType() == LoopType::_while)
        {
            int start = quads.size();
            Generate(((LoopASTNode *)node)->getCond(), symbolTable);
            // std::cout << "TrueList：" << this->trueList.size() << std::endl
            //           << "FalseList: " << this->falseList.size() << std::endl;
            std::list<int> JudgeTrue = trueList.top();
            std::list<int> JudgeFalse = falseList.top();
            trueList.pop();
            falseList.pop();
            backpatch(&JudgeTrue, JudgeTrue.back() + 2);
            while (p != NULL)
            {
                Generate(p, symbolTable->createChildTable(false));
                p = p->getPeer();
            }

            Quad *temp = new Quad(OpCode::JUMP, start);
            this->quads.push_back(*temp);
            int end = quads.size();
            backpatch(&JudgeFalse, end);
        }
        break;
    }
    case ASTNodeType::select: // Just IF and ELSE.
    {
        SelectASTNode *select = (SelectASTNode *)node;
        Generate(select->getCondition(), symbolTable);
        int start = quads.size();
        std::list<int> JudgeTrue = trueList.top();
        std::list<int> JudgeFalse = falseList.top();
        trueList.pop();
        falseList.pop();

        backpatch(&JudgeTrue, start);
        Generate(select->getBody(), symbolTable);
        if (select->getElse() != NULL)
        {
            Quad *temp = new Quad(OpCode::JUMP, (int)NULL);
            this->quads.push_back(*temp);
            temp = &quads.back();
            int elseStart = quads.size();
            Generate(select->getElse(), symbolTable);
            backpatch(&JudgeFalse, elseStart);
            int end = quads.size();
            temp->backpatch(end);
        }
        else
        {
            int end = quads.size();
            backpatch(&JudgeFalse, end);
        }
        break;
    }
    case ASTNodeType::root:
    {
        while (p != NULL)
        {
            Generate(p, symbolTable);
            p = p->getPeer();
        }
        break;
    }
    default:
        std::cout << "Hello! Something Wrong happened!\n";
        break;
    }
    // std::cout << "Last content is: " << node->getContent() << "\tType is:" << (int)node->getNodeType() << std::endl;
}

SymbolTable *InterMediate::GenerateStmt(StmtASTNode *node, SymbolTable *symbolTable)
{
    if (node->getStmtType() != StmtType::compStmt)
        return symbolTable;
    if (node->getParent()->getNodeType() == ASTNodeType::loop)
        return symbolTable;
    if (node->getParent()->getNodeType() == ASTNodeType::defFunc)
        return symbolTable;
    return symbolTable->createChildTable(false);
}

symbol *InterMediate::GenerateOp(OperatorASTNode *node, SymbolTable *symbolTable)
{
    Quad *temp;
    AbstractASTNode *arg1Node, *arg2Node;
    switch (node->getType())
    {
    case opType::Assignop:
    {
        symbol *result;
        // Quad *temp;
        try
        {
            result = symbolTable->findSymbol(node->getChild()->getContent());
        }
        catch (...)
        {
            std::cout << "Exception occured. 出现异常了！" << std::endl;
        }
        // std::cout << node->getChild()->getContent() << std::endl;
        // 这里可能得捕获 赋值给常量的异常、变量未定义的异常
        AbstractASTNode *arg1Node = node->getChild()->getPeer();
        if (arg1Node->getNodeType() == ASTNodeType::assignVar)
        {
            symbol *arg1 = symbolTable->findSymbol(arg1Node->getContent());
            temp = new Quad(OpCode::ASSIGN, arg1, result);
        }
        else if (arg1Node->getNodeType() == ASTNodeType::op)
        {
            symbol *arg1 = GenerateOp((OperatorASTNode *)arg1Node, symbolTable);
            temp = new Quad(OpCode::ASSIGN, arg1, result);
        }
        else if (arg1Node->getNodeType() == ASTNodeType::literal)
        {
            int arg1 = std::stoi(arg1Node->getContent());
            temp = new Quad(OpCode::ASSIGN, arg1, result);
        }
        this->quads.push_back(*temp);
        return result;
        break;
    }
    case opType::Relop: // 需要回填：把index加入trueList和falseList，等别的操作回填它。 < <= > >= != == 子节点 只可能是assignVar、literal
    {
        Quad *tempTrue, *tempFalse;
        arg1Node = node->getChild();
        arg2Node = arg1Node->getPeer();
        if (node->getContent() == ">")
        {
            RelopOp(tempTrue, tempFalse, OpCode::JUMP_GREAT, arg1Node, arg2Node, symbolTable);
        }
        else if (node->getContent() == ">=")
        {
            RelopOp(tempTrue, tempFalse, OpCode::JUMP_EQ_GREAT, arg1Node, arg2Node, symbolTable);
        }
        else if (node->getContent() == "<")
        {
            RelopOp(tempTrue, tempFalse, OpCode::JUMP_SMALL, arg1Node, arg2Node, symbolTable);
        }
        else if (node->getContent() == "<=")
        {
            RelopOp(tempTrue, tempFalse, OpCode::JUMP_EQ_SMALL, arg1Node, arg2Node, symbolTable);
        }
        else if (node->getContent() == "!=")
        {
            RelopOp(tempTrue, tempFalse, OpCode::JUMP_NOT_EQUAL, arg1Node, arg2Node, symbolTable);
        }
        else if (node->getContent() == "==")
        {
            RelopOp(tempTrue, tempFalse, OpCode::JUMP_EQUAL, arg1Node, arg2Node, symbolTable);
        }
        break;
    }
    case opType::Plus: // 可能需要重构一下，方便看
    {
        symbol *result = new symbol("Temp" + std::to_string(tempVar.size()), symbolType::integer);
        arg1Node = node->getChild();
        arg2Node = arg1Node->getPeer();
        tempVar.push_back(result);
        result = tempVar.back();
        temp = this->CaculateOp(OpCode::PLUS, arg1Node, arg2Node, result, symbolTable);
        this->quads.push_back(*temp);
        return result;
        break;
    }
    case opType::Minus:
    {
        symbol *result = new symbol("Temp" + std::to_string(tempVar.size()), symbolType::integer);
        arg1Node = node->getChild();
        arg2Node = arg1Node->getPeer();
        tempVar.push_back(result);
        result = tempVar.back();
        temp = this->CaculateOp(OpCode::MINUS, arg1Node, arg2Node, result, symbolTable);
        this->quads.push_back(*temp);
        return result;
        break;
    }
    case opType::Times:
    {
        symbol *result = new symbol("Temp" + std::to_string(tempVar.size()), symbolType::integer);
        arg1Node = node->getChild();
        arg2Node = arg1Node->getPeer();
        tempVar.push_back(result);
        result = tempVar.back();
        temp = this->CaculateOp(OpCode::TIMES, arg1Node, arg2Node, result, symbolTable);
        this->quads.push_back(*temp);
        return result;
        break;
    }
    case opType::Div:
    {
        symbol *result = new symbol("Temp" + std::to_string(tempVar.size()), symbolType::integer);
        arg1Node = node->getChild();
        arg2Node = arg1Node->getPeer();
        tempVar.push_back(result);
        result = tempVar.back();
        temp = this->CaculateOp(OpCode::DIV, arg1Node, arg2Node, result, symbolTable);
        this->quads.push_back(*temp);
        return result;
        break;
    }
    case opType::Mod:
    {
        symbol *result = new symbol("Temp" + std::to_string(tempVar.size()), symbolType::integer);
        arg1Node = node->getChild();
        arg2Node = arg1Node->getPeer();
        tempVar.push_back(result);
        result = tempVar.back();
        temp = this->CaculateOp(OpCode::MOD, arg1Node, arg2Node, result, symbolTable);
        this->quads.push_back(*temp);
        return result;
        break;
    }
    case opType::Power:
    {
        symbol *result = new symbol("Temp" + std::to_string(tempVar.size()), symbolType::integer);
        arg1Node = node->getChild();
        arg2Node = arg1Node->getPeer();
        tempVar.push_back(result);
        result = tempVar.back();
        temp = this->CaculateOp(OpCode::POWER, arg1Node, arg2Node, result, symbolTable);
        this->quads.push_back(*temp);
        return result;
        break;
    }
    case opType::Negative:
    {
        symbol *result = new symbol("Temp" + std::to_string(tempVar.size()), symbolType::integer);
        arg1Node = node->getChild();
        tempVar.push_back(result);
        result = tempVar.back();
        if (arg1Node->getNodeType() == ASTNodeType::assignVar)
        {
            symbol *arg1 = symbolTable->findSymbol(arg1Node->getContent());
            temp = new Quad(OpCode::NEGATIVE, arg1, result);
        }
        else if (arg1Node->getNodeType() == ASTNodeType::literal)
        {
            int arg1 = std::stoi(arg1Node->getContent());
            temp = new Quad(OpCode::NEGATIVE, arg1, result);
        }
        else if (arg1Node->getNodeType() == ASTNodeType::op)
        {
            symbol *arg1 = GenerateOp((OperatorASTNode *)arg1Node, symbolTable);
            temp = new Quad(OpCode::NEGATIVE, arg1, result);
        }
        this->quads.push_back(*temp);
        return result;
        break;
    }
    case opType::SingalAnd:
    {
        symbol *result = new symbol("Temp" + std::to_string(tempVar.size()), symbolType::integer);
        arg1Node = node->getChild();
        tempVar.push_back(result);
        if (arg1Node->getNodeType() == ASTNodeType::assignVar)
        {
            symbol *arg1 = symbolTable->findSymbol(arg1Node->getContent());
            temp = new Quad(OpCode::GET_ADDRESS, arg1, result);
        }
        else
        {
            std::cout << "\033[31mError: \033[0m"
                      << " lvalue required as unary ‘&’ operand" << std::endl;
            exit(-1);
        }
        this->quads.push_back(*temp);
        return result;
        break;
    }
    case opType::And: // 保证栈顶是：node2List, node1List,所以得先遍历子节点，再到&&节点
    {
        std::list<int> leftTrue, rightTrue, leftFalse, rightFalse;
        rightTrue = trueList.top();
        trueList.pop();
        leftTrue = trueList.top();
        trueList.pop();
        rightFalse = falseList.top();
        falseList.pop();
        leftFalse = falseList.top();
        falseList.pop();
        leftFalse.merge(rightFalse);
        falseList.push(leftFalse);
        trueList.push(rightTrue);
        backpatch(&leftTrue, signal.top());
        signal.pop();
        break;
    }
    case opType::Or:
    {
        std::list<int> leftTrue, rightTrue, leftFalse, rightFalse;
        rightTrue = trueList.top();
        trueList.pop();
        leftTrue = trueList.top();
        trueList.pop();
        rightFalse = falseList.top();
        falseList.pop();
        leftFalse = falseList.top();
        falseList.pop();
        leftTrue.merge(rightTrue);
        trueList.push(leftTrue);
        falseList.push(rightFalse);
        backpatch(&leftFalse, signal.top());
        signal.pop();
        break;
    }
    case opType::Not:
    {
        std::list<int> trueL, falseL;
        trueL = trueList.top();
        trueList.pop();
        falseL = falseList.top();
        falseList.pop();
        trueList.push(falseL);
        falseList.push(trueL);
        break;
    }
    default:
        break;
    }
    return NULL;
}

Quad *InterMediate::CaculateOp(OpCode op, AbstractASTNode *arg1Node, AbstractASTNode *arg2Node, symbol *result, SymbolTable *symbolTable)
{
    Quad *temp;
    // symbol *result = new symbol(std::to_string(tempVar.size()), symbolType::integer);
    // tempVar.push_back(result);
    // result = tempVar.back();

    if (arg1Node->getNodeType() == ASTNodeType::assignVar && arg2Node->getNodeType() == ASTNodeType::assignVar)
    {
        symbol *arg1 = symbolTable->findSymbol(arg1Node->getContent());
        symbol *arg2 = symbolTable->findSymbol(arg2Node->getContent());
        temp = new Quad(op, arg1, arg2, result);
    }
    else if (arg1Node->getNodeType() == ASTNodeType::assignVar && arg2Node->getNodeType() == ASTNodeType::op)
    {
        symbol *arg1 = symbolTable->findSymbol(arg1Node->getContent());
        symbol *arg2 = GenerateOp((OperatorASTNode *)arg2Node, symbolTable);
        temp = new Quad(op, arg1, arg2, result);
    }
    else if (arg1Node->getNodeType() == ASTNodeType::assignVar && arg2Node->getNodeType() == ASTNodeType::literal)
    {
        symbol *arg1 = symbolTable->findSymbol(arg1Node->getContent());
        int arg2 = std::stoi(arg2Node->getContent());
        temp = new Quad(op, arg1, arg2, result);
    }
    else if (arg1Node->getNodeType() == ASTNodeType::op && arg2Node->getNodeType() == ASTNodeType::assignVar)
    {
        symbol *arg1 = GenerateOp((OperatorASTNode *)arg1Node, symbolTable);
        symbol *arg2 = symbolTable->findSymbol(arg2Node->getContent());
        temp = new Quad(op, arg1, arg2, result);
    }
    else if (arg1Node->getNodeType() == ASTNodeType::op && arg2Node->getNodeType() == ASTNodeType::op)
    {
        symbol *arg1 = GenerateOp((OperatorASTNode *)arg1Node, symbolTable);
        symbol *arg2 = GenerateOp((OperatorASTNode *)arg2Node, symbolTable);
        temp = new Quad(op, arg1, arg2, result);
    }
    else if (arg1Node->getNodeType() == ASTNodeType::op && arg2Node->getNodeType() == ASTNodeType::literal)
    {
        symbol *arg1 = GenerateOp((OperatorASTNode *)arg1Node, symbolTable);
        int arg2 = std::stoi(arg2Node->getContent());
        temp = new Quad(op, arg1, arg2, result);
    }

    else if (arg1Node->getNodeType() == ASTNodeType::literal && arg2Node->getNodeType() == ASTNodeType::assignVar)
    {
        int arg1 = std::stoi(arg1Node->getContent());
        symbol *arg2 = symbolTable->findSymbol(arg2Node->getContent());
        temp = new Quad(op, arg1, arg2, result);
    }
    else if (arg1Node->getNodeType() == ASTNodeType::literal && arg2Node->getNodeType() == ASTNodeType::op)
    {
        int arg1 = std::stoi(arg1Node->getContent());
        symbol *arg2 = GenerateOp((OperatorASTNode *)arg2Node, symbolTable);
        temp = new Quad(op, arg1, arg2, result);
    }
    else if (arg1Node->getNodeType() == ASTNodeType::literal && arg2Node->getNodeType() == ASTNodeType::literal)
    {
        int arg1 = std::stoi(arg1Node->getContent());
        int arg2 = std::stoi(arg2Node->getContent());
        temp = new Quad(op, arg1, arg2, result);
    }
    return temp;
}

void InterMediate::RelopOp(Quad *trueQuad, Quad *falseQuad, OpCode op, AbstractASTNode *arg1Node, AbstractASTNode *arg2Node, SymbolTable *symbolTable)
{
    if (arg1Node->getNodeType() == ASTNodeType::assignVar && arg2Node->getNodeType() == ASTNodeType::assignVar)
    {
        trueQuad = new Quad(op, symbolTable->findSymbol(arg1Node->getContent()), symbolTable->findSymbol(arg2Node->getContent()), (int)NULL);
        falseQuad = new Quad(OpCode::JUMP, (int)NULL);
    }
    else if (arg1Node->getNodeType() == ASTNodeType::assignVar && arg2Node->getNodeType() == ASTNodeType::literal)
    {
        trueQuad = new Quad(op, symbolTable->findSymbol(arg1Node->getContent()), std::stoi(arg2Node->getContent()), (int)NULL);
        falseQuad = new Quad(OpCode::JUMP, (int)NULL);
    }
    else if (arg1Node->getNodeType() == ASTNodeType::literal && arg2Node->getNodeType() == ASTNodeType::assignVar)
    {
        trueQuad = new Quad(op, std::stoi(arg1Node->getContent()), symbolTable->findSymbol(arg2Node->getContent()), (int)NULL);
        falseQuad = new Quad(OpCode::JUMP, (int)NULL);
    }
    else if (arg1Node->getNodeType() == ASTNodeType::literal && arg2Node->getNodeType() == ASTNodeType::literal)
    {
        trueQuad = new Quad(op, std::stoi(arg1Node->getContent()), std::stoi(arg2Node->getContent()), (int)NULL);
        falseQuad = new Quad(OpCode::JUMP, (int)NULL);
    }
    std::list<int> trueL; // Use size to get the index of true quad will be pushed
    trueL.push_back(quads.size());
    this->quads.push_back(*trueQuad);
    std::list<int> falseL; // Same as the upper one
    falseL.push_back(quads.size());
    this->quads.push_back(*falseQuad);
    trueList.push(trueL);
    falseList.push(falseL);
    return;
}

std::list<int> *InterMediate::makelist(int index)
{
    std::list<int> *jumpList = new std::list<int>();
    jumpList->push_back(index);
    return jumpList;
}
std::list<int> *InterMediate::merge(std::list<int> *list1, std::list<int> *list2)
{
    list1->merge(*list2);
    return list1;
}
void InterMediate::backpatch(std::list<int> *backList, int target)
{
    std::list<int>::iterator it;
    for (it = backList->begin(); it != backList->end(); it++)
    {
        quads[*it].backpatch(target);
    }
    return;
}
void InterMediate::printQuads()
{
    std::vector<Quad>::iterator it;
    std::cout << "\t   Operator   \targ1\targ2\tresult" << std::endl;
    int count = 0;
    for (it = this->quads.begin(); it != this->quads.end(); it++)
    {
        std::cout << count++ << "\t";
        it->printQuad();
    }
    return;
}