/******************************************************************
 *  @file       file.c
 *  @version    v1.0 
 *  @author     ymm 
 *  @date       2014/11/06
 *  @brief      文件操作
 *  @history      
 *  1、2014/11/06  author ymm    初步完成
 ******************************************************************/
#include <stdio.h>
#include <string.h>

#define STR_MAX_LENGTH      1024
int main(int argc,char *argv[])
{
    if(2 != argc)
    {
        printf("Please input one file name\n");
        return -1;
    }
    FILE *fp = NULL;
    fp = fopen(argv[1],"rw+");
    if(NULL == fp)
    {
        printf("file open error \n");
        return -1;
    }

    fputs("yang",fp);
    fseek(fp, 0L, SEEK_SET);
    fclose(fp);

#if 0
    char szStr[STR_MAX_LENGTH] = {0};
    int i = 0;
    while(NULL != fgets(szStr,STR_MAX_LENGTH,fp))
    {
        //delete the '\n'
        szStr[strlen(szStr)-1]='\0';
        printf("%s\n",szStr);
    }
#endif
    return 0;
}
