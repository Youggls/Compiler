#include "symbol.h"
#include <string>

symbol::symbol() {
	this->idName = "";
	this->idType = symbolType::integer;
}

symbol::symbol(std::string idName, symbolType idType) {
	this->idName = idName;
	this->idType = idType;
}

const std::string symbol::getIdName() {
	return this->idName;
}

symbolType& symbol::getIdType() {
	return this->idType;
}
