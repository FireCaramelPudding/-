#ifndef TREE_H
#define TREE_H
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
enum DATATYPE { myINT, myOCT, myHEX, myFLOAT, myID, myTYPE, OTHERS };
//枚举（enum）允许变量只能是预设的几个值中的一个。
//枚举值默认对应整数值，从0开始，按定义的顺序递增。例如，TYPE_INT对应0，TYPE_OCT对应1，以此类推。
typedef struct node
{
    char name[32];//语法结构名称
    int line;//行号
    enum DATATYPE datatype;  // 如果是int float ID TYPE要保存其对应的值
    union {                  // 存储对应类型的值
        unsigned var_int;
        float var_float;
        char var_ID[32];
    } data;
    int token;//只有01两值，表示当前节点是否为终结符节点
    struct node* child;//指向第一个子节点(左孩子)的指针
    struct node* brother;//指向第一个兄弟节点（右兄弟）的指针
}node;
/*输入：节点指针，当前深度
输出：空
功能：打印语法分析树*/
void print_tree(node* tree_node, int depth);
/*输入：节点名称，节点值，节点类型
输出：节点的指针
功能：为终结符创建一个节点*/
node* token_node(char* name, char* value, enum DATATYPE type);
/*输入：节点名称，节点值，节点类型
输出：节点的指针
功能：为非终结符创建一个节点，并且与子节点和兄弟节点连接起来*/
node* not_token_node(char* name, int line, int children_number, ...);
/*输入：父节点指针，待连接的指针个数，参数列表
输出：空
功能：将给定的父节点同他的孩子节点和兄弟节点连接起来*/
void link_node(node* n, int num, va_list valist);
/*输入：节点指针，当前树的深度
输出：空
功能：按先根遍历的顺序打印语法分析树*/
void print_tree(node* n, int depth);
/*输入：节点指针
输出：空
功能：按先根遍历顺序释放树的内存*/
void free_tree(node* n);
#endif //TREE_H 是一个预处理器宏 