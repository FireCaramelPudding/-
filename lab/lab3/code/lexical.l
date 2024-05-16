%{
    #include "tree.h"
    #include "syntax.tab.h"
    int yycolumn = 1;
    /*维护语法单元的位置*/
    #define YY_USER_ACTION \
        yylloc.first_line=yylloc.last_line=yylineno; \
        yylloc.first_column=yycolumn; \
        yylloc.last_column=yycolumn+yyleng-1; \
        yycolumn+=yyleng;
    void my_token_node(char* name, char* value, enum DATATYPE datatype);
    void lex_error(char* msg, int yylineno, char* yytext);
    extern YYSTYPE yylval;
    int error1 = 0;
    int comment_line = 0;//记录未闭合的注释发生的行号
%}
%option yylineno
SEMI ;
COMMA ,
ASSIGNOP =
PLUS \+
MINUS -
STAR \*
DIV \/
AND &&
OR \|\|
DOT \.
NOT !
TYPE int|float
LP \(
RP \)
LB \[
RB \]
LC \{
RC \}
STRUCT struct
RETURN return
IF if
ELSE else
WHILE while
INT [1-9]+[0-9]{0,31}|0
OCT 0[0-7]{1,3}
HEX 0x[0-9A-Fa-f]{1,4}
FLOAT [0-9]+"."[0-9]+|[0-9]+"."[0-9]*[eE][+-]?[0-9]+
ID [_a-zA-Z][_0-9a-zA-Z]*
RELOP (>|<|>=|<=|==|!=)
%x INLINE_COMMENT
%x COMMENT
%%
"/*" { 
    comment_line = yylineno;
    BEGIN(COMMENT);
}

<COMMENT>{
    "*/" { BEGIN(INITIAL);}/*不维护嵌套注释计数器*/
    .|\n { /* do nothing */}
}

<COMMENT><<EOF>> {
        printf("Error type A at Line %d: unmatched comment \"/*\".\n", comment_line);/*不调用错误处理函数lex_error，否则段错误（yyless(0)引起的）*/
        error1 = 1;
        exit(1);/*退出程序，避免循环打印*/
}

"*/" {lex_error("unmatched comment", yylineno, yytext);  /*只匹配到后一半注释符时报错*/}
"//" {BEGIN(INLINE_COMMENT); }
<INLINE_COMMENT>[^\n]* {/*do nothing*/}
<INLINE_COMMENT>\n {BEGIN(INITIAL);/*忽略回车前以//开头的注释*/}
";" {my_token_node("SEMI", NULL, OTHERS);return SEMI;}
"," {my_token_node("COMMA", NULL, OTHERS);return COMMA;}
"=" {my_token_node("ASSIGNOP", NULL, OTHERS);return ASSIGNOP;}
"+" {my_token_node("PLUS", NULL, OTHERS);return PLUS;}
"-" {my_token_node("MINUS", NULL, OTHERS);return MINUS;}
"*" {my_token_node("STAR", NULL, OTHERS);return STAR;}
"/" {my_token_node("DIV", NULL, OTHERS);return DIV;}
"&&" {my_token_node("AND", NULL, OTHERS);return AND;}
"||" {my_token_node("OR", NULL, OTHERS);return OR;}
"." {my_token_node("DOT", NULL, OTHERS);return DOT;}
"!" {my_token_node("NOT", NULL, OTHERS);return NOT;}
"int" {my_token_node("TYPE", "int", myTYPE);return TYPE;}
"float" {my_token_node("TYPE", "float", myTYPE);return TYPE;}
"(" {my_token_node("LP", NULL, OTHERS);return LP;}
")" {my_token_node("RP", NULL, OTHERS);return RP;}
"[" {my_token_node("LB", NULL, OTHERS);return LB;}
"]" {my_token_node("RB", NULL, OTHERS);return RB;}
"{" {my_token_node("LC", NULL, OTHERS);return LC;}
"}" {my_token_node("RC", NULL, OTHERS);return RC;}
"struct" {my_token_node("STRUCT", NULL, OTHERS);return STRUCT;}
"return" {my_token_node("RETURN", NULL, OTHERS);return RETURN;}
"if" {my_token_node("IF", NULL, OTHERS);return IF;}
"else" {my_token_node("ELSE", NULL, OTHERS);return ELSE;}
"while" {my_token_node("WHILE", NULL, OTHERS);return WHILE;}
{INT} {my_token_node("INT", yytext, myINT);return INT;}
{OCT} {my_token_node("INT", yytext, myOCT);return INT;}
{HEX} {my_token_node("INT", yytext, myHEX);return INT;}
{FLOAT} {my_token_node("FLOAT", yytext, myFLOAT);return FLOAT;}
{ID} {my_token_node("ID", yytext, myID);return ID;}
{RELOP} {my_token_node("RELOP", yytext, OTHERS);return RELOP;}
\n {yycolumn = 1;/*对yycolumn复位*/}
[ \t\r] { /* 忽略空格、制表符 */ }
0[0-7]*[8-9][0-9]* {/*错误的八进制数*/
    lex_error("Illegal octal number", yylineno, yytext);
}
0[xX][0-9a-fA-F]*[g-zG-Z]+[0-9a-fA-F]* {/*错误的十六进制数*/
    lex_error("Illegal hexadecimal number", yylineno, yytext);
}
"."[0-9]+ {/*形如.8这样的错误*/  lex_error("Illegal floating point number", yylineno, yytext); }
[0-9]+"." {/*形如0.这样的错误*/  lex_error("Illegal floating point number", yylineno, yytext); }
[0-9]*"."[0-9]+[eE] {/*形如.1e这样的错误*/  lex_error("Illegal floating point number", yylineno, yytext); }
[0-9]+"."[0-9]*[eE] {/*形如1.1e这样的错误*/  lex_error("Illegal floating point number", yylineno, yytext); }
[0-9]+[eE][+-]?[0-9]* {/*形如9e9这样的错误*/  lex_error("Illegal floating point number", yylineno, yytext); }
"."[eE][+-]?[0-9]+ {/*形如.9e9这样的错误*/  lex_error("Illegal floating point number", yylineno, yytext); }
. {/*其他未出现的字符*/ lex_error("Mysterious characters", yylineno, yytext); }
%%
void my_token_node(char* name, char* value, enum DATATYPE datatype)
{
    yylval.Node = token_node(name, value, datatype);//使用YYSTYPE类型的变量传递终结符的值
}
void lex_error(char* msg, int yylineno, char* yytext)
{
    printf("Error type A at Line %d: %s \"%s\".\n", yylineno, msg, yytext);
    error1 = 1;
    yyless(0);/*退回到输入流开始的位置*/
    while (input() != '\n' && input() != ';' && input() != '\0');/*跳过本行语句*/
}