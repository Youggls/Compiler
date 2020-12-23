#ifndef ASMCODE_H
#define ASMCODE_H

// 首先介绍我们会经常看到的一些寄存器:
// 4个数据寄存器(EAX、EBX、ECX和EDX)
// 2个变址和指针寄存器(ESI和EDI)
// 2个指针寄存器(ESP和EBP)
// Eax可以存储的数字是DWORD（双字）
// Eax用来保存所有API函数的返回值。

// 寄存器AX和AL通常称为累加器(Accumulator)，用累加器进行的操作可能需要更少时间。累加器可用于乘、除、输入/输出等操作，它们的使用频率很高；
// 寄存器BX称为基地址寄存器(Base Register)。它可作为存储器指针来使用； 
// 寄存器CX称为计数寄存器(Count Register)。在循环和字符串操作时，要用它来控制循环次数；在位操作中，当移多位时，要用CL来指明移位的位数；
// 寄存器DX称为数据寄存器(Data Register)。在进行乘、除运算时，它可作为默认的操作数参与运算，也可用于存放I/O的端口地址。

// Asm instructor 各种各样的指令，转移、相加、push等等
#define ASM_MOV     "mov"
#define ASM_ADD     "add"
#define ASM_XOR     "xor"
#define ASM_NEG     "neg" //NEG是汇编指令中的求补指令，NEG指令对操作数执行求补运算：用零减去操作数，然后结果返回操作数。求补运算也可以表达成：将操作数按位取反后加1。
#define ASM_SUB     "sub"
#define ASM_MUL     "mul"
#define ASM_DIV     "div"
#define ASM_PUSH    "push"
#define ASM_POP     "pop"
#define ASM_CALL    "call"
#define ASM_RET     "ret" // 返回指令
#define ASM_CMP     "cmp" 
#define ASM_ENTER   "enter"
// ENTER 指令为被调用过程自动创建堆栈帧。它为局部变量保留堆栈空间，把 EBP 入栈。具体来说，它执行三个操作：
// 把 EBP 入栈 (push ebp)
// 把 EBP 设置为堆栈帧的基址 (mov ebp, esp)
// 为局部变量保留空间 (sub esp, numbytes)
// ENTER 有两个操作数：第一个是常数，定义为局部变量保存的堆栈空间字节数；第二个定义了过程的词法嵌套级。
// ENTER numbytes, nestinglevel
// 这两个操作数都是立即数。Numbytes 总是向上舍入为 4 的倍数，以便 ESP 对齐双字边界。Nestinglevel 确定了从主调过程堆栈帧复制到当前帧的堆栈帧指针的个数。在示例程序中，nestinglevel 总是为 0。
#define ASM_LEAVE   "leave"
// LEAVE 指令
// LEAVE 指令结束一个过程的堆栈帧。它反转了之前的 ENTER 指令操作：恢复了过程被调用时 ESP 和 EBP 的值

// Jump instructor 跳转指令，加条件判断等等等等
#define ASM_JUMP    "jmp"
#define ASM_JE      "je"
#define ASM_JG      "jg"
#define ASM_JGE     "jge"
#define ASM_JL      "jl"
#define ASM_JLE     "jle"
#define ASM_JNE     "jne"

// 32-bit asm register 32位asm寄存器
// 2个重要的指针寄存器(ESP和EBP)
#define ASM_EAX     "eax"
#define ASM_EBX     "ebx"
#define ASM_ECX     "ecx"
#define ASM_EDX     "edx"
#define ASM_EBP     "ebp"
#define ASM_ESP     "esp"
// 那么ESP和EBP指的分别是什么呢？

// （1）ESP：栈指针寄存器(extended stack pointer)，
// 其内存放着一个指针，该指针永远指向系统栈最上面一个栈帧的栈顶。
// （2）EBP：基址指针寄存器(extended base pointer)，
// 其内存放着一个指针，该指针永远指向系统栈最上面一个栈帧的底部。

// 在这里要注意由于在intel系统中栈是向下生长的(栈越扩大其值越小,堆恰好相反)

// pop ebp;出栈 栈扩大4byte 因为ebp为32位

// push ebp;出栈，栈减少4byte


// Date type 双字节字长？
#define DOUBLE_WORD "dword"

// Other characters 
#define ASM_LB      "["
#define ASM_RB      "]"
#define ASM_COMMA   ","
#define ASM_COLON   ":"

#endif
