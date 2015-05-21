#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <zlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int IsFileExist(const char *fileFullPath)
{
    struct stat st;
    return stat(fileFullPath,&st);
}

size_t FileSize(const char* fileName)
{
#ifdef _WIN32
    unsigned long attr = 0;
    return attr;
#else
    struct stat st;
    if (stat(fileName, &st) == 0)
        return st.st_size;
    else
        return 0;

#endif
}

int gz_compress( const char *file_name, char *buff, uint32_t buff_len)
{
    gzFile fp = gzopen( file_name, "wb6h");
    if( Z_NULL == fp )
    {
        perror("gzopen");
        return -1;
    }

    gzwrite( fp, buff, buff_len );

    gzclose(fp);

    return 0;
}

int gz_decompress( const char *file_name, char *buff, uint32_t buff_len, int *len )
{
    if( 0 == IsFileExist( file_name ) )
    {
        size_t fsize = FileSize( file_name );
        if( 0 == fsize )
        {
            printf("file %s's size is zero\n",file_name);
            remove( file_name );
            return -1;
        }

        gzFile fp = gzopen( file_name, "rb6" );
        if( Z_NULL == fp )
        {
            perror("gzopen");
            return -1;
        }

        buff_len=102;
        //*len = gzread( fp, buff, 10 );
        *len = gzread( fp, buff, buff_len );
        buff[*len] = '\0';
        printf("if endof the buff ? %s \n",((*len < buff_len)||(gzeof(fp)==1)) ? "yes" : "no" );
        printf("buff_len=%d,len=%d\n",buff_len,*len);

        gzclose(fp);
    }

    return 0;
}

int main(int argc,char *argv[])
{
    if( 2 != argc )
    {
        printf("%s param\n",argv[0]);
        return -1;
    }

    char array[]="yangmingming love qiuyue very much";
    int len = strlen(array);
    int ret = gz_compress( "file.gz", array, len );
    if( 0 != ret )
    {
        printf("compress error\n");
        return -1;
    }

    len = 0;
    char buf[1024] = {0};
    ret = gz_decompress( argv[1], buf, sizeof(buf), &len );
    if( 0 != ret )
    {
        printf("gz_decompress error\n");
        return -1;
    }
    printf("buf=%s,len=%d\n",buf,len);

	return 0;
}
