// #include <stdio.h>
#include "tree.h"
#include "syntax.tab.h"
// #include "sematic.h"
#include "ir.h"
extern FILE* yyin;
extern int yylineno;
extern int yyparse();
extern void yyrestart(FILE*);
extern node* root;
extern int error1;
extern int error2;
extern Table* mytable;//来自语义分析sematic.c
extern ir_list interCodeList;//来自中间代码生成ir.c
int main(int argc,char** argv)
{
    if (argc <= 1)
    {
        return 1;
    }
    FILE* f = fopen(argv[1],"r");
    if(!f)
    {
        perror(argv[1]);
        return 1;
    }
    FILE* i = fopen(argv[2],"w");
    if(!i)
    {
        perror(argv[2]);
        return 1;
    }
    // yydebug = 1;
    yyrestart(f);
    yyparse();
    // fclose(f);
    // printf("接下来进入语义分析\n");
    // while(yylex()!=0);
    if(!error1 && !error2)//词法分析和语法分析均没有错误时
    {   
        // printf("现在已经进入语义分析\n");
        //打印语法分析树
        // print_tree(root,0);
        /*初始化符号表*/
        // table mytable;
        mytable = initTable();
        // printf("初始化的符号表是%d\n",mytable->num);
        /*遍历树，维护符号表，打印错误*/
        sematic_tree(root);
        // printf("接下来打印符号表！\n");
        // printf("****************\n");
        // printSymbolTable(mytable);
        // printf("****************\n");



        printf("接下来进入中间代码生成！\n");
        interCodeList = createInterCodeList();
        genInterCodes(root);
        // printf("interError = %d\n",interError);
        if (!interError) {
            //printInterCode(NULL, interCodeList);
            printInterCode(i, interCodeList);
            printf("中间代码打印完成！\n");
        }
        /*释放符号表*/
        deleteTable(mytable);
    }
    fclose(f);
    fclose(i);
    free_tree(root);
    return 0;
}