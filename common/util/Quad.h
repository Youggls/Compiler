#ifndef QUAD_H
#define QUAD_H

#define VAR "10VarASTNode"
#define STMT "11StmtASTNode"
#define ROOT "11RootASTNode"
#define LOOP "11LoopASTNode"
#define DEFINE_VAR "13DefVarASTNode"
#define DEFINE_FUN "13DefFunASTNode"
#define SELECT "13SelectASTNode"
#define LITERAL "14LiteralASTNode" // 常量
#define CALL "14CallFunASTNode"
// IdentifierASTNode 等着删了，没用
#define OPERATOR "15OperatorASTNode"

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
 * @enum JUMP_EQ_GRATE: if arg1 >= arg2, JUMP
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
 * @enum PARAM: Param of the function will be called
 ************************
*/
enum class OpCode
{
    JUMP,
    JUMP_SMALL,
    JUMP_EQ_SMALL,
    JUMP_GREAT,
    JUMP_EQ_GRATE,
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
    PARAM
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
    // Quad(OpCode op, symbol *arg1, symbol *arg2, symbol *result);
    // Quad(OpCode op, symbol *arg1, symbol *arg2, int result)
};
#endif