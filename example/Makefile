CC = gcc
NASM = nasm
PROGRAM = ./parser
main:
	$(PROGRAM) test/test.txt -t
	$(NASM) -f elf out.asm -o out.o
	$(CC) -o out out.o io/asm_io.o -m32
