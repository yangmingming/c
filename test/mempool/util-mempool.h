
#ifndef __MEMPOOL_MEMPOOL_H__
#define __MEMPOOL_MEMPOOL_H__
#include <stddef.h>
#include <stdlib.h>

/*use external memory block*/
#define MEMPOOL_MODE_EXT_MEM    1
/*free the memory even though using external memory block*/
#define MEMPOOL_MODE_FORCE_FREE 2
/*multi-thread surpport, not implemented*/
#define MEMPOOL_MODE_SYN        4

typedef struct MemPool_ MemPool;
/* 
 *MemPool create functions
 *itemsize:  the size of objects this pool deal with
 *blocksize:
 *    mode = !MEMPOOL_MODE_EXT_MEM: the block size
 *    mode = MEMPOOL_MODE_EXT_MEM: the size of external memory block
 *extmem: the address of external memory block when mode=MEMPOOL_MODE_EXT_MEM, otherwise, no use.
 *max_mem_usage: 
 *    0 for umlimited memory usage
 *    mode = MEMPOOL_MODE_EXT_MEM: no use
 */
MemPool *MempoolCreateByOption( size_t itemsize,
                                size_t blocksize, int mode, void *extmem, size_t max_mem_usage);
								   
/*the pool malloc memory from the system with unlimited allocations*/
MemPool *MempoolCreate(const size_t itemsize, const size_t blocksize);
/*use external memory and the memory will not be freed when the pool is destoryed*/
MemPool *MempoolCreateEx(const size_t itemsize, const size_t blocksize, void *extmem);

/*set maximum memory usage, only valid for mode !MEMPOOL_MODE_EXT_MEM*/
void  MempoolSetMaxUsage(MemPool *pool, size_t max_mem_usage);

/* mempool_alloc */
void *MempoolAlloc(MemPool * const pool);

/* mempool_calloc */
void *MempoolCalloc(MemPool * const pool);

/* mempool_free */
int  MempoolFree(MemPool * const pool, void *data);

/* mempool_destroy */
void MempoolDestroy(MemPool *pool);

#endif /* _CP_MEMPOOL_H */

