#ifndef QUAD_H
#define QUAD_H

#include <iostream>
#include <string>
#include "../symbol/symbol.h"
#include "../trees.h"

/***********************
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
enum class OpCode
{
    JUMP,
    JUMP_SMALL,
    JUMP_EQ_SMALL,
    JUMP_GREAT,
    JUMP_EQ_GREAT,
    JUMP_EQUAL,
    JUMP_NOT_EQUAL,
    PLUS,
    MINUS,
    TIMES,
    DIV,
    MOD,
    POWER,
    NEGATIVE,
    ASSIGN,
    ASSIGN_ARRAY,
    ASSIGN_STRUCT,
    ASSIGN_POINTER,
    GET_ADDRESS,
    PARAM,
    CALL,
    RETURN,
    FUNC_DEF,
    END_FUNCTION,
    LABEL,
    GET_VALUE,
    GET_ARRAY,
    GET_STRUCT
};

union Arg {// arg是联合类型，可以代表一个符号或者一个变量
    symbol *var;
    int target;
};

class Quad
{
private:
    OpCode op;
    Arg arg1;
    Arg arg2;
    Arg result;
    /********************************
 * |      | arg1 | arg2 | result|
 * | int  |  0   |   0  |   0   |
 * |symbol|  1   |   2  |   4   |
 * *******************************
*/
    int flag;
    std::string printOp();

public:
    // Jump to the target
    Quad(OpCode op, int result);
    Quad(OpCode op, symbol *arg1, symbol *result); // assign variable to variable
    Quad(OpCode op, int arg1, symbol *result);     // assign literals to variable
    Quad(OpCode op, symbol *arg1, symbol *arg2, symbol *result);
    Quad(OpCode op, int arg1, symbol *arg2, symbol *result);
    Quad(OpCode op, symbol *arg1, int arg2, symbol *result);
    Quad(OpCode op, int arg1, int arg2, symbol *result);

    Quad(OpCode op, symbol *arg1, symbol *arg2, int result);
    Quad(OpCode op, symbol *arg1, int arg2, int result);
    Quad(OpCode op, int arg1, int arg2, int result);

    inline void backpatch(int target) { this->result.target = target; }; 
    // 上面的是回填函数，将传入参数填入到target里面，代表跳转的目标地址
    inline int getResult() { return this->result.target == 0 ? 1 : 0; }
    // 是0就返回1,不是0就返回0
    inline int getFlag() { return this->flag; }
    inline OpCode getOpCode() { return this->op; }
    inline Arg getArg(int index)
    {
        if (index == 1)
            return this->arg1;
        else if (index == 2)
            return this->arg2;
        else if (index == 3)
            return this->result;
    }
    void printQuad();
};
#endif