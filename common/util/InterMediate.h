#ifndef INTERMEDIATE_H
#define INTERMEDIATE_H

#define VAR "10VarASTNode"
#define STMT "11StmtASTNode"
#define ROOT "11RootASTNode"
#define LOOP "11LoopASTNode"
#define DEFINE_VAR "13DefVarASTNode"
#define DEFINE_FUN "13DefFunASTNode"
#define SELECT "13SelectASTNode"
#define LITERAL "14LiteralASTNode" // 常量
#define CALL "14CallFunASTNode"
// IdentifierASTNode 等着删了，没用
#define OPERATOR "15OperatorASTNode"

#include "../trees.h"
#include "./Quad.h"
#include "../symbol/symbol.h"
#include "../symbol/FuncSymbol.h"
#include <stack>
#include <list>
// Inter mediate code generator
class InterMediate
{
private:
    RootASTNode *root;
    std::vector<Quad> quads;
    std::vector<symbol> tempVar;
    FuncTable funcTable;
    SymbolTable *rootTable;

    std::stack<std::list<int>> trueList;
    std::stack<std::list<int>> falseList;

public:
    InterMediate(RootASTNode *rootNode);
    void Generate(AbstractASTNode *node, SymbolTable *symbolTable);
    // Create a child symbol table to generate follow code.
    SymbolTable *GenerateStmt(StmtASTNode *node, SymbolTable *symbolTable);
    symbol *GenerateOp(OperatorASTNode *node, SymbolTable *symbolTable);
    Quad *CaculateOp(OpCode op, AbstractASTNode *arg1Node, AbstractASTNode *arg2Node, symbol *result, SymbolTable *symbalTable);
    std::list<int> *makelist(int index);
    std::list<int> *merge(std::list<int> *list1, std::list<int> *list2);
    void backpatch(std::list<int> *backList, int target);
};
#endif
