/*巨坑！在词法分析时没有传递relop的节点值，在实验三狠狠报错！哭哭！修了两天的bug！*/
#include "ir.h"
#define TRUE 1
#define FALSE 0
unsigned int interError = FALSE;
ir_list interCodeList;/*全局变量维护生成的中间代码*/
extern table mytable;
// Operand func
/*生成一个新的中间代码节点*/
operand createOperand(int kind, ...) 
{
    operand p = (operand)malloc(sizeof(Operand));/*申请空间*/
    assert(p != NULL);
    p->kind = kind;
    va_list vaList;
    va_start(vaList, kind);
    switch (kind) {/*根据类型生成不同的节点*/
        case OP_CONSTANT:
            p->u.value = va_arg(vaList, int);/*常量类型要单独维护数值*/
            break;
        case OP_VARIABLE:
        case OP_ADDRESS:
        case OP_LABEL:
        case OP_FUNCTION:
        case OP_RELOP:
            p->u.name = va_arg(vaList, char*);/*其他类型维护名字即可*/
            break;
    }
    return p;
}
/*更改中间代码节点*/
void setOperand(operand p, int kind, void* value) 
{
    assert(p != NULL);
    p->kind = kind;
    switch (kind) {/*根据类型修改三地址码*/
        case OP_CONSTANT:
            p->u.value = (intptr_t)value;/*由于不同的类型传入的value不同，所以传入时设置为空类型，在这里进行类型强转*/
            break;
        case OP_VARIABLE:
        case OP_ADDRESS:
        case OP_LABEL:
        case OP_FUNCTION:
        case OP_RELOP:
            if (p->u.name) free(p->u.name);
            p->u.name = (char*)value;
            break;
    }
}
/*删除一个中间代码节点*/
void deleteOperand(operand p) 
{
    if (p == NULL) return;
    switch (p->kind) {
        case OP_CONSTANT:
            break;/*常量类型的中间变量直接释放即可*/
        case OP_VARIABLE:
        case OP_ADDRESS:
        case OP_LABEL:
        case OP_FUNCTION:
        case OP_RELOP:
            if (p->u.name) {
                free(p->u.name);/*其他类型的要先释放存储名字的空间*/
                p->u.name = NULL;
            }
            break;
    }
    free(p);
}
/*打印中间代码节点*/
void printOp(FILE* fp, operand op) //打印到文件中
{
    assert(op != NULL);
    if (fp == NULL) {
        printf("未传入文件指针！\n");
        return;
    } 
    else 
    {
        switch (op->kind) /*根据类型打印中间代码*/
        {
            case OP_CONSTANT:
                fprintf(fp, "#%d", op->u.value);/*打印立即数时加上#*/
                break;
            case OP_VARIABLE:
            case OP_ADDRESS:
            case OP_LABEL:
            case OP_FUNCTION:
            case OP_RELOP:
                fprintf(fp, "%s", op->u.name);
                break;
        }
    }
}


/*新建一条中间代码*/
inter_cond createInterCode(int kind, ...)
{
    inter_cond p = (inter_cond)malloc(sizeof(InterCode));
    assert(p != NULL);
    p->kind = kind;
    va_list vaList;
    switch (kind) /*按类型进行新建*/
    {
        case IR_LABEL:
        case IR_FUNCTION:
        case IR_GOTO:
        case IR_RETURN:
        case IR_ARG:
        case IR_PARAM:
        case IR_READ:
        case IR_WRITE:
            va_start(vaList, kind);
            p->u.oneOp.op = va_arg(vaList, operand);/*标号、函数、跳转、返回、传参、读写都只需要一个节点传递*/
            break;/*放在op*/
        case IR_ASSIGN:
        case IR_GET_ADDR:
        case IR_READ_ADDR:
        case IR_WRITE_ADDR:
        case IR_CALL:
            va_start(vaList, kind);/*地址、赋值、函数调用涉及两个节点传递*/
            p->u.assign.left = va_arg(vaList, operand);/*一个左值*/
            p->u.assign.right = va_arg(vaList, operand);/*一个右值*/
            break;
        case IR_ADD:
        case IR_SUB:
        case IR_MUL:
        case IR_DIV:
            va_start(vaList, kind);/*四则运算，设计三个节点传递*/
            p->u.binOp.result = va_arg(vaList, operand);
            p->u.binOp.op1 = va_arg(vaList, operand);
            p->u.binOp.op2 = va_arg(vaList, operand);
            break;
        case IR_DEC:
            va_start(vaList, kind);/*数组、结构体定义，涉及两个节点传递*/
            p->u.dec.op = va_arg(vaList, operand);
            p->u.dec.size = va_arg(vaList, int);
            break;
        case IR_IF_GOTO:
            va_start(vaList, kind);/*跳转，设计四个参数*/
            p->u.ifGoto.x = va_arg(vaList, operand);
            p->u.ifGoto.relop = va_arg(vaList, operand);
            //TODO:relop打印为空，没有正确的从参数中读到relop
            // printf("relop是%s\n",p->u.ifGoto.relop);
            p->u.ifGoto.y = va_arg(vaList, operand);/*判断条件*/
            p->u.ifGoto.z = va_arg(vaList, operand);/*结果*/
    }
    return p;
}
/*删除一条三地址代码*/
void deleteInterCode(inter_cond p) 
{
    assert(p != NULL);
    switch (p->kind) /*不同类型的变量涉及不同的域，分别释放内存*/
    {
        case IR_LABEL:
        case IR_FUNCTION:
        case IR_GOTO:
        case IR_RETURN:
        case IR_ARG:
        case IR_PARAM:
        case IR_READ:
        case IR_WRITE:
            deleteOperand(p->u.oneOp.op);/*只设计到一个变量*/
            break;
        case IR_ASSIGN:
        case IR_GET_ADDR:
        case IR_READ_ADDR:
        case IR_WRITE_ADDR:
        case IR_CALL:
            deleteOperand(p->u.assign.left);
            deleteOperand(p->u.assign.right);/*涉及到两个变量*/
            break;
        case IR_ADD:
        case IR_SUB:
        case IR_MUL:
        case IR_DIV:
            deleteOperand(p->u.binOp.result);
            deleteOperand(p->u.binOp.op1);
            deleteOperand(p->u.binOp.op2);/*涉及三个变量*/
            break;
        case IR_DEC:
            deleteOperand(p->u.dec.op);/*涉及两个变量，但数值不需要调用函数释放*/
            break;
        case IR_IF_GOTO:
            deleteOperand(p->u.ifGoto.x);/*涉及四个*/
            deleteOperand(p->u.ifGoto.relop);
            deleteOperand(p->u.ifGoto.y);
            deleteOperand(p->u.ifGoto.z);
    }
    free(p);
}
/*打印三地址代码*/
void printInterCode(FILE* fp, ir_list interCodeList) 
{
    /*沿代码链表遍历，从头部开始，只要不为空就指向next域*/
    /*事实上不需要双向，单向在这里就够使*/
    /*使用双向链表实现的线性IR
    typedef struct _interCodes {
        inter_cond code;
        inter_conds *prev, *next;//链接前驱和后继
    } InterCodes;*/
    for (inter_conds cur = interCodeList->head; cur != NULL; cur = (inter_conds)cur->next) 
    {
        if (fp == NULL) 
        {
            printf("文件读取失败！\n");
            return;
        } 
        else 
        {
            switch (cur->code->kind) /*按每条三地址代码的类型打印*/
            {
                case IR_LABEL:/*标号语句，打印标号*/
                    fprintf(fp, "LABEL ");
                    printOp(fp, cur->code->u.oneOp.op);
                    fprintf(fp, " :");
                    break;
                case IR_FUNCTION:/*函数语句，打印函数名*/
                    fprintf(fp, "FUNCTION ");
                    printOp(fp, cur->code->u.oneOp.op);
                    fprintf(fp, " :");
                    break;
                case IR_ASSIGN:/*赋值语句，打印等号和左右两值*/
                    printOp(fp, cur->code->u.assign.left);
                    fprintf(fp, " := ");
                    printOp(fp, cur->code->u.assign.right);
                    break;
                case IR_ADD:/*四则运算*/
                    printOp(fp, cur->code->u.binOp.result);
                    fprintf(fp, " := ");
                    printOp(fp, cur->code->u.binOp.op1);
                    fprintf(fp, " + ");
                    printOp(fp, cur->code->u.binOp.op2);
                    break;
                case IR_SUB:
                    printOp(fp, cur->code->u.binOp.result);
                    fprintf(fp, " := ");
                    printOp(fp, cur->code->u.binOp.op1);
                    fprintf(fp, " - ");
                    printOp(fp, cur->code->u.binOp.op2);
                    break;
                case IR_MUL:
                    printOp(fp, cur->code->u.binOp.result);
                    fprintf(fp, " := ");
                    printOp(fp, cur->code->u.binOp.op1);
                    fprintf(fp, " * ");
                    printOp(fp, cur->code->u.binOp.op2);
                    break;
                case IR_DIV:
                    printOp(fp, cur->code->u.binOp.result);
                    fprintf(fp, " := ");
                    printOp(fp, cur->code->u.binOp.op1);
                    fprintf(fp, " / ");
                    printOp(fp, cur->code->u.binOp.op2);
                    break;
                case IR_GET_ADDR:/*地址操作语句*/
                    printOp(fp, cur->code->u.assign.left);
                    fprintf(fp, " := &");
                    printOp(fp, cur->code->u.assign.right);
                    break;
                case IR_READ_ADDR:
                    printOp(fp, cur->code->u.assign.left);
                    fprintf(fp, " := *");
                    printOp(fp, cur->code->u.assign.right);
                    break;
                case IR_WRITE_ADDR:
                    fprintf(fp, "*");
                    printOp(fp, cur->code->u.assign.left);
                    fprintf(fp, " := ");
                    printOp(fp, cur->code->u.assign.right);
                    break;
                case IR_GOTO:/*跳转语句，打印goto和跳转的标号*/
                    fprintf(fp, "GOTO ");
                    printOp(fp, cur->code->u.oneOp.op);
                    break;
                case IR_IF_GOTO:/*if语句，打印判断条件和goto语句*/
                    fprintf(fp, "IF ");
                    printOp(fp, cur->code->u.ifGoto.x);
                    fprintf(fp, " ");
                    printOp(fp, cur->code->u.ifGoto.relop);
                    fprintf(fp, " ");
                    printOp(fp, cur->code->u.ifGoto.y);
                    fprintf(fp, " GOTO ");
                    printOp(fp, cur->code->u.ifGoto.z);
                    break;
                case IR_RETURN:/*返回语句*/
                    fprintf(fp, "RETURN ");
                    printOp(fp, cur->code->u.oneOp.op);
                    break;
                case IR_DEC:/*数组、结构体*/
                    fprintf(fp, "DEC ");
                    printOp(fp, cur->code->u.dec.op);
                    fprintf(fp, " ");
                    fprintf(fp, "%d", cur->code->u.dec.size);/*按大小访问各个域*/
                    break;
                case IR_ARG:
                    fprintf(fp, "ARG ");
                    printOp(fp, cur->code->u.oneOp.op);
                    break;
                case IR_CALL:/*函数调用*/
                    printOp(fp, cur->code->u.assign.left);
                    fprintf(fp, " := CALL ");
                    printOp(fp, cur->code->u.assign.right);
                    break;
                case IR_PARAM:/*传递实参*/
                    fprintf(fp, "PARAM ");
                    printOp(fp, cur->code->u.oneOp.op);
                    break;
                case IR_READ:/*读、写*/
                    fprintf(fp, "READ ");
                    printOp(fp, cur->code->u.oneOp.op);
                    break;
                case IR_WRITE:
                    fprintf(fp, "WRITE ");
                    printOp(fp, cur->code->u.oneOp.op);
                    break;
            }
            fprintf(fp, "\n");/*小细节，打印回车*/
        }
    }
}

// InterCodes func
/*创建新的代码块*/
inter_conds createInterCodes(inter_cond code) 
{
    inter_conds p = (inter_conds)malloc(sizeof(InterCodes));
    assert(p != NULL);
    p->code = code;
    p->prev = NULL;
    p->next = NULL;
}
/*删除代码列表*/
void deleteInterCodes(inter_conds p) 
{
    assert(p != NULL);
    deleteInterCode(p->code);
    free(p);
}
/*新建一个参数*/
// Arg and ArgList func
argv createArg(operand op) 
{
    argv p = (argv)malloc(sizeof(Arg));
    assert(p != NULL);
    p->op = op;
    p->next = NULL;
}
/*新建一个参数列表*/
arg_list createArgList() 
{
    arg_list p = (arg_list)malloc(sizeof(ArgList));
    assert(p != NULL);
    p->head = NULL;
    p->cur = NULL;
}
/*删除参数*/
void deleteArg(argv p) 
{
    assert(p != NULL);
    deleteOperand(p->op);
    free(p);
}
/*删除参数列表*/
void deleteArgList(arg_list p) 
{
    assert(p != NULL);
    argv q = p->head;
    while (q) {
        argv temp = q;
        q = q->next;
        deleteArg(temp);
    }
    free(p);
}
/*向参数列表中添加一个参数*/
void addArg(arg_list argList, argv arg) 
{
    if (argList->head == NULL) {
        argList->head = arg;
        argList->cur = arg;
    } else {
        argList->cur->next = arg;
        argList->cur = arg;
    }
}
/*中间代码列表，维护标号信息
typedef struct _interCodeList {
    inter_conds head;
    inter_conds cur;//维护双向链表的信息
    char* lastArrayName;  //维护结构体数组信息
    int tempVarNum;//当前变量数
    int labelNum;//标号数
} InterCodeList;*/
/*新建中间代码列表*/
ir_list createInterCodeList() 
{
    ir_list p = (ir_list)malloc(sizeof(InterCodeList));
    p->head = NULL;
    p->cur = NULL;
    p->lastArrayName = NULL;
    p->tempVarNum = 1;
    p->labelNum = 1;/*起始标号和局部变量数量都置1*/
}
/*删除中间代码列表*/
void deleteInterCodeList(ir_list p) 
{
    assert(p != NULL);
    inter_conds q = p->head;
    while (q) 
    {
        inter_conds temp = q;
        q = (inter_conds)q->next;
        deleteInterCodes(temp);
    }
    free(p);
}
/*添加一条中间代码*/
void addInterCode(ir_list interCodeList, inter_conds newCode) 
{
    if (interCodeList->head == NULL) /*当前列表中为空时*/
    {
        interCodeList->head = newCode;
        interCodeList->cur = newCode;/*把头和当前都置为这个中间代码*/
    } 
    else {/*否则更新前驱、后继和当前指向的中间代码*/
        interCodeList->cur->next = (inter_conds*)newCode;
        newCode->prev = (inter_conds*)interCodeList->cur;
        interCodeList->cur = newCode;
    }
}

// traverse func
/*新建一个局部变量*/
operand newTemp() 
{
    char tName[10] = {0};
    sprintf(tName, "t%d", interCodeList->tempVarNum);/*维护局部变量的脚标*/
    interCodeList->tempVarNum++;
    operand temp = createOperand(OP_VARIABLE, newString(tName));
    return temp;
}
/*新建一个标号*/
operand newLabel() 
{
    char lName[10] = {0};
    sprintf(lName, "label%d", interCodeList->labelNum);
    interCodeList->labelNum++;/*维护标号*/
    operand temp = createOperand(OP_LABEL, newString(lName));
    return temp;
}
/*获取数据的大小*/
int getSize(Type_* type) 
{
    if (type == NULL)
        return 0;
    else if (type->kind == BASIC)/*基本类型*/
        return 4;
    else if (type->kind == ARRAY)/*数组类型是维度*基本类型*/
        return type->u.array.size * getSize(type->u.array.elem);
    else if (type->kind == STRUCTURE) /*结构体大小是每个域大小的累加*/
    {
        int size = 0;
        fieldlist temp = type->u.structure.field;
        while (temp) /*遍历每个域*/
        {
            size += getSize(temp->type);/*累加大小*/
            temp = temp->tail;
        }
        return size;
    }
    return 0;
}
/*生成中间代码块*/
/*最宏观的调用、中间代码生成的起点*/
void genInterCodes(node* node) 
{
    if (node == NULL) return;
    if (!strcmp(node->name, "ExtDefList"))
        translateExtDefList(node);
    else 
    {
        genInterCodes(node->child);
        genInterCodes(node->brother);
    }
}
/*生成每一条三地址码*/
/*这里是中间代码生成的核心函数，要耐心*/
/*对于单一节点语句：标号、函数、返回、跳转、形参、实参、读写------生成*/
/*对于赋值、地址、函数调用------先将右值赋给临时变量，先将右值赋给临时变量*/
/*四则运算-----读三个参数，生成*/
/*数组、结构体-----按大小遍历，为每个域生成*/
/*if语句，读入四个变量*/
void genInterCode(int kind, ...) 
{
    va_list vaList;
    operand temp = NULL;
    operand result = NULL, op1 = NULL, op2 = NULL, relop = NULL;
    int size = 0;
    inter_conds newCode = NULL;/*为临时变量初始化*/
    switch (kind) /*按类型为每条三地址码生成*/
    {
        case IR_LABEL:
        case IR_FUNCTION:
        case IR_GOTO:
        case IR_RETURN:
        case IR_ARG:
        case IR_PARAM:
        case IR_READ:
        case IR_WRITE:
            va_start(vaList, kind);/*单一参数的三地址操作*/
            op1 = va_arg(vaList, operand);
            if (op1->kind == OP_ADDRESS) /*如果是地址操作*/
            {
                temp = newTemp();
                genInterCode(IR_READ_ADDR, temp, op1);/*将地址读入到中间变量中*/
                op1 = temp;/*用这个中间变量生成三地址码*/
            }
            newCode = createInterCodes(createInterCode(kind, op1));
            addInterCode(interCodeList, newCode);/*生成并添加这条三地址码*/
            break;
        case IR_ASSIGN:
        case IR_GET_ADDR:
        case IR_READ_ADDR:
        case IR_WRITE_ADDR:
        case IR_CALL:
            va_start(vaList, kind);/*左右两值的赋值操作*/
            op1 = va_arg(vaList, operand);
            op2 = va_arg(vaList, operand);
            if (kind == IR_ASSIGN &&(op1->kind == OP_ADDRESS || op2->kind == OP_ADDRESS)) /*赋值或地址操作*/
            {
                if (op1->kind == OP_ADDRESS && op2->kind != OP_ADDRESS)
                    genInterCode(IR_WRITE_ADDR, op1, op2);/*左值是地址，说明是向地址写入*/
                else if (op2->kind == OP_ADDRESS && op1->kind != OP_ADDRESS)
                    genInterCode(IR_READ_ADDR, op1, op2);/*右值是地址，说明是从地址中读出*/
                else/*否则是赋值操作*/ 
                {
                    temp = newTemp();
                    genInterCode(IR_READ_ADDR, temp, op2);/*先将右值赋给临时变量*/
                    genInterCode(IR_WRITE_ADDR, op1, temp);/*先将右值赋给临时变量*/
                }
            } 
            else /*函数调用或其他*/
            {
                newCode = createInterCodes(createInterCode(kind, op1, op2));
                addInterCode(interCodeList, newCode);
            }
            break;
        case IR_ADD:
        case IR_SUB:
        case IR_MUL:
        case IR_DIV:
            va_start(vaList, kind);/*四则运算，读三个参数*/
            result = va_arg(vaList, operand);
            op1 = va_arg(vaList, operand);
            op2 = va_arg(vaList, operand);
            if (op1->kind == OP_ADDRESS) 
            {
                temp = newTemp();
                genInterCode(IR_READ_ADDR, temp, op1);
                op1 = temp;
            }
            if (op2->kind == OP_ADDRESS) 
            {
                temp = newTemp();
                genInterCode(IR_READ_ADDR, temp, op2);
                op2 = temp;
            }/*任何一个操作数涉及到地址都要用临时变量将其读出来*/
            newCode = createInterCodes(createInterCode(kind, result, op1, op2));
            addInterCode(interCodeList, newCode);
            break;
        case IR_DEC:
            va_start(vaList, kind);/*数组、结构体*/
            op1 = va_arg(vaList, operand);
            size = va_arg(vaList, int);
            newCode = createInterCodes(createInterCode(kind, op1, size));/*按大小遍历，为每个域生成*/
            addInterCode(interCodeList, newCode);
            break;
        case IR_IF_GOTO:/*if语句，读入四个变量*/
            va_start(vaList, kind);
            result = va_arg(vaList, operand);
            relop = va_arg(vaList, operand);
            op1 = va_arg(vaList, operand);
            op2 = va_arg(vaList, operand);
            newCode =createInterCodes(createInterCode(kind, result, relop, op1, op2));
            addInterCode(interCodeList, newCode);
            break;
    }
}
/*******下面进入翻译******/
/*每个Program可以产生一个ExtDefList，这里的ExtDefList表示零个或多个ExtDef。
每个ExtDef表示一个全局变量、结构体或函数的定义。*/
    // ExtDefList -> ExtDef ExtDefList
    //             | e
void translateExtDefList(node* node) 
{
    while (node) 
    {
        translateExtDef(node->child);/*遍历变量列表，逐个翻译*/
        node = node->child->brother;
    }
}
/*每个ExtDef表示一个全局变量、结构体或函数的定义。*/
    // ExtDef -> Specifier ExtDecList SEMI
    //         | Specifier SEMI
    //         | Specifier FunDec CompSt
void translateExtDef(node* node) 
{
    assert(node != NULL);
    if (interError) return;
    /*事实上只需要处理函数声明*/
    if (!strcmp(node->child->brother->name, "FunDec")) 
    {
        translateFunDec(node->child->brother);/*分别翻译函数声明和花括号*/
        translateCompSt(node->child->brother->brother);
    }
}
/*FunDec表示对一个函数头的定义。它包括一个表示函数名的标识符以及由一对圆括号括起来的一个形参列表，
该列表由VarList表示（也可以为空）。
VarList包括一个或多个ParamDec，其中每个ParamDec都是对一个形参的定义，
该定义由类型描述符Specifier和变量定义VarDec组成。
例如一个完整的函数头为：foo(int x, float y[10])。*/
    // FunDec -> ID LP VarList RP
    //         | ID LP RP
void translateFunDec(node* node) 
{
    assert(node != NULL);
    if (interError) return;

    genInterCode(IR_FUNCTION,createOperand(OP_FUNCTION, newString(node->child->mydata)));/*首先翻译函数名*/
    Item* funcItem = searchTableItem(mytable, node->child->mydata);/*在符号表中查函数*/
    fieldlist temp = funcItem->field->type->u.function.argv;/*找到函数的参数列表*/
    while (temp) /*遍历函数的每一个形参，分别为他们生成中间代码*/
    {
        genInterCode(IR_PARAM, createOperand(OP_VARIABLE, newString(temp->name)));
        temp = temp->tail;
    }
}
/*/*CompSt表示一个由一对花括号括起来的语句块。该语句块内部先是一系列的变量定义DefList，
然后是一系列的语句StmtList。
可以发现，对CompSt这样的定义，是不允许在程序的任意位置定义变量的，必须在每一个语句块的开头才可以定义。*/
    // CompSt -> LC DefList StmtList RC
void translateCompSt(Node* node) 
{
    assert(node != NULL);
    if (interError) return;
    Node* temp = node->child->brother;/*观察花括号后第一个token*/
    if (!strcmp(temp->name, "DefList")) /*定义列表*/
    {
        translateDefList(temp);/*按定义列表翻译*/
        temp = temp->brother;
    }
    if (!strcmp(temp->name, "StmtList")) /*分号*/
    {
        translateStmtList(temp);/*按分号翻译*/
    }
}
/*出现在CompSt以及StructSpecifier产生式的右边，它就是
一串像int a; float b, c; int d[10];这样的变量定义。一个DefList可以由零个或者多个Def组成*/
    // DefList -> Def DefList
    //          | e
void translateDefList(Node* node) 
{
    if (interError) return;

    while (node) /*遍历节点，分别翻译*/
    {
        translateDef(node->child);
        node = node->child->brother;
    }
}
/*变量列表只有一个变量*/
// Def -> Specifier DecList SEMI
void translateDef(Node* node) 
{
    assert(node != NULL);
    if (interError) return;

    translateDecList(node->child->brother);
}
/*每个Def就是一条变量定义，它包括一个类型描述符Specifier以及一个DecList，例如
int a, b, c;。由于DecList中的每个Dec又可以变成VarDec ASSIGNOP Exp，这允许我们对局部
变量在定义时进行初始化，例如int a = 5;*/
    // DecList -> Dec
    //          | Dec COMMA DecList
void translateDecList(Node* node) 
{
    assert(node != NULL);
    if (interError) return;
    Node* temp = node;
    while (temp) /*遍历各个变量*/
    {
        translateDec(temp->child);
        if (temp->child->brother)
            temp = temp->child->brother->brother;/*逐个翻译，注意第一个兄弟是分号*/
        else
            break;
    }
}
/*每个Dec又可以变成VarDec ASSIGNOP Exp，这允许我们对局部
变量在定义时进行初始化，例如int a = 5;*/
    // Dec -> VarDec
    //      | VarDec ASSIGNOP Exp

void translateDec(Node* node) 
{
    assert(node != NULL);
    if (interError) return;

    if (node->child->brother == NULL)  // Dec -> VarDec变出一个变量
    {
        translateVarDec(node->child, NULL);
    }
    // Dec -> VarDec ASSIGNOP Exp 定义时初始化
    else 
    {
        operand t1 = newTemp();
        translateVarDec(node->child, t1);
        operand t2 = newTemp();
        translateExp(node->child->brother->brother, t2);/*分别为变量和初始化的表达式生成中间变量*/
        genInterCode(IR_ASSIGN, t1, t2);/*做一次赋值*/
    }
}
    // VarDec -> ID
    //         | VarDec LB INT RB
void translateVarDec(Node* node, operand place) 
{
    assert(node != NULL);
    if (interError) return;
    if (!strcmp(node->child->name, "ID")) 
    {
        item temp = searchTableItem(mytable, node->child->mydata);//在符号表中搜索ID
        /*TODO:发生段错误，访问越界，疑似未找到*/
        //解决：在语义分析时，把函数的局部变量删掉了，所以找不到
        assert(temp);
        Type_* type = temp->field->type;//获得ID的类型
        if (type->kind == BASIC) 
        {
            if (place) 
            {
                interCodeList->tempVarNum--;
                setOperand(place, OP_VARIABLE, (void*)newString(temp->field->name));
            }
        } 
        else if (type->kind == ARRAY) 
        {
            // 3.2选做
            if (type->u.array.elem->kind == ARRAY) /*遇到高维数组就报错*/
            {
                interError = TRUE;
                printf("Cannot translate: Code contains variables of multi-dimensional array type or parameters of array type.\n");
                return;
            } 
            else //否则按dec类型生成代码，注意添加大小
            {
                genInterCode(IR_DEC,createOperand(OP_VARIABLE, newString(temp->field->name)),getSize(type));
            }
        } 
        else if (type->kind == STRUCTURE) /*遇到结构体就报错*/
        {
            // 3.1选做
                interError = TRUE;
                printf("Cannot translate: Code contains variables or parameters of structure type.\n");
                return;
        }
    } 
    else //VarDec ->VarDec LB INT RB
    {
        translateVarDec(node->child, place);//递归调用
    }
}
/*StmtList就是零个或多个Stmt的组合。
每个Stmt都表示一条语句，该语句可以是一个在末尾添了分号的表达式（Exp SEMI），
可以是另一个语句块（CompSt），
可以是一条返回语句（RETURN Exp SEMI），
可以是一条if语句（IF LP Exp RP Stmt），
可以是一条if-else语句（IF LP Exp RP Stmt ELSE Stmt），
也可以是一条while语句（WHILE LP Exp RP Stmt）*/
    // StmtList -> Stmt StmtList
    //           | e
void translateStmtList(Node* node) 
{
    if (interError) return;
    while (node) 
    {
        translateStmt(node->child);/*逐个语句块翻译，以逗号分割*/
        node = node->child->brother;
    }
}
/*每个Stmt都表示一条语句，该语句可以是一个在末尾添了分号的表达式（Exp SEMI），
可以是另一个语句块（CompSt），
可以是一条返回语句（RETURN Exp SEMI），
可以是一条if语句（IF LP Exp RP Stmt），
可以是一条if-else语句（IF LP Exp RP Stmt ELSE Stmt），
也可以是一条while语句（WHILE LP Exp RP Stmt）*/
    // Stmt -> Exp SEMI
    //       | CompSt
    //       | RETURN Exp SEMI
    //       | IF LP Exp RP Stmt
    //       | IF LP Exp RP Stmt ELSE Stmt
    //       | WHILE LP Exp RP Stmt

/*翻译语句*/
void translateStmt(Node* node) 
{
    assert(node != NULL);
    if (interError) return;


    if (!strcmp(node->child->name, "Exp")) // Stmt -> Exp SEMI
    {
        translateExp(node->child, NULL);/*调用翻译EXP*/
    }

    
    else if (!strcmp(node->child->name, "CompSt")) // Stmt -> CompSt
    {
        translateCompSt(node->child);/*调用翻译语句块*/
    }

    
    else if (!strcmp(node->child->name, "RETURN")) // Stmt -> RETURN Exp SEMI
    {
        operand t1 = newTemp();
        translateExp(node->child->brother, t1);/*为return的表达式生成局部变量、翻译*/
        genInterCode(IR_RETURN, t1);/*添加语句*/
    }

    
    else if (!strcmp(node->child->name, "IF")) // Stmt -> IF LP Exp RP Stmt
    {
        Node* exp = node->child->brother->brother;/*布尔表达式*/
        Node* stmt = exp->brother->brother;/*真执行语句*/
        operand label1 = newLabel();
        operand label2 = newLabel();/*为真假出口设置标号*/

        translateCond(exp, label1, label2);/*翻译布尔表达式，设置真假出口*/
        genInterCode(IR_LABEL, label1);/*为真出口生成三地址码*/
        translateStmt(stmt);/*翻译真执行语句*/
        if (stmt->brother == NULL) /*没有else语句*/
        {
            genInterCode(IR_LABEL, label2);/*添加对应的代码，注意此时生成假出口代码*/
        }
        
        else // Stmt -> IF LP Exp RP Stmt ELSE Stmt
        {
            operand label3 = newLabel();/*为真出口语句添加新的语句，无条件跳转*/
            genInterCode(IR_GOTO, label3);/*生成真出口代码*/
            genInterCode(IR_LABEL, label2);/*生成假出口代码*/
            translateStmt(stmt->brother->brother);/*翻译无条件跳转*/
            genInterCode(IR_LABEL, label3);/*生成出口代码*/
        }

    }

    
    else if (!strcmp(node->child->name, "WHILE")) // Stmt -> WHILE LP Exp RP Stmt
    {
        /*while语句设计的不多*/
        operand label1 = newLabel();/*循环开始的位置*/
        operand label2 = newLabel();/*继续循环*/
        operand label3 = newLabel();/*循环出口*/
        genInterCode(IR_LABEL, label1);/*为循环开始生成标号*/
        translateCond(node->child->brother->brother, label2, label3);/*设置布尔表达式的真假出口*/
        genInterCode(IR_LABEL, label2);/*真出口，继续循环*/
        translateStmt(node->child->brother->brother->brother->brother);/*翻译语句*/
        genInterCode(IR_GOTO, label1);/*返回到循环开始*/
        genInterCode(IR_LABEL, label3);/*循环结束*/
    }
}
    // Exp -> Exp ASSIGNOP Exp
    //      | Exp AND Exp
    //      | Exp OR Exp
    //      | Exp RELOP Exp
    //      | Exp PLUS Exp
    //      | Exp MINUS Exp
    //      | Exp STAR Exp
    //      | Exp DIV Exp

    //      | MINUS Exp
    //      | NOT Exp
    //      | ID LP Args RP
    //      | ID LP RP
    //      | Exp LB Exp RB
    //      | Exp DOT ID
    //      | ID
    //      | INT
    //      | FLOAT
void translateExp(Node* node, operand place) 
{
    assert(node != NULL);
    if (interError) return;
    // Exp -> LP Exp RP
    if (!strcmp(node->child->name, "LP"))
        translateExp(node->child->brother, place);/*读到左括号，向右读一个*/

    else if (!strcmp(node->child->name, "Exp") ||!strcmp(node->child->name, "NOT")) 
    {
        // 条件表达式 和 基本表达式
        if (strcmp(node->child->brother->name, "LB") &&strcmp(node->child->brother->name, "DOT")) {
            // Exp -> Exp AND Exp
            //      | Exp OR Exp
            //      | Exp RELOP Exp
            //      | NOT Exp
            /*布尔表达式的判断*/
            if (!strcmp(node->child->brother->name, "AND") ||!strcmp(node->child->brother->name, "OR") ||!strcmp(node->child->brother->name, "RELOP") ||!strcmp(node->child->name, "NOT")) {
                operand label1 = newLabel();
                operand label2 = newLabel();/*设置真假出口*/
                operand true_num = createOperand(OP_CONSTANT, 1);
                operand false_num = createOperand(OP_CONSTANT, 0);/*真跳转时返回值为1，否则为0*/
                genInterCode(IR_ASSIGN, place, false_num);/*生成标志位赋值语句，即开始时默认为假*/
                translateCond(node, label1, label2);/*翻译布尔表达式*/
                genInterCode(IR_LABEL, label1);/*生成真跳转语句*/
                genInterCode(IR_ASSIGN, place, true_num);/*生成标志位赋值语句*/
            } 
            else /*赋值操作、四则运算*/
            {
                // Exp -> Exp ASSIGNOP Exp
                if (!strcmp(node->child->brother->name, "ASSIGNOP")) /*赋值操作*/
                {
                    operand t2 = newTemp();
                    translateExp(node->child->brother->brother, t2);
                    operand t1 = newTemp();
                    translateExp(node->child, t1);/*为左右两值生成临时变量*/
                    genInterCode(IR_ASSIGN, t1, t2);/*生成赋值语句*/
                } 
                else /*四则运算*/
                {
                    operand t1 = newTemp();
                    translateExp(node->child, t1);
                    operand t2 = newTemp();
                    translateExp(node->child->brother->brother, t2);
                    // Exp -> Exp PLUS Exp
                    if (!strcmp(node->child->brother->name, "PLUS")) {
                        genInterCode(IR_ADD, place, t1, t2);
                    }
                    // Exp -> Exp MINUS Exp
                    else if (!strcmp(node->child->brother->name, "MINUS")) {
                        genInterCode(IR_SUB, place, t1, t2);
                    }
                    // Exp -> Exp STAR Exp
                    else if (!strcmp(node->child->brother->name, "STAR")) {
                        genInterCode(IR_MUL, place, t1, t2);
                    }
                    // Exp -> Exp DIV Exp
                    else if (!strcmp(node->child->brother->name, "DIV")) {
                        genInterCode(IR_DIV, place, t1, t2);
                    }
                }
            }

        }
        // 数组和结构体访问
        else {
            // Exp -> Exp LB Exp RB
            if (!strcmp(node->child->brother->name, "LB")) 
            {
                //数组
                if (node->child->child->brother && !strcmp(node->child->child->brother->mydata, "LB")) 
                {
                    //多维数组，报错
                    interError = TRUE;
                    printf("Cannot translate: Code containsvariables of multi-dimensional array type or parameters of array type.\n");
                    return;
                } 
                else /*一维简单数组*/
                {
                    operand idx = newTemp();//为索引生成局部变量
                    translateExp(node->child->brother->brother, idx);
                    operand base = newTemp();//为基址生成局部变量
                    translateExp(node->child, base);
                    operand width;//计算数组宽度
                    operand offset = newTemp();//计算偏移量
                    operand target;//获得目标值
                    Item* item = searchTableItem(mytable, base->u.name);//查表，确定类型
                    assert(item->field->type->kind == ARRAY);
                    width = createOperand(OP_CONSTANT, getSize(item->field->type->u.array.elem));//计算宽度
                    genInterCode(IR_MUL, offset, idx, width);//生成地址
                    if (base->kind == OP_VARIABLE) 
                    {
                        target = newTemp();
                        genInterCode(IR_GET_ADDR, target, base);//生成局部变量，存储
                    } 
                    else {
                        target = base;//结构体内
                    }
                    genInterCode(IR_ADD, place, target, offset);//生成数组计算代码
                    place->kind = OP_ADDRESS;//更改place的类型
                    interCodeList->lastArrayName = base->u.name;
                }
            }
            // // Exp -> Exp DOT ID
            // else 
            // {
            //     //结构体
            //     operand temp = newTemp();
            //     translateExp(node->child, temp);
            //     // 两种情况，Exp直接为一个变量，则需要先取址，
            //     //若Exp为数组或者多层结构体访问或结构体形参，则target会被填成地址，可以直接用。
            //     operand target;
            //     if (temp->kind == OP_ADDRESS) 
            //     {
            //         target = createOperand(temp->kind, temp->u.name);//直接用
            //     } 
            //     else 
            //     {
            //         target = newTemp();
            //         genInterCode(IR_GET_ADDR, target, temp);//取地址
            //     }

            //     operand id = createOperand(OP_VARIABLE, newString(node->child->brother->brother->mydata));//为索引生成新的代码
            //     int offset = 0;
            //     Item* item = searchTableItem(mytable, temp->u.name);
            //     //结构体数组，temp是临时变量，查不到表，需要用处理数组时候记录下的数组名来查表
            //     if (item == NULL) 
            //     {
            //         item = searchTableItem(mytable, interCodeList->lastArrayName);
            //     }

            //     fieldlist tmp;
            //     // 结构体数组 eg: a[5].b
            //     if (item->field->type->kind == ARRAY) 
            //     {
            //         tmp = item->field->type->u.array.elem->u.structure.field;
            //     }
            //     // 一般结构体
            //     else 
            //     {
            //         tmp = item->field->type->u.structure.field;
            //     }
            //     // 遍历获得offset
            //     while (tmp) 
            //     {
            //         if (!strcmp(tmp->name, id->u.name)) break;
            //         offset += getSize(tmp->type);
            //         tmp = tmp->tail;
            //     }

            //     operand tOffset = createOperand(OP_CONSTANT, offset);
            //     if (place) 
            //     {
            //         genInterCode(IR_ADD, place, target, tOffset);//place不为空时将id存入place中
            //         // 为了处理结构体里的数组把id名通过place回传给上层
            //         setOperand(place, OP_ADDRESS, (void*)newString(id->u.name));
            //     }
            // }
        }
    }
    //单目运算符
    // Exp -> MINUS Exp
    else if (!strcmp(node->child->name, "MINUS")) 
    {
        operand t1 = newTemp();
        translateExp(node->child->brother, t1);
        operand zero = createOperand(OP_CONSTANT, 0);
        genInterCode(IR_SUB, place, zero, t1);//生成一个立即数0，转为减法
    }
    //  Exp -> NOT Exp
    else if (!strcmp(node->child->name, "NOT")) 
    {
        operand label1 = newLabel();
        operand label2 = newLabel();//生成真假跳转出口
        operand true_num = createOperand(OP_CONSTANT, 1);
        operand false_num = createOperand(OP_CONSTANT, 0);//真设置为1，假设置为0
        genInterCode(IR_ASSIGN, place, false_num);//首先将place设置为假
        translateCond(node, label1, label2);//翻译not后的布尔表达式
        genInterCode(IR_LABEL, label1);
        genInterCode(IR_ASSIGN, place, true_num);//调转真假出口
    }
    // Exp -> ID LP Args RP
    //		| ID LP RP
    else if (!strcmp(node->child->name, "ID") && node->child->brother) 
    {
        operand funcTemp = createOperand(OP_FUNCTION, newString(node->child->mydata));
        // Exp -> ID LP Args RP 有参数的函数
        if (!strcmp(node->child->brother->brother->name, "Args")) 
        {
            arg_list argList = createArgList();//维护参数列表
            translateArgs(node->child->brother->brother, argList);
            if (!strcmp(node->child->mydata, "write")) 
            {
                genInterCode(IR_WRITE, argList->head->op);
            } 
            else 
            {
                argv argTemp = argList->head;
                while (argTemp) //遍历参数列表
                {
                    // if (argTemp->op == OP_VARIABLE) {
                    //     Item* item = searchTableItem(mytable, argTemp->op->u.name);

                    //     // 结构体作为参数需要传址
                    //     if (item && item->field->type->kind == STRUCTURE) 
                    //     {
                    //         operand varTemp = newTemp();
                    //         genInterCode(IR_GET_ADDR, varTemp, argTemp->op);
                    //         operand varTempCopy =
                    //             createOperand(OP_ADDRESS, varTemp->u.name);
                    //         // varTempCopy->isAddr = TRUE;
                    //         genInterCode(IR_ARG, varTempCopy);
                    //     }
                    // }
                    // // 一般参数直接传值
                    // else {
                        genInterCode(IR_ARG, argTemp->op);
                    // }
                    argTemp = argTemp->next;
                }
                if (place) 
                {
                    genInterCode(IR_CALL, place, funcTemp);//上层调用提供place则使用
                } 
                else 
                {
                    operand temp = newTemp();
                    genInterCode(IR_CALL, temp, funcTemp);//否则创建新的中间变量节点存储
                }
            }
        }
        // Exp -> ID LP RP没有参数的函数调用
        else 
        {
            if (!strcmp(node->child->mydata, "read")) 
            {
                genInterCode(IR_READ, place);//read函数单独处理
            } 
            else 
            {
                if (place) 
                {
                    genInterCode(IR_CALL, place, funcTemp);//place不为空时，将中间代码放在place中
                } 
                else 
                {
                    operand temp = newTemp();
                    genInterCode(IR_CALL, temp, funcTemp);//否则创建一个新的临时节点存放中间代码
                }
            }
        }
    }
    // Exp -> ID
    else if (!strcmp(node->child->name, "ID")) {
        Item* item = searchTableItem(mytable, node->child->mydata);
        //TODO:在查找item时访问越界，此时返回的item为空
        assert(item);
        // 根据讲义，因为结构体不允许赋值，结构体做形参时是传址的方式
        interCodeList->tempVarNum--;
        if (item->field->isArg && item->field->type->kind == STRUCTURE) 
        {
            setOperand(place, OP_ADDRESS, (void*)newString(node->child->mydata));
        }
        // 非结构体参数情况都当做变量处理
        else {
            setOperand(place, OP_VARIABLE, (void*)newString(node->child->mydata));
        }

    }
     else 
     {
        // // Exp -> FLOAT
        // 无浮点数常数
        if (!strcmp(node->child->name, "FLOAT")) {
            operand t1 = createOperand(OP_CONSTANT, node->child->mydata);
            genInterCode(IR_ASSIGN, place, t1);
        }
        // Exp -> INT
        interCodeList->tempVarNum--;
        setOperand(place, OP_CONSTANT, (void*)(intptr_t)atoi(node->child->mydata));
    }
}
    // Exp -> Exp AND Exp
    //      | Exp OR Exp
    //      | Exp RELOP Exp
    //      | NOT Exp
    /*翻译布尔表达式*/
void translateCond(Node* node, operand labelTrue, operand labelFalse) {
    assert(node != NULL);
    if (interError) return;
    // Exp -> NOT Exp
    if (!strcmp(node->child->name, "NOT")) 
    {
        translateCond(node->child->brother, labelFalse, labelTrue);/*假出口为真，真出口为假*/
    }
    // Exp -> Exp RELOP Exp
    else if (!strcmp(node->child->brother->name, "RELOP")) 
    {
        operand t1 = newTemp();
        operand t2 = newTemp();
        translateExp(node->child, t1);
        translateExp(node->child->brother->brother, t2);/*为左右两值生成临时变量*/
        operand relop = createOperand(OP_RELOP, newString(node->child->brother->mydata));/*为relop创立节点*/
        //其中一个是地址访问
        if (t1->kind == OP_ADDRESS) 
        {
            operand temp = newTemp();
            genInterCode(IR_READ_ADDR, temp, t1);
            t1 = temp;
        }
        if (t2->kind == OP_ADDRESS) 
        {
            operand temp = newTemp();
            genInterCode(IR_READ_ADDR, temp, t2);
            t2 = temp;
        }
        //没有地址访问
        genInterCode(IR_IF_GOTO, t1, relop, t2, labelTrue);//为真出口生成语句
        genInterCode(IR_GOTO, labelFalse);//生成假出口的跳转语句
    }
    // Exp -> Exp AND Exp
    else if (!strcmp(node->child->brother->name, "AND")) 
    {
        operand label1 = newLabel();//真出口只用设置一个
        translateCond(node->child, label1, labelFalse);//第一个表达式为真时继续
        genInterCode(IR_LABEL, label1);//第一个表达式为假时直接跳转到假出口
        translateCond(node->child->brother->brother, labelTrue, labelFalse);//判断第二个表达式
    }
    // Exp -> Exp OR Exp
    else if (!strcmp(node->child->brother->name, "OR")) 
    {
        operand label1 = newLabel();//假出口只用设置一个
        translateCond(node->child, labelTrue, label1);//为真时直接跳出去
        genInterCode(IR_LABEL, label1);//第一个为假时继续判断
        translateCond(node->child->brother->brother, labelTrue, labelFalse);
    }
    // other cases
    else //常量、不等于
    {
        operand t1 = newTemp();
        translateExp(node, t1);
        operand t2 = createOperand(OP_CONSTANT, 0);
        operand relop = createOperand(OP_RELOP, newString("!="));//生成局部变量和relop

        if (t1->kind == OP_ADDRESS) 
        {
            operand temp = newTemp();
            genInterCode(IR_READ_ADDR, temp, t1);
            t1 = temp;
        }//存在地址就生成局部变量读
        genInterCode(IR_IF_GOTO, t1, relop, t2, labelTrue);//判断if语句，跳转真出口
        genInterCode(IR_GOTO, labelFalse);//跳转到假出口
    }
}
    // Args -> Exp COMMA Args
    //       | Exp
    /*翻译参数*/
void translateArgs(Node* node, arg_list argList) 
{
    assert(node != NULL);
    assert(argList != NULL);
    if (interError) return;
    // Args -> Exp
    argv temp = createArg(newTemp());
    translateExp(node->child, temp->op);//为参数生成临时变量
    if (temp->op->kind == OP_VARIABLE) 
    {
        Item* item = searchTableItem(mytable, temp->op->u.name);
        if (item && item->field->type->kind == ARRAY) //多维数组
        {
            interError = TRUE;
            printf("Cannot translate: Code containsvariables of multi-dimensional array type or parameters of array type.\n");
            return;
        }
    }
    addArg(argList, temp);//向参数列表中添加参数

    // Args -> Exp COMMA Args
    if (node->child->brother != NULL) 
    {
        translateArgs(node->child->brother->brother, argList);//参数列表，逐个遍历
    }
}
