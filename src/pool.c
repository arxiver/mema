
#include "pool.h"

bool initPool(struct Pool *pool, size_t poolSize)
{
  pool->freeSize = poolSize;
  pool->poolSize = poolSize;
  pool->mem = malloc(poolSize);
  if (pool->mem == NULL)
  {
    return false;
  }
  pool->initialized = true;
  return true;
}

bool freePool(struct Pool *pool)
{
  if (!pool->initialized)
    return false;
  // free blocks allocated
  struct Block *b = pool->head;
  while (b != NULL)
  {
    pool->head = b->next;
    // free the chunk
    free(b->ptr);
    // free the block
    free(b);
    b = pool->head;
  }
  if (pool->freeSize != 0)
    free(pool->mem);
  return true;
}

bool pfree(struct Pool *pool, void *ptr)
{
  // If pool is not initialized, return false
  if (!pool->initialized)
    return false;
  // Find the block that contains the provided pointer
  struct Block *b = pool->head;
  while (b != NULL)
    if (b->ptr == ptr)
      break;
  // If not found, return false
  if (b == NULL)
    return false;

  // if the block is the head, update the head
  if (pool->head == b)
    pool->head = b->next;

  // if the block is the tail, update the tail
  if (pool->tail == b)
    pool->tail = b->prev;

  // Disconnect the block from the list
  if (b->prev != NULL)
    b->prev->next = b->next;

  // Regain memory to the pool
  // - from the chunk
  pool->freeSize += b->size;
  // - from the block
  if (b->poolAllocated)
  {
    pool->freeSize += sizeof(struct Block);
  }
  // to the pool
  void *ret = realloc(pool->mem, pool->freeSize);
  if (ret == NULL)
  {
    merror("block allocation failed");
    return false;
  }
  else
  {
    pool->mem = ret;
  }

  free(ptr);
  free(b);
  b = NULL;
  ptr = NULL;
  return true;
}

void *palloc(struct Pool *pool, size_t size)
{
  void *ret;
  if (!pool->initialized)
  {
    merror("pool not initialized");
    return NULL;
  }
  if (size > pool->freeSize)
  {
    merror("no memory available");
    return NULL;
  }
  // Create block instance
  struct Block *b = (struct Block *)malloc(sizeof(struct Block));
  if (b == NULL)
  {
    // Make use of the pool memory
    pool->freeSize -= sizeof(struct Block);
    ret = realloc(pool->mem, pool->freeSize);
    if (ret == NULL && pool->freeSize != 0)
    {
      merror("block allocation failed (1) while reallocating pool");
      return NULL;
    }
    else
    {
      pool->mem = ret;
    }
    b = (struct Block *)malloc(sizeof(struct Block));
    b->poolAllocated = true;
    if (b == NULL)
    {
      // regain memory to the pool
      pool->freeSize += sizeof(struct Block);
      ret = realloc(pool->mem, pool->freeSize);
      if (ret == NULL && pool->freeSize != 0)
      {
        merror("block allocation & restoration failed (1) while reallocating pool");
        return NULL;
      }
      else
      {
        pool->mem = ret;
      }
      merror("block allocation failed (1) while allocating block in the mem");
      return NULL;
    }
  }
  // Add block to the list at the tail
  b->prev = pool->tail;
  b->next = NULL;
  b->size = size;

  // Add block to the list
  // if the pool is empty (head == NULL)
  if (pool->head == NULL)
  {
    pool->head = b;
    pool->tail = b;
  }
  else
  {
    pool->tail->next = b;
    pool->tail = b;
  }

  // Reduce pool free size
  pool->freeSize -= size;

  // Re-allocate memory
  ret = realloc(pool->mem, pool->freeSize);
  if (ret == NULL && pool->freeSize != 0)
  {
    merror("chunk allocation failed (1) while reallocating pool");
    return NULL;
  }
  // Set the pointer to the resized memory
  pool->mem = ret;

  // Allocate chunk in the pool
  b->ptr = malloc(size);
  if (b->ptr == NULL)
  {
    // Regain memory to the pool
    pool->freeSize += size;
    if (b->poolAllocated)
    {
      free(b);
      pool->freeSize += sizeof(struct Block);
    }
    else
    {
      free(b);
    }
    ret = realloc(pool->mem, pool->freeSize);
    if (ret == NULL && pool->freeSize != 0)
    {
      merror("chunk allocation & restoration failed (2) while reallocating pool");
      return NULL;
    }
    pool->mem = ret;
    merror("chunk allocation failed (2) while allocating chunk in the mem");
    return NULL;
  }
  return b->ptr;
}
