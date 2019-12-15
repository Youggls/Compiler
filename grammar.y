%{
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "../common/trees.h"
#include "../common/util/InterMediate.h"
class AbstractASTNode;
extern char *yytext;
extern int yylex();
extern int column;
extern FILE * yyin;
extern int yylineno;
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
%left <ast> SINGALAND
%left <str> RELOP
%left <ast> MINUS PLUS
%left <ast> STAR DIV MOD
%left <ast> POWER
%right <ast> NOT
%left LP RP LB RB
%nonassoc LOWER_THAN_ELSE
%token ERRID
%token <str> INT
%token <str> TYPE
%token <str> ID
%token FOR
%nonassoc SEMI COMMA
%nonassoc RETURN IF ELSE WHILE
%token LC RC
%type <str> VarDec Specifier
%type <ast> ExtDefList ExtDef ExtDecList
%type <ast> Exp CompSt
%type <ast> StmtList Stmt Dec DecList Def
%type <ast> Args ParamDec VarList FunDec DecFor
%%

Program: ExtDefList {
        root = new RootASTNode();
        root->addChildNode($1);
    }
    ;
ExtDefList:
    ExtDef {
        $$ = $1;
    }
    | ExtDefList ExtDef {
        $1->getLastPeerNode()->addPeerNode($2);
        $$ = $1;
    }
    ;
ExtDef: Specifier ExtDecList SEMI {
        DefVarASTNode* defVar = (DefVarASTNode*)$2;
        defVar->setAllType($1);
        $$ = defVar;
    }
    | Specifier SEMI {
    }
    | Specifier FunDec CompSt {
        DefFunASTNode* temp = (DefFunASTNode*)$2;
        temp->setFunBody($3);
        temp->setRevType($1);
        $$ = temp;
    }
    | Specifier FunDec SEMI {
    }
    | error SEMI { yyerrok; $$ = NULL;}
    ;
ExtDecList: VarDec {
        $$ = new DefVarASTNode($1);
    }
    | ExtDecList COMMA VarDec {
        DefVarASTNode* temp = new DefVarASTNode($3);
        $1->getLastPeerNode()->addPeerNode(temp);
        $$ = $1;
    }
    ;

/* Specifiers */
Specifier: TYPE {
        $$ = strdup($1);
    }
    | TYPE STAR {
        $$ = (char*)("integer pointer");
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
        $$ = new DefFunASTNode($1, $3, NULL);
    }
    | ID LP RP {
        $$ = new DefFunASTNode($1, NULL, NULL);
    }
    ;
VarList: VarList COMMA ParamDec {
        $1->getLastPeerNode()->addPeerNode($3);
        $$ = $1;
    }
    | ParamDec {
        $$ = $1;
    }
    ;
ParamDec: Specifier VarDec {
        DefVarASTNode* var = new DefVarASTNode($2, NULL);
        var->setAllType($1);
        $$ = var;
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

DecFor:
    Def {
        $$ = $1;
    }
    | Exp {
        $$ = $1;
    }
    ;

Stmt: Exp SEMI {
        AbstractASTNode* temp = new StmtASTNode(StmtType::expStmt);
        temp->addChildNode($1);
        $$ = temp;
    }
    | Def SEMI {
        AbstractASTNode* temp = new StmtASTNode(StmtType::defStmt);
        temp->addChildNode($1);
        $$ = temp;
    }
    | CompSt {
        $$ = $1;
    }
    | RETURN Exp SEMI {
        AbstractASTNode* temp = new StmtASTNode(StmtType::returnStmt);
        temp->addChildNode($2);
        $$ = temp;
    }
    | RETURN SEMI {
        $$ = new StmtASTNode(StmtType::returnStmt);
    }
    | IF LP Exp RP Stmt{
        $$ = new SelectASTNode((char*)"", SelectType::_if, $5, $3);
    }
    | IF LP Exp RP Stmt ELSE Stmt %prec LOWER_THAN_ELSE{
        $$ = new SelectASTNode((char*)"", SelectType::_if, $5, $3, $7);
    }
    | WHILE LP Exp RP Stmt {
        $$ = new LoopASTNode((char*)"", LoopType::_while, $5, $3);
    }
    | FOR LP SEMI SEMI RP Stmt {
        $$ = new LoopASTNode((char*)"", LoopType::_for, $6, NULL, NULL, NULL);
    }
    | FOR LP DecFor SEMI SEMI RP Stmt {
        $$ = new LoopASTNode((char*)"", LoopType::_for, $7, $3, NULL, NULL);
    }
    | FOR LP SEMI Exp SEMI RP Stmt {
        $$ = new LoopASTNode((char*)"", LoopType::_for, $7, NULL, $4, NULL);
    }
    | FOR LP SEMI SEMI Exp RP Stmt {
        $$ = new LoopASTNode((char*)"", LoopType::_for, $7, NULL, NULL, $5);
    }
    | FOR LP DecFor SEMI Exp SEMI Exp RP Stmt {
        $$ = new LoopASTNode((char*)"", LoopType::_for, $9, $3, $5, $7);
    }
    | FOR LP DecFor SEMI Exp SEMI RP Stmt {
        $$ = new LoopASTNode((char*)"", LoopType::_for, $8, $3, $5, NULL);
    }
    | FOR LP DecFor SEMI SEMI Exp RP Stmt {
        $$ = new LoopASTNode((char*)"", LoopType::_for, $8, $3, NULL, $6);
    }
    | FOR LP SEMI Exp SEMI Exp RP Stmt {
        $$ = new LoopASTNode((char*)"", LoopType::_for, $8, NULL, $4, $6);
    }
    | error SEMI { yyerrok; }
    ;



/* Local Definitions */
Def: Specifier DecList {
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
        AbstractASTNode* temp = new OperatorASTNode((char*)"&&", opType::And);
        temp->addChildNode($1);
        $1->addPeerNode($3);
        $$ = temp;
    }
    | Exp OR Exp {
        AbstractASTNode* temp = new OperatorASTNode((char*)"||", opType::Or);
        temp->addChildNode($1);
        $1->addPeerNode($3);
        $$ = temp;
    }
    | Exp RELOP Exp {
        AbstractASTNode* temp = new OperatorASTNode($2, opType::Relop);
        temp->addChildNode($1);
        $1->addPeerNode($3);
        $$ = temp;
    }
    | Exp PLUS Exp {
        AbstractASTNode* temp = new OperatorASTNode((char*)"+", opType::Plus);
        temp->addChildNode($1);
        $1->addPeerNode($3);
        $$ = temp;
    }
    | Exp MINUS Exp {
        AbstractASTNode* temp = new OperatorASTNode((char*)"-", opType::Minus);
        temp->addChildNode($1);
        $1->addPeerNode($3);
        $$ = temp;
    }
    | Exp STAR Exp {
        AbstractASTNode* temp = new OperatorASTNode((char*)"*", opType::Times);
        temp->addChildNode($1);
        $1->addPeerNode($3);
        $$ = temp;
    }
    | Exp DIV Exp {
        AbstractASTNode* temp = new OperatorASTNode((char*)"/", opType::Div);
        temp->addChildNode($1);
        $1->addPeerNode($3);
        $$ = temp;
    }
    | Exp MOD Exp {
        AbstractASTNode* temp = new OperatorASTNode((char*)"%", opType::Mod);
        temp->addChildNode($1);
        $1->addPeerNode($3);
        $$ = temp;
    }
    | Exp POWER Exp {
        AbstractASTNode* temp = new OperatorASTNode((char*)"^", opType::Power);
        temp->addChildNode($1);
        $1->addPeerNode($3);
        $$ = temp;
    }
    | LP Exp RP {
        $$ = $2;
    }
    | MINUS Exp {
        AbstractASTNode* temp = new OperatorASTNode((char*)"-", opType::Negative);
        temp->addChildNode($2);
        $$ = temp;
    }
    | NOT Exp {
        AbstractASTNode* temp = new OperatorASTNode((char*)"!", opType::Not);
        temp->addChildNode($2);
        $$ = temp;
    }
    | SINGALAND ID {
        AbstractASTNode* op = new OperatorASTNode((char*)"&", opType::SingalAnd);
        AbstractASTNode* var = new VarASTNode((char*)$2);
        op->addChildNode(var);
        $$ = op;
    }
    | ID LP Args RP {
        $$ = new CallFunASTNode($1, $3);
    }
    | ID LP RP {
        $$ = new CallFunASTNode($1, NULL);
    }
    | Exp LB Exp RB {
        $$ = NULL;
    }
    | ID {
        $$ = new VarASTNode($1);
    }
    | INT {
        $$ = new LiteralASTNode($1);
    }
    | error RP { yyerrok; }
    ;
Args: Args COMMA Exp {
        $1->getLastPeerNode()->addPeerNode($3);
        $$ = $1;
    }
    | Exp {
        $$ = $1;
    }
    ;

%%

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: At line %d. %s\n", yylineno, s);
	exit(1);
}

int main(int argc,char* argv[])
{
    InterMediate* im;
    bool flag_print_ast = false;
    char* filename = NULL;
    if (argc == 1) {
        printf("Error! Please input file name!\n");
        printf("Usage: parser [-t] [-v] [-B] [-i] source [out]\n");
        printf("  -t  print the abstract syntax tree (AST)\n");
        printf("  -v  verbose mode\n");
        printf("  -B  disable basic block optimizing\n");
        printf("  -i  generate IR code instead of assemble code\n");
        return -1;
    } else if (argc >= 2) {
        for (int i=1; i<argc; i++) {
            if (*argv[i] != '-') {
                if (filename == NULL) filename = argv[i];
            }
            else if (strcmp(argv[i], "-t") == 0) flag_print_ast = true;
            else printf("Invalid parameter \"%s\"\n", argv[i]);
        }
    }
    FILE* file = fopen(filename, "r");
    yyin = file;
    do {
		yyparse();
	} while(!feof(yyin));
    if (flag_print_ast) {
        root->printTree();
        root->printTree();
        im = new InterMediate((RootASTNode *)root);
        im->Generate(im->getRoot(), im->getTable());
    }
    return 0;
}
