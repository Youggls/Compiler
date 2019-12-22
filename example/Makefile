CC = gcc
NASM = nasm
PROGRAM = ./parser

all: swap loop fibo struct array larra

swap: test/swap.c
	$(PROGRAM) test/swap.c
	$(NASM) -f elf test/swap.asm -o swap.o
	$(CC) -o swap swap.o io/asm_io.o -m32

loop: test/basic_loop.c
	$(PROGRAM) test/basic_loop.c
	$(NASM) -f elf test/basic_loop.asm -o basic_loop.o
	$(CC) -o basic_loop basic_loop.o io/asm_io.o -m32

fibo: test/fibo.c
	$(PROGRAM) test/fibo.c
	$(NASM) -f elf test/fibo.asm -o fibo.o
	$(CC) -o fibo fibo.o io/asm_io.o -m32

struct: test/struct.c
	$(PROGRAM) test/struct.c
	$(NASM) -f elf test/struct.asm -o struct.o
	$(CC) -o struct struct.o io/asm_io.o -m32

array: test/array.c
	$(PROGRAM) test/array.c
	$(NASM) -f elf test/array.asm -o array.o
	$(CC) -o array array.o io/asm_io.o -m32

larra: test/larra.c
	$(PROGRAM) test/larra.c
	$(NASM) -f elf test/larra.asm -o larra.o
	$(CC) -o larra larra.o io/asm_io.o -m32
