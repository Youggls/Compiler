parser:	lexer.l grammar.y
	mkdir ./Linux
	bison --output="./Linux/grammar.tab.cpp" --defines="./Linux/grammar.tab.h" grammar.y
	flex --outfile="./Linux/lexer.flex.cpp" lexer.l
	sed -i '1i\#include "../common/trees.h"' ./Linux/grammar.tab.h
	g++ -o $@ ./Linux/grammar.tab.cpp ./Linux/lexer.flex.cpp ./common/symbol.cpp ./common/trees/* -lm
clean:
	rm -f file \
	./Linux/grammar.tab.cpp ./Linux/grammar.tab.h ./Linux/lexer.flex.cpp parser
