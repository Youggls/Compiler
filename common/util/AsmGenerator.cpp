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

std::string AsmCode::generateVar(int offset) {
    std::string ans = ASM_LB + std::string(ASM_EBP);
    if (offset > 0) {
        ans += "-";
        ans += std::to_string(offset);
    } else {
        ans += "+";
        ans += std::to_string(-offset);
    }
    ans += ASM_RB;
    return ans;
}

std::string AsmCode::generateInstanceNumber(int value) {
    std::string ans = DOUBLE_WORD;
    ans += " " + std::to_string(value);
    return ans;
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

void AsmCode::generateBinaryInstructor(std::string instructor, std::string var1, std::string var2) {
    this->codeBuffer += instructor + " " + var1 +
                        + ASM_COMMA + var2 + "\n";
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

void AsmCode::mov(std::string var1, std::string var2) {
    this->generateBinaryInstructor(ASM_MOV, var1, var2);
}

// Save the answer to eax
void AsmCode::mul(asmRegister reg1, asmRegister reg2) {
    this->asmXor(asmRegister::edx, asmRegister::edx);
    this->mov(asmRegister::eax, reg1);
    this->generateUnaryInstructor(ASM_MUL, reg2);
}

void AsmCode::mul(asmRegister reg, std::string var) {
    this->asmXor(asmRegister::edx, asmRegister::edx);
    this->mov(asmRegister::eax, reg);
    this->generateUnaryInstructor(ASM_MUL, DOUBLE_WORD + var);
}

void AsmCode::mul(std::string var1, std::string var2) {
    this->asmXor(asmRegister::edx, asmRegister::edx);
    this->mov(asmRegister::eax, var1);
    this->generateUnaryInstructor(ASM_MUL, DOUBLE_WORD + var2);
}

void AsmCode::div(asmRegister reg1, asmRegister reg2) {
    this->asmXor(asmRegister::edx, asmRegister::edx);
    this->mov(asmRegister::eax, reg1);
    this->generateUnaryInstructor(ASM_DIV, reg2);
}

void AsmCode::div(asmRegister reg, std::string var) {
    this->asmXor(asmRegister::edx, asmRegister::edx);
    this->mov(asmRegister::eax, reg);
    this->generateUnaryInstructor(ASM_DIV, DOUBLE_WORD + var);
}

void AsmCode::div(std::string var, asmRegister reg) {
    this->asmXor(asmRegister::edx, asmRegister::edx);
    this->mov(asmRegister::eax, var);
    this->generateUnaryInstructor(ASM_DIV, reg);
}

void AsmCode::div(std::string var1, std::string var2) {
    this->asmXor(asmRegister::edx, asmRegister::edx);
    this->mov(asmRegister::eax, var1);
    this->generateUnaryInstructor(ASM_DIV, DOUBLE_WORD + var2);
}


void AsmCode::asmXor(asmRegister reg1, asmRegister reg2) {
    this->generateBinaryInstructor(ASM_XOR, reg1, reg2);
}

void AsmCode::push(asmRegister reg) {
    this->generateUnaryInstructor(ASM_PUSH, reg);
}

void AsmCode::push(std::string var) {
    this->generateUnaryInstructor(ASM_PUSH, var);
}

void AsmCode::pop(asmRegister reg) {
    this->generateUnaryInstructor(ASM_POP, reg);
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
    this->preSetLabel();
    eax = 0;
    ebx = 0;
    ecx = 0;
    edx = 0;
}

void AsmGenerator::releaseRegister(asmRegister reg) {
    if (reg == asmRegister::ebx) {
        ebx = 0;
        int index = (int)asmRegister::ebx;
        this->registerUsedVar[index - 1] = "";
    } else if (reg == asmRegister::ecx) {
        ecx = 0;
        int index = (int)asmRegister::ecx;
        this->registerUsedVar[index - 1] = "";
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
    int flag = q.getFlag();
    // Special case, assign operate is unary operator.
    if (opcode == OpCode::ASSIGN) {
        symbol* result = q.getArg(3).var;
        int offset = result->getOffset();
        std::string result_ebp_offset = this->asmcode.generateVar(offset);
        if (flag == 7) {
            std::string tempVar = q.getArg(1).var->getIdName();
            if (tempVar[0] == 'T') {
                asmRegister tempVarReg = this->findRegister(tempVar);
                this->asmcode.mov(result_ebp_offset, tempVarReg);
                this->releaseRegister(tempVarReg);
            } else {
                int varOffset = q.getArg(1).var->getOffset();
                std::string varEbpOffset = this->asmcode.generateVar(varOffset);
                this->asmcode.mov(asmRegister::edx, varEbpOffset);
                this->asmcode.mov(result_ebp_offset, asmRegister::edx);
            }
        }
        else {
            int tempVar = q.getArg(1).target;
            this->asmcode.mov(result_ebp_offset, DOUBLE_WORD + std::string(" ") +std::to_string(tempVar));
        }
        return;
    }
    if (opcode == OpCode::PLUS) instructor = ASM_ADD;
    else if (opcode == OpCode::MINUS) instructor = ASM_SUB;

    asmRegister tempVar1Reg = asmRegister::unset;
    asmRegister tempVar2Reg = asmRegister::unset;
    asmRegister resultReg = asmRegister::unset;
    int value1, value2;
    std::string arg1IdName = "";
    std::string arg2IdName = "";
    // Result must be temp var or var, cannot be instance number
    std::string resultIdName = q.getArg(3).var->getIdName();
    
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
        if (tempVar1Reg != asmRegister::unset && tempVar2Reg != asmRegister::unset) {
            if (opcode == OpCode::PLUS || opcode == OpCode::MINUS) {
                this->asmcode.generateBinaryInstructor(instructor, tempVar1Reg, tempVar2Reg);
            } else {
                if (opcode == OpCode::TIMES) {
                    this->asmcode.mul(tempVar1Reg, tempVar1Reg);
                } else if (opcode == OpCode::DIV || opcode == OpCode::MOD) {
                    this->asmcode.div(tempVar1Reg, tempVar2Reg);
                }
            }
            if (resultReg != asmRegister::unset) {
                if (opcode == OpCode::PLUS || opcode == OpCode::MINUS) {
                    if (tempVar1Reg != resultReg) {
                        this->asmcode.mov(resultReg, tempVar1Reg);
                    }
                } else {
                    if (opcode == OpCode::TIMES || opcode == OpCode::DIV) {
                        this->asmcode.mov(resultReg, asmRegister::eax);
                    } else {
                        this->asmcode.mov(resultReg, asmRegister::edx);
                    }
                }
            } else {
                symbol* result = q.getArg(3).var;
                int offset = result->getOffset();
                std::string ebp_offset = this->asmcode.generateVar(offset);
                if (opcode == OpCode::PLUS || opcode == OpCode::MINUS) {
                    if (tempVar1Reg != resultReg) {
                        this->asmcode.mov(ebp_offset, tempVar1Reg);
                    }
                } else {
                    if (opcode == OpCode::TIMES || opcode == OpCode::DIV) {
                        this->asmcode.mov(ebp_offset, asmRegister::eax);
                    } else {
                        this->asmcode.mov(ebp_offset, asmRegister::edx);
                    }
                }
            }
        } else if (tempVar1Reg != asmRegister::unset || tempVar2Reg != asmRegister::unset) {
            asmRegister reg = asmRegister::unset;
            symbol* vars = NULL;
            std::string var = "";
            if (tempVar1Reg == asmRegister::unset) {
                reg = tempVar2Reg;
                symbol* vars = q.getArg(1).var;
                int offset = vars->getOffset();
                var = this->asmcode.generateVar(offset);
                if (opcode == OpCode::PLUS || opcode == OpCode::MINUS) {
                    this->asmcode.generateBinaryInstructor(instructor, var, reg);
                    this->asmcode.mov(reg, var);
                } else {
                    if (opcode == OpCode::TIMES || opcode == OpCode::DIV) {
                        if (opcode == OpCode::TIMES) {
                            this->asmcode.mul(reg, var);
                        } else {
                            this->asmcode.div(var, reg);
                        }
                        this->asmcode.mov(reg, asmRegister::eax);
                    } else {
                        this->asmcode.div(var, reg);
                        this->asmcode.mov(reg, asmRegister::edx);
                    }
                }
            } else {
                reg = tempVar1Reg;
                symbol* vars = q.getArg(2).var;
                int offset = vars->getOffset();
                var = this->asmcode.generateVar(offset);
                if (opcode == OpCode::PLUS || opcode == OpCode::MINUS) {
                    this->asmcode.generateBinaryInstructor(instructor, reg, var);
                } else {
                    if (opcode == OpCode::TIMES || opcode == OpCode::DIV) {
                         if (opcode == OpCode::TIMES) {
                            this->asmcode.mul(reg, var);
                        } else {
                            this->asmcode.div(reg, var);
                        }
                        if (reg != resultReg) {
                            this->asmcode.mov(resultReg, asmRegister::eax);
                        } else {
                            this->asmcode.mov(reg, asmRegister::eax);
                        }
                    } else {
                        this->asmcode.div(reg, var);
                        this->asmcode.mov(reg, asmRegister::edx);
                    }
                }
                // this->asmcode.generateBinaryInstructor(instructor, reg, var);
            }
            if (resultReg != asmRegister::unset) {
                if (reg != resultReg) {
                    this->asmcode.mov(resultReg, reg);
                }
            } else {
                symbol* result = q.getArg(3).var;
                int offset = result->getOffset();
                std::string ebp_offset = this->asmcode.generateVar(offset);
                this->asmcode.mov(ebp_offset, reg);
            }
        } else if (tempVar1Reg == asmRegister::unset && tempVar2Reg == asmRegister::unset) {
            symbol* var1 = q.getArg(1).var;
            symbol* var2 = q.getArg(2).var;
            std::string var1_ebp_offset = this->asmcode.generateVar(var1->getOffset());
            std::string var2_ebp_offset = this->asmcode.generateVar(var2->getOffset());
            if (resultReg != asmRegister::unset) {
                if (opcode == OpCode::PLUS || opcode == OpCode::MINUS) {
                    this->asmcode.mov(resultReg, var1_ebp_offset);
                    this->asmcode.generateBinaryInstructor(instructor, resultReg, var2_ebp_offset);
                } else {
                    if (opcode == OpCode::TIMES) {
                        this->asmcode.mul(var1_ebp_offset, var2_ebp_offset);
                    } else {
                        this->asmcode.div(var1_ebp_offset, var2_ebp_offset);
                    }
                    if (opcode == OpCode::MOD) {
                        this->asmcode.mov(resultReg, asmRegister::edx);
                    } else {
                        this->asmcode.mov(resultReg, asmRegister::eax);
                    }
                }
            }
        }
    } else if (flag == 6 || flag == 5) {
        if (flag == 6) {
            value1 = q.getArg(1).target;
            std::string instance = this->asmcode.generateInstanceNumber(value1);
            arg2IdName = q.getArg(2).var->getIdName();
            if (arg2IdName[0] == 'T') {
                tempVar2Reg = this->findRegister(arg2IdName);
                this->releaseRegister(tempVar2Reg);
                resultReg = this->getRegister(resultIdName);
                if (opcode == OpCode::PLUS || opcode == OpCode::MINUS) {
                    this->asmcode.generateBinaryInstructor(instructor, tempVar2Reg, instance);
                    if (opcode == OpCode::MINUS) {
                        this->asmcode.generateUnaryInstructor(ASM_NEG, tempVar2Reg);
                    }
                    if (resultReg != tempVar2Reg) {
                        this->asmcode.mov(resultReg, tempVar2Reg);
                    }
                } else {
                    this->asmcode.asmXor(asmRegister::edx, asmRegister::edx);
                    asmRegister regInstance = asmRegister::eax;
                    this->asmcode.mov(regInstance, instance);
                    if (opcode == OpCode::TIMES) {
                        this->asmcode.generateUnaryInstructor(ASM_MUL, tempVar2Reg);
                        this->asmcode.mov(resultReg, asmRegister::eax);
                    } else {
                        this->asmcode.generateUnaryInstructor(ASM_DIV, tempVar2Reg);
                        if (opcode == OpCode::DIV) {
                            this->asmcode.mov(resultReg, asmRegister::eax);
                        } else {
                            this->asmcode.mov(resultReg, asmRegister::edx);
                        }
                    }
                }                
            } else {
                resultReg = this->getRegister(resultIdName);
                int offset = q.getArg(2).var->getOffset();
                std::string ebpOffset = DOUBLE_WORD + this->asmcode.generateVar(offset);
                if (opcode == OpCode::PLUS || opcode == OpCode::MINUS) {
                    this->asmcode.asmXor(resultReg, resultReg);
                    this->asmcode.mov(resultReg, instance);
                    this->asmcode.generateBinaryInstructor(instructor, resultReg, ebpOffset);
                } else {
                    this->asmcode.asmXor(asmRegister::edx, asmRegister::edx);
                    this->asmcode.mov(asmRegister::eax, instance);
                    if (opcode == OpCode::TIMES) {
                        this->asmcode.generateUnaryInstructor(ASM_MUL, ebpOffset);
                        this->asmcode.mov(resultReg, asmRegister::eax);
                    } else {
                        this->asmcode.generateUnaryInstructor(ASM_DIV, ebpOffset);
                        if (opcode == OpCode::DIV) {
                            this->asmcode.mov(resultReg, asmRegister::eax);
                        } else {
                            this->asmcode.mov(resultReg, asmRegister::edx);
                        }
                    }
                }
            }
        } else {
            value2 = q.getArg(2).target;
            arg1IdName = q.getArg(1).var->getIdName();
            std::string instance = this->asmcode.generateInstanceNumber(value2);
            if (arg1IdName[0] == 'T') {
                tempVar1Reg = this->findRegister(arg1IdName);
                this->releaseRegister(tempVar1Reg);
                resultReg = this->getRegister(resultIdName);
                if (opcode == OpCode::PLUS || opcode == OpCode::MINUS) {
                    this->asmcode.generateBinaryInstructor(instructor, tempVar1Reg, instance);
                    if (resultReg != tempVar1Reg) {
                        this->asmcode.mov(resultReg, tempVar2Reg);
                    }
                } else {
                    this->asmcode.asmXor(asmRegister::edx, asmRegister::edx);
                    resultReg = this->getRegister(resultIdName);
                    // the instance number use result register.
                    asmRegister regInstance = resultReg;
                    this->asmcode.mov(regInstance, instance);
                    int offset = q.getArg(1).var->getOffset();
                    std::string ebpOffset = this->asmcode.generateVar(offset);
                    this->asmcode.mov(asmRegister::eax, ebpOffset);

                    if (opcode == OpCode::TIMES) {
                        this->asmcode.generateUnaryInstructor(ASM_MUL, regInstance);
                        this->asmcode.mov(resultReg, asmRegister::eax);
                    } else {
                        this->asmcode.generateUnaryInstructor(ASM_DIV, regInstance);
                        if (opcode == OpCode::DIV) {
                            this->asmcode.mov(resultReg, asmRegister::eax);
                        } else {
                            this->asmcode.mov(resultReg, asmRegister::edx);
                        }
                    }
                }
            } else {
                resultReg = this->getRegister(resultIdName);
                int offset = q.getArg(1).var->getOffset();
                std::string ebpOffset = DOUBLE_WORD + this->asmcode.generateVar(offset);
                if (opcode == OpCode::PLUS || opcode == OpCode::MINUS) {
                    this->asmcode.asmXor(resultReg, resultReg);
                    this->asmcode.mov(resultReg, ebpOffset);
                    this->asmcode.generateBinaryInstructor(instructor, resultReg, instance);
                } else {
                    this->asmcode.asmXor(asmRegister::edx, asmRegister::edx);
                    asmRegister instanceReg = resultReg;
                    this->asmcode.mov(asmRegister::eax, ebpOffset);
                    this->asmcode.mov(instanceReg, instance);
                    if (opcode == OpCode::TIMES) {
                        this->asmcode.generateUnaryInstructor(ASM_MUL, instanceReg);
                        this->asmcode.mov(resultReg, asmRegister::eax);
                    } else {
                        this->asmcode.generateUnaryInstructor(ASM_DIV, instanceReg);
                        if (opcode == OpCode::DIV) {
                            this->asmcode.mov(resultReg, asmRegister::eax);
                        } else {
                            this->asmcode.mov(resultReg, asmRegister::edx);
                        }
                    }
                }
            }
        }
    } else if (flag == 4) {
        value1 = q.getArg(1).target;
        value2 = q.getArg(2).target;
        std::string instance1 = this->asmcode.generateInstanceNumber(value1);
        std::string instance2 = this->asmcode.generateInstanceNumber(value2);
        resultReg = this->getRegister(resultIdName);
        if (opcode == OpCode::PLUS || opcode == OpCode::MINUS) {
            this->asmcode.mov(resultReg, instance1);
            this->asmcode.generateBinaryInstructor(instructor, resultReg, instance2);
        } else {
            this->asmcode.asmXor(asmRegister::edx, asmRegister::edx);
            this->asmcode.mov(asmRegister::eax, instance1);
            this->asmcode.mov(resultReg, instance2);
            if (opcode == OpCode::TIMES) {
                this->asmcode.generateUnaryInstructor(ASM_MUL, resultReg);
                this->asmcode.mov(resultReg, asmRegister::eax);
            } else {
                this->asmcode.generateUnaryInstructor(ASM_DIV, resultReg);
                if (opcode == OpCode::DIV) {
                    this->asmcode.mov(resultReg, asmRegister::eax);
                } else {
                    this->asmcode.mov(resultReg, asmRegister::edx);
                }
            }
        }
    }
}

void AsmGenerator::generateDefFunction(Quad& q) {
    std::string funcName = q.getArg(1).var->getIdName();
    this->asmcode.label(funcName);
    this->asmcode.addCode(ASM_ENTER + std::string(" ") + std::to_string(currentTable->getTotalOffset()) + ASM_COMMA + "0");
    this->asmcode.push(asmRegister::ebx);
    this->asmcode.push(asmRegister::ecx);
}

void AsmGenerator::generateReturn(Quad& q) {
    if (q.getArg(1).target == 0) {
        this->generateEndFunction(q);
        return;
    }
    int flag = q.getFlag();
    if (flag == 7) {
        symbol* s = q.getArg(1).var;
        std::string name = s->getIdName();
        if (name[0] == 'T') {
            asmRegister reg = this->findRegister(name);
            this->releaseRegister(reg);
            this->asmcode.mov(asmRegister::eax, reg);
        } else {
            int offset = s->getOffset();
            std::string varEbpOffset = this->asmcode.generateVar(offset);
            this->asmcode.mov(asmRegister::eax, varEbpOffset);
        }
    } else {
        int value = q.getArg(1).target;
        this->asmcode.mov(asmRegister::eax, std::to_string(value));
    }
}

void AsmGenerator::generateEndFunction(Quad& q) {
    this->asmcode.pop(asmRegister::ecx);
    this->asmcode.pop(asmRegister::ebx);
    this->asmcode.addCode(ASM_LEAVE);
    this->asmcode.addCode(ASM_RET);
}

void AsmGenerator::generateCallBuildInFunction(Quad& q, Quad& arg) {
    std::string funcName = q.getArg(1).var->getIdName();
    int tempVar = 0;
    int varOffSet = 0;
    std::string argNam = arg.getArg(1).var->getIdName();
    asmRegister tempVarReg = asmRegister::unset;
    if (argNam[0] == 'T') {
        tempVarReg = this->findRegister(argNam);
    } else {
        symbol* s = arg.getArg(1).var;
        varOffSet = s->getOffset();
    }
    if (funcName == "print_int_i") {
        if (tempVarReg != asmRegister::unset) {
            this->asmcode.mov(asmRegister::eax, tempVarReg);
        } else {
            std::string varEbpOffset = this->asmcode.generateVar(varOffSet);
            this->asmcode.mov(asmRegister::eax, varEbpOffset);
        }
        this->generateCallFunction(q);
    } else if (funcName == "read_int_i") {
        this->generateCallFunction(q);
        std::string varEbpOffset = this->asmcode.generateVar(varOffSet);
        this->asmcode.mov(varEbpOffset, asmRegister::eax);
    }
}

void AsmGenerator::generateCallFunction(Quad& q) {
    std::string funcName = q.getArg(1).var->getIdName();
    this->asmcode.generateUnaryInstructor(ASM_CALL, funcName);
    if (q.getArg(3).var != NULL) {
        std::string tempVar = q.getArg(3).var->getIdName();
        asmRegister tempReg = this->getRegister(tempVar);
        this->asmcode.mov(tempReg, asmRegister::eax);
    }
    // Protect the esp
    FuncSymbol* func = funcTable.findFunction(funcName);
    int offset = func->getTotalArgOffset();
    if (offset != 0) this->asmcode.add(asmRegister::esp, std::to_string(offset));
}

void AsmGenerator::generateSetArg(Quad& q) {
    int flag = q.getFlag();
    std::string varName = "";
    if (flag == 7) {
        varName = q.getArg(1).var->getIdName();
        if (varName[0] != 'T') {
            int offset = q.getArg(1).var->getOffset();
            std::string varEbpOffset = this->asmcode.generateVar(offset);
            this->asmcode.push(varEbpOffset);
        } else {
            asmRegister reg = this->findRegister(varName);
            this->releaseRegister(reg);
            this->asmcode.push(reg);
        }
    } else {
        int value = q.getArg(1).target;
        std::string instanceNumber = this->asmcode.generateInstanceNumber(value);
        this->asmcode.push(instanceNumber);
    }
}

void AsmGenerator::generateJump(Quad& q) {
    OpCode opcode = q.getOpCode();
    std::string label = "label" + std::to_string(labelMap[q.getArg(3).target]);
    if (opcode == OpCode::JUMP) {
        this->asmcode.generateUnaryInstructor(ASM_JUMP, label);
    } else {
        int flag = q.getFlag();
        if (flag == 0) {
            std::string value1 = std::to_string(q.getArg(1).target);
            std::string value2 = std::to_string(q.getArg(2).target);
            this->asmcode.mov(asmRegister::edx, value1);
            this->asmcode.generateBinaryInstructor(ASM_CMP, asmRegister::edx, value2);
        } else if (flag == 1) {
            std::string value2 = this->asmcode.generateInstanceNumber(q.getArg(2).target);
            std::string var1Name = q.getArg(1).var->getIdName();
            if (var1Name[0] == 'T') {
                asmRegister var1Reg = this->findRegister(var1Name);
                this->releaseRegister(var1Reg);
                this->asmcode.generateBinaryInstructor(ASM_CMP, var1Reg, value2);
            } else {
                int offset = q.getArg(1).var->getOffset();
                std::string var1EbpOffset = this->asmcode.generateVar(offset);
                this->asmcode.generateBinaryInstructor(ASM_CMP, var1EbpOffset, value2);
            }
        } else if (flag == 2) {
            std::string value1 = this->asmcode.generateInstanceNumber(q.getArg(1).target);
            std::string var2Name = q.getArg(2).var->getIdName();
            if (var2Name[0] == 'T') {
                asmRegister var2Reg = this->findRegister(var2Name);
                this->asmcode.mov(asmRegister::edx, value1);
                this->releaseRegister(var2Reg);
                this->asmcode.generateBinaryInstructor(ASM_CMP, asmRegister::edx, var2Reg);
            } else {
                int offset = q.getArg(2).var->getOffset();
                std::string var2EbpOffset = this->asmcode.generateVar(offset);
                this->asmcode.generateBinaryInstructor(ASM_CMP, var2EbpOffset, value1);
            }
        } else if (flag == 3) {
            std::string value1 = std::to_string(q.getArg(1).target);
            std::string value2 = std::to_string(q.getArg(2).target);
            if (value1[0] == 'T' && value1[0] == 'T') {
                asmRegister v1 = this->findRegister(value1);
                asmRegister v2 = this->findRegister(value2);
                this->asmcode.generateBinaryInstructor(ASM_CMP, v1, v2);
            } else if (value1[0] == 'T') {
                asmRegister v1 = this->findRegister(value1);
                int offset = q.getArg(2).var->getOffset();
                std::string v2EbpOffset = this->asmcode.generateVar(offset);
                this->asmcode.generateBinaryInstructor(ASM_CMP, v1, v2EbpOffset);
            } else if (value2[0] == 'T') {
                asmRegister v2 = this->findRegister(value2);
                int offset = q.getArg(1).var->getOffset();
                std::string v1EbpOffset = this->asmcode.generateVar(offset);
                this->asmcode.mov(asmRegister::edx, v1EbpOffset);
                this->asmcode.generateBinaryInstructor(ASM_CMP, asmRegister::edx, v2);
            } else {
                std::string v1EbpOffset = this->asmcode.generateVar(q.getArg(1).var->getOffset());
                std::string v2EbpOffset = this->asmcode.generateVar(q.getArg(2).var->getOffset());
                this->asmcode.mov(asmRegister::edx, v1EbpOffset);
                this->asmcode.generateBinaryInstructor(ASM_CMP, asmRegister::edx, v2EbpOffset);
            }
        }
        if (opcode == OpCode::JUMP_EQ_GREAT) {
            this->asmcode.generateUnaryInstructor(ASM_JGE, label);
        } else if (opcode == OpCode::JUMP_GREAT) {
            this->asmcode.generateUnaryInstructor(ASM_JG, label);
        } else if (opcode == OpCode::JUMP_EQ_SMALL) {
            this->asmcode.generateUnaryInstructor(ASM_JLE, label);
        } else if (opcode == OpCode::JUMP_SMALL) {
            this->asmcode.generateUnaryInstructor(ASM_JL, label);
        } else if (opcode == OpCode::JUMP_EQUAL) {
            this->asmcode.generateUnaryInstructor(ASM_JE, label);
        } else if (opcode == OpCode::JUMP_NOT_EQUAL) {
            this->asmcode.generateUnaryInstructor(ASM_JNE, label);
        }
    }
}

void AsmGenerator::preSetLabel() {
    std::vector<Quad> quad;
    int labelNumber = 0;
    for (size_t i = 0; i < quads.size(); i++) {
        OpCode opcode = quads[i].getOpCode();
        if (this->isJumpQuad(opcode)) {
            int lineNum = quads[i].getArg(3).target;
            if (labelMap.count(lineNum) == 0) {
                labelMap[lineNum] = labelNumber;
                labelNumber++;
            }
        }
    }
    for (size_t i = 0; i < quads.size(); i++) {
        if (labelMap.count(i) > 0) {
            Quad q(OpCode::LABEL, labelMap[i], (symbol*)NULL, (symbol*)NULL);
            quad.push_back(q);
        }
        quad.push_back(quads[i]);
    }
    quads=quad;
    for (size_t i = 0; i < quads.size(); i++) quads[i].printQuad();
}

bool AsmGenerator::isJumpQuad(OpCode opcode) {
    return opcode == OpCode::JUMP || opcode == OpCode::JUMP_SMALL || opcode == OpCode::JUMP_EQ_SMALL ||
        opcode == OpCode::JUMP_GREAT || opcode == OpCode::JUMP_EQ_GREAT || opcode == OpCode::JUMP_EQUAL ||
        opcode == OpCode::JUMP_NOT_EQUAL;
}

void AsmGenerator::generate() {
    currentTable = rootTable;
    // Set header info
    this->asmcode.addCode("\%include \"io/asm_io.inc\"\nsection .text\nglobal main\n");
    for (size_t i = 0; i < this->quads.size(); i++) {
        Quad& q = quads[i];
        OpCode opcode = q.getOpCode();
        if (opcode == OpCode::FUNC_DEF) {
            this->generateDefFunction(q);
            if (currentTable == rootTable) {
                currentTable = currentTable->getChild();
            } else {
                currentTable = currentTable->getPeer();
            }
        }
        else if (opcode == OpCode::PLUS || opcode == OpCode::MINUS ||
                 opcode == OpCode::DIV || opcode == OpCode::TIMES ||
                 opcode == OpCode::ASSIGN || opcode == OpCode::MOD) {
            this->generateArithmetic(q);
        }
        else if (opcode == OpCode::PARAM) {
            Quad& next = quads[i + 1];
            if (next.getOpCode() == OpCode::CALL) {
                if (next.getArg(1).var->getIdName() == "print_int_i" || 
                    next.getArg(1).var->getIdName() == "read_int_i") {
                        this->generateCallBuildInFunction(next, q);
                        i = i + 1;
                        continue;
                    }
            }
            // Push the args to stack
            this->generateSetArg(q);
        }
        else if (opcode == OpCode::CALL) {
            this->generateCallFunction(q);
        } else if (opcode == OpCode::END_FUNCTION) {
            this->generateEndFunction(q);
        } else if (opcode == OpCode::RETURN) {
            this->generateReturn(q);
        } else if (opcode == OpCode::LABEL) {
            int labelIndex = q.getArg(1).target;
            this->asmcode.label("label" + std::to_string(labelIndex));
        } else if (this->isJumpQuad(opcode)) {
            this->generateJump(q);
        }
    }
}
