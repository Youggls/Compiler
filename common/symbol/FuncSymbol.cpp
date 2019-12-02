#include "./FuncSymbol.h"

int FuncTable::num = 0;

FuncSymbol::FuncSymbol(AbstractASTNode* func) {
    if (func->getNodeType() != ASTNodeType::defFunc) {
        throw "Error AST Node type! Must be ASTNodeType::defFunc!";
        return;
    }
    DefFunASTNode* defFunc = (DefFunASTNode*)func;
    this->funcName = defFunc->getContent();
    this->keyName = defFunc->getContent();
    AbstractASTNode* t = defFunc->getArgList();
    while (t) {
        DefVarASTNode* var = (DefVarASTNode*)t;
        this->typeList.push_back(var->getSymbolType());
        if (var->getSymbolType() == symbolType::integer) {
            this->keyName += "_i";
        } else if (var->getSymbolType() == symbolType::pointer) {
            this->keyName += "_p";
        }
        t = t->getPeer();
    }   
}

bool FuncSymbol::operator== (const FuncSymbol& another) {
    return this->keyName == another.keyName; 
}

FuncTable::FuncTable() { }

bool FuncTable::addFunction(FuncSymbol* func) {
    if (this->findFunction(func->getKeyName())) {
        return false;
    } else {
        this->funcHashTable[func->getKeyName()] = func;
        return true;
    }
}

bool FuncTable::addFunction(AbstractASTNode* funcAST) {
    FuncSymbol* func = new FuncSymbol(funcAST);
    return this->addFunction(func);
}

FuncSymbol* FuncTable::findFunction(std::string keyName) {
    std::unordered_map<std::string, FuncSymbol*>::iterator iter;
    iter = this->funcHashTable.find(keyName);
    if (iter != this->funcHashTable.end()) return iter->second;
    else return NULL;
}
