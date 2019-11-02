win_bison.exe --output="./win/grammar.tab.cpp" --defines="./win/grammar.tab.h"  "grammar.y"
win_flex.exe --outfile="./win/lexer.flex.cpp" --wincompat  "lexer.l"
