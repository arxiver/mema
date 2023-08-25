- Pool Size: 2 MB Block size per memory allocation request: 5 KB

```sh
Pool: 2097152 B,        free: 2097152 B init: 1 #al: 0  #de: 0
Elapsed time for allocating 200 chunks of size 5120 is 0.001617 seconds
Elapsed time for freeing the pool is 0.000062 seconds
```
- Pool Size: 1024 MB Block size per memory allocation request: 2 MB

```sh
Pool: 1073741824 B,     free: 1073741824 B      init: 1 #al: 0  #de: 0
Elapsed time for allocating 500 chunks of size 2097152 is 0.007076 seconds
Elapsed time for freeing the pool is 0.004724 seconds
```

- Pool Size: 1024 MB Block size per memory allocation request: Variable Sized
```sh
Pool: 1073741824 B,     free: 1073741824 B      init: 1 #al: 0  #de: 0
Elapsed time for allocating 50 chunks of size 2097152 is 0.000033 seconds
Elapsed time for allocating 50 chunks of size 1048576 is 0.000171 seconds
Elapsed time for freeing 2 of the ptrs is 0.000108 seconds
Elapsed time for allocating 50 chunks of size 1048576 is 0.000139 seconds
Pool: 1073741824 B,     free: 915406848 B       init: 1 #al: 8  #de: 5
Elapsed time for freeing the bool is 0.000060 seconds
```