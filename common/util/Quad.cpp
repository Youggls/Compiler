#include "Quad.h"
#include <typeinfo>


// flag的不同值如下:
/* 
enum class symbolType
{
    unset = -1,
    integer = 0,
    function = 1,
    pointer = 2,
    boolean = 3,
    Void = 4,
    Struct = 5,
    Array = 6,
    literal = 7
};
*/

// 四元式：
/*
四元式实际上是一种“三地址语句”的等价表示。它的一般形式为：
(op,arg1,arg2,result)
*/

/*
symbol代表变量，int代表字面量
比如 int a = 1；
这里面，a是变量，1是字面量
char a[100] = "111223";
就是将字符串字面量赋值给变量
*/

/*********************** opCode 的操作有很多，对应函数的第一个参数
 * Operation Code for a Quad:
 * @enum JUMP:  JUMP operation.
 * @enum JUMP_SMALL:    if arg1 <  arg2, JUMP
 * @enum JUMP_EQ_SMALL: if arg1 <= arg2, JUMP
 * @enum JUMP_GRATE:    if arg1 >  arg2, JUMP
 * @enum JUMP_EQ_GREAT: if arg1 >= arg2, JUMP
 * @enum JUMP_EQUAL:    if arg1 == arg2, JUMP
 * @enum JUMP_NOT_EQUAL:if arg1 != arg2, JUMP
 * @enum PLUS:  arg1 + arg2 to result
 * @enum MINUS: arg1 - arg2 to result
 * @enum TIMES: arg1 * arg2 to result
 * @enum DIV:   arg1 / arg2 to result
 * @enum MOD:   arg1 % arg2 to result
 * @enum POWER: arg1 ^ arg2 to result
 * @enum NEGATIVE:   - arg1 to result
 * @enum ASSIGN:       arg1 to result
 * @enum ASSIGN_ARRAY: result[arg2] = arg1
 * @enum ASSIGN_STRUCT: result.arg2 = arg1
 * @enum GET_ADDRESS: &arg1 to reuslt
 * @enum PARAM: Param of the function will be called
 * @enum CALL: CALL function
 * @enum RETURN: Exit from a function
 * @enum GET_VALUE: Get the value of a pointer
 * @enum GET_ARRAY: Get the value of an array
 * @enum GET_STRUCT:GET the value of a struct
 ************************
*/
Quad::Quad(OpCode op, int result)// bool 运算符,代表正负
{
    this->op = op;
    this->arg1.var = NULL;
    this->arg2.var = NULL;
    this->result.target = result;
    this->flag = 3;
}

Quad::Quad(OpCode op, symbol *arg1, symbol *result) 
// assign variable to variable
{
    this->op = op;
    this->arg1.var = arg1;
    this->arg2.var = NULL;
    this->result.var = result;
    this->flag = 7;
}

Quad::Quad(OpCode op, int arg1, symbol *result)
// assign literals to variable
// 字面量到变量
{
    this->op = op;
    this->arg1.target = arg1;
    this->arg2.var = NULL;
    this->result.var = result;
    this->flag = 6;
}

Quad::Quad(OpCode op, symbol *arg1, symbol *arg2, symbol *result) 
// 二元运算符，两个变量运算
{
    this->op = op;
    this->arg1.var = arg1;
    this->arg2.var = arg2;
    this->result.var = result;
    this->flag = 7;
}

Quad::Quad(OpCode op, int arg1, symbol *arg2, symbol *result)
// 变量跟字面量运算：2*a
{
    this->op = op;
    this->arg1.target = arg1;
    this->arg2.var = arg2;
    this->result.var = result;
    this->flag = 6;
}

Quad::Quad(OpCode op, symbol *arg1, int arg2, symbol *result)
// 变量跟字面量运算：a*2
{
    this->op = op;
    this->arg1.var = arg1;
    this->arg2.target = arg2;
    this->result.var = result;
    this->flag = 5;
}
Quad::Quad(OpCode op, int arg1, int arg2, symbol *result)
// 字面量跟字面量运算：2*2
{
    this->op = op;
    this->arg1.target = arg1;
    this->arg2.target = arg2;
    this->result.var = result;
    this->flag = 4;
}

Quad::Quad(OpCode op, symbol *arg1, symbol *arg2, int result)
// 变量跟变量运算，值为int
{
    this->op = op;
    this->arg1.var = arg1;
    this->arg2.var = arg2;
    this->result.target = result;
    this->flag = 3;
}
Quad::Quad(OpCode op, symbol *arg1, int arg2, int result)
// 变量跟字面量运算，值为int
{
    this->op = op;
    this->arg1.var = arg1;
    this->arg2.target = arg2;
    this->result.target = result;
    this->flag = 1;
}
Quad::Quad(OpCode op, int arg1, int arg2, int result)
// 都是字面量： 5 = 1*5 
{
    this->op = op;
    this->arg1.target = arg1;
    this->arg2.target = arg2;
    this->result.target = result;
    this->flag = 0;
}
// 打印生成的运算符
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
        return "     DIV      ";
    case OpCode::MOD:
        return "     MOD      ";
    case OpCode::POWER:
        return "    POWER     ";
    case OpCode::NEGATIVE:
        return "   NEGATIVE   ";
    case OpCode::ASSIGN:
        return "    ASSIGN    ";
    case OpCode::ASSIGN_ARRAY:
        return " ASSIGN_ARRAY ";
    case OpCode::ASSIGN_STRUCT:
        return "ASSIGN_STRUCT ";
    case OpCode::GET_ADDRESS:
        return " GET_ADDRESS  ";
    case OpCode::ASSIGN_POINTER:
        return "ASSIGN_POINTER";
    case OpCode::PARAM:
        return "    PARAM     ";
    case OpCode::CALL:
        return "     CALL     ";
    case OpCode::RETURN:
        return "    RETURN    ";
    case OpCode::FUNC_DEF:
        return "   FUNC_DEF   ";
    case OpCode::END_FUNCTION:
        return " END_FUNCTION ";
    case OpCode::LABEL:
        return "     LABEL    ";
    case OpCode::GET_VALUE:
        return "  GET_VALUE   ";
    case OpCode::GET_ARRAY:
        return "  GET_ARRAY   ";
    case OpCode::GET_STRUCT:
        return "  GET_STRUCT  ";
    default:
        break;
    }
}
void Quad::printQuad()
// 打印生成的四元式
{
    switch (this->flag)
    {
    case 0:
    {
        std::cout << this->printOp() << "\t" << this->arg1.target << "\t" << this->arg2.target << "\t" << this->result.target << std::endl;
    // Quad::Quad(OpCode op, int arg1, int arg2, int result)
    // 都是字面量： 5 = 1*5 
        break;
    }
    case 1:
    {
        // Quad::Quad(OpCode op, symbol *arg1, int arg2, int result)
        // 变量跟字面量运算，值为int
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