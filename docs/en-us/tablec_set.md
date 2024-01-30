# The tablec_set function

`tablec_set` is a function that saves a key and a value to the hashtable.

## Usage

```c
//          Table     Key       Value
tablec_set(&tablec, "furry", (void *)true);
```

## Parameters

```c
NULL tablec_set(
  struct tablec_ht *tablec,
  char *            key
  void *            value
);
```

`tablec_set` is the function with the most parameters, having 4 parameters, take a look at them:

*  `Table`  - `struct tablec_ht` The hashtable variable, is used to save keys and values.
*  `Key`    - `char *`           The key to search the value related to it.
*  `Value`  - `void *`           The value to save to the key.

## Return value

`tablec_set` doesn't return any value, due to being a function with type `void`.

## What does it do internally?

1. Hashes the key
2. Verifies the capacity of the array of the hash index
    - If it's full, it will do a optimized resize
    - If it's empty, continue
3. Iterates through the array of the hash index, checking for empty slots
    - If it finds one, it will add the key to it
    - If it doesn't, it will allocate new slots (capacity * 2) and copy the existing keys to the new slots, and then add the key to the first slot empty.
4. Saves the value to the key
5. Increments the length of the hashtable

## Stability

`tablec_set` is stable and can be used in a production environment flawlessly.

## See also

*  [`tablec_get`](tablec_get.md) - Getting values based on a key.
*  [`tablec_del`](tablec_del.md) - Deleting keys of the hashtable.
