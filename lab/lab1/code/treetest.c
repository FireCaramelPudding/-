#include "tree.h"

extern node* token_node(char* name, char* value, enum DATATYPE type);
extern node* not_token_node(char* name, int line, int children_number, ...);
extern void link_node(node* n, int num, va_list valist);
extern void print_tree(node* n, int depth);
extern void free_tree(node* n);
/*typedef struct node
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
}node;*/
//enum DATATYPE { INT, OCT, HEX, FLOAT, ID, TYPE, OTHERS };
int main() {
    // 创建一个根节点和两个子节点
    node* child1 = token_node("child1", "56", INT);
    node* child2 = token_node("child2", "0237", OCT);
    node* child3 = token_node("child3", "0XFF32", HEX);
    node* child4 = token_node("child4", "1000.65e-4", FLOAT);
    node* child5 = not_token_node("ID", 2, 3, child2, child3, child4);
    node* root = not_token_node("root", 1, 2, child1, child5);
    // 将子节点连接到根节点
    // link_node(root, 2, child1, child5);

    // 打印树
    print_tree(root, 0);

    // 释放树的内存
    free_tree(root);

    return 0;
}
