#ifndef INTERMEDIATE_H
#define INTERMEDIATE_H

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
    std::vector<symbol *> tempVar;
    FuncTable funcTable;
    SymbolTable *rootTable;

    std::stack<std::list<int>> trueList;
    std::stack<std::list<int>> falseList;
    std::stack<int> signal;
    std::stack<symbol *> childValue;
    // Function for backpatch.
    std::list<int> *makelist(int index);
    std::list<int> *merge(std::list<int> *list1, std::list<int> *list2);
    void backpatch(std::list<int> *backList, int target);

public:
    inline AbstractASTNode *getRoot() { return this->root; }
    inline SymbolTable *getTable() { return this->rootTable; }
    inline FuncTable &getFuncTable() { return this->funcTable; }
    inline std::vector<Quad> &getQuads() { return this->quads; }
    inline std::vector<symbol *> &getTempVars() { return this->tempVar; }
    InterMediate(RootASTNode *rootNode, StructTable *structTable);
    void Generate(AbstractASTNode *node, SymbolTable *symbolTable);
    // Create a child symbol table to generate follow code.
    SymbolTable *GenerateStmt(StmtASTNode *node, SymbolTable *symbolTable);
    SymbolTable *GenerateReturn(StmtASTNode *node, SymbolTable *symbolTable);
    symbol *GenerateOp(OperatorASTNode *node, SymbolTable *symbolTable);
    Quad *CaculateOp(OpCode op, AbstractASTNode *arg1Node, AbstractASTNode *arg2Node, symbol *result, SymbolTable *symbalTable);
    void RelopOp(Quad *trueQuad, Quad *falseQuad, OpCode op, AbstractASTNode *arg1Node, AbstractASTNode *arg2Node, SymbolTable *symbolTable);
    void printQuads();
};
#endif
