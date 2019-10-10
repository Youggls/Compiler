%{
#include "stdio.h"
#include <stdlib.h>
#define LT					1
#define	LE					2
#define GT					3
#define	GE					4
#define	EQ					5
#define NE					6
#define LP          7
#define RP          8
#define LBRACE      9
#define RBRACE      10
#define WHILE				18
#define	DO					19
#define ID          20
#define NUMBER      21
#define RELOP       22
#define NEWLINE     23
#define ERRORCHAR   24
#define INT         25
#define MAIN        26
#define VOID        27
#define DOUBLE      28
#define SEMICOLON   29
#define IF          30
#define ELSE        31
#define ASSIGN      32
#define LNOT        33

int yylval;
int installNum ();
char* lookup(int, char*);
struct Identifer {
	char *id_name;
	int id_type;
};
#define NHASH 9997
struct Identifer idtab[NHASH];

%}


delim [ \t\n]
ws    {delim}+
letter [a-zA-Z_]
digit [0-9]
ID    {letter}({letter}|{digit})*
number {digit}+(\.{digit}+)?(E[+-]?{digit}+)?
 

%%
while           {return (WHILE);}
do              {return (DO); }
double          {return (DOUBLE);}
int             {return (INT);}
void            {return (VOID);}
if              {return (IF);}
else            {return (ELSE);}
main            {return (MAIN);}
"("             {return (LP);}
")"             {return (RP);}
"{"             {return (LBRACE);}
"}"             {return (RBRACE);}
!               {return (LNOT);}
{ID}            {yytext = lookup (1, yytext); return ID;}
{number}        {yylval = installNum (); return NUMBER;}
{ws}            {;}

;               {yylval = SEMICOLON; return (SEMICOLON);}
"+"             {return (RELOP);}
"-"             {return (RELOP);}
"*"             {return (RELOP);}
"/"             {return (RELOP);}
"^"             {return (RELOP);}
"%"             {return (RELOP);}
"<"	            {yylval = LT; return (LT);}
"<="	          {yylval = LE; return (LE);}
"=="	          {yylval = EQ; return (EQ);}
"="             {yylval = ASSIGN; return (ASSIGN);}
"<>"	          {yylval = NE; return (NE);}
">"	            {yylval = GT; return (GT);}
">="	          {yylval = GE; return (GE);}
.								{yylval = ERRORCHAR; return ERRORCHAR;}
%%
 

extern void *malloc();

unsigned idhash(char *id)
{
  unsigned int hash = 0;
  unsigned c;

  while(c = *id++) hash = hash*9 ^ c;

  return hash;
}

char *lookup(int type, char* id)
{
  struct Identifer *sp = &idtab[idhash(id)%NHASH];
  int scount = NHASH;

  while(--scount >= 0) {
    if(sp->id_name && !strcmp(sp->id_name, id) && sp->id_type == type) { return sp->id_name; }
    if(sp->id_name && !strcmp(sp->id_name, id) && sp->id_type != type) {
      sp->id_type = type;
      return sp->id_name;
    }
    if(!sp->id_name) {
      sp->id_name = strdup(id);
      sp->id_type = type;
      return sp->id_name;
    }

    if(++sp >= idtab+NHASH) sp = idtab;
  }
  fputs("id table overflow\n", stderr);
  abort();

}


int installNum () {
  int num = atoi(yytext);
  return num;
}
void writeout(int c){
  switch(c){
  	case ERRORCHAR: fprintf(yyout, "(ERRORCHAR, \"%s\") ", yytext);break;
  	case RELOP: fprintf(yyout, "RELOP           %s\n", yytext); break;  	  
    case DO: fprintf(yyout, "(DO, \"%s\") ", yytext);break;
    //case NUMBER: fprintf(yyout, "(NUM, \"%s\") ", yytext);break;
    case INT: fprintf(yyout, "INT             int\n");break;
    case WHILE: fprintf(yyout, "WHILE           while\n");break;
    case MAIN: fprintf(yyout, "MAIN            main\n");break;
    case VOID: fprintf(yyout, "VOID            void\n");break;
    case LP: fprintf(yyout, "LP              (\n");break;
    case RP: fprintf(yyout, "RP              )\n");break;
    case LBRACE: fprintf(yyout, "LBRACE          {\n");break;
    case RBRACE: fprintf(yyout, "RBRACE          }\n");break;
    case IF: fprintf(yyout, "IF              if\n");break;
    case ELSE: fprintf(yyout, "ELSE            else\n");break;
    case ASSIGN: fprintf(yyout, "ASSIGN          =\n");break;
    case NUMBER: fprintf(yyout, "NUMBER          %-16d%-16d\n", yylval, yylval);break;
    case SEMICOLON: fprintf(yyout, "SEMICOLON       ;\n");break;
    case LNOT: fprintf(yyout, "LNOT            !\n");break;
    case ID: fprintf(yyout, "ID              %-16s%-16p\n", yytext, yytext);break;
    default:break;
  }
  return;
}
int main (int argc, char ** argv){
	int c,j=0;
	if (argc>=2){
	  if ((yyin = fopen(argv[1], "r")) == NULL){
	    printf("Can't open file %s\n", argv[1]);
	    return 1;
	  }
	  if (argc>=3){
	    yyout=fopen(argv[2], "w");
	  }
	}
	/* yyin和yyout是lex中定义的输入输出文件指针，它们指明了
	 * lex生成的词法分析器从哪里获得输入和输出到哪里。
	 * 默认：键盘输入，屏幕输出。 
	 */
	while (c = yylex()){
		writeout(c);
		j++;
		if (j%5 == 0) writeout(NEWLINE);
	}
	if(argc>=2){
	  fclose(yyin);
	  if (argc>=3) fclose(yyout);
	}
	return 0;
}
int yywrap()
{
   return(1);
}
