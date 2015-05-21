/******************************************************************
 *  @file       pthread_spinlock.c
 *  @version    v1.0 
 *  @author     ymm 
 *  @date       2015/04/28
 *  @brief      查看 pthread_spinlock_t 锁在不同情况下的不同值
 *  @history      
 *  1、2015/04/28  author ymm    初步完成
 ******************************************************************/

#include <stdio.h>
#include <string.h>
#include <pthread.h>

int main(int argc,char *argv[])
{
    pthread_spinlock_t lock;
    printf("uninit %d\n",lock);
    int ret = pthread_spin_init( &lock, PTHREAD_PROCESS_PRIVATE );
    if( 0 != ret )
    {
        printf("lock init error\n");
        return -1;
    }
    printf("after init %d\n",lock);
    pthread_spin_lock( &lock );
    printf("after lock %d\n",lock);
    pthread_spin_unlock( &lock );
    printf("after unlock %d\n",lock);
    pthread_spin_unlock( &lock );
    printf("after unlock 2 %d\n",lock);
    pthread_spin_destroy( &lock );
    printf("after destroy %d\n",lock);

	return 0;
}
