# The tablec_resize function

`tablec_resize` is not an important function, whatsoever, it's just a function that resizes the hashtable, and it's used by `tablec_set` when the hashtable is full, but only if the `secure mode` is enabled.

## Usage

`tablec_resize` is simple to use, but if you resize the hashtable with a value that is smaller than the current capacity, it will end up in a crash, so be careful with it.

```c
//             Table   Capacity 
tablec_resize(&tablec,   128);
```

## Parameters

```c
NULL tablec_resize(
  struct tablec_ht *tablec,
  size_t            newCapacity
);
```

`tablec_resize` has only 2 parameters, used to resize the hashtable, take a look at them:

*  `Table`  - `struct tablec_ht` The hashtable variable, is used to save keys and values.
*  `Capacity` - `size_t`         The new capacity of the hashtable.

## Return value

`tablec_resize` will update the hashtable with new one,you will only need to be sure that you have enough run for that and replace the actual one with the new one, all keys will be rehashed and the table will be freed automatically.

## What does it do internally?

`tablec_resize` will simply `realloc` the hashtable to the new capacity, and it will also set the new capacity to the hashtable. 

## Stability

`tablec_resize` is considered unstable, and it's not recommended to use it. 

## See also

*  [`tablec_init`](tablec_init.md) - Initializing the hashtable.
