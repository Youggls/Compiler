#include <string>

class symbol {
private:
	std::string idName;
	int idType;
public:
	symbol();
	symbol(std::string idName, int idType);
	const std::string getIdName();
	const int getIdType();
};
