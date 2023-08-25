#include <pool.h>
#include <time.h> // for clock_t, clock(), CLOCKS_PER_SEC

void main()
{
 printf("\n------------- TEST 01 START -----------------\n");
 // clock vars
 double time_spent = 0.0;
 clock_t begin, end;
 
 // Creating the pool
 struct Pool pool;
 bool ok;
 ok = initPool(&pool, MB(2));
 if (!ok)
 {
  merror("failed to init the pool");
  exit(1);
 }

 // Printing the stats of the pool
 pstats(pool);

 // Number of chunks to be allocated
 const int N = 200;
 // Chunk size
 const int CHUNK_SIZE = KB(5);

 // to store the execution time of code
 time_spent = 0.0;
 begin = clock();

 // Intending not to keep pointing to the memory, because it will be freed by freePool
 for (int i = 0; i < N; i++)
 {
  palloc(&pool, CHUNK_SIZE);
 }

 end = clock();

 time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

 printf("Elapsed time for allocating %d chunks of size %d is %lf seconds\n", N, CHUNK_SIZE, time_spent);

 // Freeing the pool
 time_spent = 0.0;
 begin = clock();
 ok = freePool(&pool);
 end = clock();
 time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
 printf("Elapsed time for freeing the pool is %lf seconds\n", time_spent);
 if (!ok)
 {
  merror("freePool failed");
 }
 printf("\n------------- TEST 01 END -----------------\n");
}
