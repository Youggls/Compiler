#include "../trees/DefVarASTNode.h"
#include "../trees/DefFunASTNode.h"
#include "./symbol.h"
#include <string>

symbol::symbol()
{
    this->idName = "";
    this->idType = symbolType::integer;
}

symbol::symbol(std::string idName, symbolType idType)
{
    this->idName = idName;
    this->idType = idType;
}

const std::string symbol::getIdName()
{
    return this->idName;
}

symbolType &symbol::getIdType()
{
    return this->idType;
}

symbol *SymbolTable::findInThisTable(const std::string name)
{
    std::unordered_map<std::string, symbol *>::iterator iter;
    iter = this->symbolHashTable.find(name);
    if (iter != this->symbolHashTable.end())
        return iter->second;
    else
        return NULL;
}

SymbolTable::SymbolTable(bool isFun, StructTable *structTable)
{
    this->structTable = structTable;
    this->childTable = NULL;
    this->parentTable = NULL;
    this->baseTable = this;
    this->symbolItemCount = 0;
    this->totalOffset = 4;
    this->isFunctionTable = isFun;
    if (isFun)
    {
        this->symbolArray = new std::vector<symbol *>();
        this->argArray = new std::vector<symbol *>();
    }
}

SymbolTable::SymbolTable(SymbolTable *parent, bool isFun)
{
    this->childTable = NULL;
    this->parentTable = parent;
    this->isFunctionTable = isFun;
    this->structTable = parent->structTable;
    SymbolTable *p = this;
    while (!p->isFunctionTable)
    {
        p = p->parentTable;
    }
    this->baseTable = p;
    this->symbolItemCount = 0;
    this->totalOffset = 4;

    if (isFun)
    {
        this->symbolArray = new std::vector<symbol *>();
        this->argArray = new std::vector<symbol *>();
    }
}

symbol *SymbolTable::findSymbol(std::string name)
{
    SymbolTable *t = this;
    while (t != NULL)
    {
        symbol *target = t->findInThisTable(name);
        if (target == NULL)
        {
            // Not found in current table, goto parent table.
            t = t->parentTable;
        }
        else
        {
            return target;
        }
    }
    std::cout << "\033[31mError: \033[0m"
              << "value " << name << " is not defined" << std::endl;
    exit(1);
    return NULL;
}

structDecSymbol::structDecSymbol(std::string structType, std::string structIdName)
    : symbol(structIdName, symbolType::Struct)
{
    this->structTypeName = structType;
}

int StructTable::num = 0;

// int structSymbol::insert(std::string name, int offset) {
//     this->offsetTable[name] = offset;
//     this->totalOffsets += offset;
// }

structSymbol::structSymbol()
{
}

structSymbol::structSymbol(std::string name, AbstractASTNode *node)
{
    this->totalOffsets = 0;
    int offset = 0;
    this->idName = name;
    AbstractASTNode *currentNode = node;
    while (currentNode)
    {
        DefVarASTNode *var = (DefVarASTNode *)currentNode;
        offsetTable[var->getContent()] = offset;
        offset += 4;
        currentNode = currentNode->getPeer();
    }
    this->totalOffsets = offset;
}

int structSymbol::getMemberOffset(std::string key)
{
    if (this->offsetTable.count(key) == 0)
    {
        return -1;
    }
    else
    {
        return this->offsetTable[key];
    }
}

StructTable::StructTable()
{
}

bool StructTable::addStruct(structSymbol *sSymbol)
{
    if (this->findStruct(sSymbol->getStructName()))
    {
        return false;
    }
    else
    {
        this->structHashTable[sSymbol->getStructName()] = sSymbol;
        return true;
    }
}

structSymbol *StructTable::findStruct(std::string keyName)
{
    std::unordered_map<std::string, structSymbol *>::iterator iter;
    iter = this->structHashTable.find(keyName);
    if (iter != this->structHashTable.end())
        return iter->second;
    else
        return NULL;
}

SymbolTable *SymbolTable::createChildTable(bool isFun)
{
    SymbolTable *child = new SymbolTable(this, isFun);
    if (this->childTable == NULL)
        this->setChild(child);
    else if (this->childTable->peerTable == NULL)
    {
        this->childTable->peerTable = child;
    }
    else
    {
        SymbolTable *peer = this->childTable->peerTable;
        while (peer != NULL)
        {
            if (peer->peerTable == NULL)
                break;
            peer = peer->peerTable;
        }
        peer->peerTable = child;
    }
    return child;
}

int SymbolTable::addSymbol(symbol *s)
{
    if (this->findInThisTable(s->getIdName()) == NULL)
    {
        this->symbolHashTable[s->getIdName()] = s;
        return SUCCESS;
    }
    else
        return FAIL;
}

int SymbolTable::addSymbol(std::string idName, symbolType idType)
{
    symbol *s = new symbol(idName, idType);
    if (this->findInThisTable(s->getIdName()) != NULL)
        return FAIL;

    this->baseTable->symbolArray->push_back(s); // why add to baseTable, not this table ?
    s->setIndex(this->baseTable->symbolItemCount++);
    s->setOffset(this->baseTable->totalOffset);
    if (idType == symbolType::integer || idType == symbolType::pointer)
    {
        this->baseTable->totalOffset += INT_OFFSET;
    }
    return this->addSymbol(s);
}

int SymbolTable::addStructSymbol(std::string structTypeName, std::string structIdName)
{
    structDecSymbol *s = new structDecSymbol(structTypeName, structIdName);
    if (this->findInThisTable(structIdName) != NULL)
        return FAIL;
    else
    {
        structSymbol *target = this->structTable->findStruct(structTypeName);
        if (target == NULL)
        {
            return FAIL;
        }
        else
        {
            this->baseTable->symbolArray->push_back(s);
            s->setIndex(this->baseTable->symbolItemCount++);
            s->setOffset(this->baseTable->totalOffset);
            this->baseTable->totalOffset += target->getTotalOffsets();
            this->symbolHashTable[structIdName] = s;
            return SUCCESS;
        }
    }
}

int SymbolTable::addArraySymbol(AbstractASTNode *decArray)
{
    DefVarASTNode *array = (DefVarASTNode *)decArray;
    std::string name = decArray->getContent();
    if (this->findInThisTable(name) != NULL)
        return FAIL;
    else
    {
        symbol *s = new symbol(name, symbolType::Array);
        this->baseTable->symbolArray->push_back(s);
        s->setIndex(this->baseTable->symbolItemCount++);
        s->setOffset(this->baseTable->totalOffset);
        this->baseTable->totalOffset += array->getArrayLength() * 4;
        this->symbolHashTable[name] = s;
        return SUCCESS;
    }
}

void SymbolTable::visitFuncArgs(AbstractASTNode *funArg, int &offset, int &index)
{
    if (funArg == NULL)
        return;
    else
    {
        this->visitFuncArgs(funArg->getPeer(), offset, index);
        DefVarASTNode *arg = (DefVarASTNode *)funArg;
        if (arg->getSymbolType() == symbolType::integer || arg->getSymbolType() == symbolType::pointer)
        {
            offset -= 4;
            symbol *s = new symbol(arg->getContent(), arg->getSymbolType());
            s->setIndex(index--);
            s->setOffset(offset);
            symbolHashTable[s->getIdName()] = s;
            arg = (DefVarASTNode *)arg->getPeer();
        }
    }
}

void SymbolTable::addFromFunctionArgs(AbstractASTNode *func)
{
    DefFunASTNode *defFunc = (DefFunASTNode *)func;
    int offset = -4;
    int index = -1;
    this->visitFuncArgs(defFunc->getArgList(), offset, index);
    this->argTotalOffset = -(offset + 4);
}
