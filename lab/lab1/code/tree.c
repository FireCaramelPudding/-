#include "tree.h"
// enum DATATYPE {myINT, myOCT, myHEX, myFLOAT, myID, myTYPE, OTHERS};
// //枚举（enum）允许变量只能是预设的几个值中的一个。
// //枚举值默认对应整数值，从0开始，按定义的顺序递增。例如，TYPE_INT对应0，TYPE_OCT对应1，以此类推。
// typedef struct node
// {
//     char name[32];//语法结构名称
//     int line;//行号
//     enum DATATYPE datatype;  // 如果是int float ID TYPE要保存其对应的值
//     union {                  // 存储对应类型的值
//         unsigned var_int;
//         float var_float;
//         char var_ID[32];
//     } data;
//     int token;//只有01两值，表示当前节点是否为终结符节点
//     struct node* child;//指向第一个子节点的指针
//     struct node* brother;//指向第一个兄弟节点的指针
// }node;

/*a）如果当前结点是词法单元ID，则要求额外打印该标识符所对应的词素；
b）如果当前结点是词法单元TYPE，则要求额外打印说明该类型为int还是float；
c）如果当前结点是词法单元INT或者FLOAT，则要求以十进制的形式额外打印该数字所对应的数值；
d）词法单元所额外打印的信息与词法单元名之间以一个冒号和空格隔开*/
node* token_node(char* name, char* value, enum DATATYPE type){
    node* n = (node*)malloc(sizeof(node));//为节点分配空间
    n->token = 1;//将标志位置1
    n->child = NULL;
    n->brother = NULL;//将指针置空
    n->datatype = type;
    sscanf(name, "%s", n->name);
    switch (type)//根据读入的type类型决定填充内容
    {
    case myINT://如果当前结点是词法单元INT或者FLOAT，则要求以十进制的形式额外打印该数字所对应的数值；
        sscanf(value, "%u", &n->data.var_int);
        break;
    case myOCT:
        sscanf(value, "%o", &n->data.var_int);
        n->datatype = myINT;
        break;
    case myHEX:
        sscanf(value, "%x", &n->data.var_int);
        n->datatype = myINT;
        break;
    case myFLOAT://sscanf实现了八进制、十六进制和科学计数法表示的数转换为十进制表示
        sscanf(value, "%f", &n->data.var_float);
        break;
    case myID://如果当前结点是词法单元ID，则要求额外打印该标识符所对应的词素
        sscanf(value, "%s", n->data.var_ID);
        break;
    case myTYPE://如果当前结点是词法单元TYPE，则要求额外打印说明该类型为int还是float；
        sscanf(value, "%s", n->data.var_ID);
        break;
    default:
        break;
    }
    return n;
}
node* not_token_node(char* name, int line, int children_number, ...){
    node* n = (node*)malloc(sizeof(node));//为节点分配空间
    n->token = 0;//非终结符置0
    n->child = NULL;
    n->brother = NULL;//将指针置空
    n->line = line;
    sscanf(name, "%s", n->name);
    va_list valist;//va_list是一个用于访问可变参数的类型，
    va_start(valist, children_number);//va_start宏用于初始化va_list
    link_node(n, children_number, valist);//为非终结符设置子节点和兄弟节点
    va_end(valist);//va_end宏用于结束参数获取。
    return n;
}
void link_node(node* n, int num, va_list valist){
    int i = 0;
    node* my_node;
    for(i = 0; i<num; i++){//找到参数列表里第一个非空节点
        my_node = va_arg(valist, node*);
        if(my_node != NULL){
            break;
        }
    }
    int j = i+1;
    n->child = my_node;//将其设为第一个子节点
    for(j = i + 1; j < num; j++){//将其余的兄弟节点连接起来
        my_node->brother = va_arg(valist, node*);
        if ((my_node->brother) != NULL) {
            my_node = my_node->brother;
        }
    }
}
void print_tree(node* n, int depth){
    if(n == NULL){
        //printf("节点为空！\n");
        return;
    }
    for (int i = 0; i < depth; i++) {//打印当前节点深度
        printf("  ");
    }
    printf("%s", n->name);//打印符号名称
    if (n->token == 1) {//当前节点为终结符时，按规则打印
        switch (n->datatype) {
            case myINT://如果当前结点是词法单元INT或者FLOAT，则要求以十进制的形式额外打印该数字所对应的数值；
                printf(": %u", n->data.var_int);
                break;
            case myFLOAT:
                printf(": %f", n->data.var_float);
                break;
            case myID://如果当前结点是词法单元ID，则要求额外打印该标识符所对应的词素；
                printf(": %s", n->data.var_ID);
                break;
            case myTYPE://如果当前结点是词法单元TYPE，则要求额外打印说明该类型为int还是float；
                printf(": %s", n->data.var_ID);
                break;
            default:
                break;
        }
    } 
    else {//非终结符打印行号
        printf(" (%d)", n->line);
    }
    printf("\n");
    print_tree(n->child, depth + 1);//先根遍历二叉树，先遍历左孩子
    print_tree(n->brother, depth);//再遍历右兄弟
}
void free_tree(node* n){
    if(n == NULL){
        return;
    }
    if(n->child != NULL){
        free_tree(n->child);
    }
    if(n->brother != NULL){
        free_tree(n->brother);
    }
    free(n);
}