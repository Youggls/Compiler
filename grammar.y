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
%token <str> INT
%token <str> TYPE
%token <str> ID
%token FOR
%nonassoc SEMI COMMA
%nonassoc RETURN IF ELSE WHILE
%type <str> VarDec Specifier
%type <ast> ExtDefList ExtDef
%type <ast> Exp CompSt
%type <ast> StmtList Stmt Dec DecList Def
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
        $3->printTree();
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
        $$ = strdup($1);
    }
;

/* Declarators */
VarDec: ID {
        $$ = strdup($1);
    }
    | VarDec LB INT RB {
        $$ = NULL;
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
CompSt:
    LC StmtList RC {
        AbstractASTNode* compStmt = new StmtASTNode(StmtType::compStmt);
        compStmt->addChildNode($2);
        $$ = compStmt;
    }
    | error RC { yyerrok; }
    ;
StmtList: 
	StmtList Stmt {
        if ($1 == NULL) $$ = $2;
        else {
            $1->getLastPeerNode()->addPeerNode($2);
        }
    }
    | {
        $$ = NULL;
    }
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
        AbstractASTNode* temp = new StmtASTNode(StmtType::expStmt);
        temp->addChildNode($1);
        $$ = temp;
    }
    | Def {
        AbstractASTNode* temp = new StmtASTNode(StmtType::defStmt);
        temp->addChildNode($1);
        $$ = temp;
    }
    | CompSt {
        AbstractASTNode* temp = new StmtASTNode(StmtType::compStmt);
        temp->addChildNode($1);
        $$ = temp;
    }
    | RETURN Exp SEMI {
        $$ = NULL;
    }
    | IF LP Exp RP Stmt {
        $$ = NULL;
    }
    | IF LP Exp RP Stmt ELSE Stmt %prec LOWER_THAN_ELSE {
        $$ = NULL;
    }
    | WHILE LP Exp RP Stmt {
        $$ = NULL;
    }
    | FOR LP FORLIST RP Stmt {
        $$ = NULL;
    }
    | error SEMI { yyerrok; }
    ;


/* Local Definitions */
Def: Specifier DecList SEMI {
        DefVarASTNode* temp = (DefVarASTNode*)$2;
        temp->setAllType($1);
        $$ = temp;
    }
    | error SEMI { yyerrok; }
    ;
DecList: Dec {
        $$ = $1;
    }
    | Dec COMMA DecList {
        $1->getLastPeerNode()->addPeerNode($3);
        $$ = $1;
    }
    ;
Dec: VarDec {
        AbstractASTNode* temp = new DefVarASTNode($1);
        $$ = temp;
    }
    | VarDec ASSIGNOP Exp {
        AbstractASTNode* temp = new DefVarASTNode($1, $3);
        $$ = temp;
    }
;

/* Expressions */
Exp:
    Exp ASSIGNOP Exp {
        AbstractASTNode* temp = new OperatorASTNode((char*)"=", opType::Assignop);
        temp->addChildNode($1);
        $1->addPeerNode($3);
        $$ = temp;
    }
    | Exp AND Exp {
        $$ = NULL;
    }
    | Exp OR Exp {
        $$ = NULL;
    }
    | Exp RELOP Exp {
        $$ = NULL;
    }
    | Exp PLUS Exp {
        $$ = NULL;
    }
    | Exp MINUS Exp {
        $$ = NULL;
    }
    | Exp STAR Exp {
        $$ = NULL;
    }
    | Exp DIV Exp {
        $$ = NULL;
    }
    | LP Exp RP {
        $$ = NULL;
    }
    | MINUS Exp {
        $$ = NULL;
    }
    | NOT Exp {
        $$ = NULL;
    }
    | ID LP Args RP {
        $$ = NULL;
    }
    | ID LP RP {
        $$ = NULL;
    }
    | Exp LB Exp RB {
        $$ = NULL;
    }
    | ID {
        AbstractASTNode* temp = new VarASTNode($1);
        $$ = temp;
    }
    | INT {
        AbstractASTNode* temp = new LiteralASTNode($1);
        $$ = temp;
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
