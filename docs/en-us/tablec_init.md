# The tablec_init function

The `tablec_init` function is the most important function, which initialized the hashtable so it can be used, allocates the buckets and the hashtable itself, sets the max capacity and the empty slots, and pretty much everything important.

## Usage

`tablec_init` is easy to comprehend, but you need to pay attention to the hashtable maximum capacity, which if you set more keys than the maximum capacity, would end up not working, so be careful with it.

```c
struct tablec_ht tablec;
//          Table     Capacity
tablec_init(&tablec,   314159);
```

## Parameters

`tablec_init` has 3 parameters, used to initialize and allocate some fields, take a look at them:

*  `Table`       - `struct tablec_ht` The hashtable variable, is used to save keys and values.
*  `Capacity`    - `size_t`           The maximum capacity of the hashtable.

## Return value

`tablec_init` doesn't return any values, but in fact, changes some values of the TableC hashtable struct, this is because there is nothing that can go wrong with it, only if you don't have more RAM to allocate.

## What does it do internally?

`tablec_init` will simply `malloc` the hashtable to the capacity, and it will also set the capacity to the hashtable variables.

## Stability

`tablec_init` is considered stable because it doesn't have anything that could segfault your software, it's just a simple function that allocates memory.

## See also

*  [`tablec_set`](tablec_set.md) - Setting values to keys.
*  [`tablec_get`](tablec_get.md) - Getting values based on a key.
*  [`tablec_del`](tablec_del.md) - Deleting keys of the hashtable.
*  [`tablec_resize`](tablec_resize.md) - Resizes the hashtable.
