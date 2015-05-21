/******************************************************************
 *  @file       define.c
 *  @version    v1.0 
 *  @author     ymm 
 *  @date       2015/04/22
 *  @brief      通过gcc -E的方式，获取类型的原始定义
 *  @history      
 *  1、2015/04/22  author ymm    初步完成
 ******************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>       //time
#include <sys/time.h>   //gettimeofday

int main(int argc,char *argv[])
{
    time_t curr_time;    //time
    struct timeval *tv;  //gettimeofday
#if 0
    struct timeval {
        time_t      tv_sec;     /* seconds */
        suseconds_t tv_usec;    /* microseconds */
    };
#endif

    size_t strlen_len;  //strlen

    int8_t  i1;
    int16_t i2;
    int32_t i3;
    int64_t i4;

    uint8_t  ui1;
    uint16_t ui2;
    uint32_t ui3;
    uint64_t ui4;

    return 0;
}

