#ifndef ERROR_H
#define ERROR_H
#include <string>
enum class ErrorType {
    UndefErr = 1,
    RedefErr = 2,
    TypeErr = 3
};

class error {
private:
    ErrorType errType;
    std::string content;
    int lineNum;
public:
    error(ErrorType type, std::string content, int lineNum);
    std::string getErrInfo();
};

#endif