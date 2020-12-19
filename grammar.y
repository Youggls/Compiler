/* 第一部分：说明部分 */
/*
  YACC源程序说明部分定义语法规则中要用的终结符号，
  语义动作中使用的数据类型、变量、语义值的联合类型以及语法规则中运算符的优先级等。说明部分可以是空的。
  说明部分通常包含两部分内容：

  C语言代码部分
  Yacc说明部分
  
  这两部分可以拆分成下面四个小部分：
  头文件表
  宏定义
  数据类型定义
  全局变量定义
*/
%{
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include "../common/trees.h"
#include "../common/util/InterMediate.h"
#include "../common/util/AsmGenerator.h"
class AbstractASTNode; // 数据类型定义：定义语义动作使用到的数据类型
extern char *yytext; // 外部变量和全局变量定义
extern int yylex();
extern int column;
extern FILE * yyin;
extern int yylineno;
AbstractASTNode* root;
StructTable *structTable;
void yyerror(const char *str);
%}

/* 第二部分
文法开始符号定义
语义值类型定义
终结符定义
非终结符定义
优先级和结合性定义
*/

/* 语法开始符号定义
上下文无关文法的开始符号是一个特殊的非终结符，所有的推导都从这个非终结符开始
在yacc中，语法开始符定义语句是
% start 非终结符……
如果没有上面的说明，yacc自动将语法规则部分中第一条语法规则左部的非终结符作为语法开始符
*/

/* 
例:
 % union{
int ival
double dval
INTERVAL vval;
}
引用时候的方式
%token <ival> DREG VREG
%token <dval> CONST
%type  <dval>dexp
%type  <vval>vexp
以%token开始的行定义的是终结符的类型
以%type开始的行定义是非终结符的类型
*/

%union {
	AbstractASTNode* ast;
    char* str;
}
%locations
%define parse.error verbose

/* 
优先级和结合性定义
%left 左结合
%right 右结合
%nonassoc 无结合性
%prec <终结符> 强制定义优先级
 */
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
%nonassoc SEMI COMMA
%nonassoc RETURN IF ELSE WHILE STRUCT GETMEMBER


/* 
在yacc源程序语法规则部分出现的所有终结符（正文字符“+”，“-”等除外）等必须用%token定义，定义形式：
单一数据类型：
%token 终结符1 终结符2
多数据类型：
%token <类型> 终结符1 终结符2 …
 */
%token ERRID
%token <str> INT
%token <str> TYPE
%token <str> ID
%token FOR
%token LC RC

/* 非终结符 */
%type <ast> VarDec 
%type <str> Specifier
%type <ast> ExtDefList ExtDef ExtDecList
%type <ast> Exp CompSt
%type <ast> StmtList Stmt Dec DecList Def
%type <ast> Args ParamDec VarList FunDec DecFor
%type <ast> StructSpecifier StructDecList StructDec
%%

/* 
语法规则部分是整个YACC源程序的主体，它是由一组产生式及相应的语义动作组成。
规则部分包括修改的BNF格式的文法规则，
以及将在识别出识别出相关的文法规则时被执行的C代码中的动作
（即根据LALR（1）分析算法，在归约中使用）。
文法规则中使用的元符号惯例如下：
通常，竖线|被用作替换（也可以分别写出替换项），
而用来分隔文法规则的左右两边的箭头符号-〉
在YACC中用冒号表示，最后，必须用分号来结束每个文法规则。

 */


 /* 
 对文法中的产生式
在YACC程序中可表示成
A：  α1  |  {语义动作1}
    | α2 {语义动作2}  
    |
    | αm {语义动作m}   
;
  */

/* 没有默认指定%start，默认使用program为文法开始符号 */
/* 
  YACC中的动作是由在每个文法规则中将其写作真正的C代码（在大括号中）来实现的。
  在书写动作时，可以使用YACC伪变量。当识别一个文法规则时，
  规则中的每个符号都拥有一个值，除非它被参数改变了。
  这些值由YACC保存在一个与分析栈保持平行的值栈（value stack）中，
  每个在栈中的符号值都可以使用以$开始的伪变量来引用。
  $$代表刚才被识别出来的非终结符的值，也就是文法规则左边的符号。
  伪变量$1、$2、$3等代表了文法规则右边的每个连续的符号。
*/
Program: ExtDefList {
        root = new RootASTNode();
        root->addChildNode($1);
    }
    ;
/* 
  例：文法规则和动作：
  exp	:	exp '+' term	{ $$ = $1 + $3; }
  含义是：当识别规则exp->exp+term时，
  左边exp值为右边的exp的值与右边的term的值之和，
  其中$$代表规则左部符号exp的值，
  $1代表规则右部第一个符号exp的值
  $3表示规则右部第三个符号term的值。
*/
ExtDefList: //定义列表，比如int a,b,c....
    ExtDef {
        $$ = $1;
    }
    | ExtDefList ExtDef {
        if ($1 == NULL) {
            $$ = $2;
        } else {
            if ($2 != NULL) {
                $1->getLastPeerNode()->addPeerNode($2);
            }
            $$ = $1;
        }
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
    | StructSpecifier SEMI {
        $$ = $1;
    }
    | error SEMI { yyerrok; $$ = NULL;}
    ;
ExtDecList: VarDec {
        $$ = $1;
    }
    | ExtDecList COMMA VarDec {
        $1->getLastPeerNode()->addPeerNode($3);
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

StructSpecifier: STRUCT ID LC StructDecList RC {
        if (structTable == NULL) {
            structTable = new StructTable();
        }
        structSymbol* sSymble = new structSymbol($2, $4);
        structTable->addStruct(sSymble);
        $$ = NULL;
    }
    ;

StructDecList: StructDec {
        $$ = $1;
    }
    | StructDecList StructDec {
        $1->getLastPeerNode()->addPeerNode($2);
        $$ = $1;
    }
    ;

StructDec: Specifier ID SEMI {
        DefVarASTNode* var = new DefVarASTNode($2);
        var->setAllType($1);
        $$ = var;
    }
    ;

/* Declarators */
VarDec: ID {
        $$ = new DefVarASTNode($1);
    }
    | ID LB INT RB {
        DefVarASTNode* var = new DefVarASTNode($1);
        var->setAllType((char*)("array"));
        var->setArrayLength($3);
        $$ = var;
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
ParamDec: Specifier ID {
        DefVarASTNode* var = new DefVarASTNode($2);
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
    | STRUCT ID ID SEMI {
        AbstractASTNode* temp = new StmtASTNode(StmtType::defStmt);
        AbstractASTNode* structDec = new DefVarASTNode($2, $3);
        temp->addChildNode(structDec);
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
        $$ = $1;
    }
    | VarDec ASSIGNOP Exp {
        $1->addChildNode($3);
        $$ = $1;
    }
    ;

/* Expressions */
Exp:
    Exp ASSIGNOP Exp {
        AbstractASTNode* temp = NULL;
        if ($1->getNodeType() == ASTNodeType::op) {
            OperatorASTNode* left = (OperatorASTNode*)$1;
            if (left->getType() == opType::GetArrayValue) {
                temp = new OperatorASTNode((char*)"=", opType::AssignArray);
            } else if (left->getType() == opType::GetMember) {
                temp = new OperatorASTNode((char*)"=", opType::AssignMember);
            } else {
                temp = new OperatorASTNode((char*)"=", opType::Assignop);
            }
        }
        else {
            temp = new OperatorASTNode((char*)"=", opType::Assignop);
        }
        temp->addChildNode($1);
        $1->addPeerNode($3);
        $3->setParent(temp);
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
    | ID LB Exp RB {
        AbstractASTNode* op = new OperatorASTNode((char*)"[]", opType::GetArrayValue);
        AbstractASTNode* var = new VarASTNode((char*)$1);
        op->addChildNode(var);
        var->addPeerNode($3);
        $$ = op;
    }
    | ID GETMEMBER ID {
        AbstractASTNode* op = new OperatorASTNode((char*)".", opType::GetMember);
        VarASTNode* var1 = new VarASTNode($1);
        VarASTNode* var2 = new VarASTNode($3);
        op->addChildNode(var1);
        var1->addPeerNode(var2);
        $$ = op;
    }
    | INT {
        $$ = new LiteralASTNode($1);
    }
    | STAR ID {
        AbstractASTNode* op = new OperatorASTNode((char*)"*", opType::GetValue);
        AbstractASTNode* var = new VarASTNode((char*)$2);
        op->addChildNode(var);
        $$ = op;
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

/* 
YACC源程序的程序部分包括：
主程序 main()
错误信息执行程序 yyerror(s)
词法分析程序yylex(),可以与LEX进行整合
用户在语义动作中用到的子程序
YACC约定：
传递词法分析程序token属性值的全程变量名：yylval
生成的语法分析程序名为：yyparse();
 */

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: At line %d. %s\n", yylineno, s);
	exit(1);
}

std::string replaceExtName(char* fileName) {
    int dotIndex = 0;
    int nameLength = strlen(fileName);
    for (int i = nameLength - 1; i >= 0; i--) {
        if (fileName[i] == '.') {
            dotIndex = i;
            break;
        }
    }
    char* buf = new char[dotIndex];
    strncpy(buf, fileName, dotIndex);
    std::string rev(buf);
    rev += ".asm";
    return rev;
}

int main(int argc,char* argv[])
{
    InterMediate* im;
    bool flag_print_ast = false;
    bool flag_print_ir = false;
    bool flag_print_asm = false;
    char* filename = NULL;
    if (argc == 1) {
        printf("Error! Please input file name!\n");
        printf("Usage: parser [-t] [-i] [-a] [-d]\n");
        printf("  -t  print the abstract syntax tree (AST)\n");
        printf("  -i  print IR code\n");
        printf("  -a  print asm code\n");
        printf("  -d  debug mode print all\n");
        return -1;
    } else if (argc >= 2) {
        for (int i=1; i<argc; i++) {
            if (*argv[i] != '-') {
                if (filename == NULL) filename = argv[i];
            }
            else if (strcmp(argv[i], "-t") == 0) flag_print_ast = true;
            else if (strcmp(argv[i], "-i") == 0) flag_print_ir = true;
            else if (strcmp(argv[i], "-a") == 0) flag_print_asm = true;
            else if (strcmp(argv[i], "-d") == 0) {
                flag_print_ast = true;
                flag_print_ir = true;
                flag_print_asm = true;
            }
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
    }
    im = new InterMediate((RootASTNode *)root, structTable);
    im->Generate(im->getRoot(), im->getTable());
    if (flag_print_ir) {
        im->printQuads();
    }
    AsmGenerator* asmgenerator = new AsmGenerator(im->getQuads(), im->getTempVars(), im->getTable(), im->getFuncTable());
    asmgenerator->generate();
    if (flag_print_asm) {
        std::cout << asmgenerator->getAsmCode();
    }

    std::string outFileName = replaceExtName(filename);
    std::ofstream outasm(outFileName);
    outasm << asmgenerator->getAsmCode();
    return 0;
}
