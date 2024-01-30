# The tablec_del function

`tablec_del` is an important function since it's one of the systems used by TableC to accelerate the `tablec_set` function, using the empty slots array as one of its main features.

## Usage

```c
//          Table     Key
tablec_del(&tablec, "furry");
```

## Parameters

```c
NULL tablec_del(
  struct tablec_ht *tablec,
  char *            key
);
```

`tablec_del` has 3 parameters, used to delete the key and value, take a look at them:

*  `Table`  - `struct tablec_ht` The hashtable variable, is used to save keys and values.
*  `Key`    - `char *`           The key to delete the key and value related to it.

## Return value

`tablec_del` doesn't return any value, due to being a function with type `void`.

## What does it do internally?

1. Hashes the key
2. Verifies the capacity of the array of the hash index
    - If it's 0, it will ignore and `return;`
    - If it's 1 or more, continue
3. Iterates through the array of the hash index, checking for the key with `strcmp`
    - If it finds it, it will delete the key and value
    - If it doesn't, it will ignore and `return;`
4. Decrements the length of the hashtable

## Stability

`tablec_del` is stable and can be used in a production environment flawlessly.

## See also

*  [`tablec_set`](tablec_set.md) - Setting values to keys.
*  [`tablec_get`](tablec_get.md) - Getting values based on a key.
