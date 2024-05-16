#ifndef SEMANTIC_H
#define SEMENTIC_H
/*
    命名规则：实体的命名，首字母大写
            指向实体的指针，首字母小写
            实例化的实体，加上my
*/
#include "tree.h"
#include <string.h>
#define HASH_SIZE 0x3fff
struct Type_;

typedef struct Type_* type;
typedef struct FieldList_* fieldlist;/*结构体域链表的定义*/
typedef struct Hash* hash;
typedef struct Stack* stack;
typedef struct Item* item;
typedef struct Table* table;
/*定义符号表的表项*/
/*符号表是由深度、表项值、指向同深度下一个符号指针、同哈希值下一符号指针构成的。
这是基于十字链表和open hashing散列表的Imperative Style的符号表设计。
每次向散列表中插入元素时，总是将新插入的元素放到该槽下挂的链表以及该层所对应的链表的表头。
每次查表时如果定位到某个槽，则按顺序遍历这个槽下挂的链表并返回这个槽中符合条件的第一个变量，（每次查询都从表头、即从深度最深的地方开始查询）
如此一来便可以保证：如果出现了变量既在外层又在内层被定义的情况，符号表能够返回最内层的那个定义
（当然最内层的定义不一定在当前这一层，因此我们还需要符号表能够为每个变量记录一个深度信息）。
每次进入一个语句块，需要为这一层语句块新建一个链表用来串联该层中新定义的变量；
每次离开一个语句块，则需要顺着代表该层语句块的链表将所有本层定义变量全部删除。
*/

typedef struct Item
{
    int depth;//存储深度
    fieldlist field;//表项的值
    item next_symbol;//同深度下一个符号
    item next_hash;//下一个哈希值相同的符号
}Item;
/*定义哈希表*/
/*哈希表是由表项类型的数组实现的*/
typedef struct Hash
{
    item* hash_array;
}Hash;
/*定义存储嵌套哈希表的栈*/
/*栈中存储当前这个哈希表的深度和哈希表信息*/
typedef struct Stack
{
    int depth;//当前深度
    item* stack_array;//使用数组模拟栈
}Stack;
/*定义符号表，包含哈希表和存储嵌套哈希表的栈*/
typedef struct Table
{
    hash hash_table;//全局变量的哈希表
    stack table_stack;//存放局部声明变量的哈希表的栈
    int num;//跟踪未命名的结构体数量，如如struct { int real, image; }这样的结构体
}Table;

/*
    接下来是一些枚举值的定义，包括token种类、基本数据类型、数据种类、错误种类
*/
typedef enum kind_ { BASIC, ARRAY, STRUCTURE,FUNCTION} kind;
typedef enum basic_type_ {INT_,FLOAT_}basic_type;
typedef enum error_type_{
    UNDEF_VAR = 1,//变量在使用时未经定义 Exp -> ID
    UNDEF_FUN,//函数在使用时未经定义     Exp -> ID LP Args RP 带参数类型的函数
    REDEF_VAR,//变量出现重复定义，或变量与前面定义过的结构体名字重复。ExtDecList -> VarDec 单个变量声明 || ParamDec -> Specifier VarDec ||  Dec -> VarDec ||Dec -> VarDec ASSIGNOP Exp
    REDEF_FUN,//函数出现重复定义（即同样的函数名出现了不止一次定义）    FunDec -> ID LP VarList RP
    UNMATCH_TYPE_ASSIGN,//赋值号两边的表达式类型不匹配   Dec -> VarDec ASSIGNOP Exp
    LEFT_VAR_ASSIGN,//赋值号左边出现一个只有右值的表达式    Exp -> Exp ASSIGNOP Exp 赋值语句
    UNMATCH_TYPE_OP,//操作数类型不匹配或操作数类型与操作符不匹配（例如整型变量与数组变量相加减，或数组（或结构体）变量与数组（或结构体）变量相加减）。Exp -> Exp AND Exp算数二元操作符
    UNMATCH_TYPE_RETURN,//return语句的返回类型与函数定义的返回类型不匹配    Stmt -> RETURN Exp SEMI 返回语句
    UNMATCH_FUN_ARGV,//函数调用时实参与形参的数目或类型不匹配。 Exp -> ID LP RP    ||  Args -> Exp COMMA Args 
    NOT_ARRAY,//对非数组型变量使用“[…]”（数组访问）操作符。Exp -> Exp LB Exp RB 数组访问
    NOT_FUN,//对普通变量使用“(…)”或“()”（函数调用）操作符. Exp -> ID LP Args RP
    NOT_INT_IN_ARRAY,//数组访问操作符“[…]”中出现非整数（例如a[1.5]）. Exp -> Exp LB Exp RB
    ABUSE_DOT,//对非结构体型变量使用“.”操作符。Exp -> Exp DOT ID
    UNDEF_FIELD,//访问结构体中未定义过的域。Exp -> Exp DOT ID
    REDEF_FIELD,//结构体中域名重复定义（指同一结构体中），或在定义时对域进行初始化（例如struct A { int a = 0; }） Dec -> VarDec || Dec -> VarDec ASSIGNOP Exp 既定义又初始化
    RENAME_STRUCT,//结构体的名字与前面定义过的结构体或变量的名字重复。StructSpecifier->STRUCT OptTag LC DefList RC 
    UNDEF_STRUCT//直接使用未定义过的结构体来定义变量 StructSpecifier->STRUCT Tag
}error_type;

/*C--中的类型*/
typedef struct Type_
{
    kind kind;
    union 
    {
        //基本类型
        int basic;
        //数组类型信息包括元素类型与数组大小构成
        struct 
        {
           type elem;
           int size;
        } array;
        //结构体类型信息是一个链表
        struct {
            char* struct_name;
            fieldlist field;
        }structure;
        //函数类型信息包括输入参数个数、参数列表、返回值
        struct{
            int argc;//参数个数
            fieldlist argv;//指向参数列表的指针
            type re_type;//返回值的类型
        }function;
    } u;
    
}Type_;
/*结构体链表/域链表*/
/*结构体的域是用一个链表串起来的，每个链表项记录结构体域的名称、类型、指向下一个域的指针*/
typedef struct FieldList_
{
    char* name;//域的名字
    type type;//域的类型
    fieldlist tail;//指向下一个域
}FieldList;

/*############接下来是函数定义############*/
char* newString(char* src);
unsigned int hash_pjw(char* name);
void error_print(error_type type, int line, char* msg);
/*=======类型操作======*/
/*新建一个type*/
type newType(kind kind, ...);

/*复制一个type*/
type copyType(type src);

/*删除一个type*/
void delete_type(type t);

/*检查type*/
unsigned int checkType(type type1, type type2);

/*打印type*/
void printType(type type);

/*=======结构体域链表的操作=======*/
/*新建一个结构体域链表*/
fieldlist newFieldList(char* newName, type newType);

/*复制一个结构体域链表*/
fieldlist copyFieldList(fieldlist src);

/*删除一个结构体域链表*/
void deleteFieldList(fieldlist fieldList);

/*设置结构体域链表名字*/
void setFieldListName(fieldlist p, char* newName);

/*打印结构体域链表*/
void printFieldList(fieldlist fieldList);

/*========表项操作=======*/
/*创建新表项*/
item newItem(int symbolDepth, fieldlist pfield);

/*删除表项*/
void deleteItem(item item);

/*======哈希表操作======*/
/*新建哈希表*/
hash newHash();

/*删除哈希表*/
void deleteHash(hash hash);

/*读哈希表*/
item getHashHead(hash hash, int index);

/*向哈希表添加一项*/
void setHashHead(hash hash, int index, item newVal);

/*======表操作======*/
table initTable();

/*删除表*/
void deleteTable(table mytable);

/*检索符号表*/
item searchTableItem(table mytable, char* name);

/*检查符号表冲突情况*/
int checkTableItemConflict(table mytable, item myitem);

/*添加表项*/
void addTableItem(table mytable, item myitem);

/*删除表项*/
void deleteTableItem(table mytable, item myitem);

/*判断是不是结构体*/
int isStructDef(item src);

/*清除当前栈中一个链表*/
void clearCurDepthStackList(table mytable);

/*=======栈的操作=======*/
/*创建一个栈*/
stack newStack();

/*删除栈*/
void deleteStack(stack  mystack);

/*增加栈的深度*/
void addStackDepth(stack mystack);

/*减少栈的深度/出栈*/
void minusStackDepth(stack mystack);

/*得到当前栈顶元素*/
item getCurDepthStackHead(stack mystack);

/*更改当前栈顶元素/入栈*/
void setCurDepthStackHead(stack mystack, item newVal);

/*遍历语法分析树*/
void sematic_tree(node* root);

/*############接下来是产生式对应动作定义############*/

/*全局变量及函数定义ExtDef*/
void ExtDef(node* root);

/*每个Program可以产生一个ExtDefList，这里的ExtDefList表示零个或多个ExtDef。每个ExtDef表示一个全局变量、结构体或函数的定义。*/
void ExtDecList(node* mynode, type specifier);

/*Specifier是类型描述符，它有两种取值，一种是Specifier → TYPE，直接变成基本类型int或float，
另一种是Specifier → StructSpecifier，变成结构体类型。*/
/*函数返回变量的类型*/
type Specifier(node* mynode);

/*
对于结构体类型来说：
a) 产生式StructSpecifier → STRUCT OptTag LC DefList RC：这是定义结构体的基本格式，例如struct Complex { int real, image; }。
其中OptTag可有可无，因此也可以这样写：struct { int real, image; }。
b) 产生式StructSpecifier → STRUCT Tag：如果之前已经定义过某个结构体，比如struct Complex {…}，
那么之后可以直接使用该结构体来定义变量，例如struct Complex a, b;，而不需要重新定义这个结构体。
*/
/*函数返回结构体的类型*/
type StructSpecifier(node* mynode);

/*VarDec表示对一个变量的定义。该变量可以是一个标识符（例如int a中的a），也可以是一个标识符后面跟着若干对方括号括起来的数字
（例如int a[10][2]中的a[10][2]，这种情况下a是一个数组）*/
/*函数返回变量的表项*/
item VarDec(node* mynode, type specifier);


/*FunDec表示对一个函数头的定义。它包括一个表示函数名的标识符以及由一对圆括号括起来的一个形参列表，该列表由VarList表示（也可以为空）。
VarList包括一个或多个ParamDec，其中每个ParamDec都是对一个形参的定义，该定义由类型描述符Specifier和变量定义VarDec组成。
例如一个完整的函数头为：foo(int x, float y[10])。*/
void FunDec(node* mynode, type returnType);

/*VarList包括一个或多个ParamDec，
其中每个ParamDec都是对一个形参的定义，该定义由类型描述符Specifier和变量定义VarDec组成*/
void VarList(node* mynode, item func);

/*每个ParamDec都是对一个形参的定义，该定义由类型描述符Specifier和变量定义VarDec组成*/
/*这个函数返回函数参数的域*/
fieldlist ParamDec(node* mynode);

/*CompSt表示一个由一对花括号括起来的语句块。该语句块内部先是一系列的变量定义DefList，然后是一系列的语句StmtList。
可以发现，对CompSt这样的定义，是不允许在程序的任意位置定义变量的，必须在每一个语句块的开头才可以定义。*/
void CompSt(node* mynode, type returnType);

/*StmtList就是零个或多个Stmt的组合。*/
void StmtList(node* mynode, type returnType);

/*每个Stmt都表示一条语句，该语句可以是一个在末尾添了分号的表达式（Exp SEMI），
可以是另一个语句块（CompSt），
可以是一条返回语句（RETURN Exp SEMI），
可以是一条if语句（IF LP Exp RP Stmt），
可以是一条if-else语句（IF LP Exp RP Stmt ELSE Stmt），
也可以是一条while语句（WHILE LP Exp RP Stmt）*/
/*处理思路：跳过关键词，处理语句块和表达式*/
void Stmt(node* mynode, type returnType);

/*DefList这个语法单元前面曾出现在CompSt以及StructSpecifier产生式的右边，它就是
一串像int a; float b, c; int d[10];这样的变量定义。一个DefList可以由零个或者多个Def组成*/
void DefList(node* mynode, item structInfo);

/*每个Def就是一条变量定义，它包括一个类型描述符Specifier以及一个DecList，例如
int a, b, c;。由于DecList中的每个Dec又可以变成VarDec ASSIGNOP Exp，这允许我们对局部
变量在定义时进行初始化，例如int a = 5;*/
void Def(node* mynode, item structInfo);

/*DecList中的每个Dec又可以变成VarDec ASSIGNOP Exp，这允许我们对局部
变量在定义时进行初始化，例如int a = 5;*/
void DecList(node* mynode, type specifier, item structInfo);

/*每个Dec又可以变成VarDec ASSIGNOP Exp，这允许我们对局部
变量在定义时进行初始化，例如int a = 5;*/
void Dec(node* mynode, type specifier, item structInfo);

/*表达式；这里是最繁琐的代码部分之一*/
/*函数返回计算得到的变量的类型*/
type Exp(node* mynode);

/*语法单元Args表示实参列表，每个实参都可以变成一个表达式Exp*/
/*处理思路：遍历形参列表，依次与实参比较*/
void Args(node* mynode, item funcInfo);

#endif