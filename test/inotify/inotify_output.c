#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <sys/inotify.h>

/* According to POSIX.1-2001 */
#include <sys/select.h>

/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>


#define NAME_LEN 512
#define EVENT_SIZE ( sizeof(struct inotify_event) )
#define EVENT_BUFF_LEN ( 8 * ( EVENT_SIZE + NAME_LEN ) )

char * event_array[] = {
    "File was accessed",
    "File was modified",
    "File attributes were changed",
    "writtable file closed",
    "Unwrittable file closed",
    "File was opened",
    "File was moved from X",
    "File was moved to Y",
    "Subfile was created",
    "Subfile was deleted",
    "Self was deleted",
    "Self was moved",
    "",
    "Backing fs was unmounted",
    "Event queued overflowed",
    "File was ignored"
};
#define EVENT_NUM 16

int monitor(char *path)
{
    if( NULL == path )
    {
        printf("The path is null ,exit. \n");
        exit(-1);
    }

    int fd = inotify_init();
    if( fd < 0 )
    {
        perror("inotify_init");
        exit(-1);
    }

    int wd = inotify_add_watch( fd, path, IN_MODIFY | IN_CREATE | IN_DELETE );
    if ( wd < 0 )
    {
        perror("inotify_add_watch");
        exit(-1);
    }

    fd_set fd_sets;
    struct timeval time_to_wait;
    FD_ZERO( &fd_sets );
    FD_SET( fd, &fd_sets );

    time_to_wait.tv_sec = 3;
    time_to_wait.tv_usec = 0;

    char buffer[EVENT_BUFF_LEN] = {0};
    int i = 0;
    int j = 0;
    int ret = 0;
    int length = 0;
    while( 1 )
    {
        ret = select( fd + 1, &fd_sets, NULL, NULL, NULL );
        if( ret > 0 )
        {
            if( FD_ISSET( fd, &fd_sets ) )
            {
                length = read( fd, buffer, EVENT_BUFF_LEN );
                if( length < 0 )
                {
                    continue;
                }

                i = 0;
                while ( i < length )
                {
                    struct inotify_event *event = ( struct inotify_event * )( buffer + i );
                    printf("\ninotify name : %s ,mask : %08X \n",event->name,event->mask);
                    for( j = 0; j < EVENT_NUM; j++ )
                    {
                        if ( event_array[j][0] == '\0' )
                        {
                            continue;
                        }
                        else
                        {
                            if ( event->mask & ( 1 << j ) )
                            {
                                printf(" %s ",event_array[j]);
                            }
                        }
                    }

                    i += EVENT_SIZE + event->len ;
                }
                printf("\n");
            }
        }
    }

    inotify_rm_watch( fd, wd );
    close( fd );

    return 0;
}

int main(int argc,char *argv[])
{
    if( 2 != argc )
    {
        printf("%s param\n",argv[0]);
        return -1;
    }

    monitor(argv[1]);

	return 0;
}
