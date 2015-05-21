#include <stdio.h>
#include <string.h>
#include "util-primetable.h"

#define NUM 9999
int main(int argc,char *argv[])
{
    int prime = 0;
    int i = 0;
    for( i = 0; i < NUM; i++ )
    {
        prime = FindNearestPrime(i);
        //if( prime < i )
        if( 1 )
        {
            printf("%d,%d\n",i,prime);
        }
    }

	return 0;
}
