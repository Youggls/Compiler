#include "AsmGenerator.h"

std::string AsmCode::transRegister(asmRegister reg) {
    if (reg == asmRegister::eax) return EAX;
    else if (reg == asmRegister::ebx) return EBX;
    else if (reg == asmRegister::ecx) return ECX;
    else if (reg == asmRegister::edx) return EDX;
    else if (reg == asmRegister::ebp) return EBP;
    else if (reg == asmRegister::esp) return ESP;
    else return "";
}

void AsmCode::generateBinaryInstructor(std::string insturctor, asmRegister reg1, asmRegister reg2) {
    this->codeBuffer += insturctor + std::string(" ") + this->transRegister(reg1) 
                        + "," + this->transRegister(reg2) + "\n";
}

void AsmCode::generateBinaryInstructor(std::string insturctor, asmRegister reg, std::string var) {
    this->codeBuffer += insturctor + std::string(" ") + this->transRegister(reg) 
                        + "," + var + "\n";
}

void AsmCode::generateUnaryInstructor(std::string instructor, asmRegister reg) {
    this->codeBuffer += instructor + " " + this->transRegister(reg) + "\n";
}

void AsmCode::generateUnaryInstructor(std::string instructor, std::string var) {
    this->codeBuffer += instructor + " " + var + "\n";
}

AsmCode::AsmCode() {

}

void AsmCode::addCode(std::string code) {
    this->codeBuffer += code;
    this->codeBuffer += "\n";
}

void AsmCode::add(asmRegister reg1, asmRegister reg2) {
    this->generateBinaryInstructor(ADD, reg1, reg2);
}

void AsmCode::add(asmRegister reg, std::string var) {
    this->generateBinaryInstructor(ADD, reg, var);
}

void AsmCode::sub(asmRegister reg1, asmRegister reg2) {
    this->generateBinaryInstructor(SUB, reg1, reg2);
}

void AsmCode::sub(asmRegister reg, std::string var) {
    this->generateBinaryInstructor(SUB, reg, var);
}

void AsmCode::mul(asmRegister reg1, asmRegister reg2) {
    this->generateBinaryInstructor(MUL, reg1, reg2);
}

void AsmCode::mul(asmRegister reg, std::string var) {
    this->generateBinaryInstructor(MUL, reg, var);
}

void AsmCode::div(asmRegister reg1, asmRegister reg2) {
    this->generateBinaryInstructor(DIV, reg1, reg2);
}

void AsmCode::div(asmRegister reg, std::string var) {
    this->generateBinaryInstructor(DIV, reg, var);
}

void AsmCode::push(asmRegister reg) {
    this->generateUnaryInstructor(PUSH, reg);
}

void AsmCode::push(std::string var) {
    this->generateUnaryInstructor(PUSH, var);
}

void AsmCode::label(std::string label) {
    this->codeBuffer += label + COLON;
}

AsmGenerator::AsmGenerator() {
    eax = 0;
    ebx = 0;
    ecx = 0;
    edx = 0;
}

std::string AsmGenerator::getRegister() {

}
