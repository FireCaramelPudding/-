#include <stdio.h>
#include "tree.h"
#include "syntax.tab.h"
extern FILE* yyin;
extern int yylineno;
extern int yyparse();
extern void yyrestart(FILE*);
extern node* root;
extern int error1;
extern int error2;
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
    
    // yydebug = 1;
    yyrestart(f);
    yyparse();
    fclose(f);
    // while(yylex()!=0);
    if(!error1 && !error2)//词法分析和语法分析均没有错误时
    {
        print_tree(root,0);
        free_tree(root);
    }
    return 0;
}