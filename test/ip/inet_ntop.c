#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <arpa/inet.h>

int ConvertLittleEndianIPToBinary(const char *str_ip,uint32_t *int_ip)
{
#ifndef _WIN32
    inet_pton(AF_INET,str_ip ,int_ip);
printf("inet_pton: 0x%x\n", *int_ip);
#endif

    return 0;
}

int ConvertBigEndianIPToBinary(const char *str_ip,uint32_t *int_ip)
{

#ifndef _WIN32
    uint32_t tmpVal = 0;
    inet_pton(AF_INET, str_ip, &tmpVal);

    *int_ip = ntohl(tmpVal);
#endif
printf("inet_pton: 0x%x\n", *int_ip);

    return 0;
}
int main (void)
{
    printf("%d,%d\n",INET_ADDRSTRLEN,INET6_ADDRSTRLEN );
#if 0
    char IPdotdec[20]; //存放点分十进制IP地址
    struct in_addr s; // IPv4地址结构体
    // 输入IP地址
    printf("Please input IP address: ");
    scanf("%s", IPdotdec);
    // 转换
    inet_pton(AF_INET, IPdotdec, (void *)&s);
    printf("inet_pton: 0x%x\n", s.s_addr); // 注意得到的字节序
    // 反转换
    inet_ntop(AF_INET, (void *)&s, IPdotdec, 16);
    printf("inet_ntop: %s\n", IPdotdec);
#endif
#if 0
    char IPdotdec[20]; //存放点分十进制IP地址
    uint32_t tmpVal;
    // 输入IP地址
    printf("Please input IP address: ");
    scanf("%s", IPdotdec);
    // 转换
    inet_pton(AF_INET, IPdotdec, (void *)&tmpVal);
    printf("inet_pton: 0x%x\n", tmpVal); // 注意得到的字节序
    // 反转换
    inet_ntop(AF_INET, (void *)&tmpVal, IPdotdec, 16);
    printf("inet_ntop: %s\n", IPdotdec);
#endif
#if 0
struct sockaddr_in sa;
char str[INET_ADDRSTRLEN];

// store this IP address in sa:
inet_pton(AF_INET, "192.0.2.33", &(sa.sin_addr));

// now get it back and print it
inet_ntop(AF_INET, &(sa.sin_addr), str, INET_ADDRSTRLEN);

printf("%s\n", str); // prints "192.0.2.33"
#endif

// IPv6 demo of inet_ntop() and inet_pton()
// (basically the same except with a bunch of 6s thrown around)

struct sockaddr_in6 sa;
char str[INET6_ADDRSTRLEN];

// store this IP address in sa:
inet_pton(AF_INET6, "2001:db8:8714:3a90::12", &(sa.sin6_addr));

// now get it back and print it
inet_ntop(AF_INET6, &(sa.sin6_addr), str, INET6_ADDRSTRLEN);

printf("%s\n", str); // prints "2001:db8:8714:3a90::12"

exit(0);
    char IPdotdec[120]; //存放点分十进制IP地址
    uint32_t tmpVal;
    // 输入IP地址
    printf("Please input IP address: ");
    scanf("%s", IPdotdec);
    // 转换
    ConvertBigEndianIPToBinary(IPdotdec,&tmpVal);
    printf("inet_pton: 0x%x\n", tmpVal); // 注意得到的字节序
    ConvertLittleEndianIPToBinary(IPdotdec,&tmpVal);
    printf("inet_pton: 0x%x\n", tmpVal); // 注意得到的字节序

    return 0;
}
