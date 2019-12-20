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
%option yylineno
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
"int"                             { yylval.str=strdup(yytext); return(TYPE); }
"void"                            { yylval.str=strdup(yytext); return(TYPE);}
"main"                            { yylval.str=strdup(yytext); return(ID);}
"return"                          { return(RETURN); }
"for"                             { return(FOR);}
"while"                           { return(WHILE);}
"if"                              { return(IF); }
"else"                            { return(ELSE);}
"struct"                          { return(STRUCT);}
";"                               { return(SEMI); }
","                               { return(COMMA); }
"="                               { return(ASSIGNOP); }
(>=)|(<=)|(==)|(!=)|<|>           { yylval.str=strdup(yytext); return(RELOP); }
"+"                               { return(PLUS); }
"-"                               { return(MINUS); }
"*"                               { return(STAR); }
"/"                               { return(DIV); }
"%"                               { return(MOD);}
"^"                               { return(POWER);}
"&&"                              { return(AND); }
"&"                               { return(SINGALAND); }
"||"                              { return(OR); }
"!"                               { return(NOT); }
"("                               { return(LP); }
")"                               { return(RP); }
"["                               { return(LB); }
"]"                               { return(RB); }
"{"                               { return(LC); }
"}"                               { return(RC); }
"."                               { return(GETMEMBER); }
{L}({D}|{L})*                     { yylval.str=strdup(yytext); return(ID); }
{D}{L}({D}|{L})*                  { return (ERRID); }
[ \t\v\f\r\n]                     { }
(([1-9]|-){D}*)|0                     { yylval.str=strdup(yytext); return(INT);}
%%
int yywrap()
{return 1;}
