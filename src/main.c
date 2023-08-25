#include <pool.h>

void main()
{
 struct Pool pool;
 bool ok;
 ok = initPool(&pool, 10);
 if (!ok)
  return;
 pstats(pool);
 int *a = (int *)palloc(&pool, 4);
 int *b = (int *)palloc(&pool, 6);
 *a = 10;
 *b = 20;
 printf("a: %d\n", *a);
 printf("b: %d\n", *b);
 pstats(pool);
 ok = pfree(&pool, a);
 if (!ok)
 {
  perror("pfree failed");
 }
 a = (int *)palloc(&pool, 2);
 *a = 5;
 pstats(pool);
 printf("a: %d\n", *a);
 ok = pfree(&pool, b);
 if (!ok)
 {
  perror("pfree failed");
 }
 pstats(pool);
 ok = pfree(&pool, a);
 if (!ok)
 {
  perror("pfree failed");
 }
 ok = freePool(&pool);
 if (!ok)
 {
  perror("freePool failed");
 }
}
