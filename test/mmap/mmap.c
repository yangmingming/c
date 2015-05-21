#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <sys/mman.h>
#include <errno.h>
#define READFILE_BUFFER_SIZE 1050 * 1024 * 1024

int main()
{
    uint32_t read_len = (READFILE_BUFFER_SIZE + 4095) & ~4095U;
    uint8_t *read_buffer = (uint8_t *)mmap(0, read_len, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    if ( MAP_FAILED == read_buffer )
    {
        printf("mmap error!errno=%d\n",errno);
        return -1;
    }
    printf("errno=%d\n",errno);

    if( read_buffer ){
        munmap(read_buffer, read_len);
        read_buffer = NULL;
    }

	return 0;
}
