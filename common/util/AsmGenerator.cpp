#include "AsmGenerator.h"

AsmCode::AsmCode() {

}

std::string AsmCode::transRegister(asmRegister reg) {
    if (reg == asmRegister::eax) return ASM_EAX;
    else if (reg == asmRegister::ebx) return ASM_EBX;
    else if (reg == asmRegister::ecx) return ASM_ECX;
    else if (reg == asmRegister::edx) return ASM_EDX;
    else if (reg == asmRegister::ebp) return ASM_EBP;
    else if (reg == asmRegister::esp) return ASM_ESP;
    else return "";
}

void AsmCode::generateBinaryInstructor(std::string instructor, asmRegister reg1, asmRegister reg2) {
    this->codeBuffer += instructor + std::string(" ") + this->transRegister(reg1) 
                        + "," + this->transRegister(reg2) + "\n";
}

void AsmCode::generateBinaryInstructor(std::string instructor, asmRegister reg, std::string var) {
    this->codeBuffer += instructor + std::string(" ") + this->transRegister(reg) 
                        + "," + var + "\n";
}

void AsmCode::generateBinaryInstructor(std::string instructor, std::string var, asmRegister reg) {
    this->codeBuffer += instructor + std::string(" ") + var
                        + "," + this->transRegister(reg) + "\n";
}

void AsmCode::generateUnaryInstructor(std::string instructor, asmRegister reg) {
    this->codeBuffer += instructor + " " + this->transRegister(reg) + "\n";
}

void AsmCode::generateUnaryInstructor(std::string instructor, std::string var) {
    this->codeBuffer += instructor + " " + var + "\n";
}

void AsmCode::addCode(std::string code) {
    this->codeBuffer += code;
    this->codeBuffer += "\n";
}

void AsmCode::add(asmRegister reg1, asmRegister reg2) {
    this->generateBinaryInstructor(ASM_ADD, reg1, reg2);
}

void AsmCode::add(asmRegister reg, std::string var) {
    this->generateBinaryInstructor(ASM_ADD, reg, var);
}

void AsmCode::sub(asmRegister reg1, asmRegister reg2) {
    this->generateBinaryInstructor(ASM_SUB, reg1, reg2);
}

void AsmCode::sub(asmRegister reg, std::string var) {
    this->generateBinaryInstructor(ASM_SUB, reg, var);
}

void AsmCode::mov(asmRegister reg1, asmRegister reg2) {
    this->generateBinaryInstructor(ASM_MOV, reg1, reg2);
}

void AsmCode::mov(asmRegister reg, std::string var) {
    this->generateBinaryInstructor(ASM_MOV, reg, var);
}

void AsmCode::mov(std::string var, asmRegister reg) {
    this->generateBinaryInstructor(ASM_MOV, var, reg);
}

void AsmCode::mul(asmRegister reg1, asmRegister reg2) {
    this->generateBinaryInstructor(ASM_MUL, reg1, reg2);
}

void AsmCode::mul(asmRegister reg, std::string var) {
    this->generateBinaryInstructor(ASM_MUL, reg, var);
}

void AsmCode::div(asmRegister reg1, asmRegister reg2) {
    this->generateBinaryInstructor(ASM_DIV, reg1, reg2);
}

void AsmCode::div(asmRegister reg, std::string var) {
    this->generateBinaryInstructor(ASM_DIV, reg, var);
}

void AsmCode::push(asmRegister reg) {
    this->generateUnaryInstructor(ASM_PUSH, reg);
}

void AsmCode::push(std::string var) {
    this->generateUnaryInstructor(ASM_PUSH, var);
}

void AsmCode::label(std::string label) {
    this->codeBuffer += label + ASM_COLON + "\n";
}

std::ostream& operator<<(std::ostream& os, const AsmCode& code) {
    os << code.codeBuffer;
    return os;
}

AsmGenerator::AsmGenerator(std::vector<Quad>& quads, std::vector<symbol*>& tempVar, SymbolTable* rootTable, FuncTable& funcTable) {
    this->quads = quads;
    this->tempVar = tempVar;
    this->rootTable = rootTable;
    this->funcTable = funcTable;
    eax = 0;
    ebx = 0;
    ecx = 0;
    edx = 0;
}

void AsmGenerator::releaseRegister(asmRegister reg) {
    if (reg == asmRegister::ebx) {
        ebx = 0;
        int index = (int)asmRegister::ebx;
        this->registerUsedVar[index] = "";
    } else if (reg == asmRegister::ecx) {
        ecx = 0;
        int index = (int)asmRegister::ecx;
        this->registerUsedVar[index] = "";
    }
}

asmRegister AsmGenerator::getRegister(std::string var) {
    if (ebx == 0) {
        ebx = 1;
        int index = (int)asmRegister::ebx;
        this->registerUsedVar[index - 1] = var;
        return asmRegister::ebx;
    } else if (ecx == 0) {
        ecx = 1;
        int index = (int)asmRegister::ecx;
        this->registerUsedVar[index - 1] = var;
        return asmRegister::ecx;
    }
}

asmRegister AsmGenerator::findRegister(std::string var) {
    for (int i = 0; i < 6; i++) {
        if (this->registerUsedVar[i] == var) {
            return asmRegister(i + 1);
        }
    }
}

void AsmGenerator::generateArithmetic(Quad& q) {
    std::string instructor;
    OpCode opcode = q.getOpCode();
    // Special case, assign operate is unary operator.
    if (opcode == OpCode::ASSIGN) {
        symbol* result = q.getArg(3).var;
        int offset = result->getOffset();
        std::string tempVar = q.getArg(1).var->getIdName();
        asmRegister tempVarReg = this->findRegister(tempVar);
        this->asmcode.mov("[ebp - " + std::to_string(offset) + "]", tempVarReg);
        return;
    }
    if (opcode == OpCode::PLUS) instructor = ASM_ADD;
    else if (opcode == OpCode::MINUS) instructor = ASM_SUB;
    else if (opcode == OpCode::TIMES) instructor = ASM_MUL;
    else instructor = ASM_DIV;

    asmRegister tempVar1Reg = asmRegister::unset;
    asmRegister tempVar2Reg = asmRegister::unset;
    asmRegister resultReg = asmRegister::unset;
    int value1, value2;
    std::string arg1IdName = "";
    std::string arg2IdName = "";
    // Result must be temp var or var, cannot be instance number
    std::string resultIdName = q.getArg(3).var->getIdName();
    int flag = q.getFlag();
    // All args and reslut is var or temp var.
    if (flag == 7) {
        arg1IdName = q.getArg(1).var->getIdName();
        arg2IdName = q.getArg(2).var->getIdName();
        if (arg1IdName[0] == 'T') {
            tempVar1Reg = this->findRegister(arg1IdName);
            this->releaseRegister(tempVar1Reg);
        }
        if (arg2IdName[0] == 'T') {
            tempVar2Reg = this->findRegister(arg2IdName);
            this->releaseRegister(tempVar2Reg);
        }
        if (resultIdName[0] == 'T') {
            resultReg = this->getRegister(resultIdName);
        }
    } else if (flag == 6 || flag == 5) {
        if (flag == 6) {
            value1 = q.getArg(1).target;
            arg2IdName = q.getArg(2).var->getIdName();
            if (arg2IdName[0] == 'T') {
                tempVar2Reg = this->findRegister(arg2IdName);
                this->releaseRegister(tempVar2Reg);
            }
        } else {
            value2 = q.getArg(2).target;
            arg1IdName = q.getArg(1).var->getIdName();
            if (arg1IdName[0] == 'T') {
                tempVar1Reg = this->findRegister(arg1IdName);
                this->releaseRegister(tempVar1Reg);
            }
        }
        resultReg = this->getRegister(resultIdName);
    } else if (flag == 4) {
        value1 = q.getArg(1).target;
        value2 = q.getArg(2).target;
        resultReg = this->getRegister(resultIdName);
        this->asmcode.mov(resultReg, std::to_string(value1));
        this->asmcode.add(resultReg, std::to_string(value2));
    }
}

void AsmGenerator::generate() {
    currentTable = rootTable;
    for (size_t i = 0; i < this->quads.size(); i++) {
        Quad& q = quads[i];
        OpCode opcode = q.getOpCode();
        if (opcode == OpCode::FUNC_DEF) {
            std::string funcName = q.getArg(1).var->getIdName();
            this->asmcode.label(funcName);
            if (currentTable == rootTable) {
                currentTable = currentTable->getChild();
            } else {
                currentTable = currentTable->getPeer();
            }
        }
        if (opcode == OpCode::PLUS || opcode == OpCode::MINUS || opcode == OpCode::DIV || opcode == OpCode::TIMES || opcode == OpCode::ASSIGN) {
            this->generateArithmetic(q);
        }
    }
    this->asmcode.addCode("ret");
}
