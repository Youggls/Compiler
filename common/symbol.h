#ifndef SYMBOL_H
#define SYMBOL_H
#include <string>

enum class symbolType {
	integer = 0,
	function = 1,
	pointer = 2,
	boolean = 3
};

class symbol {
private:
	std::string idName;
	symbolType idType;
public:
	symbol();
	symbol(std::string idName, symbolType idType);
	const std::string getIdName();
	symbolType& getIdType();
};

#endif // !SYMBOL_H
