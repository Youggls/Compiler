#ifndef ASMGENERATOR_H
#define ASMGENERATOR_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "./AsmCode.h"
#include "../symbol/symbol.h"
#include "./Quad.h"
#include "../symbol/FuncSymbol.h"
enum class asmRegister {
    unset = -1,
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
public:
    AsmCode();
    std::string generateVar(int offset);
    std::string generateInstanceNumber(int value);
    void generateBinaryInstructor(std::string instructor, asmRegister reg1, asmRegister reg2);
    void generateBinaryInstructor(std::string instructor, asmRegister reg, std::string var);
    void generateBinaryInstructor(std::string instructor, std::string var, asmRegister reg);
    void generateBinaryInstructor(std::string instructor, std::string var1, std::string var2);
    void generateUnaryInstructor(std::string instructor, std::string var);
    void generateUnaryInstructor(std::string instructor, asmRegister reg);
    // ADD instructor, add reg1, reg2
    void add(asmRegister reg1, asmRegister reg2);
    // ADD instructor, add reg, var
    void add(asmRegister reg, std::string var);
    void sub(asmRegister reg1, asmRegister reg2);
    void sub(asmRegister reg, std::string var);
    void mov(asmRegister reg1, asmRegister reg2);
    void mov(asmRegister reg, std::string var);
    void mov(std::string var, asmRegister reg);
    void mov(std::string var1, std::string var2);
    void mul(asmRegister reg1, asmRegister reg2);
    void mul(asmRegister reg, std::string var);
    void mul(std::string var1, std::string var2);
    void mul(asmRegister reg, int instance);
    void mul(std::string var, int intsance);
    void mul(int instance1, int instance2);
    void div(asmRegister reg1, asmRegister reg2);
    void div(asmRegister reg, std::string var);
    void div(std::string var, asmRegister reg);
    void div(std::string var1, std::string var2);
    void div(asmRegister reg, int instance);
    void div(int instance, asmRegister reg);
    void div(std::string var, int instance);
    void div(int instance, std::string var);
    void div(int instance1, int instance2);
    void asmXor(asmRegister reg1, asmRegister reg2);
    void push(asmRegister reg);
    void push(std::string var);
    void pop(asmRegister reg);
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
    AsmCode asmcode;
    std::string registerUsedVar[6];
    std::vector<symbol*> tempVar;
    std::vector<Quad> quads;
    SymbolTable* rootTable;
    SymbolTable* currentTable;
    FuncTable funcTable;
    void releaseRegister(asmRegister reg);
    asmRegister getRegister(std::string var);
    asmRegister findRegister(std::string var);
    void generateDefFunction(Quad& q);
    void generateReturn(Quad& q);
    void generateEndFunction(Quad& q);
    void generateCallFunction(Quad& q);
    void generateCallBuildInFunction(Quad& q, Quad& arg);
    void generateSetArg(Quad& q);
    void generateArithmetic(Quad& q);
    void generateJmp(Quad& q);
public:
    inline AsmCode& getAsmCode() { return this->asmcode; }
    AsmGenerator(std::vector<Quad>& quads, std::vector<symbol*>& tempVar, SymbolTable* rootTable, FuncTable& funcTable);
    void generate();
};

#endif
