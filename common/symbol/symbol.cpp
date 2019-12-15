#include "symbol.h"
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

SymbolTable::SymbolTable(bool isFun)
{
    this->childTable = NULL;
    this->parentTable = NULL;
    this->baseTable = this;
    this->symbolItemCount = 0;
    this->totalOffset = 0;
    this->isFunctionTable = isFun;
    if (isFun)
    {
        this->symbolArray = new std::vector<symbol *>();
    }
}

SymbolTable::SymbolTable(SymbolTable *parent, bool isFun)
{
    this->childTable = NULL;
    this->parentTable = parent;
    this->isFunctionTable = isFun;
    // parent->setChild(this);
    SymbolTable *p = this;
    while (!p->isFunctionTable)
    {
        p = p->parentTable;
    }
    this->baseTable = p;
    this->symbolItemCount = 0;
    this->totalOffset = 0;

    if (isFun)
    {
        this->symbolArray = new std::vector<symbol *>();
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

int SymbolTable::addSymbol(symbol *s) // 为啥不按照下面操作操作
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
