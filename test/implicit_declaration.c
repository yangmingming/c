/******************************************************************
 *  @file       implicit_declaration.c
 *  @version    v1.0 
 *  @author     ymm 
 *  @date       2015/02/03
 *  @brief      隐式声明应用举例
 *  @history      
 *  1、2015/02/03  author ymm    初步完成
 ******************************************************************/
#include <stdio.h>  
//Note:include the head blow
//#include <stdlib.h>  
int main(void) 
{ 
    int i = 0;
    i = 2147483647;
    printf("i=%d\n",i);
    i++;
    printf("i++=%d\n",i);

    long l = 0;
    l = 2147483648;
    printf("l=%ld\n",l);

    l=atol("2147483648"); 
    printf("l=%ld\n",l);                 

    return 0; 
}

