PROGRAM = parser
GRAMMARFOLDER = ./Linux/
EXIST = $(shell if [ -d $(GRAMMARFOLDER) ]; then echo "exist"; else echo "notexist"; fi;)
DEPS = $(shell find ./ -name "*.h")
SRC = $(shell find ./ -name "*.cpp")
OBJ = $(SRC:%.cpp=%.o)
CXX = g++
FLEX = flex
BISON = bison
CXXVER = c++11

$(PROGRAM): grammar $(OBJ)
	$(CXX) -o $(PROGRAM) $(OBJ) -std=$(CXXVER)

grammar: lexer.l grammar.y
ifeq ($(EXIST),notexist)
	mkdir $(GRAMMARFOLDER)
endif
	$(BISON) --output="./Linux/grammar.tab.cpp" --defines="./Linux/grammar.tab.h" grammar.y
	$(FLEX) --outfile="./Linux/lexer.flex.cpp" lexer.l
	sed -i "1i\#include \"../common/trees.h\"" ./Linux/grammar.tab.h
	$(CXX) -c ./Linux/grammar.tab.cpp -o ./Linux/grammar.tab.o -std=$(CXXVER)
	$(CXX) -c ./Linux/lexer.flex.cpp -o ./Linux/lexer.flex.o -std=$(CXXVER)

%.o: %.cpp $(DEPS)
	$(CXX) -c $< -o $@ -std=$(CXXVER)

clean:
	rm -rf $(GRAMMARFOLDER) $(OBJ)
