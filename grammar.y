%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern char *yytext;
extern int yylex();
extern int column;
extern FILE * yyin;
struct tree* root;
void yyerror(const char *str);
%}

%union {
	struct tree* ast;
    char* str;
}
%locations
%define parse.error verbose

%right ASSIGNOP

%left OR
%left AND
%left RELOP
%left MINUS PLUS
%left STAR DIV
%right NOT
%left LP RP LB RB
%nonassoc LOWER_THAN_ELSE

%token LC RC
%token INT
%token FLOAT
%token TYPE
%token ID
%nonassoc SEMI COMMA
%nonassoc STRUCT RETURN IF ELSE WHILE

%%

Program: ExtDefList {
    printf("Root\n");
    }
    ;
ExtDefList:
    ExtDef {
    }
    | ExtDef ExtDefList {  }
    ;
ExtDef: Specifier ExtDecList SEMI {
    }
    | Specifier SEMI {
    }
    | Specifier FunDec CompSt {
        printf("Function!\n");
    }
    | Specifier FunDec SEMI {
    }
    | error SEMI { yyerrok; }
    ;
ExtDecList: VarDec {
    }
    | VarDec COMMA ExtDecList {
    }
    ;

/* Specifiers */
Specifier: TYPE {
    }
;

/* Declarators */
VarDec: ID {
    }
    | VarDec LB INT RB {
    }
    ;
FunDec: ID LP VarList RP {
    }
    | ID LP RP {
    }
    ;
VarList: ParamDec COMMA VarList {
    }
    | ParamDec {
    }
    ;
ParamDec: Specifier VarDec {
    }
    | Specifier {
    }
    ;

/* Statements */
CompSt: LC DefList StmtList RC {
    }
    | error RC { yyerrok; }
    ;
StmtList: Stmt StmtList {
    }
    | /* empty */ {  }
    ;
Stmt: Exp SEMI {
    }
    | CompSt {
    }
    | RETURN Exp SEMI {
    }
    | IF LP Exp RP Stmt {
    }
    | IF LP Exp RP Stmt ELSE Stmt %prec LOWER_THAN_ELSE {
    }
    | WHILE LP Exp RP Stmt {
    }
    | error SEMI { yyerrok; }
    ;

/* Local Definitions */
DefList: Def DefList {
    }
    | /* empty */ {  }
    ;
Def: Specifier DecList SEMI {
    }
    | error SEMI { yyerrok; }
    ;
DecList: Dec {
    }
    | Dec COMMA DecList {
    }
    ;
Dec: VarDec {
    }
    | VarDec ASSIGNOP Exp {
    }
    ;

/* Expressions */
Exp: Exp ASSIGNOP Exp {
    }
    | Exp AND Exp {
    }
    | Exp OR Exp {
    }
    | Exp RELOP Exp {
    }
    | Exp PLUS Exp {
    }
    | Exp MINUS Exp {
    }
    | Exp STAR Exp {
    }
    | Exp DIV Exp {
    }
    | LP Exp RP {
    }
    | MINUS Exp {
    }
    | NOT Exp {
    }
    | ID LP Args RP {
    }
    | ID LP RP {
    }
    | Exp LB Exp RB {
    }
    | ID {
    }
    | INT {
    }
    | FLOAT {
    }
    | error RP { yyerrok; }
    ;
Args: Exp COMMA Args {
    }
    | Exp {
    }
    ;

%%

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}

int main(int argc,char* argv[])
{
    FILE* file = fopen(argv[1], "r");
    yyin = file;
    do {
		yyparse();
	} while(!feof(yyin));
    
    return 0;
}
