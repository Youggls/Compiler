%{
#include "grammar.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern char *yytext;
extern int column;
extern FILE * yyin;
extern YYSTYPE yylval;
void yyerror(const char *str);
%}

D   [0-9]
L   [a-zA-Z_]
%%
"int" {yylval.str=(char*)"int";return(TYPE);}
"if" {return(IF);}
"else" {return(ELSE);}
"for" {return(FOR);}
";" { return(SEMI); }
"," { return(COMMA); }
"=" { return(ASSIGNOP); }
(>=)|(<=)|(==)|(!=)|<|> { return(RELOP); }
"+" { return(PLUS); }
"-" { return(MINUS); }
"*" { return(STAR); }
"/" { return(DIV); }
"&&" { return(AND); }
"||" { return(OR); }
"!" { return(NOT); }
"(" { return(LP); }
")" { return(RP); }
"[" { return(LB); }
"]" { return(RB); }
"{" { return(LC); }
"}" { return(RC); }
{L}({D}|{L})* {return(ID);}
[ \t\v\f\r\n] { }
%%
int yywrap()
{return 1;}
