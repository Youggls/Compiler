#include "InterMediate.h"

InterMediate::InterMediate(RootASTNode *rootNode)
{
    tempVar.reserve(100);
    this->root = rootNode;
    this->rootTable = new SymbolTable(false);
}

void InterMediate::Generate(AbstractASTNode *node, SymbolTable *symbolTable)
{
    if (node == NULL)
        return;
    AbstractASTNode *p = node->getChild();
    switch (node->getNodeType())
    {
    case ASTNodeType::defFunc:
        FuncSymbol *func = new FuncSymbol(node);
        this->funcTable.addFunction(func);
        while (p != NULL)
        {
            Generate(p, symbolTable->createChildTable(true));
            p = p->getPeer();
        }
        break;
        // case ASTNodeType::callFunc:
        // 暂且放下，没想好四元式咋表示
        // JUMP - - Functable
        /*
            param t_1
            param t_2
            param t_3
            param t_4
            call f, 4
        */
    case ASTNodeType::literal: //必是叶节点，直接pass. ！不能直接pass，父节点是&& || !的时候，要弄个truelist 和falselist
        if (node->getParent()->getNodeType() == ASTNodeType::op)
        {
            OperatorASTNode *par = (OperatorASTNode *)node->getParent();
            if (par->getType() == opType::And || par->getType() == opType::Or || par->getType() == opType::Not)
            {
                Quad *trueQuad = new Quad(OpCode::JUMP_GREAT, std::stoi(node->getContent()), 0, (int)NULL);
                Quad *falseQuad = new Quad(OpCode::JUMP, (int)NULL);
                std::list<int> trueL(quads.size());
                quads.push_back(*trueQuad);
                std::list<int> falseL(quads.size());
                quads.push_back(*falseQuad);
                trueList.push(trueL);
                falseList.push(falseL);
            }
        }
        break;
    case ASTNodeType::op: // 它的子节点只能是 literal / assignVar / op
        this->GenerateOp((OperatorASTNode *)node, symbolTable);
        break;
    case ASTNodeType::stmt: // (1/1) 子符号表 仅在Exp Stmt时候创建子符号表
        while (p != NULL)
        {
            Generate(p, this->GenerateStmt((StmtASTNode *)node, symbolTable));
            p = p->getPeer();
        }
        break;
    case ASTNodeType::defVar:
        DefVarASTNode *tempNode = (DefVarASTNode *)node; // 下面一直报错，看着烦
        symbolTable->addSymbol(tempNode->getContent(), tempNode->getSymbolType());
        while (p != NULL)
        {
            Generate(p, symbolTable);
            p = p->getPeer();
        }
        break;
    case ASTNodeType::assignVar: // 叶节点
        if (node->getParent()->getNodeType() == ASTNodeType::op)
        {
            OperatorASTNode *par = (OperatorASTNode *)node->getParent();
            if (par->getType() == opType::And || par->getType() == opType::Or || par->getType() == opType::Not)
            {
                symbol *arg1 = symbolTable->findSymbol(node->getContent());
                Quad *trueQuad = new Quad(OpCode::JUMP_GREAT, arg1, 0, (int)NULL);
                Quad *falseQuad = new Quad(OpCode::JUMP, (int)NULL);
                std::list<int> trueL(quads.size());
                quads.push_back(*trueQuad);
                std::list<int> falseL(quads.size());
                quads.push_back(*falseQuad);
                trueList.push(trueL);
                falseList.push(falseL);
            }
        }
        break;
    case ASTNodeType::loop: // for(1.DefASTNODE, 2.OperatorASTNODE, 3.OperatorASTNODE, 4.StmtASTNODE)
        LoopASTNode *loop = (LoopASTNode *)node;
        if (loop->getType() == LoopType::_for)
        {
        }
        else if (loop->getType() == LoopType::_while)
        {
            int start = quads.size();
            while (p != NULL)
            {
                Generate(p, symbolTable->createChildTable(false));
                p = p->getPeer();
            }
            std::list<int> JudgeTrue = trueList.top();
            std::list<int> JudgeFalse = falseList.top();
            trueList.pop();
            falseList.pop();

            backpatch(&JudgeTrue, JudgeTrue.back() + 2);
            Quad *temp = new Quad(OpCode::JUMP, start);
            quads.push_back(*temp);
            int end = quads.size();
            backpatch(&JudgeFalse, end);
        }
        break;
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
            quads.push_back(*temp);
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
        while (p != NULL)
        {
            Generate(p, symbolTable);
            p = p->getPeer();
        }
        break;
    default:
        std::cout << "Hello! Something Wrong happened!";
        break;
    }
}

SymbolTable *InterMediate::GenerateStmt(StmtASTNode *node, SymbolTable *symbolTable)
{
    if (node->getStmtType() != StmtType::compStmt)
        return symbolTable;
    if (node->getParent()->getNodeType() == ASTNodeType::loop)
        return symbolTable;
    return symbolTable->createChildTable(false);
}

symbol *InterMediate::GenerateOp(OperatorASTNode *node, SymbolTable *symbolTable)
{
    Quad *temp;
    AbstractASTNode *arg1Node, *arg2Node;
    switch (node->getType()) // 报错是switch 多重定义
    {
    case opType::Assignop:
        symbol *result;
        // Quad *temp;
        try
        {
            result = symbolTable->findSymbol(node->getChild()->getContent());
        }
        catch (...)
        {
            std::cout << "Exception occured" << std::endl;
        }
        // 这里可能得捕获 赋值给常量的异常、变量未定义的异常
        AbstractASTNode *arg1Node = node->getChild()->getPeer();
        if (arg1Node->getNodeType == ASTNodeType::assignVar) // Var = Var
        {
            symbol *arg1 = symbolTable->findSymbol(arg1Node->getContent());
            temp = new Quad(OpCode::ASSIGN, arg1, result);
        }
        else if (arg1Node->getNodeType == ASTNodeType::op)
        {
            symbol *arg1 = GenerateOp((OperatorASTNode *)arg1Node, symbolTable);
            temp = new Quad(OpCode::ASSIGN, arg1, result);
        }
        else if (arg1Node->getNodeType == ASTNodeType::literal)
        {
            int arg1 = std::stoi(arg1Node->getContent());
            temp = new Quad(OpCode::ASSIGN, arg1, result);
        }
        this->quads.push_back(*temp);
        break;
    case opType::Relop: // 需要回填：把index加入trueList和falseList，等别的操作回填它。 < <= > >= != == 子节点 只可能是assignVar、literal
        Quad *tempTrue, *tempFalse;
        arg1Node = node->getChild();
        arg2Node = arg1Node->getPeer();
        if (node->getContent() == ">")
        {
            RelopOp(tempTrue, tempFalse, OpCode::JUMP_GREAT, arg1Node, arg2Node, symbolTable);
        }
        else if (node->getContent() == ">=")
        {
            RelopOp(tempTrue, tempFalse, OpCode::JUMP_EQ_GRATE, arg1Node, arg2Node, symbolTable);
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
    case opType::Plus: // 可能需要重构一下，方便看
        symbol *result = new symbol(std::to_string(tempVar.size()), symbolType::integer);
        arg1Node = node->getChild();
        arg2Node = arg1Node->getPeer();
        tempVar.push_back(result);
        result = tempVar.back();
        temp = this->CaculateOp(OpCode::PLUS, arg1Node, arg2Node, result, symbolTable);
        this->quads.push_back(*temp);
        break;
    case opType::Minus:
        symbol *result = new symbol(std::to_string(tempVar.size()), symbolType::integer);
        arg1Node = node->getChild();
        arg2Node = arg1Node->getPeer();
        tempVar.push_back(result);
        result = tempVar.back();
        temp = this->CaculateOp(OpCode::MINUS, arg1Node, arg2Node, result, symbolTable);
        this->quads.push_back(*temp);
        break;
    case opType::Times:
        symbol *result = new symbol(std::to_string(tempVar.size()), symbolType::integer);
        arg1Node = node->getChild();
        arg2Node = arg1Node->getPeer();
        tempVar.push_back(result);
        result = tempVar.back();
        temp = this->CaculateOp(OpCode::TIMES, arg1Node, arg2Node, result, symbolTable);
        this->quads.push_back(*temp);
        break;
    case opType::Div:
        symbol *result = new symbol(std::to_string(tempVar.size()), symbolType::integer);
        arg1Node = node->getChild();
        arg2Node = arg1Node->getPeer();
        tempVar.push_back(result);
        result = tempVar.back();
        temp = this->CaculateOp(OpCode::DIV, arg1Node, arg2Node, result, symbolTable);
        this->quads.push_back(*temp);
        break;
    case opType::Mod:
        symbol *result = new symbol(std::to_string(tempVar.size()), symbolType::integer);
        arg1Node = node->getChild();
        arg2Node = arg1Node->getPeer();
        tempVar.push_back(result);
        result = tempVar.back();
        temp = this->CaculateOp(OpCode::MOD, arg1Node, arg2Node, result, symbolTable);
        this->quads.push_back(*temp);
        break;
    case opType::Power:
        symbol *result = new symbol(std::to_string(tempVar.size()), symbolType::integer);
        arg1Node = node->getChild();
        arg2Node = arg1Node->getPeer();
        tempVar.push_back(result);
        result = tempVar.back();
        temp = this->CaculateOp(OpCode::POWER, arg1Node, arg2Node, result, symbolTable);
        this->quads.push_back(*temp);
        break;
    case opType::Negative:
        symbol *result = new symbol(std::to_string(tempVar.size()), symbolType::integer);
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
        break;

    case opType::SingalAnd:
        std::cout << "Operation for '&' has not been finished." << std::endl;
        break;
    case opType::And: // 保证栈顶是：node2List, node1List,所以得先遍历子节点，再到&&节点
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
        backpatch(&leftTrue, rightTrue.front()); // rightTrue.fromt() 这儿感觉会出bug，rightTrue里面不止一个的时候咋办
        break;
    case opType::Or:
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
        backpatch(&leftFalse, rightTrue.front());
        break;
    case opType::Not:
        std::list<int> trueL, falseL;
        trueL = trueList.top();
        trueList.pop();
        falseL = falseList.top();
        falseList.pop();

        trueList.push(falseL);
        falseList.push(trueL);
        break;
    // 上述好像得回填，跟relop一块解决 子节点可能是assignVar、literal和relop
    default:
        break;
    }
    return;
}

Quad *InterMediate::CaculateOp(OpCode op, AbstractASTNode *arg1Node, AbstractASTNode *arg2Node, symbol *result, SymbolTable *symbolTable)
{
    Quad *temp;
    symbol *result = new symbol(std::to_string(tempVar.size()), symbolType::integer);
    tempVar.push_back(result);
    result = tempVar.back();

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
    // arg1 assignVar || literal

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
    std::list<int> trueL(quads.size()); // Use size to get the index of true quad will be pushed.
    quads.push_back(*trueQuad);
    std::list<int> falseL(quads.size()); // Same as the upper on.
    quads.push_back(*falseQuad);
    trueList.push(trueL);
    falseList.push(falseL);
    // 感觉这儿可能会出问题，留意！
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
// void InterMediate::CompareOp(OpCode op, AbstractASTNode* arg1Node, AbstractASTNode *arg2Node, symbol)