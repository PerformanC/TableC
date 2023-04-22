# The tablec_get function

The `tablec_get` function is used to get the value of a key using the key as a search parameter and returning the value of it.

## Usage

`tablec_get` is an easy function to use, and your syntax is easy to understand and read, this will be an example of getting the set value of the key `furry`:

```c
//                      Table     Key 
int value = tablec_get(&tablec, "furry");

printf("[TableC]: Value of the key \"furry\": %d\n", value);
```

Remember that this will only return the value of the key if you have set it before, if you haven't set it, it will return `NULL`. In case you want to set it, see the [`tablec_set`](tablec_set.md) docs to see how to set it.

## Parameters

```c
void *tablec_get(
  struct tablec_ht *tablec,
  char *            key
);
```

`tablec_get` has 3 parameters, used to find the value of it, take a look at them:

*  `Table`  - `struct tablec_ht` The hashtable variable, is used to save keys and values.
*  `Key`    - `char *`           The key to search the value related to it.

## Return value

`tablec_get` will return `void *`, in which the type is the same as the value of the key, and if the key does not exist, it will return `NULL`.

## What does it do internally?

`tablec_get` will first hash the key and then verify the length of the array that the key is in, in case it's 0, it will ignore and `return;`, in case it's 1 or more, it will iterate through the array, `strcmp`ing the keys, and if it finds the key, it will return the value of it, and if it doesn't find the key, it will ignore and `return;`.

## Stability

`tablec_get` is stable and can be used in a production environment flawlessly.

## See also

*  [`tablec_set`](tablec_set.md) - Setting values to keys.
*  [`tablec_del`](tablec_del.md) - Deleting keys of the hashtable.
