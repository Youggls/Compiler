# 中间代码生成  
中间代码生成主要通过遍历语法分析生成的语法树实现，深度优先遍历语法树，针对不同类型的树节点采取不同类型的操作，生成中间代码（四元式），存放在`quads`中。  
## 相关类  
### Quad  
使用Quad类保存记录一条四元式，并且添加了对应的工具函数，如：`backpatch`进行回填操作，填入跳转目标指令

### InterMediate  
`InterMediate`为中间代码生成的方法类，其中保存了记录中间代码四元式的列表`quads`，及其他IR生成过程中需要用到的数据结构。

#### 相关函数  
`void backpatch(std::list<int> *backList, int target)`：实现回填操作，接受参数需要回填的四元式序号，及回填目标序号。

`inline AbstractASTNode *getRoot()   { return this->root; }`：获取根节点。  

`inline SymbolTable *getTable()    { return this->rootTable; }`：获取根符号表。  

`InterMediate(RootASTNode *rootNode);`：构造函数，构造IR生成类，主要工作为初始化中间代码生成过程中用到的数据结构。 

`void Generate(AbstractASTNode *node, SymbolTable *symbolTable);`：生成**中间代码**主要函数，输入抽象语法树的根节点，生成对应的中间代码。

`SymbolTable *GenerateStmt(StmtASTNode *node SymbolTable *symbolTable);`：
针对节点类型为**语句类型**（`StmtASTNode`)的节点，生成对应四元式。  

`symbol *GenerateOp(OperatorASTNode *node SymbolTable *symbolTable);`：针对节点类型为**操作符类型**(`OperatorASTNode`)的节点，生成对应的四元式   

`Quad *CaculateOp(OpCode op, AbstractASTNode *arg1Node, AbstractASTNode *arg2Node, symbol *result, SymbolTable *symbalTable);`：针对**运算操作符**（+、-、*、/、%、^），生成其对应的四元式

`void RelopOp(Quad *trueQuad, Quad *falseQuad, OpCode op, AbstractASTNode *arg1Node, AbstractASTNode *arg2Node, SymbolTable *symbolTable);`：针对**布尔表达式操作符**(>、<、==、!=、=>、<=)，生成对应的跳转语句。

## 建议阅读顺序：
Quad(四元式) -> Intermediate(中间代码) -> AsmCode(生成汇编) -> AsmGenerator