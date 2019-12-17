#ifndef ASMGENERATOR_H
#define ASMGENERATOR_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "./AsmCode.h"

enum class asmRegister {
    eax = 1,
    ebx = 2,
    ecx = 3,
    edx = 4,
    esp = 5,
    ebp = 6
};

class AsmCode {
private:
    std::string codeBuffer;
    std::string transRegister(asmRegister reg);
    void generateBinaryInstructor(std::string instructor, asmRegister reg1, asmRegister reg2);
    void generateBinaryInstructor(std::string instructor, asmRegister reg, std::string reg2);
    void generateUnaryInstructor(std::string instructor, std::string var);
    void generateUnaryInstructor(std::string instructor, asmRegister reg);
public:
    AsmCode();
    // ADD instructor, add reg1, reg2
    void add(asmRegister reg1, asmRegister reg2);
    // ADD instructor, add reg, var
    void add(asmRegister reg, std::string var);
    void sub(asmRegister reg1, asmRegister reg2);
    void sub(asmRegister reg, std::string var);
    void mov(asmRegister reg1, asmRegister reg2);
    void mov(asmRegister reg, std::string var);
    void mul(asmRegister reg1, asmRegister reg2);
    void mul(asmRegister reg, std::string var);
    void div(asmRegister reg1, asmRegister reg2);
    void div(asmRegister reg, std::string var);
    void push(asmRegister reg);
    void push(std::string var);
    void label(std::string label);
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
