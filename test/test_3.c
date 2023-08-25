#include <pool.h>
#include <time.h> // for clock_t, clock(), CLOCKS_PER_SEC

void main()
{
 printf("\n------------- TEST 03 START -----------------\n");
 // clock vars
 double time_spent = 0.0;
 clock_t begin, end;
 // Creating the pool
 struct Pool pool;
 bool ok;
 ok = initPool(&pool, MB(1024));
 if (!ok)
 {
  merror("failed to init the pool");
  exit(1);
 }

 // Printing the stats of the pool
 pstats(pool);

 // Number of chunks to be allocated
 int N = 50;
 // Chunk size
 int CHUNK_SIZE = MB(2);

 // to store the execution time of code
 time_spent = 0.0;
 begin = clock();

 void *chunks = palloc(&pool, CHUNK_SIZE * N);

 end = clock();

 time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

 printf("Elapsed time for allocating %d chunks of size %d is %lf seconds\n", N, CHUNK_SIZE, time_spent);

 // Different sizes
 N = 50;
 CHUNK_SIZE = MB(1);

 // to store the execution time of code
 begin = clock();
 void *ptrs[N];
 for (int i = 0; i < N; i++)
 {
  ptrs[i] = palloc(&pool, CHUNK_SIZE);
 }
 int BULK_COUNT = 10;
 void *bulk_chunks = palloc(&pool, CHUNK_SIZE * BULK_COUNT);
 end = clock();
 time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
 printf("Elapsed time for allocating %d chunks of size %d is %lf seconds\n", BULK_COUNT, CHUNK_SIZE, time_spent);

 // Free some of the ptrs
 time_spent = 0.0;
 begin = clock();
 for (int i = 0; i < N / 2; i++)
 {
  pfree(&pool, ptrs[i]);
 }
 end = clock();
 time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
 printf("Elapsed time for freeing %d of the ptrs is %lf seconds\n", N / 2, time_spent);

 // Create another bulk chunk
 begin = clock();
 void *bulk_chunks2 = palloc(&pool, CHUNK_SIZE);
 end = clock();
 time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
 printf("Elapsed time for allocating %d chunks of size %d is %lf seconds\n", BULK_COUNT, CHUNK_SIZE, time_spent);
 pstats(pool);

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
 printf("\n------------- TEST 03 END -----------------\n");
}
