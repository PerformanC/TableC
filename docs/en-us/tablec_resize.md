# The tablec_resize function

`tablec_resize` is not an important function, whatsoever, it's just a function that resizes the hashtable, and it's used by `tablec_set` when the hashtable is full, but only if the `secure mode` is enabled.

## Usage

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

`tablec_resize` doesn't return any value, due to being a function with type `void`.

## What does it do internally?

1. Creates a new hashtable with the new capacity
2. Iterates through the old hashtable, copying the keys and values to the new hashtable
3. Frees the old hashtable
4. Sets the new hashtable to the old hashtable

## Stability

`tablec_resize` is stable and can be used in a production environment flawlessly.

## See also

*  [`tablec_init`](tablec_init.md) - Initializing the hashtable.
