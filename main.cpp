#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 8
char *Key[MAX]={"const","main","if","else","while","int","for","return"};
char Word[20],ch;

int IsAlpha(char c){    //判断字母
    if(((c<='z')&&(c>='a'))||((c<='Z')&&(c>='A')))
        return 1;
    else
        return 0;
}

int IsNum(char c){      //判断数字
    if(c>='0'&&c<='9')
        return 1;
    else
        return 0;
}

int IsKey(char *Word){      //判断关键字
    int  m,i;
    for(i=0;i<MAX;i++){
        if((m=strcmp(Word,Key[i]))==0){ //比较字符串
            return 1;
        }
    }
    return 0;
}

void scanner(FILE *fp){     //扫描文档
    char Word[20]={'\0'};
    char ch;
    int i,c;
    ch=fgetc(fp);   //文件指针
    if(IsAlpha(ch)){    //判断字母
        Word[0]=ch;
        ch=fgetc(fp);
        i=1;
        while(IsNum(ch)||IsAlpha(ch)){  //继续判断字母或数字
            Word[i]=ch;
            i++;
            ch=fgetc(fp);
        }
        Word[i]='\0';   //字符结束
        fseek(fp,-1,1); //指针回退
        c=IsKey(Word);  //判断关键字
        if(c==0)    //不是关键字
            printf("(2,\t%s)\n",Word);
        else
            printf("(1,\t%s)\n",Word);    //输出关键字
    }
    else
        if(IsNum(ch)){  //判断数字
            Word[0]=ch;
            ch=fgetc(fp);
            i=1;
            while(IsNum(ch)){   //继续判断
                Word[i]=ch;
                i++;
                ch=fgetc(fp);
            }
            Word[i]='\0';   //结束
            fseek(fp,-1,1); //回退
            printf("(3,\t%s)\n",Word);    //输出
        }
        else{   //判断符号
            Word[0]=ch;
            switch(ch){
                case'[':
                case']':
                case'(':
                case')':
                case'{':
                case'}':
                case',':
                case'"':
                case';':
                case'+':
                case'-':
                case'*':
                case'/':
                case'!':
                case'=':
                    ch=fgetc(fp);
                    Word[1]=ch;
                    if(ch=='='){
                        printf("(4,\t%s)\n",Word);
                    }
                    else{
                        fseek(fp,-1,1);
                        Word[1]='\0';
                        printf("(4,\t%s)\n",Word);
                    }
                    break;
                case'<':
                    ch=fgetc(fp);
                    Word[1]=ch;
                    if(ch=='='){
                        printf("(4,\t%s)\n",Word);
                    }
                    else{
                        fseek(fp,-1,1);
                        Word[1]='\0';
                        printf("(4,\t%s)\n",Word);
                    }
                    break;
                case'>':
                    ch=fgetc(fp);
                    Word[1]=ch;
                    if(ch=='='){
                        printf("(4,\t%s)\n",Word);
                    }
                    else{
                        fseek(fp,-1,1);
                        Word[1]='\0';
                        printf("(4,\t%s)\n",Word);
                    }
                    break;
                case'%':printf("(4,\t%s)\n",Word);break;
                default:printf("无法识别字符\n\n");break;

            }
        }
}

int main() {
    char in_fn[30]; ///Users/wangh7/Desktop/test.txt
    FILE *fp;
    printf("\n");
    while(1){
        gets(in_fn);
        if((fp=fopen(in_fn,"r"))!=NULL)
            break;
        else
            printf("文件路径出错");
    }
    printf("分析如下\n");
    do{
        ch=fgetc(fp);
        if(ch=='#')
            break;
        else if(ch==' '||ch=='\t'||ch=='\n'){}
        else{
            fseek(fp,-1,1);
            scanner(fp);
        }
    }while(ch!='#');
    return 0;
}