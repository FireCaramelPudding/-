#ifndef IR_H
#define IR_H
#include "tree.h"
#include "sematic.h"
#include <stdint.h>/*包含intptr_t*/
/*****命名规则*****/
//结构体原型名字 名字+下划线，如Operand_。这是参考指导书给出的
//结构体实体名字 名字，首字母大写，以大驼峰风格书写，如Operand，InterCode
//结构体指针名字 名字，首字母小写，以下划线风格书写，如operand,inter_cond
//函数命名，以小驼峰为主，如newOperand
typedef struct _operand* operand;/*单条中间代码*/
typedef struct _interCode* inter_cond;
typedef struct _interCodes* inter_conds;
typedef struct _arg* argv;
typedef struct _argList* arg_list;
typedef struct _interCodeList* ir_list;
extern unsigned int interError;//在中间代码生成中是否有误
extern ir_list interCodeList;//中间代码列表
/*单条中间代码每一部分的数据结构，由代码类型、值和名字构成*/
typedef struct _operand 
{
    enum 
    {
        OP_VARIABLE,//变量
        OP_CONSTANT,//常量
        OP_ADDRESS,//地址
        OP_LABEL,//标号
        OP_FUNCTION,//函数类型
        OP_RELOP,//比较
    } kind;

    union 
    {
        char* name;
        int value;
    } u;
} Operand;
/*每条中间代码由类型和值构成*/
typedef struct _interCode 
{
    enum 
    {
        IR_LABEL,//标号
        IR_FUNCTION,//函数
        /*赋值和四则运算*/
        IR_ASSIGN,
        IR_ADD,
        IR_SUB,
        IR_MUL,
        IR_DIV,
        /*地址的创建、读、写*/
        IR_GET_ADDR,
        IR_READ_ADDR,
        IR_WRITE_ADDR,
        /*跳转和返回*/
        IR_GOTO,
        IR_IF_GOTO,
        IR_RETURN,
        IR_DEC,//数组、结构体
        /*函数调用、传参*/
        IR_ARG,//实参
        IR_CALL,
        IR_PARAM,//形参
        /*read和write*/
        IR_READ,
        IR_WRITE,
    } kind;

    union 
    {
        struct 
        {
            operand op;
        } oneOp;//单节点定义，例如标号、函数、跳转、返回、传参、读写
        struct 
        {
            operand right, left;
        } assign;//赋值，例如地址操作、函数调用
        struct 
        {
            operand result, op1, op2;
        } binOp;//双目运算
        struct 
        {
            operand x, relop, y, z;
        } ifGoto;//if跳转语句
        struct 
        {
            operand op;
            int size;
        } dec;//数组、结构体，包含本身和占用的空间
    } u;
} InterCode;
/*使用双向链表实现的线性IR*/
typedef struct _interCodes 
{
    inter_cond code;
    inter_conds *prev, *next;//链接前驱和后继
} InterCodes;
/*参数，以单向链表的形式组织*/
typedef struct _arg 
{
    operand op;
    argv next;
} Arg;
/*参数列表，组织列表的头和当前指向的的参数*/
typedef struct _argList 
{
    argv head;
    argv cur;//便于遍历
} ArgList;
/*中间代码列表，维护标号信息*/
typedef struct _interCodeList 
{
    inter_conds head;
    inter_conds cur;/*维护双向链表的信息*/
    char* lastArrayName; 
    int tempVarNum;//局部变量个数
    int labelNum;//标号数
} InterCodeList;



/*中间代码节点的增、删、改、打印*/
operand createOperand(int kind, ...);
void deleteOperand(operand p);
void setOperand(operand p, int kind, void* val);
void printOp(FILE* fp, operand op);

/*一条中间代码的增、删、打印*/
inter_cond createInterCode(int kind, ...);
void deleteInterCode(inter_cond p);
void printInterCode(FILE* fp, ir_list interCodeList);

/*中间代码段的增、删*/
inter_conds createInterCodes(inter_cond code);
void deleteInterCodes(inter_conds p);

/*函数参数列表的增、删、改*/
argv createArg(operand op);
arg_list createArgList();
void deleteArg(argv p);
void deleteArgList(arg_list p);
void addArg(arg_list argList, argv arg);

/*全局中间代码维护的增、删、改*/
ir_list createInterCodeList();
void deleteInterCodeList(ir_list p);
void addInterCode(ir_list interCodeList, inter_conds newCode);

/*生成新的局部变量和标号*/
operand newTemp();
operand newLabel();
/*生成中间代码*/
int getSize(type mytype);
void genInterCodes(node* mynode);
void genInterCode(int kind, ...);
/*逐个表达式翻译*/
/*全局定义*/
void translateExtDef(node* mynode);
void translateExtDefList(node* mynode);
/*语句块、语句*/
void translateCompSt(node* mynode);
void translateStmt(node* mynode);
void translateStmtList(node* mynode);
/*定义和定义列表*/
void translateDef(node* mynode);
void translateDefList(node* mynode);
/*函数定义*/
void translateFunDec(node* mynode);
/*参数*/
void translateArgs(node* mynode, arg_list argList);
/*变量和变量列表*/
void translateVarDec(node* mynode, operand place);
void translateDec(node* mynode);
void translateDecList(node* mynode);
/*布尔表达式*/
void translateCond(node* mynode, operand labelTrue, operand labelFalse);
/*EXP表达式*/
void translateExp(node* mynode, operand place);
#endif

