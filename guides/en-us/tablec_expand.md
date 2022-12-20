# The tablec_resize function

`tablec_resize` is not an important function, whatsoever, it's just a function that expands the hashtable, and it's used by `tablec_set` when the hashtable is full, but only if the `secure mode` is enabled.

## Usage

`tablec_resize` is simple to use, but if you resize the hashtable with a value that is smaller than the current capacity, it will end up in a crash, so be careful with it.

```c
//             Table   Capacity 
tablec_resize(&tablec,   128);
```

## Parameters

```c
NULL tablec_resize(
  struct hashtable *tablec,
  size_t            newCapacity
);
```

`tablec_resize` has only 2 parameters, used to resize the hashtable, take a look at them:

*  `Table`  - `struct hashtable` The hashtable variable, is used to save keys and values.
*  `Capacity` - `size_t`         The new capacity of the hashtable.

## Return value

`tablec_resize` doesn't return anything, since there is nothing to return, it will just resize the hashtable.

## What does it do internally?

`tablec_resize` will simply `realloc` the hashtable to the new capacity, and it will also set the new capacity to the hashtable. 

## Stability

`tablec_resize` is rock stable because it's a small function and can't cause any problems, except if you don't have any more RAM. 

## See also

*  [`tablec_init`](tablec_init.md) - Initializing the hashtable.
