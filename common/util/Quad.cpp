#include "Quad.h"
#include <typeinfo>

Quad::Quad(OpCode op, int result)
{
    this->op = op;
    this->arg1.var = NULL;
    this->arg2.var = NULL;
    this->result.target = result;
    this->flag = 3;
}

Quad::Quad(OpCode op, symbol *arg1, symbol *result)
{
    this->op = op;
    this->arg1.var = arg1;
    this->arg2.var = NULL;
    this->result.var = result;
    this->flag = 7;
}

Quad::Quad(OpCode op, int arg1, symbol *result)
{
    this->op = op;
    this->arg1.target = arg1;
    this->arg2.var = NULL;
    this->result.var = result;
    this->flag = 6;
}

Quad::Quad(OpCode op, symbol *arg1, symbol *arg2, symbol *result)
{
    this->op = op;
    this->arg1.var = arg1;
    this->arg2.var = arg2;
    this->result.var = result;
    this->flag = 7;
}

Quad::Quad(OpCode op, int arg1, symbol *arg2, symbol *result)
{
    this->op = op;
    this->arg1.target = arg1;
    this->arg2.var = arg2;
    this->result.var = result;
    this->flag = 6;
}

Quad::Quad(OpCode op, symbol *arg1, int arg2, symbol *result)
{
    this->op = op;
    this->arg1.var = arg1;
    this->arg2.target = arg2;
    this->result.var = result;
    this->flag = 5;
}
Quad::Quad(OpCode op, int arg1, int arg2, symbol *result)
{
    this->op = op;
    this->arg1.target = arg1;
    this->arg2.target = arg2;
    this->result.var = result;
    this->flag = 4;
}

Quad::Quad(OpCode op, symbol *arg1, symbol *arg2, int result)
{
    this->op = op;
    this->arg1.var = arg1;
    this->arg2.var = arg2;
    this->result.target = result;
    this->flag = 3;
}
Quad::Quad(OpCode op, symbol *arg1, int arg2, int result)
{
    this->op = op;
    this->arg1.var = arg1;
    this->arg2.target = arg2;
    this->result.target = result;
    this->flag = 1;
}
Quad::Quad(OpCode op, int arg1, int arg2, int result)
{
    this->op = op;
    this->arg1.target = arg1;
    this->arg2.target = arg2;
    this->result.target = result;
    this->flag = 0;
}
std::string Quad::printOp()
{
    switch (this->op)
    {
    case OpCode::JUMP:
        return "     JUMP     ";
    case OpCode::JUMP_SMALL:
        return "  JUMP_SMALL  ";
    case OpCode::JUMP_EQ_SMALL:
        return "JUMP_EQ_SMALL ";
    case OpCode::JUMP_GREAT:
        return "  JUMP_GREAT  ";
    case OpCode::JUMP_EQ_GREAT:
        return "JUMP_EQ_GREAT ";
    case OpCode::JUMP_EQUAL:
        return "  JUMO_EQUAL  ";
    case OpCode::JUMP_NOT_EQUAL:
        return "JUMP_NOT_EQUAL";
    case OpCode::PLUS:
        return "     PLUS     ";
    case OpCode::MINUS:
        return "    MINUS     ";
    case OpCode::TIMES:
        return "    TIMES     ";
    case OpCode::DIV:
        return "      DIV     ";
    case OpCode::MOD:
        return "      MOD     ";
    case OpCode::POWER:
        return "    POWER     ";
    case OpCode::NEGATIVE:
        return "   NEGATIVE   ";
    case OpCode::ASSIGN:
        return "    ASSIGN    ";
    case OpCode::GET_ADDRESS:
        return " GET_ADDRESS  ";
    case OpCode::PARAM:
        return "    PARAM     ";
    case OpCode::RETURN:
        return "   RETURN     ";
    default:
        break;
    }
}
void Quad::printQuad()
{
    switch (this->flag)
    {
    case 0:
    {
        std::cout << this->printOp() << "\t" << this->arg1.target << "\t" << this->arg2.target << "\t" << this->result.target << std::endl;
        break;
    }
    case 1:
    {
        if (arg1.var == NULL)
            std::cout << this->printOp() << "\t-\t" << this->arg2.target << "\t" << this->result.target << std::endl;
        else
            std::cout << this->printOp() << "\t" << this->arg1.var->getIdName() << "\t" << this->arg2.target << "\t" << this->result.target << std::endl;
        break;
    }
    case 2:
    {
        if (arg2.var == NULL)
            std::cout << this->printOp() << "\t" << this->arg1.target << "\t" << this->arg2.var->getIdName() << "\t" << this->result.target << std::endl;
        else
            std::cout << this->printOp() << "\t" << this->arg1.target << "\t-\t" << this->result.target << std::endl;
        break;
    }
    case 3:
    {
        if (arg1.var == NULL)
        {
            if (arg2.var == NULL)
                std::cout << this->printOp() << "\t-\t-\t" << this->result.target << std::endl;
            else
                std::cout << this->printOp() << "\t-\t" << this->arg2.var->getIdName() << "\t" << this->result.target << std::endl;
        }
        else
        {
            if (arg2.var == NULL)
                std::cout << this->printOp() << "\t" << this->arg1.var->getIdName() << "\t-\t" << this->result.target << std::endl;
            else
                std::cout << this->printOp() << "\t" << this->arg1.var->getIdName() << "\t" << this->arg2.var->getIdName() << "\t" << this->result.target << std::endl;
        }
        break;
    }
    case 4:
    {
        if (result.var == NULL)
            std::cout << this->printOp() << "\t" << this->arg1.target << "\t" << this->arg2.target << "\t-" << std::endl;
        else
            std::cout << this->printOp() << "\t" << this->arg1.target << "\t" << this->arg2.target << "\t" << this->result.var->getIdName() << std::endl;
    }
    break;
    case 5:
    {
        if (arg1.var == NULL)
            std::cout << this->printOp() << "\t-\t" << this->arg2.target << "\t";
        else
            std::cout << this->printOp() << "\t" << this->arg1.var->getIdName() << "\t" << this->arg2.target << "\t";

        if (result.var == NULL)
            std::cout << "-" << std::endl;
        else
            std::cout << this->result.var->getIdName() << std::endl;
    }
    break;
    case 6:
    {
        if (arg2.var == NULL)
            std::cout << this->printOp() << "\t" << this->arg1.target << "\t-\t";
        else
            std::cout << this->printOp() << "\t" << this->arg1.target << "\t" << this->arg2.var->getIdName() << "\t";
        if (result.var == NULL)
            std::cout << "-" << std::endl;
        else
            std::cout << this->result.var->getIdName() << std::endl;
    }
    break;
    case 7:
    {
        if (arg1.var == NULL)
            std::cout << this->printOp() << "\t-\t";
        else
            std::cout << this->printOp() << "\t" << this->arg1.var->getIdName() << "\t";
        if (arg2.var == NULL)
            std::cout << "-\t";
        else
            std::cout << this->arg2.var->getIdName() << "\t";
        if (result.var == NULL)
            std::cout << "-" << std::endl;
        else
            std::cout << this->result.var->getIdName() << std::endl;
    }
    default:
        break;
    }
}