#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//大端==》ip
char* IPntoa(unsigned int  ip4, char str[]){
    int  sip[4];
    sip[0] = ip4 & 0xFF;
    sip[1] = (ip4>>8) & 0xFF;
    sip[2] = (ip4>>16) & 0xFF;
    sip[3] = (ip4>>24) & 0xFF;
    snprintf(str, 16, "%d.%d.%d.%d",sip[3], sip[2], sip[1], sip[0]);
    return str;
}

int main(int argc,char *argv[])
{
#if 0
    unsigned short x=0x1234;
    printf("0x%X\n",x );
    printf("0x%X\n",x & 0x00FF);
    printf("0x%X\n",x & 0xFF00);

    unsigned short y=ntohs(x);
    printf("0x%X\n",y );
    printf("0x%X\n",y & 0x00FF);
    printf("0x%X\n",y & 0xFF00);

    unsigned short z=htons(x);
    printf("0x%X\n",z );
    printf("0x%X\n",z & 0x00FF);
    printf("0x%X\n",z & 0xFF00);
#endif
#if 1
uint32_t a;
printf("argc=%d\n",argc);
if(argc != 2)
{
    a= inet_addr("10.110.3.51");
}
else
{
	a=inet_addr(argv[1]);
}
    //uint32_t a = 2885681162;
    //printf("%"PRIu32"\n",a);
    printf("%0X\n",a);
    int b = ntohl(a);
    int c = htonl(a);
    printf("b = %0X, c = %0X \r\n", b, c);
    //printf("b = %"PRIu32", c = %"PRIu32" \r\n", b, c);

    struct sockaddr_in src;
    src.sin_addr.s_addr = a;
    printf("%s\n",inet_ntoa(src.sin_addr));

    char str[20]={0};
    IPntoa(a,str);
    printf("%s\n",str);
    IPntoa(b,str);
    printf("%s\n",str);

    //src.sin_addr.s_addr = htonl(a);
    //printf("%s\n",inet_ntoa(src.sin_addr));
    //src.sin_addr.s_addr = ntohl(a);
    //printf("%s\n",inet_ntoa(src.sin_addr));
#endif
    int i = 0;

#if 0
    //int -->> ip
    int iArrayIP[]={
        846247388,
        -1702632603,
        248704883,
        248704883,
        248704883,
        248704883,
        248704883,
        248704883,
        -1702632603,
        248704883,
        248704883,
        248704883,
        -1702632603,
        248704883,
        248704883,
        248704883,
        -1702632603,
        248704883,
        248704883,
        248704883,
        248704883,
        248704883,
        -1702632603,
        248704883,
        0,
        -1702632603
    };
    struct sockaddr_in src;
    for(i=0;i<(sizeof(iArrayIP)/sizeof(int));i++)
    {
        src.sin_addr.s_addr = iArrayIP[i];
        printf("%s\n",inet_ntoa(src.sin_addr));
    }

#endif
#if 0
    char str[][20]={
        "101.227.131.154",
        "103.7.31.152",
        "14.17.42.23",
        "163.177.65.166",
        "111.13.48.100",
        "182.254.18.201",
        "112.90.14.190",
        "220.181.112.50",
        "115.239.210.14",
        "74.125.203.188"
    };

    int iNum = sizeof(str)/sizeof(str[0]);
    for(i=0;i<iNum;i++)
    {
        int a = inet_addr(str[i]);
        printf("%d\n",a);
    }
    printf("%d\n",sizeof(str));
    printf("%d\n",sizeof(str[0]));
#endif
#if 0
    if(2 != argc)
    {
        printf("Please input one file name!\n");
        return -1;
    }
    FILE *fp = NULL;
    fp = fopen(argv[1],"rt");
    if(NULL == fp)
    {
        printf("file open error \n");
        return -1;
    }

#define STR_MAX_LENGTH      20
    char szStr[STR_MAX_LENGTH] = {0};
    int i = 0;
    while(NULL != fgets(szStr,STR_MAX_LENGTH,fp))
    {
        //delete the '\n'
        szStr[strlen(szStr)-1]='\0';
        //printf("%s\n",szStr);
        int a = inet_addr(szStr);
        printf("%d\n",a);
    }
#endif
    return 0;
}
