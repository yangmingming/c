#include <stdio.h>
#include <string.h>
#include <time.h>       //time
#include <sys/time.h>   //gettimeofday

#define NUM 10
int main(int argc,char *argv[])
{
    if( 2 != argc )
    {
        printf("%s param\n",argv[0]);
        return -1;
    }
    time_t start_time, curr_time;
    time(&start_time);
    while(1)
    {
        time( &curr_time );
        if( difftime( curr_time, start_time ) > NUM )
        {
            printf("After %d seconds,begin=%ld,end=%ld\n", NUM, start_time, curr_time );
            break;
        }

        usleep(300000);
    }


    //method2
    struct timeval now_time;
    gettimeofday( &now_time, NULL );
    printf("seconds=%ld, microseconds=%ld\n", now_time.tv_sec, now_time.tv_usec);
    size_t a;

    return 0;
}
