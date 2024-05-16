#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<dirent.h>

FILE* fout=NULL;    //用于输出的文件指针


void run(const char* filename,const char* outputdir){
    //处理单个文件
    //若outputdir为空则输出到屏幕
    static char tmpbuf[256];
    static char tmpbuf1[256];
    if(outputdir != NULL){
        int len=strlen(filename);
        strcpy(tmpbuf,filename);
        for(int i=len - 1; i >= 0; i--)
            if(filename[i] == '/'){
                strcpy(tmpbuf,filename + i + 1);
                break;
            }
        sprintf(tmpbuf1,"%s/%s.ans",outputdir,tmpbuf);
        fout=fopen(tmpbuf1,"w");
        if(fout == NULL){
            printf("Error: Cannot write result file '%s'\n",tmpbuf1);
            exit(-1);
        }
    }else 
        fout=stdout;
    FILE* f=fopen(filename,"r");
    if(f == NULL){
        printf("Error: Cannot open file '%s'\n",filename);
        exit(-1);
    }
    
    //TODO: 根据文件指针f进行处理，结果输出到fout中，填写自己的代码


    fclose(f);
    if(fout != stdout)
        fclose(fout);
}

//用法：
//1. ./cmm [输入文件名]
//  处理【当前文件夹下的】单个文件，将结果输出到屏幕
//2. ./cmm -all
//  读取tests文件夹下的所有文件，将结果输出到results文件夹里
//3. ./cmm -all [输入文件夹]
//  手动指定【当前文件夹下的】输入文件夹，将结果输出到results文件夹里
//4. ./cmm -all [输入文件夹] [输出文件夹]
//  手动指定【当前文件夹下的】输入输出文件夹
//注意：输入输出文件夹需要在当前文件夹下！！

int main(int argc,char** argv){
    if(argc < 2){
        printf("Error: Too few args.\n");
        return -1;
    }
    static char tmpbuf[1024];
    if(strcmp(argv[1],"-all") == 0){    //基于文件的批量测试
        const char* outputdir=(argc < 4) ? "results" : argv[3];
        DIR* dout=opendir(outputdir);
        if(dout == NULL){
            sprintf(tmpbuf,"mkdir %s",outputdir);
            system(tmpbuf);
        }
        closedir(dout);
        const char* path=(argc < 3) ? "tests" : argv[2];
        DIR* dir=opendir(path);
        if(dir == NULL){
            printf("Cannot access directory '%s'\n",path);
            return -1;
        }
        for(struct dirent* dirfile=readdir(dir); dirfile != NULL; dirfile=readdir(dir)){
            if(dirfile->d_name[0] == '.')
                continue;
            sprintf(tmpbuf,"%s/%s",path,dirfile->d_name);
            run(tmpbuf,outputdir);
        }
        closedir(dir);

    }else
        run(argv[1],NULL);
    
    return 0;
}