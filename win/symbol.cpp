#include "symbol.h"
#include <string>

symbol::symbol() {
	this->idName = "";
	this->idType = 0;
}

symbol::symbol(std::string idName, int idType) {
	this->idName = idName;
	this->idType = idType;
}

const std::string symbol::getIdName() {
	return this->idName;
}

const int symbol::getIdType() {
	return this->idType;
}

