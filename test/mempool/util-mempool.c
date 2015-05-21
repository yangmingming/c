
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include "util-mempool.h"

#ifdef _HAS_GETPAGESIZE
#include <unistd.h>		       /* for getpagesize() */
#else
int getpagesize() { return 0x1000; } /*4096*/
#endif

#ifndef WORD_SIZE
#define WORD_SIZE (sizeof(void *))
#endif /* WORD_SIZE */

static size_t pagesize = 0;

struct MemPool_
{
	size_t item_size;        /*the size of objects in this pool*/
	size_t block_size;       /*the block size that the pool allocates from system at a time*/
	size_t items_per_block;  /*number of items per block*/

	 /*maximum blocks the pool can allocate from the system
	  *max_allocs_==0: unlimited allocations */
	size_t max_blocks;
	size_t n_blocks;         /*number of blocks allocated*/
	size_t n_items;          /*number of items allocated in this block*/

	int   mode;
	char *reuse_pool;        /*list of freed objects*/
	char *alloc_pool;        /*current page*/
	char *alloc_start;   /*the allocation start position in current block*/
};

MemPool *MempoolCreateByOption( size_t itemsize,
                                   size_t blocksize, int mode, void *extmem, size_t max_mem_usage)
{
	MemPool *pool = (MemPool *) calloc(1, sizeof(MemPool));
	if (pool == NULL) return NULL;

	/*Get the physical page size*/
	if (pagesize == 0) pagesize = getpagesize();
	/*Round the item size to multiple word size*/
	if (itemsize < sizeof(void*)) itemsize = sizeof(void*);
	if (itemsize % WORD_SIZE)
		itemsize += ((WORD_SIZE) - (itemsize % WORD_SIZE));
	pool->item_size = itemsize;
	
	pool->mode = mode;
	pool->reuse_pool = NULL;
	if(  mode & MEMPOOL_MODE_EXT_MEM ) // use external memory
	{
		if( !extmem ) 
		{
			free(pool);
			return NULL;
		}
		pool->block_size  = blocksize;
		pool->items_per_block = blocksize/itemsize; //no need to hold an pointer
		pool->n_items     = 0;
		pool->alloc_pool  = (char *) extmem;
		pool->alloc_start = pool->alloc_pool;
	}
	else
	{
		/*make sure the block size larger than 16 itemsizes to improve performance*/
		if (blocksize < itemsize * 16 + sizeof(void *))
			blocksize = itemsize * 16 + sizeof(void *);
		/*if (blocksize < pagesize * 10) blocksize = pagesize * 10;*/
		/*make sure the block size is multiple times of pagesizes*/
		if (blocksize % pagesize)
			blocksize += (pagesize - (blocksize % pagesize));
		pool->block_size = blocksize;

		pool->items_per_block = (blocksize - sizeof(void *)) / itemsize;
		if( max_mem_usage )
		{
			pool->max_blocks = max_mem_usage/blocksize;
			if( pool->max_blocks < 1 ) pool->max_blocks = 1;
		}
		
		pool->n_blocks   = 0;
		/*triger a allocation when next mempool_alloc come*/
		pool->n_items    = pool->items_per_block;
		pool->alloc_start = NULL;
		pool->alloc_pool  = NULL;
	}
	return pool;
}							   

MemPool *MempoolCreate(const size_t itemsize, const size_t blocksize)
{
	return MempoolCreateByOption( itemsize, blocksize, 0, NULL, 0);
}

MemPool *MempoolCreateEx(const size_t itemsize, const size_t blocksize, void *extmem)
{
	return MempoolCreateByOption( itemsize, blocksize, MEMPOOL_MODE_EXT_MEM, extmem, 0);
}

void *MempoolAlloc(MemPool * const pool)
{
	void *p;

	if (pool->reuse_pool)
	{
		/*if there have freed objects, return one of them*/
		p = pool->reuse_pool;
		pool->reuse_pool = *(void **)p;
	}
	else
	{
		/*the space of current block has been run out of*/
		if (pool->n_items == pool->items_per_block)
		{
			if( pool->mode & MEMPOOL_MODE_EXT_MEM )
				return NULL;
			
			if( pool->max_blocks && (pool->n_blocks==pool->max_blocks) )
				return NULL;
			
			p = malloc(pool->block_size);
			if (p == NULL) return NULL;
			/*
			 * printf("Allocate a new block: %p\n", p);
			 */
			*(void **) p = pool->alloc_pool;
			pool->alloc_pool  = p;
			pool->alloc_start = pool->alloc_pool + sizeof(void *);
			pool->n_items     = 0;
			pool->n_blocks++;
		}
		p = pool->alloc_start + pool->item_size*pool->n_items++;
	}

	return p;
}

void  MempoolSetMaxUsage(MemPool *pool, size_t max_mem_usage)
{
	pool->max_blocks = max_mem_usage/pool->block_size;
	if( pool->max_blocks < 1 ) pool->max_blocks = 1;
}

void *MempoolCalloc(MemPool * const pool)
{
	void *p = MempoolAlloc(pool);
	if (p)
		memset(p, 0, pool->item_size);
	return p;
}

int MempoolFree(MemPool * const pool, void *data)
{
	*(void **) data = pool->reuse_pool;
	pool->reuse_pool = data;
	return 0;
}

void MempoolDestroy(MemPool *pool)
{
	if (pool)
	{
		if( !(pool->mode & MEMPOOL_MODE_EXT_MEM) )
		{
			/*free all blocks if the pool do not use external memorys*/
			void *p;
			int  cnt = 0;
			while ((p = pool->alloc_pool))
			{
				pool->alloc_pool = *(void **) pool->alloc_pool;
				//printf("Destroy a block: %p\n", p);
				free(p);
				cnt++;
			}
			//printf("%d blocks have been freed\n", cnt);
		}
		else if( pool->mode & MEMPOOL_MODE_FORCE_FREE )
		{
			/*if the pool set MEMPOOL_MODE_FORCE_FREE, free the block*/
			free(pool->alloc_pool);
		}
		free(pool);
	}
}


