#include "error.h"

error::error(ErrorType type, std::string content, int lineNum) {
    this->errType = type;
    this->content = content;
    this->lineNum = lineNum;
}

std::string error::getErrInfo() {
    if (this->errType == ErrorType::UndefErr) {
        return "Undefined symbol " + this->content + ". At line " + std::to_string(this->lineNum) + "\n";
    } else if (this->errType == ErrorType::RedefErr) {
        return "Redefined symbol " + this->content + ". At line " + std::to_string(this->lineNum) + "\n";
    } else if (this->errType == ErrorType::TypeErr) {
        return "Type error! At line " + std::to_string(this->lineNum) + "\n";
    }
    return "";
}
