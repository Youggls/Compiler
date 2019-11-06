%{
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "../common/trees.h"
class AbstractASTNode;
extern char *yytext;
extern int yylex();
extern int column;
extern FILE * yyin;
AbstractASTNode* root;
void yyerror(const char *str);
%}

%union {
	AbstractASTNode* ast;
    char* str;
}
%locations
%define parse.error verbose

%right ASSIGNOP

%left <ast> OR
%left <ast> AND
%left <ast> RELOP
%left <ast> MINUS PLUS
%left <ast> STAR DIV
%right <ast> NOT
%left LP RP LB RB
%nonassoc LOWER_THAN_ELSE
%token ERRID
%token LC RC
%token <ast> INT
%token <ast> TYPE
%token <ast> ID
%token FOR
%nonassoc SEMI COMMA
%nonassoc RETURN IF ELSE WHILE
%type <ast> ExtDefList ExtDef
%%

Program: ExtDefList {
    }
    ;
ExtDefList:
    ExtDef {
    }
    | ExtDefList ExtDef {
    }
    ;
ExtDef: Specifier ExtDecList SEMI {
    }
    | Specifier SEMI {
    }
    | Specifier FunDec CompSt {
    }
    | Specifier FunDec SEMI {
    }
    | error SEMI { yyerrok; $$ = NULL;}
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
StmtList: 
	StmtList Stmt {}
    | {}
    ;

FORLIST:
    SEMI SEMI {
    }
    | Exp SEMI SEMI {
    }
    | SEMI Exp SEMI {
    }
    | SEMI SEMI Exp {
    }
    | Exp SEMI Exp SEMI Exp {
    }
    | Exp SEMI Exp SEMI {
    }
    | Exp SEMI SEMI Exp {
    }
    | SEMI Exp SEMI Exp {
    }
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
    | FOR LP FORLIST RP Stmt {
    }
    | FOR LP FORLIST RP LC StmtList RC {
    }
    | error SEMI { yyerrok; }
    ;


/* Local Definitions */
DefList:
	Def {
	}
	|
	Def DefList {
    }
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
