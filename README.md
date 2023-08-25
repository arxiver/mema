# mema (MEmory MAnager)
Memory Manager for C language to maintain the memory allocation and dellactions and works as a memory pool

### Building blocks

The building blocks of the app is two data structs
- Block
```c
typedef struct Block
{
  void *ptr;          // pointer to the data chunk
  size_t size;        // size of the data chunk
  struct Block *next; // pointer to the next block
  struct Block *prev; // pointer to the previous block
  bool poolAllocated; // true if the block is allocated in the pool
} Block;
```

- Pool
```c
typedef struct Pool
{
  size_t poolSize;    // BYTES: unsigned int contains the size of the pool
  size_t freeSize;    // BYTES: current pool free size
  bool initialized;   // pool is initialized, true if initialized
  void *mem;          // pointer to the first byte of the pool
  struct Block *head; // head of the list of the allocated blocks
  struct Block *tail; // tail of the list of the allocated blocks
} Pool;
```

### Diagram of the system

![diagram](./assets/diagram.svg)

### The interface

```c
// Initialize the pool (1)
bool initPool(Pool *pool, size_t poolSize);
// Allocate memory from the pool [chunk] (2)
void *palloc(Pool *pool, size_t size);
// Free memory from the pool [chunk] (3)
bool pfree(Pool *pool, void *ptr);
// Free the pool (destroy) (4)
bool freePool(Pool *pool);
```


### Strategy
- Create Pool with size of poolSize
- Initialize the pool
  - Reserve memory for the pool `malloc(poolSize);`
  - Initialize the pool (setting the freeSize to the poolSize)
- Allocate chunk?
  - Go to the pool and create a new block
    - If the block cannot be allocated from the memory?
      - Allocate from the pool.
    - Free (to the memory) the requested chunk size from the pool if it is available.
    - Allocate the requested chunk size from the memory.
    - Connect the Block which contains a pointer to the allocated mem to the chain of the allocated blocks which is connected to the pool through the (head/tail) ptrs
- Deallocate chunk?
  - Go to the pool and free the block from the memory and the chunk as well add the size to the pool and resize the pool to the new available free size
- Free the pool
  - Go to the chain and free it
  - Free the mem of the pool from the memory
  - Free the pool

### Build
```sh
make clean
make run
```

### Test
```sh
make test
```

### Author
Mohamed Mokhtar [@rrrokhtar](https://github.com/rrrokhtar)


  
