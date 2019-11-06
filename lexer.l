%x COMMENT
%{
#include "grammar.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/trees.h"

extern char *yytext;
extern int column;
extern FILE * yyin;
extern YYSTYPE yylval;
void yyerror(const char *str);
%}

D   [0-9]
L   [a-zA-Z_]
E   [Ee][+-]?{D}+
delim [ \t\n]
ws    {delim}+

%%
"/*"           { BEGIN(COMMENT) ; }
<COMMENT>"*/"  { BEGIN(INITIAL); }
<COMMENT>{ws}   {printf("inside commenet ws\n");}
<COMMENT>([^*]|\en)+|.
<COMMENT><<EOF>>    {printf("Unterminated comment\n"); return 0;}
 /* C++ comment, a common extension */
"//".*\n
"int"                             { return(TYPE); }
"main"                            { return(ID);}
"return"                          { return(RETURN); }
"for"                             { return(FOR);}
"while"                           { return(WHILE);}

"if"                              { return(IF); }
";"                               { return(SEMI); }
","                               { return(COMMA); }
"="                               { return(ASSIGNOP); }
(>=)|(<=)|(==)|(!=)|<|>           { return(RELOP); }
"+"                               { return(PLUS); }
"-"                               { return(MINUS); }
"*"                               { return(STAR); }
"/"                               { return(DIV); }
"&&"                              { return(AND); }
"||"                              { return(OR); }
"!"                               { return(NOT); }
"("                               { return(LP); }
")"                               { return(RP); }
"["                               { return(LB); }
"]"                               { return(RB); }
"{"                               { return(LC); }
"}"                               { return(RC); }
{L}({D}|{L})*                     { return(ID); }
{D}{L}({D}|{L})*                  { return (ERRID); }
[ \t\v\f\r\n]                     { }
([1-9]{D}*)|0                     { return(INT);}
%%
int yywrap()
{return 1;}
