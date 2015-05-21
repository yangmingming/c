#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int IsFileExist( const char *fileFullPath )
{
    struct stat st;
    return stat( fileFullPath, &st );
}

int IsDirExist( const char *dirPath)
{
    struct stat st;
    return stat( dirPath, &st );
}

int IsFile( const char *file )
{
    struct stat st;
    if( 0 == stat( file, &st ) )
        return S_ISREG( st.st_mode ) == 1 ? 0 : -1 ;
    else
        return -1;
}

int IsDir( const char *dir )
{
    struct stat st;
    if( 0 == stat( dir, &st ) )
        return S_ISDIR( st.st_mode ) == 1 ? 0 : -1 ;
    else
        return -1;
}

int main(int argc,char *argv[])
{
    if( 2 != argc )
    {
        printf("%s param\n",argv[0]);
        return -1;
    }

    printf("IsFileExist\t=%d\n",IsFileExist(argv[1]));
    printf("IsDirExist\t=%d\n",IsDirExist(argv[1]));
    printf("IsFile\t=%d\n",IsFile(argv[1]));
    printf("IsDir\t=%d\n",IsDir(argv[1]));
    //printf("IsFileExist\t=%d\n",IsFileExist(argv[1]));

	return 0;
}
