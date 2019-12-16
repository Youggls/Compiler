#include "AsmGenerator.h"

AsmCode::AsmCode() {

}

void AsmCode::addCode(std::string code) {
    this->codeList.push_back(code);
}

std::ostream& operator<<(std::ostream& os, const AsmCode& asmcode) {
    for (int i = 0; i < asmcode.codeList.size(); i++) {
        os << asmcode.codeList[i];
    }
    return os;
}

AsmGenerator::AsmGenerator() {
    eax = 0;
    ebx = 0;
    ecx = 0;
    edx = 0;
}

std::string AsmGenerator::findRegister() {
    
}
