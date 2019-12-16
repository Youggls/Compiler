#ifndef ASMGENERATOR_H
#define ASMGENERATOR_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "./AsmCode.h"

class AsmCode {
private:
    std::vector<std::string> codeList;
public:
    AsmCode();
    void addCode(std::string code);
    friend std::ostream& operator<<(std::ostream& os, const AsmCode& asmcode);
};

class AsmGenerator
{
private:
    int eax;
    int ebx;
    int ecx;
    int edx;
    std::string getRegister();
    void generateCallFunction();
    void generateSetArg();
    void generateArithmetic();
    void generateJmp();
    void generateDefFunction();
public:
    AsmGenerator();
    void generate();
};

#endif
