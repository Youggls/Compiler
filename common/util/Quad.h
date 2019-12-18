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
 * @enum GET_ADDRESS: &arg1 to reuslt
 * @enum PARAM: Param of the function will be called
 * @enum CALL: CALL function
 * @enum RETURN: Exit from a function
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
    GET_ADDRESS,
    PARAM,
    CALL,
    RETURN,
    FUNC_DEF,
    END_FUNCTION,
    LABEL
};

union Arg {
    symbol *var;
    // double *tempVar; // 临时变量 也用symbol存储，只不过存储在vector中
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
    inline int getResult() { return this->result.target == 0 ? 1 : 0; }
    inline int getFlag() { return this->flag; }
    inline OpCode getOpCode() { return this->op; }
    inline Arg getArg(int index) {
        if (index == 1) return this->arg1;
        else if (index == 2) return this->arg2;
        else if (index == 3) return this->result;
    }
    void printQuad();
    // Quad(OpCode op, symbol *arg1, symbol *arg2, symbol *result);
    // Quad(OpCode op, symbol *arg1, symbol *arg2, int result)
};
#endif