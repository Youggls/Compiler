#include "StructSymbol.h"

int StructTable::num = 0;

int structSymbol::insert(std::string name, int offset) {
    this->offsetTable[name] = offset;
    this->totalOffsets += offset;
}

structSymbol::structSymbol() {
}

structSymbol::structSymbol(std::string name, AbstractASTNode * node) {
    this->totalOffsets = 0;
    int offset = 0;
    this->idName = name;
    AbstractASTNode* currentNode = node;
    while(currentNode) {
        DefVarASTNode *var = (DefVarASTNode*)node;
        offsetTable[var->getContent()] = offset;
        this->totalOffsets += offset;
        offset += 4;
        currentNode = currentNode->getPeer();
    }
}

StructTable::StructTable() {
}

bool StructTable::addStruct(structSymbol* sSymble) {
    if (this->findStruct(sSymble->getStructName())) {
        return false;
    } else {
        this->structHashTable[sSymble->getStructName()] = sSymble;
        return true;
    }
}

structSymbol* StructTable::findStruct(std::string keyName) {
    return NULL;
}
