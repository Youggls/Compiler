#ifndef ASMGENERATOR_H
#define ASMGENERATOR_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include "./AsmCode.h"
#include "../symbol/symbol.h"
#include "./Quad.h"
#include "../symbol/FuncSymbol.h"
// assembly language，缩写为 asm，中文译为汇编语言
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
    // 生成变量    
    std::string generateInstanceNumber(int value);
    // 生成数字？实例？
    void generateBinaryInstructor(std::string instructor, asmRegister reg1, asmRegister reg2);
    // 生成
    void generateBinaryInstructor(std::string instructor, asmRegister reg, std::string var);
    void generateBinaryInstructor(std::string instructor, std::string var, asmRegister reg);
    void generateBinaryInstructor(std::string instructor, std::string var1, std::string var2);
    void generateUnaryInstructor(std::string instructor, std::string var);
    void generateUnaryInstructor(std::string instructor, asmRegister reg);
    std::string findValueByAddress(asmRegister reg);
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
    void div(asmRegister reg1, asmRegister reg2);
    void div(asmRegister reg, std::string var);
    void div(std::string var, asmRegister reg);
    void div(std::string var1, std::string var2);
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
    std::string registerUsedVar[6]; // 哪个变量用了哪个寄存器，是决定从变量拿还是寄存器拿数据的关键
    std::vector<symbol*> tempVar;
    std::vector<Quad> quads;
    std::map<int, int> labelMap;
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
    void generateJump(Quad& q);
    void generateNeg(Quad& q);
    void generatePower(Quad& q);
    void generateGetAddress(Quad& q);
    void generateGetMember(Quad& q);
    void generateGetArrayValue(Quad& q);
    void generateAssignMember(Quad& q);
    void generateAssignArray(Quad& q);
    void preSetLabel();
    bool isJumpQuad(OpCode code);
public:
    inline AsmCode& getAsmCode() { return this->asmcode; }
    AsmGenerator(std::vector<Quad>& quads, std::vector<symbol*>& tempVar, SymbolTable* rootTable, FuncTable& funcTable);
    void generate();
};

#endif
