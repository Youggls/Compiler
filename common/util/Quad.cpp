#include "Quad.h"
#include <typeinfo>

Quad::Quad(OpCode op, int result)
{
    this->op = op;
    this->result.target = result;
}

Quad::Quad(OpCode op, symbol *arg1, symbol *result)
{
    this->op = op;
    this->arg1.var = arg1;
    this->result.var = result;
}

Quad::Quad(OpCode op, int arg1, symbol *result)
{
    this->op = op;
    this->arg1.target = arg1;
    this->result.var = result;
}

Quad::Quad(OpCode op, symbol *arg1, symbol *arg2, symbol *result)
{
    this->op = op;
    this->arg1.var = arg1;
    this->arg2.var = arg2;
    this->result.var = result;
}

Quad::Quad(OpCode op, int arg1, symbol *arg2, symbol *result)
{
    this->op = op;
    this->arg1.target = arg1;
    this->arg2.var = arg2;
    this->result.var = result;
}

Quad::Quad(OpCode op, symbol *arg1, int arg2, symbol *result)
{
    this->op = op;
    this->arg1.var = arg1;
    this->arg2.target = arg2;
    this->result.var = result;
}
Quad::Quad(OpCode op, int arg1, int arg2, symbol *result)
{
    this->op = op;
    this->arg1.target = arg1;
    this->arg2.target = arg2;
    this->result.var = result;
}

Quad::Quad(OpCode op, symbol *arg1, symbol *arg2, int result)
{
    this->op = op;
    this->arg1.var = arg1;
    this->arg2.var = arg2;
    this->result.target = result;
}
Quad::Quad(OpCode op, symbol *arg1, int arg2, int result)
{
    this->op = op;
    this->arg1.var = arg1;
    this->arg2.target = arg2;
    this->result.target = result;
}
Quad::Quad(OpCode op, int arg1, int arg2, int result)
{
    this->op = op;
    this->arg1.target = arg1;
    this->arg2.target = arg2;
    this->result.target = result;
}
