/******************************************************************
 *  @file       main.c
 *  @version    v1.0 
 *  @author     ymm 
 *  @date       2015/04/28
 *  @brief      内存池的使用
 *  @history      
 *  1、2015/04/28  author ymm    初步完成
 ******************************************************************/

#include <stdio.h>
#include <string.h>
#include "util-mempool.h"
typedef struct stu_
{
    int id;
    char a[2];
}stu;

#define NUM 10
int main(int argc,char *argv[])
{
    if( 2 != argc )
    {
        printf("%s param\n",argv[0]);
        return -1;
    }
    stu *array[NUM];

    MemPool *pool = MempoolCreate( sizeof(stu), NUM );

    int i = 0;
    for( i = 0; i < NUM; i++ )
    {
        stu *s = (stu *)MempoolAlloc( pool );
        s->id = i;

        array[i] = s;
    }

    for( i = 0; i < NUM; i++ )
    {
        printf("%d\n",array[i]->id);
    }

    for( i = 0; i < 5; i++ )
    {
        /* 内存池节点的回收，为了重复利用 */
        MempoolFree( pool, array[i] );
    }
    printf("After the MempoolFree\n");
    for( i = 0; i < 5; i++ )
    {
        stu *s = (stu *)MempoolAlloc( pool );
        s->id = i*5;

        array[i] = s;
    }
    for( i = 0; i < NUM; i++ )
    {
        printf("%d\n",array[i]->id);
    }

    MempoolDestroy( pool );
    
	return 0;
}
