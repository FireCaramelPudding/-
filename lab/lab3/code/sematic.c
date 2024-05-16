#include "sematic.h"
table mytable;
/*
typedef struct Type_* type;
typedef struct FieldList_* fieldlist;
typedef struct Hash* hash;
typedef struct Stack* stack;
typedef struct Item* item;
typedef struct Table* table;
*/
/*函数名：char* newString(char* src)
输入：待生成的字符串指针
输出：新的字符串指针
功能：拷贝字符串，避免指针问题
*/
char* newString(char* src) {
    if (src == NULL) return NULL;
    int length = strlen(src) + 1;
    char* p = (char*)malloc(sizeof(char) * length);
    strncpy(p, src, length);
    return p;
}
/*函数名：void error_print(error_type type, int line, char* msg)
输入：错误类型，行号，错误打印信息
输出：空
功能：打印错误信息
*/
void error_print(error_type type, int line, char* msg) {
    printf("Error type %d at Line %d: %s\n", type, line, msg);
}
/*P.J.提出的哈希函数实现*/
unsigned int hash_pjw(char* name)
{
    unsigned int val = 0, i;
    for (; *name; ++name)
    {
        val = (val << 2) + *name;
        if (i = val & ~HASH_SIZE) val = (val ^ (i >> 12)) & HASH_SIZE;
    }
    return val;
}
/*=======类型操作======*/
/*新建type*/
/*功能：根据token类型，创建一个新的type指针p，根据传入的参数列表初始化p，并返回*/
type newType(kind kind, ...) 
{
    type p = (type)malloc(sizeof(Type_));
    p->kind = kind;
    va_list vaList;
    va_start(vaList, kind);  // Start with 'kind' as it's the last named argument
    switch (kind) {
        case BASIC:
            va_start(vaList, kind);
            p->u.basic = va_arg(vaList, basic_type);
            break;
        case ARRAY:
            va_start(vaList, kind);
            p->u.array.elem = va_arg(vaList, type);
            p->u.array.size = va_arg(vaList, int);
            break;
        case STRUCTURE:
            va_start(vaList, kind);
            p->u.structure.struct_name = va_arg(vaList, char*);
            p->u.structure.field = va_arg(vaList, fieldlist);
            break;
        case FUNCTION:
            va_start(vaList, kind);
            p->u.function.argc = va_arg(vaList, int);
            p->u.function.argv = va_arg(vaList, fieldlist);
            p->u.function.re_type = va_arg(vaList, type);
            break;
    }
    va_end(vaList);
    return p;
}

/*复制一个type*/
/*功能：根据token类型，创建一个新的type指针p，根据传入的参数列表初始化p，并返回*/
type copyType(type src) 
{
    if (src == NULL) return NULL;
    type p = (type)malloc(sizeof(Type_));
    p->kind = src->kind;
    switch (p->kind) {
        case BASIC:
            p->u.basic = src->u.basic;
            break;
        case ARRAY:
            p->u.array.elem = copyType(src->u.array.elem);
            p->u.array.size = src->u.array.size;
            break;
        case STRUCTURE:
            p->u.structure.struct_name = newString(src->u.structure.struct_name);
            p->u.structure.field = copyFieldList(src->u.structure.field);
            break;
        case FUNCTION:
            p->u.function.argc = src->u.function.argc;
            p->u.function.argv = copyFieldList(src->u.function.argv);
            p->u.function.re_type = copyType(src->u.function.re_type);
            break;
    }

    return p;
}
/*删除一个type*/
/*按类型分别删除t的各个域*/
void delete_type(type t)
{
    assert(t);
    if (t == NULL) return;
    fieldlist temp = NULL;
    switch (t->kind)
    {
    case BASIC:
        break;
    case ARRAY:
        delete_type(t->u.array.elem);
        t->u.array.elem = NULL;
        break;
    case STRUCTURE:
        if(t->u.structure.struct_name) free(t->u.structure.struct_name);
        t->u.structure.struct_name = NULL;
        temp = t->u.structure.field;
        while(temp)
        {
            fieldlist delet = temp;
            temp = temp->tail;
            deleteFieldList(delet);
        }
        t->u.structure.field = NULL;
        break;
    case FUNCTION:
        delete_type(t->u.function.re_type);
        t->u.function.re_type = NULL;
        temp = t->u.function.argv;
        while(temp){
            fieldlist delet = temp;
            temp = temp->tail;
            deleteFieldList(delet);
        }
        t->u.function.argv = NULL;
        break;
    }
    // free(t);/*在前已经按t的类型释放了占用的内存，如果此处再次释放则会报告double free detected in tcache 2的错误*/
}
/*检查type*/
/*这里实现了选做3的要求，将结构体相同的判定从名相同改为结构相同*/
unsigned int checkType(type type1, type type2) 
{
    if (type1 == NULL || type2 == NULL) return 1;//指针为空时返回相同
    if (type1->kind == FUNCTION || type2->kind == FUNCTION) return 0;//如果有一个是函数则返回不同
    if (type1->kind != type2->kind)
        return 0;//二者类型不同时返回不同
    else {
        switch (type1->kind) {
            case BASIC://基本类型比较其实际的变量类型
                return type1->u.basic == type2->u.basic;
            case ARRAY://数组类型比较数组元素类型
                return checkType(type1->u.array.elem, type2->u.array.elem);
            case STRUCTURE:
                // // 首先比较结构体名称
                // if (strcmp(type1->u.structure.struct_name,type2->u.structure.struct_name) != 0)
                //     return 0;
                // 获取结构体成员列表
                FieldList *list1 = type1->u.structure.field;
                FieldList *list2 = type2->u.structure.field;
                // 遍历成员列表
                while (list1 != NULL && list2 != NULL) {
                    // 比较每个成员的类型
                    if (!checkType(list1->type, list2->type))
                        return 0;
                    list1 = list1->tail;
                    list2 = list2->tail;
                }
                // 如果一个列表比另一个列表长，那么结构体类型不同
                if (list1 != NULL || list2 != NULL)
                    return 0;
                // 否则，结构体类型相同
                return 1;
                // return !strcmp(type1->u.structure.struct_name,type2->u.structure.struct_name);
        }
    }
}

/*=======结构体域类型链表的操作=======*/
/*新建一个域链表*/
fieldlist newFieldList(char* newName, type newType) 
{
    fieldlist p = (fieldlist)malloc(sizeof(FieldList));
    p->name = newString(newName);
    p->type = newType;
    p->tail = NULL;//将指向下一个域的指针设为空
    p->isArg = 0;
    return p;
}
/*复制一个域链表*/
fieldlist copyFieldList(fieldlist src) 
{
    fieldlist head = NULL, cur = NULL;
    fieldlist temp = src;
    while (temp) {
        if (!head) {/*新链表为空时*/
            head = newFieldList(temp->name, copyType(temp->type));
            cur = head;/*更新当前链表*/
            temp = temp->tail;/*指针后移*/
        } 
        else {/*从第二项开始*/
            cur->tail = newFieldList(temp->name, copyType(temp->type));/*递归调用*/
            cur = cur->tail;/*更新当前链表*/
            temp = temp->tail;/*指针后移*/
        }
    }
    return head;/*返回链表头*/
}
/*删除一个域链表*/
/*分别释放内存*/
void deleteFieldList(fieldlist fieldList) 
{
    if (fieldList->name) 
    {
        free(fieldList->name);
        fieldList->name = NULL;
    }
    if (fieldList->type) delete_type(fieldList->type);
    fieldList->type = NULL;
    free(fieldList);
}
/*设置域链表名字*/
void setFieldListName(fieldlist p, char* newName) 
{
    if (p->name != NULL) {
        free(p->name);
    }
    p->name = newString(newName);
}

/*========表项操作=======*/
/*typedef struct Item
{
    int depth;//存储深度
    fieldlist field;//表项的值
    item next_symbol;//同深度下一个符号
    item next_hash;//下一个哈希值相同的符号
}Item;*/
/*新建一个表项*/
item newItem(int symbolDepth, fieldlist pfield) 
{
    item p = (item)malloc(sizeof(Item));
    p->depth = symbolDepth;
    p->field = pfield;
    p->next_hash = NULL;
    p->next_symbol = NULL;
    return p;
}
/*删除表项*/
void deleteItem(item item) 
{
    if (item->field != NULL) 
        deleteFieldList(item->field);
    free(item);
}
/*======哈希表操作======*/
/*typedef struct Hash
{
    item* hash_array;
}Hash;*/
/*新建哈希表*/
hash newHash() 
{
    hash p = (hash)malloc(sizeof(Hash));/*申请指针*/
    if (p == NULL){printf("初始化哈希表失败！\n");}
    p->hash_array = (item*)malloc(sizeof(item) * HASH_SIZE);/*申请数组模拟哈希表*/
    if (p == NULL){printf("初始化哈希表失败！\n");}
    for (int i = 0; i < HASH_SIZE; i++) {
        p->hash_array[i] = NULL;/*逐个置为空*/
    }
    return p;
}
/*删除哈希表*/
void deleteHash(hash hash) 
{
    for (int i = 0; i < HASH_SIZE; i++) {
        item temp = hash->hash_array[i];
        while (temp) {
            item tdelete = temp;
            temp = temp->next_hash;
            deleteItem(tdelete);
        }/*遍历哈希表每个表项，分别删除表项，再置指针为空*/
        hash->hash_array[i] = NULL;
    }
    free(hash->hash_array);
    hash->hash_array = NULL;
    free(hash);
}
/*读哈希表*/
item getHashHead(hash hash, int index) 
{
    return hash->hash_array[index];
}
/*向哈希表添加一项*/
void setHashHead(hash hash, int index, item newVal) 
{
    hash->hash_array[index] = newVal;
}
/*======表操作======*/
/*typedef struct Table
{
    hash hash_table;//全局变量的哈希表
    stack table_stack;//存放局部声明变量的哈希表的栈
    int num;//跟踪未命名的结构体数量
}Table;*/
/*初始化符号表*/
table initTable() 
{
    table mytable = (table)malloc(sizeof(Table));
    mytable->hash_table = newHash();
    mytable->table_stack = newStack();/*分别为哈希表和栈申请空间*/
    mytable->num = 0;/*置当前深度为0*/
    //TODO:在初始化符号表时，将read、write两个函数添加到符号表中
    item read_fun = newItem(0, newFieldList(newString("read"),newType(FUNCTION, 0, NULL, newType(BASIC, myINT))));
    item write_fun = newItem(0, newFieldList(newString("write"),newType(FUNCTION, 1,newFieldList("arg1", newType(BASIC, myINT)),newType(BASIC, myINT))));
    addTableItem(mytable, read_fun);
    addTableItem(mytable, write_fun);//这里之前忘加了
    return mytable;
};
/*删除表*/
void deleteTable(table mytable) 
{
    deleteHash(mytable->hash_table);
    mytable->hash_table = NULL;
    deleteStack(mytable->table_stack);
    mytable->table_stack = NULL;
    free(mytable);
};
/*检索符号表*/
item searchTableItem(table mytable, char* name) 
{
    unsigned hashCode = hash_pjw(name);/*按pjw提出的哈希算法计算哈希值*/
    item temp = getHashHead(mytable->hash_table, hashCode);/*按哈希值得到表项*/
    if (temp == NULL) return NULL;
    while (temp) {/*沿槽从深度深到浅遍历链表*/
        if (!strcmp(temp->field->name, name)) 
            return temp;/*和当前符号名相同时返回*/
        temp = temp->next_hash;
    }
    return NULL;/*否则不存在、未找到*/
}
/*检查符号表冲突情况*/
int checkTableItemConflict(table mytable, item myitem) 
{
    item temp = searchTableItem(mytable, myitem->field->name);
    if (temp == NULL) return 0;/*未找到说明不存在冲突*/
    while (temp) /*在符号表中找到这项时*/
    {
        if (!strcmp(temp->field->name, myitem->field->name)) /*当二者域名相同时*/
        {
            if (temp->field->type->kind == STRUCTURE || myitem->field->type->kind == STRUCTURE)
                return 1;/*二者有一个是结构体类型，则冲突*/
            if (temp->depth == mytable->table_stack->depth) return 1;/*二者重名且在同一深度下，说明在同一个函数作用域中重复声明，返回冲突*/
        }
        temp = temp->next_hash;/*沿同一哈希值的链表方向查找*/
    }
    return 0;/*同一哈希值的链表方向均无冲突时，则无冲突*/
}
/*
typedef struct Item
{
    int depth;//存储深度
    fieldlist field;//表项的值
    item next_symbol;//同深度下一个符号
    item next_hash;//下一个哈希值相同的符号
}Item;
*/
/*添加表项*/
void addTableItem(table mytable, item myitem) {
    unsigned hashCode = hash_pjw(myitem->field->name);/*计算哈希值*/
    hash myhash = mytable->hash_table;
    stack mystack = mytable->table_stack;/*更新栈和符号表信息*/
    myitem->next_symbol = getCurDepthStackHead(mystack);
    setCurDepthStackHead(mystack, myitem);/*获取当前哈希表头，并将新项加入哈希链表头*/

    myitem->next_hash = getHashHead(myhash, hashCode);
    setHashHead(myhash, hashCode, myitem);/*获取当前深度表头，并将新项加入深度链表头*/
}
/*删除表项*/
void deleteTableItem(table mytable, item myitem) {

    unsigned hashCode = hash_pjw(myitem->field->name);/*计算哈希值*/
    if (myitem == getHashHead(mytable->hash_table, hashCode))/*如果槽中第一个就是待删除的表项*/
        setHashHead(mytable->hash_table, hashCode, myitem->next_hash);/*将自己的下一个表项设置为当前表头*/
    else /*否则沿着哈希表链表查询待删除表项*/
    {
        item cur = getHashHead(mytable->hash_table, hashCode);
        item last = cur;
        while (cur != myitem) {
            last = cur;
            cur = cur->next_hash;
        }
        last->next_hash = cur->next_hash;
    }
    deleteItem(myitem);/*递归调用*/
}
/*判断是不是结构体*/
int isStructDef(item src) {
    if (src == NULL) return 0;//表项为空时返回0
    if (src->field->type->kind != STRUCTURE) return 0;//变量类型不为结构体时返回0
    if (src->field->type->u.structure.struct_name) return 0;//名字为空是返回0
    return 1;
}
/*清除当前栈中一个链表*/
void clearCurDepthStackList(table mytable) {
    stack mystack = mytable->table_stack;
    item temp = getCurDepthStackHead(mystack);/*找到链表头*/
    while (temp) {
        item tDelete = temp;
        temp = temp->next_symbol;/*依次向后遍历链表*/
        deleteTableItem(mytable, tDelete);
    }
    setCurDepthStackHead(mystack, NULL);/*将当前链表头指针置为空*/
    minusStackDepth(mystack);/*深度减一*/
}
/*=======栈的操作=======*/
/*typedef struct Stack
{
    int depth;//当前深度
    item* stack_array;//使用数组模拟栈
}Stack;*/
/*创建一个栈*/
stack newStack() {
    stack p = (stack)malloc(sizeof(Stack));
    p->stack_array = (item*)malloc(sizeof(item) * HASH_SIZE);/*为栈和栈中哈希表申请内存*/
    for (int i = 0; i < HASH_SIZE; i++) {
        p->stack_array[i] = NULL;/*初始化*/
    }
    p->depth = 0;/*置深度为0*/
    return p;
}
/*删除栈*/
void deleteStack(stack  mystack) {
    free(mystack->stack_array);/*删除哈希表*/
    mystack->stack_array = NULL;/*删除指针*/
    mystack->depth = 0;/*深度置0*/
    free(mystack);/*释放内存*/
}
/*增加栈的深度*/
void addStackDepth(stack mystack) {
    mystack->depth++;
}
/*减少栈的深度/出栈*/
void minusStackDepth(stack mystack) {
    mystack->depth--;
}
/*得到当前栈顶元素*/
item getCurDepthStackHead(stack mystack) {
    return mystack->stack_array[mystack->depth];/*即当前深度的元素*/
}
/*更改当前栈顶元素/入栈*/
void setCurDepthStackHead(stack mystack, item newVal) {
    mystack->stack_array[mystack->depth] = newVal;
}
/*遍历语法分析树*/
void sematic_tree(node* root)
{   
    if(root == NULL) return ;/*节点为空时结束递归*/
    if(strcmp(root->name,"ExtDef") == 0) ExtDef(root);/*遇到定义时。调用extdef函数*/
    sematic_tree(root ->child);/*否则依次遍历孩子和兄弟*/
    sematic_tree(root ->brother);
}
/*
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
*/
/*全局变量及函数定义ExtDef*/
void ExtDef(node* root)
{
    // ExtDef -> Specifier ExtDecList SEMI 全局变量的定义
    //         | Specifier SEMI 结构体定义 struct{...}
    //         | Specifier FunDec CompSt    函数定义
    type specifier_type = Specifier(root->child);/*通过寻找Specifier对应的内容得到变量类型，结构体类型的变量在这里已处理*/
    char* name = root->child->brother->name;/*得到变量的名字*/

    if(strcmp(name, "ExtDecList")==0)//Specifier ExtDecList SEMI 全局变量
    {
        ExtDecList(root->child->brother, specifier_type);/*调用ExtDecList产生式*/
    }
    else if (strcmp(name,"FunDec")==0)//Specifier FunDec CompSt 函数定义
    {
        FunDec(root->child->brother,specifier_type);/*调用FunDec产生式*/
        CompSt(root->child->brother->brother,specifier_type);
    }
    if(specifier_type) delete_type(specifier_type);/*删除对应节点*/
}
/*每个Program可以产生一个ExtDefList，这里的ExtDefList表示零个或多个ExtDef。每个ExtDef表示一个全局变量、结构体或函数的定义。*/
void ExtDecList(node* mynode, type specifier) 
{
    // ExtDecList -> VarDec 单个变量声明
    //             | VarDec COMMA ExtDecList 以逗号分割的多个变量声明 a a,b,c
    node* temp = mynode;
    while (temp) /*当前节点不为空时*/
    {
        item myitem = VarDec(temp->child, specifier);/*调用VarDec处理变量定义*/
        if (checkTableItemConflict(mytable, myitem)) /*查询表项冲突，判断重复定义REDEF_VAR错误*/
        {
            char msg[100] = {0};
            sprintf(msg, "Redefined variable \"%s\".", myitem->field->name);
            error_print(REDEF_VAR, temp->line, msg);
            deleteItem(myitem);/*不要忘记释放节点*/
        } 
        else 
        {
            addTableItem(mytable, myitem);/*将这个变量声明加入符号表*/
        }
        if (temp->child->brother) /*当前节点还有右兄弟时，即以逗号分割的多个变量声明的情况（右面还有一个逗号）*/
        {
            temp = temp->brother->brother->child;/*更新temp，注意第一个右兄弟是逗号，第二个右兄弟才是下一个变量*/
        } 
        else 
        {
            break;/*全部声明读入完毕*/
        }
    }
}
/*Specifier是类型描述符，它有两种取值，一种是Specifier → TYPE，直接变成基本类型int或float，
另一种是Specifier → StructSpecifier，变成结构体类型。*/
/*函数返回变量的类型*/
type Specifier(node* mynode) {
    // Specifier -> TYPE
    //            | StructSpecifier

    node* t = mynode->child;
    // Specifier -> TYPE 基本类型
    if (!strcmp(t->name, "TYPE")) /*读入的是基本类型*/
    {
        if (!strcmp(t->mydata, "float")) 
        {
            return newType(BASIC, myFLOAT);
        } 
        else 
        {
            return newType(BASIC, myINT);/*按类型名分配类型*/
        }
    }
    // Specifier -> StructSpecifier
    else {
        return StructSpecifier(t);/*按结构体分配类型*/
    }
}
/*
对于结构体类型来说：
a) 产生式StructSpecifier → STRUCT OptTag LC DefList RC：这是定义结构体的基本格式，例如struct Complex { int real, image; }。
其中OptTag可有可无，因此也可以这样写：struct { int real, image; }。
b) 产生式StructSpecifier → STRUCT Tag：如果之前已经定义过某个结构体，比如struct Complex {…}，
那么之后可以直接使用该结构体来定义变量，例如struct Complex a, b;，而不需要重新定义这个结构体。
*/
/*函数返回结构体的类型*/
type StructSpecifier(node* mynode) {
    // StructSpecifier -> STRUCT OptTag LC DefList RC 包含域的结构体定义
    //                  | STRUCT Tag 按结构体定义变量

    // OptTag -> ID | e 可选的结构体名字
    // Tag -> ID    
    type returnType = NULL;
    node* t = mynode->child->brother;/*判断使用产生式一还是产生式二*/
    // StructSpecifier->STRUCT OptTag LC DefList RC
    if (strcmp(t->name, "Tag")) /*使用产生式一*/
    {
        item structItem = newItem(mytable->table_stack->depth,newFieldList("", newType(STRUCTURE, NULL, NULL)));/*为结构体申请表项*/
        if (!strcmp(t->name, "OptTag")) /*和产生式一格式相符*/
        {
            setFieldListName(structItem->field, t->child->mydata);/*为结构体的域设置名字*/
            t = t->brother;/*将t更新为t的右兄弟LC*/
        }
        else /*否则，则是省略OptTag的结构体，如struct { int real, image; }*/
        {
            mytable->num++;/*更新计数器*/
            char structName[20] = {0};
            sprintf(structName, "%d", mytable->num);/*用标号命名结构体*/
            setFieldListName(structItem->field, structName);
        }
        if (!strcmp(t->brother->name, "DefList")) /*LC右兄弟是DefList*/
        {
            DefList(t->brother, structItem);/*调用DefList创建域名列表*/
        }

        if (checkTableItemConflict(mytable, structItem)) /*检查符号表，判断命名冲突*/
        {
            char msg[100] = {0};
            sprintf(msg, "Duplicated name \"%s\".", structItem->field->name);
            error_print(RENAME_STRUCT, mynode->line, msg);
            deleteItem(structItem);
        } 
        else /*不存在冲突时*/
        {
            returnType = newType(STRUCTURE, newString(structItem->field->name),copyFieldList(structItem->field->type->u.structure.field));/*为结构体类型变量创建类型*/
            if (!strcmp(mynode->child->brother->name, "OptTag")) /*按第一条产生式格式命名的结构体*/
            {
                addTableItem(mytable, structItem);/*将表项添加到符号表中*/
            }
            // OptTag -> e
            else 
            {
                deleteItem(structItem);/*否则删除这一项*/
            }
        }
    }

    // StructSpecifier->STRUCT Tag
    else /*使用第二条产生式产生的结构体定义变量struct Complex a, b*/
    {
        item structItem = searchTableItem(mytable, t->child->mydata);/*在符号表中查询结构体名*/
        if (structItem == NULL || !isStructDef(structItem)) /*没查到或不是结构体定义*/
        {
            char msg[100] = {0};
            sprintf(msg, "Undefined structure \"%s\".", t->child->mydata);
            error_print(UNDEF_STRUCT, mynode->line, msg);/*报告UNDEF_STRUCT错误*/
        } 
        else
            returnType = newType(STRUCTURE, newString(structItem->field->name),copyFieldList(structItem->field->type->u.structure.field));/*为结构体类型变量创建类型*/
    }
    return returnType;
}
/*VarDec表示对一个变量的定义。该变量可以是一个标识符（例如int a中的a），也可以是一个标识符后面跟着若干对方括号括起来的数字
（例如int a[10][2]中的a[10][2]，这种情况下a是一个数组）*/
/*函数返回变量的表项*/
item VarDec(node* mynode, type specifier) 
{
    // VarDec -> ID 标识符
    //         | VarDec LB INT RB   标识符+方括号数字
    node* id = mynode;
    while (id->child) id = id->child;/*遍历，直到找到ID标识符*/
    item p = newItem(mytable->table_stack->depth, newFieldList(id->mydata, NULL));/*为当前变量创建表项*/

    // VarDec -> ID
    if (!strcmp(mynode->child->name, "ID")) 
    {
        p->field->type = copyType(specifier);/*一开始就是ID，正常的变量定义，按域创建类型返回给指针*/
    }
    // VarDec -> VarDec LB INT RB
    else /*数组的定义*/
    {
        node* varDec = mynode->child;/*ID或另一个数组*/
        type temp = specifier;/*数组的类型*/
        while (varDec->brother) /*向右遍历各维数组定义*/
        {
            p->field->type = newType(ARRAY, copyType(temp), atoi(varDec->brother->brother->mydata));/*为各维数组新建类型*/
            temp = p->field->type;
            varDec = varDec->child;/*更新数组维度和类型*/
        }
    }
    return p;
}
/*FunDec表示对一个函数头的定义。它包括一个表示函数名的标识符以及由一对圆括号括起来的一个形参列表，该列表由VarList表示（也可以为空）。
VarList包括一个或多个ParamDec，其中每个ParamDec都是对一个形参的定义，该定义由类型描述符Specifier和变量定义VarDec组成。
例如一个完整的函数头为：foo(int x, float y[10])。*/
void FunDec(node* mynode, type returnType) 
{
    // FunDec -> ID LP VarList RP 带参数列表的函数定义
    //         | ID LP RP  不带参数列表的函数定义。在这里没处理
    item p = newItem(mytable->table_stack->depth,newFieldList(mynode->child->mydata,newType(FUNCTION, 0, NULL, copyType(returnType))));/*为这个函数创建表项*/
    if (p == NULL) printf("在FunDec传入空指针！\n");
    // FunDec -> ID LP VarList RP
    if (!strcmp(mynode->child->brother->brother->name, "VarList")) 
    {
        VarList(mynode->child->brother->brother, p);/*判断第三个字段是不是VarList，是则调用对应的函数*/
    }

    if (checkTableItemConflict(mytable, p)) /*检查函数定义的冲突*/
    {
        char msg[100] = {0};
        sprintf(msg, "Redefined function \"%s\".", p->field->name);
        error_print(REDEF_FUN, mynode->line, msg);
        deleteItem(p);
        p = NULL;
    } 
    else /*没有冲突则填表*/
    {
        addTableItem(mytable, p);
    }
}
/*VarList包括一个或多个ParamDec，
其中每个ParamDec都是对一个形参的定义，该定义由类型描述符Specifier和变量定义VarDec组成*/
void VarList(node* mynode, item func) 
{
    // VarList -> ParamDec COMMA VarList 逗号分割的形参列表
    //          | ParamDec 形参
    addStackDepth(mytable->table_stack);/*栈深度加一，为存放新的符号表提供位置*/
    int argc = 0;/*符号个数计数器*/
    node* temp = mynode->child;/*指向第一个形参*/
    fieldlist cur = NULL;

    // VarList -> ParamDec
    fieldlist paramDec = ParamDec(temp);/*调用ParamDec函数创建参数链表项*/
    func->field->type->u.function.argv = copyFieldList(paramDec);/*传递链表项*/
    cur = func->field->type->u.function.argv;/*更新*/
    argc++;

    // VarList -> ParamDec COMMA VarList
    while (temp->brother) /*参数列表还有时*/
    {
        temp = temp->brother->brother->child;
        paramDec = ParamDec(temp);
        if (paramDec) 
        {
            cur->tail = copyFieldList(paramDec);
            cur = cur->tail;
            argc++;/*重复VarList -> ParamDec的处理过程*/
        }
    }

    func->field->type->u.function.argc = argc;/*更新函数的参数计数器*/

    minusStackDepth(mytable->table_stack);/*栈深度减一，函数参数列表处理完毕*/
}
/*每个ParamDec都是对一个形参的定义，该定义由类型描述符Specifier和变量定义VarDec组成*/
/*这个函数返回函数参数的域*/
fieldlist ParamDec(node* mynode) 
{
    // ParamDec -> Specifier VarDec
    type specifierType = Specifier(mynode->child);
    item p = VarDec(mynode->child->brother, specifierType);
    if (specifierType) delete_type(specifierType);
    if (checkTableItemConflict(mytable, p)) 
    {
        char msg[100] = {0};
        sprintf(msg, "Redefined variable \"%s\".", p->field->name);
        error_print(REDEF_VAR, mynode->line, msg);/*检查表项冲突*/
        deleteItem(p);
        return NULL;
    } 
    else 
    {
        p->field->isArg = 1;/*此处将结构体判断标志置为真*/
        addTableItem(mytable, p);/*填表*/
        return p->field;
    }
}
/*CompSt表示一个由一对花括号括起来的语句块。该语句块内部先是一系列的变量定义DefList，然后是一系列的语句StmtList。
可以发现，对CompSt这样的定义，是不允许在程序的任意位置定义变量的，必须在每一个语句块的开头才可以定义。*/
void CompSt(node* mynode, type returnType) 
{
    // CompSt -> LC DefList StmtList RC
    addStackDepth(mytable->table_stack);/*深度加一，为函数存放局部变量的符号表取得空间*/
    node* temp = mynode->child->brother;
    if (!strcmp(temp->name, "DefList")) 
    {
        DefList(temp, NULL);/*处理变量定义*/
        temp = temp->brother;
    }
    if (!strcmp(temp->name, "StmtList")) 
    {
        StmtList(temp, returnType);/*处理语句*/
    }

    // clearCurDepthStackList(mytable);/*清除当前深度的栈的符号链表*/
}
/*StmtList就是零个或多个Stmt的组合。
每个Stmt都表示一条语句，该语句可以是一个在末尾添了分号的表达式（Exp SEMI），
可以是另一个语句块（CompSt），
可以是一条返回语句（RETURN Exp SEMI），
可以是一条if语句（IF LP Exp RP Stmt），
可以是一条if-else语句（IF LP Exp RP Stmt ELSE Stmt），
也可以是一条while语句（WHILE LP Exp RP Stmt）*/
void StmtList(node* mynode, type returnType) 
{
    // StmtList -> Stmt StmtList
    //           | e
    while (mynode) 
    {
        Stmt(mynode->child, returnType);/*调用语句函数Stmt*/
        mynode = mynode->child->brother;/*处理下一条语句，直至为空*/
    }
}
/*每个Stmt都表示一条语句，该语句可以是一个在末尾添了分号的表达式（Exp SEMI），
可以是另一个语句块（CompSt），
可以是一条返回语句（RETURN Exp SEMI），
可以是一条if语句（IF LP Exp RP Stmt），
可以是一条if-else语句（IF LP Exp RP Stmt ELSE Stmt），
也可以是一条while语句（WHILE LP Exp RP Stmt）*/
/*处理思路：跳过关键词，处理语句块和表达式*/
void Stmt(node* mynode, type returnType) 
{
    // Stmt -> Exp SEMI
    //       | CompSt
    //       | RETURN Exp SEMI
    //       | IF LP Exp RP Stmt
    //       | IF LP Exp RP Stmt ELSE Stmt
    //       | WHILE LP Exp RP Stmt

    type expType = NULL;
    // Stmt -> Exp SEMI 表达式语句
    if (!strcmp(mynode->child->name, "Exp")) expType = Exp(mynode->child);/*调用Exp函数处理*/

    // Stmt -> CompSt 语句块
    else if (!strcmp(mynode->child->name, "CompSt"))
        CompSt(mynode->child, returnType);/*调用CompSt函数处理*/

    // Stmt -> RETURN Exp SEMI 返回语句
    else if (!strcmp(mynode->child->name, "RETURN")) 
    {
        expType = Exp(mynode->child->brother);/*先处理返回的值*/

        // check return type
        if (!checkType(returnType, expType))/*检查返回值类型和函数定义是否一致*/
            error_print(UNMATCH_TYPE_RETURN, mynode->line,"Type mismatched for return.");
    }

    // Stmt -> IF LP Exp RP Stmt      IF语句
    else if (!strcmp(mynode->child->name, "IF")) 
    {
        node* stmt = mynode->child->brother->brother->brother->brother;
        expType = Exp(mynode->child->brother->brother);/*处理判断条件表达式*/
        Stmt(stmt, returnType);/*处理语句块*/
        // Stmt -> IF LP Exp RP Stmt ELSE Stmt 带ELSE的IF语句
        if (stmt->brother != NULL) Stmt(stmt->brother->brother, returnType);/*多处理一条语句*/
    }

    // Stmt -> WHILE LP Exp RP Stmt
    else if (!strcmp(mynode->child->name, "WHILE")) 
    {
        expType = Exp(mynode->child->brother->brother);
        Stmt(mynode->child->brother->brother->brother->brother, returnType);/*同上*/
    }

    if (expType) delete_type(expType);/*清理临时变量，防止堆栈溢出！！！*/
}
/*DefList这个语法单元前面曾出现在CompSt以及StructSpecifier产生式的右边，它就是
一串像int a; float b, c; int d[10];这样的变量定义。一个DefList可以由零个或者多个Def组成*/
void DefList(node* mynode, item structInfo) 
{
    // DefList -> Def DefList
    //          | e
    while (mynode) 
    {
        Def(mynode->child, structInfo);/*当右兄弟不为0时，逐个处理变量定义。*/
        mynode = mynode->child->brother;
    }
}
/*每个Def就是一条变量定义，它包括一个类型描述符Specifier以及一个DecList，例如
int a, b, c;。由于DecList中的每个Dec又可以变成VarDec ASSIGNOP Exp，这允许我们对局部
变量在定义时进行初始化，例如int a = 5;*/
void Def(node* mynode, item structInfo) 
{
    // Def -> Specifier DecList SEMI
    type dectype = Specifier(mynode->child);/*声明变量*/
    DecList(mynode->child->brother, dectype, structInfo);/*调用DecList处理参数列表*/
    if (dectype) delete_type(dectype);/*清理临时变量*/
}
/*DecList中的每个Dec又可以变成VarDec ASSIGNOP Exp，这允许我们对局部
变量在定义时进行初始化，例如int a = 5;*/
void DecList(node* mynode, type specifier, item structInfo) 
{
    // DecList -> Dec
    //          | Dec COMMA DecList
    node* temp = mynode;
    while (temp) /*变量还有时*/
    {
        Dec(temp->child, specifier, structInfo);/*调用Dec处理变量*/
        if (temp->child->brother)/*不为空时，更新temp，否则结束*/
            temp = temp->child->brother->brother;
        else
            break;
    }
}
/*每个Dec又可以变成VarDec ASSIGNOP Exp，这允许我们对局部
变量在定义时进行初始化，例如int a = 5;*/
void Dec(node* mynode, type specifier, item structInfo) 
{
    // Dec -> VarDec
    //      | VarDec ASSIGNOP Exp

    // Dec -> VarDec    只定义不初始化
    if (mynode->child->brother == NULL) 
    {
        if (structInfo != NULL) /*检查当前变量是否在结构体内部？*/
        {
            item decitem = VarDec(mynode->child, specifier);/*申请表项*/
            fieldlist payload = decitem->field;
            fieldlist structField = structInfo->field->type->u.structure.field;
            fieldlist last = NULL;
            while (structField != NULL) 
            {
                if (!strcmp(payload->name, structField->name)) /*检查结构体内部是否有相同名字的变量*/
                {
                    char msg[100] = {0};
                    sprintf(msg, "Redefined field \"%s\".",decitem->field->name);
                    error_print(REDEF_FIELD, mynode->line, msg);/*是则出现REDEF_FIELD错误*/
                    deleteItem(decitem);
                    return;
                } 
                else /*未重定义，将这一项加入结构体的域链表中*/
                {
                    last = structField;
                    structField = structField->tail;
                }
            }
            if (last == NULL) /*说明链表为空*/
            {
                structInfo->field->type->u.structure.field = copyFieldList(decitem->field);/*将这一项加入结构体的域链表中*/
            } 
            else /*否则，就在其后面添加一个域*/
            {
                last->tail = copyFieldList(decitem->field);
            }
            // TODO:这里要将局部变量加入到符号表中
            addTableItem(mytable, decitem);
            // deleteItem(decitem);/*清除临时变量*/
        } 
        else /*当前变量不在结构体中*/
        {
            item decitem = VarDec(mynode->child, specifier);
            if (checkTableItemConflict(mytable, decitem)) /*检查冲突*/
            {
                char msg[100] = {0};
                sprintf(msg, "Redefined variable \"%s\".",decitem->field->name);
                error_print(REDEF_VAR, mynode->line, msg);
                deleteItem(decitem);
            } 
            else 
            {
                addTableItem(mytable, decitem);/*无冲突时添加表项*/
            }
        }
    }
    // Dec -> VarDec ASSIGNOP Exp 既定义又初始化
    else {
        if (structInfo != NULL) 
        {
            error_print(REDEF_FIELD, mynode->line,"Illegal initialize variable in struct.");/*在结构体内这么做，不合法*/
        } 
        else 
        {
            item decitem = VarDec(mynode->child, specifier);
            type exptype = Exp(mynode->child->brother->brother);/*处理变量*/
            if (checkTableItemConflict(mytable, decitem)) /*检查冲突*/
            {
                char msg[100] = {0};
                sprintf(msg, "Redefined variable \"%s\".", decitem->field->name);
                error_print(REDEF_VAR, mynode->line, msg);/*重定义*/
                deleteItem(decitem);
            }
            if (!checkType(decitem->field->type, exptype)) /*检查查到的变量类型和声明的是否一致*/
            {
                error_print(UNMATCH_TYPE_ASSIGN, mynode->line,"Type mismatchedfor assignment.");/*类型不匹配*/
                deleteItem(decitem);
            }
            if (decitem->field->type && decitem->field->type->kind == ARRAY) 
            {
                error_print(UNMATCH_TYPE_ASSIGN, mynode->line,"Illegal initialize variable.");/*对不是basic类型的变量赋值*/
                deleteItem(decitem);
            } 
            else 
            {
                addTableItem(mytable, decitem);/*没有冲突，添加到符号表中*/
            }
            if (exptype) delete_type(exptype);/*清理临时变量*/
        }
    }
}
/*表达式；这里是最繁琐的代码部分之一*/
/*函数返回计算得到的变量的类型*/
type Exp(node* mynode) 
{
    // Exp -> Exp ASSIGNOP Exp
    //      | Exp AND Exp
    //      | Exp OR Exp
    //      | Exp RELOP Exp
    //      | Exp PLUS Exp
    //      | Exp MINUS Exp
    //      | Exp STAR Exp
    //      | Exp DIV Exp
    //      | LP Exp RP
    //      | MINUS Exp
    //      | NOT Exp
    //      | ID LP Args RP
    //      | ID LP RP
    //      | Exp LB Exp RB
    //      | Exp DOT ID
    //      | ID
    //      | INT
    //      | FLOAT
    node* t = mynode->child;
    /*exp表示二值运算*/
    if (!strcmp(t->name, "Exp")) 
    {
        /*基本数学运算符*/
        if (strcmp(t->brother->name, "LB") && strcmp(t->brother->name, "DOT")) /*既不是访问函数也不是访问结构体*/
        {
            type p1 = Exp(t);
            type p2 = Exp(t->brother->brother);
            type returnType = NULL;

            // Exp -> Exp ASSIGNOP Exp 赋值语句
            if (!strcmp(t->brother->name, "ASSIGNOP")) 
            {
                /*检查左值，左值必须为变量*/
                node* tchild = t->child;

                if (!strcmp(tchild->name, "FLOAT") || !strcmp(tchild->name, "INT")) /*基本类型*/
                {
                    error_print(LEFT_VAR_ASSIGN, t->line, "The left-hand side of an assignment must be a variable.");

                } 
                else if (!strcmp(tchild->name, "ID") || !strcmp(tchild->brother->name, "LB") || !strcmp(tchild->brother->name, "DOT")) /*标识、括号、点*/
                {
                    if (!checkType(p1, p2)) /*检查等号两侧变量类型*/
                    {
                        error_print(UNMATCH_TYPE_ASSIGN, t->line,"Type mismatched for assignment.");
                    } 
                    else/*一致时，返回一个*/
                        returnType = copyType(p1);
                } 
                else /*其他变量类型，不能在左侧*/
                {
                    error_print(LEFT_VAR_ASSIGN, t->line,"The left-hand side of an assignment must be a variable.");
                }

            }
            /*算数二元操作符*/
            // Exp -> Exp AND Exp
            //      | Exp OR Exp
            //      | Exp RELOP Exp
            //      | Exp PLUS Exp
            //      | Exp MINUS Exp
            //      | Exp STAR Exp
            //      | Exp DIV Exp
            else 
            {
                if (p1 && p2 && (p1->kind == ARRAY || p2->kind == ARRAY)) /*指针非空且有一个类型为数组时*/
                {
                    error_print(UNMATCH_TYPE_OP, t->line, "Type mismatched for operands.");
                } 
                else if (!checkType(p1, p2)) /*类型不匹配时*/
                {
                    error_print(UNMATCH_TYPE_OP, t->line, "Type mismatched for operands.");
                } 
                else /*正常运算不报错*/
                {
                    if (p1 && p2) 
                    {
                        returnType = copyType(p1);/*返回一个类型*/
                    }
                }
            }

            if (p1) delete_type(p1);
            if (p2) delete_type(p2);/*释放内存*/
            return returnType;
        }
        /*数组和结构体访问*/
        else 
        {
            // Exp -> Exp LB Exp RB 数组访问
            if (!strcmp(t->brother->name, "LB")) 
            {
                //数组
                type p1 = Exp(t);
                type p2 = Exp(t->brother->brother);
                type returnType = NULL;

                if (!p1) 
                {
                    // do nothing here
                } 
                else if (p1 && p1->kind != ARRAY) /*非数组使用[]运算符*/
                {
                    char msg[100] = {0};
                    sprintf(msg, "\"%s\" is not an array.", t->child->mydata);
                    error_print(NOT_ARRAY, t->line, msg);
                } 
                else if (!p2 || p2->kind != BASIC || p2->u.basic != myINT) /*数组索引不为int*/
                {
                    char msg[100] = {0};
                    sprintf(msg, "\"%s\" is not an integer.",t->brother->brother->child->mydata);
                    error_print(NOT_INT_IN_ARRAY, t->line, msg);
                } 
                else /*正常返回类型*/
                {
                    returnType = copyType(p1->u.array.elem);/*返回数组的类型*/
                }
                if (p1) delete_type(p1);
                if (p2) delete_type(p2);/*释放内存*/
                return returnType;
            }
            // Exp -> Exp DOT ID 结构体访问
            else 
            {
                type p1 = Exp(t);
                type returnType = NULL;
                if (!p1 || p1->kind != STRUCTURE || !p1->u.structure.struct_name) /*对非结构体使用.运算符*/
                {
                    error_print(ABUSE_DOT, t->line, "Illegal use of \".\".");
                    if (p1) delete_type(p1);
                } 
                else /*查找域名*/
                {
                    node* ref_id = t->brother->brother;
                    fieldlist structfield = p1->u.structure.field;
                    while (structfield != NULL) 
                    {
                        if (!strcmp(structfield->name, ref_id->mydata)) 
                        {
                            break;/*找到时退出*/
                        }
                        structfield = structfield->tail;
                    }
                    if (structfield == NULL) 
                    {
                        //报错，没有可以匹配的域名
                        char msg[100] = {0};
                        // printf("ref_id->mydata是%s\n",ref_id->mydata);
                        sprintf(msg, "Non-existent filed \"%s\"",ref_id->mydata);
                        error_print(UNDEF_FIELD, t->line, msg);
                        
                    } 
                    else 
                    {
                        returnType = copyType(structfield->type);/*返回域的类型*/
                    }
                }
                if (p1) delete_type(p1);
                return returnType;
            }
        }
    }
    /*单目运算符*/
    // Exp -> MINUS Exp
    //      | NOT Exp
    else if (!strcmp(t->name, "MINUS") || !strcmp(t->name, "NOT")) 
    {
        type p1 = Exp(t->brother);
        type returnType = NULL;
        if (!p1 || p1->kind != BASIC) /*结构体和数组不能使用这两个运算*/
        {
            printf("Error type %d at Line %d: %s.\n", 7, t->line, "TYPE_MISMATCH_OP");
        } 
        else /*返回操作数的类型*/
        {
            returnType = copyType(p1);
        }
        if (p1) delete_type(p1);
        return returnType;
    } 
    else if (!strcmp(t->name, "LP")) /*带括号的就向右走一个*/
    {
        return Exp(t->brother);
    }
    // Exp -> ID LP Args RP 带参数类型的函数
    //		| ID LP RP 
    else if (!strcmp(t->name, "ID") && t->brother) 
    {
        item funcInfo = searchTableItem(mytable, t->mydata);
        if (funcInfo == NULL) /*函数名不存在*/
        {
            char msg[100] = {0};
            sprintf(msg, "Undefined function \"%s\".", t->mydata);
            error_print(UNDEF_FUN, mynode->line, msg);
            return NULL;
        } 
        else if (funcInfo->field->type->kind != FUNCTION) /*类型不是函数*/
        {
            char msg[100] = {0};
            sprintf(msg, "\"%s\" is not a function.", t->mydata);
            error_print(NOT_FUN, mynode->line, msg);
            return NULL;
        }
        // Exp -> ID LP Args RP 带参数列表的先处理参数
        else if (!strcmp(t->brother->brother->name, "Args")) 
        {
            Args(t->brother->brother, funcInfo);
            return copyType(funcInfo->field->type->u.function.re_type);
        }
        // Exp -> ID LP RP
        else /*不带参数列表的*/
        {
            if (funcInfo->field->type->u.function.argc != 0) /*如果argc不为0则报错*/
            {
                char msg[100] = {0};
                sprintf(msg,"Function \"%s\" is not applicable for your arguments. except %d arguments.",funcInfo->field->name,funcInfo->field->type->u.function.argc);
                error_print(UNMATCH_FUN_ARGV, mynode->line, msg);
            }
            return copyType(funcInfo->field->type->u.function.re_type);/*返回函数返回值的类型*/
        }
    }
    
    // Exp -> ID
    else if (!strcmp(t->name, "ID")) 
    {
        item tp = searchTableItem(mytable, t->mydata);
        // printf("t现在的行号是%d\n",t->line);
        if (tp == NULL || isStructDef(tp))  /*未命名的变量名*/
        {
            char msg[100] = {0};
            sprintf(msg, "Undefined variable \"%s\".", t->mydata);
            //TODO:调试用,打印不出正确的行号
            //printf("t->mydata的数据是%s\n",t->mydata);
            // printf("现在的行号是%d\n",t->line);
            error_print(UNDEF_VAR, mynode->line, msg);
            return NULL;
        } 
        else 
        {
            return copyType(tp->field->type);/*返回对应的类型*/
        }
    } 
    else /*只剩下基本类型*/
    {
        // Exp -> FLOAT
        if (!strcmp(t->name, "FLOAT")) 
        {
            return newType(BASIC, myFLOAT);
        }
        // Exp -> INT
        else 
        {
            return newType(BASIC, myINT);/*直接返回*/
        }
    }
}
/*语法单元Args表示实参列表，每个实参都可以变成一个表达式Exp*/
/*处理思路：遍历形参列表，依次与实参比较*/
void Args(node* mynode, item funcInfo) 
{
    // Args -> Exp COMMA Args 
    //       | Exp
    node* temp = mynode;
    fieldlist arg = funcInfo->field->type->u.function.argv;
    while (temp) 
    {
        if (arg == NULL) /*检查形参列表是否为空。如果为空，那么函数不应接受任何实参*/
        {
            char msg[100] = {0};
            sprintf(msg, "Function \"%s\" is not applicable for your arguments. except %d arguments.",funcInfo->field->name, funcInfo->field->type->u.function.argc);
            error_print(UNMATCH_FUN_ARGV, mynode->line, msg);
            break;
        }
        type realType = Exp(temp->child);/*计算实参的类型*/
        if (!checkType(realType, arg->type)) /*检查实参和形参类型是否匹配*/
        {
            char msg[100] = {0};
            sprintf(msg, "Function \"%s\" is not applicable for arguments.",funcInfo->field->name);
            error_print(UNMATCH_FUN_ARGV, mynode->line, msg);
            if (realType) delete_type(realType);
            return;
        }
        if (realType) delete_type(realType);

        arg = arg->tail;/*移动到形参列表的下一个元素*/
        if (temp->child->brother) /*如果有，移动到实参列表的下一个元素*/
        {
            temp = temp->child->brother->brother;
        } 
        else 
        {
            break;
        }
    }
    if (arg != NULL)/*如果形参列表还有剩余的元素，那么生成一个错误信息*/
    {
        char msg[100] = {0};
        sprintf(msg, "Function \"%s\" is not applicable for your arguments. except %d arguments.",funcInfo->field->name, funcInfo->field->type->u.function.argc);
        error_print(UNMATCH_FUN_ARGV, mynode->line, msg);
    }
}


/***在这里添加一个打印符号表的调试函数***/


/* 打印类型 */
void printType(type t) {
    if (t == NULL) {
        printf("NULL\n");
        return;
    }
    switch (t->kind) {
        case BASIC:
            printf("Basic Type: %s\n", t->u.basic == myINT ? "int" : "float");
            break;
        case ARRAY:
            printf("Array Type: Element Type = ");
            printType(t->u.array.elem);
            printf(", Size = %d\n", t->u.array.size);
            break;
        case STRUCTURE:
            printf("Structure Type: %s\n", t->u.structure.struct_name);
            break;
        case FUNCTION:
            printf("Function Type: Returns ");
            printType(t->u.function.re_type);
            printf(", Takes %d Arguments\n", t->u.function.argc);
            break;
    }
}

/* 打印字段列表 */
void printFieldList(fieldlist list) {
    printf("Fields:\n");
    while (list != NULL) {
        printf("  Name: %s, ", list->name);
        printType(list->type);
        list = list->tail;
    }
    printf("\n");
}

/* 打印表项 */
void printItem(item it) {
    printf("Item: Depth = %d, ", it->depth);
    printFieldList(it->field);
}

/* 打印哈希表槽 */
void printHashTableSlot(hash h, int index) {
    item current = getHashHead(h, index);
    // printf("Slot %d:\n", index);
    while (current != NULL) {
        printItem(current);
        current = current->next_hash;
    }
}

/* 打印整个符号表 */
void printSymbolTable(table t) {
    printf("Symbol Table:\n");
    printf("Global Scope:\n");
    for (int i = 0; i < HASH_SIZE; i++) {
        printHashTableSlot(t->hash_table, i);
    }

    /* 遍历栈中的所有局部作用域 */
    for (int i = 0; i <= t->table_stack->depth; i++) {
        printf("Scope Depth %d:\n", i);
        item current = getCurDepthStackHead(t->table_stack);
        while (current != NULL) {
            printItem(current);
            current = current->next_symbol;
        }
    }
}
