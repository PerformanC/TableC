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

`tablec_resize` doesn't return any value, due to being a function with type `void`.

## What does it do internally?

`tablec_resize` will first create a new hashtable with the new capacity, and then it will iterate through the old hashtable, and copy the keys and values to the new hashtable, and then it will free the old hashtable, and set the new hashtable to the old hashtable.

## Stability

`tablec_resize` is stable and can be used in a production environment flawlessly, but it's not recommended to use it, since depending on the size of the hashtable, it can take a while to resize it.

## See also

*  [`tablec_init`](tablec_init.md) - Initializing the hashtable.
