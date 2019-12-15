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
    // case ASTNodeType::literal: //必是叶节点，直接pass
    //     break;
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
        // node = (DefVarASTNode *)node; //下面一直报错，看着烦
        symbolTable->addSymbol(node->getContent(), node->getSymbolType());
        while (p != NULL)
        {
            Generate(p, symbolTable);
            p = p->getPeer();
        }
        break;
    // case ASTNodeType::assignVar: // 叶节点
    //     break;
    // case ASTNodeType::loop:
    //     break;
    // case ASTNodeType::select:
    //     break;
    case ASTNodeType::root:
        while (p != NULL)
        {
            Generate(p, symbolTable);
            p = p->getPeer();
        }
        break;
    default:
        std::cout << "Hello";
        break;
    }
}

SymbolTable *InterMediate::GenerateStmt(StmtASTNode *node, SymbolTable *symbolTable)
{
    if (node->getStmtType() != StmtType::expStmt)
        return symbolTable;
    return symbolTable->createChildTable(false);
}

symbol *InterMediate::GenerateOp(OperatorASTNode *node, SymbolTable *symbolTable)
{
    Quad *temp;
    switch (node->getType())
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
    case opType::Relop: // 需要回填
        break;
    case opType::Plus: // 可能需要重构一下，方便看
        symbol *result = new symbol(std::to_string(tempVar.size()), symbolType::integer);
        AbstractASTNode *arg1Node = node->getChild();
        AbstractASTNode *arg2Node = arg1Node->getPeer();
        tempVar.push_back(*result);
        result = &tempVar.back();
        temp = this->CaculateOp(OpCode::PLUS, arg1Node, arg2Node, result, symbolTable);
        this->quads.push_back(*temp);
        break;
    case opType::Minus:
        symbol *result = new symbol(std::to_string(tempVar.size()), symbolType::integer);
        AbstractASTNode *arg1Node = node->getChild();
        AbstractASTNode *arg2Node = arg1Node->getPeer();
        tempVar.push_back(*result);
        result = &tempVar.back();
        temp = this->CaculateOp(OpCode::MINUS, arg1Node, arg2Node, result, symbolTable);
        this->quads.push_back(*temp);
        break;
    case opType::Times:
        symbol *result = new symbol(std::to_string(tempVar.size()), symbolType::integer);
        AbstractASTNode *arg1Node = node->getChild();
        AbstractASTNode *arg2Node = arg1Node->getPeer();
        tempVar.push_back(*result);
        result = &tempVar.back();
        temp = this->CaculateOp(OpCode::TIMES, arg1Node, arg2Node, result, symbolTable);
        this->quads.push_back(*temp);
        break;
    case opType::Div:
        symbol *result = new symbol(std::to_string(tempVar.size()), symbolType::integer);
        AbstractASTNode *arg1Node = node->getChild();
        AbstractASTNode *arg2Node = arg1Node->getPeer();
        tempVar.push_back(*result);
        result = &tempVar.back();
        temp = this->CaculateOp(OpCode::DIV, arg1Node, arg2Node, result, symbolTable);
        this->quads.push_back(*temp);
        break;
    case opType::Mod:
        symbol *result = new symbol(std::to_string(tempVar.size()), symbolType::integer);
        AbstractASTNode *arg1Node = node->getChild();
        AbstractASTNode *arg2Node = arg1Node->getPeer();
        tempVar.push_back(*result);
        result = &tempVar.back();
        temp = this->CaculateOp(OpCode::MOD, arg1Node, arg2Node, result, symbolTable);
        this->quads.push_back(*temp);
        break;
    case opType::Power:
        symbol *result = new symbol(std::to_string(tempVar.size()), symbolType::integer);
        AbstractASTNode *arg1Node = node->getChild();
        AbstractASTNode *arg2Node = arg1Node->getPeer();
        tempVar.push_back(*result);
        result = &tempVar.back();
        temp = this->CaculateOp(OpCode::POWER, arg1Node, arg2Node, result, symbolTable);
        this->quads.push_back(*temp);
        break;
    case opType::And:
        break;
    case opType::Or:
        break;
    case opType::Not:
        break;
    // 上述好像得回填，跟relop一块解决
    default:
        break;
    }
    return;
}

Quad *InterMediate::CaculateOp(OpCode op, AbstractASTNode *arg1Node, AbstractASTNode *arg2Node, symbol *result, SymbolTable *symbolTable)
{
    Quad *temp;
    symbol *result = new symbol(std::to_string(tempVar.size()), symbolType::integer);
    tempVar.push_back(*result);
    result = &tempVar.back();

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