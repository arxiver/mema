#ifndef MEMA_H
#define MEMA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <errno.h>

// Error handling
#define merror(e) printf("pmem: " e "\n")

// Stats macro for dynamic memory allocation
#define ppstats(p) printf("Pool size: %lu, free size: %lu, init: %u\n", p->poolSize, p->freeSize, p->initialized)

// Stats macro for static memory allocation
#define pstats(p) printf("Pool size: %lu, free size: %lu, init: %u\n", p.poolSize, p.freeSize, p.initialized)

typedef struct Block
{
  void *ptr;          // pointer to the data chunk
  size_t size;        // size of the data chunk
  struct Block *next; // pointer to the next block
  struct Block *prev; // pointer to the previous block
  bool poolAllocated; // true if the block is allocated in the pool
} Block;

typedef struct Pool
{
  size_t poolSize;    // BYTES: unsigned int contains the size of the pool
  size_t freeSize;    // BYTES: current pool free size
  bool initialized;   // pool is initialized, true if initialized
  void *mem;          // pointer to the first byte of the pool
  struct Block *head; // head of the list of the allocated blocks
  struct Block *tail; // tail of the list of the allocated blocks
} Pool;

bool initPool(struct Pool *pool, size_t poolSize);
bool freePool(struct Pool *pool);
void *palloc(struct Pool *pool, size_t size);
bool pfree(struct Pool *pool, void *ptr);

#endif // MEMA_H