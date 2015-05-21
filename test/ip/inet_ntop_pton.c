/******************************************************************
 *  @file       inet_ntop_pton.c
 *  @version    v1.0 
 *  @author     ymm 
 *  @date       2015/05/21
 *  @brief      inet_ntop 和 inet_pton 函数对于ipv4 和 ipv6 处理
 *              gcc inet_ntop_pton.c
 *              gcc inet_ntop_pton.c -D IPV4
 *  @history      
 *  1、2015/05/21  author ymm    初步完成
 ******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>

#include <arpa/inet.h>

int main ()
{
    printf("%d,%d\n",INET_ADDRSTRLEN,INET6_ADDRSTRLEN );
#ifdef IPV4
    struct sockaddr_in sa;
    char str[INET_ADDRSTRLEN];

    // store this IP address in sa:
    inet_pton(AF_INET, "192.0.2.33", &(sa.sin_addr));

    // now get it back and print it
    inet_ntop(AF_INET, &(sa.sin_addr), str, INET_ADDRSTRLEN);

    printf("%u\n", sa.sin_addr.s_addr);
    printf("%s\n", str); // prints "192.0.2.33"
#else

    // IPv6 demo of inet_ntop() and inet_pton()
    // (basically the same except with a bunch of 6s thrown around)

    struct sockaddr_in6 sa;
    char str[INET6_ADDRSTRLEN];

    // store this IP address in sa:
    inet_pton(AF_INET6, "2001:db8:8714:3a90::12", &(sa.sin6_addr));

    // now get it back and print it
    inet_ntop(AF_INET6, &(sa.sin6_addr), str, INET6_ADDRSTRLEN);

    int i = 0;
    for(i=0; i<16; i++)
    {
        printf("%u ",sa.sin6_addr.__in6_u.__u6_addr8[i]);
    }
    printf("\n");
    printf("%s\n", str); // prints "2001:db8:8714:3a90::12"
#endif

    return 0;
}
