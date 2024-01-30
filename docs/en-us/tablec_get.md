# The tablec_get function

The `tablec_get` function is used to get the value of a key using the key as a search parameter and returning the value of it.

## Usage

```c
//                                         Table     Key 
struct tablec_bucket *bucket = tablec_get(&tablec, "furry");

printf("[TableC]: Value of the key \"furry\": %d\n", bucket->key, (int)bucket->value);
```

> [!NOTE]
> This functin will return `NULL` if the key does not exist.

## Parameters

```c
struct tablec_bucket *tablec_get(
  struct tablec_ht *tablec,
  char *            key
);
```

`tablec_get` has 2 parameters, used to find the value of it, take a look at them:

*  `Table`  - `struct tablec_ht` The hashtable variable, is used to save keys and values.
*  `Key`    - `char *`           The key to search the value related to it.

## Return value

1. If the key is found, returns a `struct tablec_bucket *` with the `key` and `value` fields.
2. If the key is not found, returns `NULL`.

## What does it do internally?

1. Hashes the key
2. Verifies the capacity of the array of the hash index
    - If it's 0, it will return an empty bucket
    - If it's 1 or more, continue
3. Iterates through the array of the hash index, checking for the key with `strcmp`
    - If it finds it, it will return the bucket
    - If it doesn't, it will return an empty bucket

## Stability

`tablec_get` is stable and can be used in a production environment flawlessly.

## See also

*  [`tablec_set`](tablec_set.md) - Setting values to keys.
*  [`tablec_del`](tablec_del.md) - Deleting keys of the hashtable.
