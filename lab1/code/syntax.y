%{
    #include <stdio.h>
    #include "tree.h"
    #include "lex.yy.c"
    extern int yylineno;
    extern char* yytext;
    int yyerr_line=0;
    int yylex();
    void yyerror(char* s);
    node* root;
    int error2 = 0;
    extern int error1;
%}
%locations
%union {
    node* Node;
}
/*终结符*/
%token  <Node> INT
%token  <Node> FLOAT
%token  <Node> ID
%token  <Node> TYPE
%token  <Node> COMMA
%token  <Node> DOT
%token  <Node> SEMI
%token  <Node> RELOP
%token  <Node> ASSIGNOP
%token  <Node> PLUS
%token  <Node> MINUS
%token  <Node> STAR
%token  <Node> DIV
%token  <Node> AND
%token  <Node> OR
%token  <Node> NOT
%token  <Node> LP
%token  <Node> RP
%token  <Node> LB
%token  <Node> RB
%token  <Node> LC
%token  <Node> RC
%token  <Node> IF
%token  <Node> ELSE
%token  <Node> WHILE
%token  <Node> STRUCT
%token  <Node> RETURN
/*优先级和结合性*/
%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS 
%left MINUS
%left STAR 
%left DIV
%right NOT
%left DOT
%left LB RB
%left LP RP
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
/*非终结符 */
%type <Node> Program
%type <Node> ExtDefList
%type <Node> ExtDef
%type <Node> ExtDecList
%type <Node> Specifier
%type <Node> StructSpecifier
%type <Node> OptTag
%type <Node> Tag
%type <Node> VarDec
%type <Node> FunDec
%type <Node> VarList
%type <Node> ParamDec
%type <Node> CompSt
%type <Node> StmtList
%type <Node> Stmt
%type <Node> DefList
%type <Node> Def
%type <Node> DecList
%type <Node> Dec
%type <Node> Exp
%type <Node> Args
%start Program
%%
/*输入：节点名称，节点值，节点类型
输出：节点的指针
功能：为非终结符创建一个节点，并且与子节点和兄弟节点连接起来
node* not_token_node(char* name, int line, int children_number, ...);*/
/*error添加：①右括号/分号前②表达式*/
/*High-level Definitions*/
Program : ExtDefList    {$$ = not_token_node("Program", @$.first_line, 1, $1);root = $$;}
    ;
ExtDefList : ExtDef ExtDefList  {$$ = not_token_node("ExtDefList", @$.first_line, 2, $1, $2);}
    |   {$$=NULL;/*空串将节点置空即可*/}
    ;
ExtDef : Specifier ExtDecList SEMI  {$$ = not_token_node("ExtDef", @$.first_line, 3, $1, $2, $3);}/*全局变量*/
    |Specifier SEMI {$$ = not_token_node("ExtDef", @$.first_line, 2, $1, $2);}/*结构体*/
    |Specifier FunDec CompSt    {$$ = not_token_node("ExtDef", @$.first_line, 3, $1, $2, $3);}/*函数*/
    |Specifier error SEMI  { yyerrok; }
    |error CompSt  {/*错误的函数类型*/yyerrok; }
    |error SEMI    {/*错误的类型*/yyerrok; }
    |error ExtDef  {/*错误的类型定义*/} 
    |Specifier error CompSt    {/*错误的函数名*/yyerrok;}
    ;
ExtDecList : VarDec {$$ = not_token_node("ExtDecList", @$.first_line, 1, $1);}
    |VarDec COMMA ExtDecList    {$$ = not_token_node("ExtDecList", @$.first_line, 3, $1, $2, $3);}
    ;
/*Specifiers*/
Specifier : TYPE    {$$ = not_token_node("Specifier", @$.first_line, 1, $1);}/*基本类型*/
    |StructSpecifier    {$$ = not_token_node("Specifier", @$.first_line, 1, $1);}/*结构体*/
    ;
StructSpecifier : STRUCT OptTag LC DefList RC   {$$ = not_token_node("StructSpecifier", @$.first_line, 5, $1, $2, $3, $4, $5);}
    |STRUCT Tag {$$ = not_token_node("StructSpecifier", @$.first_line, 2, $1, $2);}
    |STRUCT OptTag LC DefList error RC             {/*在右括号前添加error*/yyerrok;}
    ;
OptTag : ID {$$ = not_token_node("OptTag", @$.first_line, 1, $1);}
    |   {$$ = NULL;}
    ;
Tag : ID    {$$ = not_token_node("Tag", @$.first_line, 1, $1);}
    ;
/*Declarators*/
VarDec : ID {$$ = not_token_node("VarDec", @$.first_line, 1, $1);}/*变量定义*/
    |VarDec LB INT RB   {$$ = not_token_node("VarDec", @$.first_line, 4, $1, $2, $3, $4);}
    |VarDec LB error RB {/*在右括号前添加error*/yyerrok;}
    ;
FunDec : ID LP VarList RP   {$$ = not_token_node("FunDec", @$.first_line, 4, $1, $2, $3, $4);}/*函数头定义*/
    |ID LP RP   {$$ = not_token_node("FunDec", @$.first_line, 3, $1, $2, $3);}
    |ID error RP {/*在右括号前添加error*/yyerrok;}
    ;
VarList : ParamDec COMMA VarList    {$$ = not_token_node("VarList", @$.first_line, 3, $1, $2, $3);}/*形参列表*/
    |ParamDec   {$$ = not_token_node("VarList", @$.first_line, 1, $1);}
    ;
ParamDec : Specifier VarDec {$$ = not_token_node("ParamDec", @$.first_line, 2, $1, $2);}/*形参*/
    ;
/*Statements*/
CompSt : LC DefList StmtList RC {$$ = not_token_node("CompSt", @$.first_line, 4, $1, $2, $3, $4);}/*花括号括起来的代码块*/
    ;
StmtList : Stmt StmtList    {$$ = not_token_node("StmtList", @$.first_line, 2, $1, $2);}/*语句*/
    |   {$$ = NULL;}
    ;
Stmt : Exp SEMI {$$ = not_token_node("Stmt", @$.first_line, 2, $1, $2);}/*以分号结尾的表达式*/
    | CompSt    {$$ = not_token_node("Stmt", @$.first_line, 1, $1);}/*代码块*/
    | RETURN Exp SEMI   {$$ = not_token_node("Stmt", @$.first_line, 3, $1, $2, $3);}/*返回语句*/
    | IF LP Exp RP Stmt {$$ = not_token_node("Stmt", @$.first_line, 5, $1, $2, $3, $4, $5);}/*if-else语句*/
    | IF LP Exp RP Stmt ELSE Stmt   {$$ = not_token_node("Stmt", @$.first_line, 7, $1, $2, $3, $4, $5, $6, $7);}
    | WHILE LP Exp RP Stmt  {$$ = not_token_node("Stmt", @$.first_line, 5, $1, $2, $3, $4, $5);}/*while语句*/
    | error SEMI    {yyerrok;}
    | error Stmt    {yyerrok;}
    | Exp error {}
    | IF LP error RP Stmt %prec LOWER_THAN_ELSE {}
    | IF LP error RP Stmt ELSE Stmt {}
    | WHILE LP error RP Stmt    {yyerrok;}
    ;
/*Local Definitions*/
DefList : Def DefList   {$$ = not_token_node("DefList", @$.first_line, 2, $1, $2);}/*局部变量的定义*/
    |   {$$ = NULL;}
    ;
Def : Specifier DecList SEMI    {$$ = not_token_node("Def", @$.first_line, 3, $1, $2, $3);}
    | Specifier DecList error SEMI  {yyerrok;}
    | Specifier error SEMI  {yyerrok;}
    ;
DecList : Dec   {$$ = not_token_node("DecList", @$.first_line, 1, $1);}
    | Dec COMMA DecList {$$ = not_token_node("DecList", @$.first_line, 3, $1, $2, $3);}
    ;
Dec : VarDec    {$$ = not_token_node("Dec", @$.first_line, 1, $1);}
    | VarDec ASSIGNOP Exp   {$$ = not_token_node("Dec", @$.first_line, 3, $1, $2, $3);}/*在定义的同时赋值*/
    ;
/*Expressions*/
Exp : Exp ASSIGNOP Exp  {$$ = not_token_node("Exp", @$.first_line, 3, $1, $2, $3);}/*二元表达式*/
    | Exp AND Exp   {$$ = not_token_node("Exp", @$.first_line, 3, $1, $2, $3);}
    | Exp OR Exp    {$$ = not_token_node("Exp", @$.first_line, 3, $1, $2, $3);}
    | Exp RELOP Exp {$$ = not_token_node("Exp", @$.first_line, 3, $1, $2, $3);}
    | Exp PLUS Exp  {$$ = not_token_node("Exp", @$.first_line, 3, $1, $2, $3);}
    | Exp MINUS Exp {$$ = not_token_node("Exp", @$.first_line, 3, $1, $2, $3);}
    | Exp STAR Exp  {$$ = not_token_node("Exp", @$.first_line, 3, $1, $2, $3);}
    | Exp DIV Exp   {$$ = not_token_node("Exp", @$.first_line, 3, $1, $2, $3);}
    | LP Exp RP {$$ = not_token_node("Exp", @$.first_line, 3, $1, $2, $3);}
    | MINUS Exp {$$ = not_token_node("Exp", @$.first_line, 2, $1, $2);}
    | NOT Exp   {$$ = not_token_node("Exp", @$.first_line, 2, $1, $2);}/*一元表达式*/
    | ID LP Args RP {$$ = not_token_node("Exp", @$.first_line, 4, $1, $2, $3, $4);}
    | ID LP RP  {$$ = not_token_node("Exp", @$.first_line, 3, $1, $2, $3);}
    | Exp LB Exp RB {$$ = not_token_node("Exp", @$.first_line, 4, $1, $2, $3, $4);}
    | Exp DOT ID    {$$ = not_token_node("Exp", @$.first_line, 3, $1, $2, $3);}
    | ID    {$$ = not_token_node("Exp", @$.first_line, 1, $1);}/*基本表达式*/
    | INT   {$$ = not_token_node("Exp", @$.first_line, 1, $1);}
    | FLOAT {$$ = not_token_node("Exp", @$.first_line, 1, $1);}
    | Exp ASSIGNOP error    {} /*将EXP或下一步变为终结符的产生式左部替换为error*/ 
    | Exp AND error {}    
    | Exp OR error  {}    
    | Exp RELOP error   {}    
    | Exp PLUS error    {}    
    | Exp MINUS error   {}  
    | Exp STAR error    {}    
    | Exp DIV error {}     
    | LP error RP   {yyerrok;}   
    | LP Exp error  {}    
    | MINUS error   {}           
    | NOT error {}  
    | ID LP error RP    {yyerrok;}  
    | Exp LB error RB   {yyerrok;}  
    ;
Args : Exp COMMA Args   {$$ = not_token_node("Args", @$.first_line, 3, $1, $2, $3);}/*实参列表*/
    | Exp   {$$ = not_token_node("Args", @$.first_line, 1, $1);}
    | error COMMA Exp   {/*错误的表达式*/}
    ;
%%
void yyerror(char* s){
    if(yyerr_line==yylineno){
        return;/*如果已经在该行报错则退出*/
    }
    yyerr_line=yylineno;
    error2 = 1;
    if(!error1)
    {
        printf("Error type B at Line %d : %s, near \"%s\".\n",yylineno,s,yytext);
    }
    
}
