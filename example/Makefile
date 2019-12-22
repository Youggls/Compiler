CC = gcc
NASM = nasm
PROGRAM = ./parser

all: swap loop fibo struct array

swap:
	$(PROGRAM) test/swap.c
	$(NASM) -f elf test/swap.asm -o swap.o
	$(CC) -o swap swap.o io/asm_io.o -m32

loop:
	$(PROGRAM) test/basic_loop.c
	$(NASM) -f elf test/basic_loop.asm -o basic_loop.o
	$(CC) -o basic_loop basic_loop.o io/asm_io.o -m32

fibo:
	$(PROGRAM) test/fibo.c
	$(NASM) -f elf test/fibo.asm -o fibo.o
	$(CC) -o fibo fibo.o io/asm_io.o -m32

struct:
	$(PROGRAM) test/struct.c
	$(NASM) -f elf test/struct.asm -o struct.o
	$(CC) -o struct struct.o io/asm_io.o -m32

array:
	$(PROGRAM) test/array.c
	$(NASM) -f elf test/array.asm -o array.o
	$(CC) -o struct array.o io/asm_io.o -m32

larra:
	$(PROGRAM) test/larra.c
	$(NASM) -f elf test/larra.asm -o larra.o
	$(CC) -o larra larra.o io/asm_io.o -m32
