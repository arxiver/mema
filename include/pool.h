#ifndef MEMA_H
#define MEMA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <errno.h>

// Utils macros for testing
#define MB(m) 1024 * 1024 * m
#define KB(m) 1024 * m

// Error handling
#define merror(e) printf("pmem: " e "\n")

// Stats macro for dynamic memory allocation
#define ppstats(p) printf("Pool size: %lu, free size: %lu, init: %u, #al: %lu, #de: %lu\n", p->poolSize, p->freeSize, p->initialized, p->allocatedCount, p->deallocatedCount)

// Stats macro for static memory allocation
#define pstats(p) printf("Pool: %lu B,\tfree: %lu B\tinit: %u\t#al: %lu \t#de: %lu\n", p.poolSize, p.freeSize, p.initialized, p.allocatedCount, p.deallocatedCount)

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
  size_t allocatedCount;   // number of allocated blocks
  size_t deallocatedCount; // number of deallocated blocks
  size_t poolSize;         // BYTES: unsigned int contains the size of the pool
  size_t freeSize;         // BYTES: current pool free size
  bool initialized;        // pool is initialized, true if initialized
  void *mem;               // pointer to the first byte of the pool
  struct Block *head;      // head of the list of the allocated blocks
  struct Block *tail;      // tail of the list of the allocated blocks
} Pool;

// Initialization
bool initPool(Pool *pool, size_t poolSize);

// Free/Destruction
bool freePool(Pool *pool);

// Memory allocation
void *palloc(Pool *pool, size_t size);

// Memory deallocation
bool pfree(Pool *pool, void *ptr);

#endif // MEMA_H