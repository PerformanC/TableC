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

`tablec_get` will return `void *`, which the type will be defined by the type of the value put in the hashtable, and if the key does not exist, it will return `NULL`.

## What does it do internally?

`tablec_get` will do a lot of things internally, and it will be explained in this section, take a look at them:

First, it will see what's the capacity of the bucket, and with it, it will define the best way to try to seek it, in case the capacity is `1`, it will see only one bucket, but if it has `1+` capacity, it will `do {} while();` loop on the slot array to see if it's able to find.
If it can find it, it will return the value of the key, but if it is not able to find it, it will return `NULL`.

## Stability

`tablec_get` is stable, but the dependency of other functions may make it not stable, but the function by itself is stable.

## See also

*  [`tablec_set`](tablec_set.md) - Setting values to keys.
*  [`tablec_del`](tablec_del.md) - Deleting keys of the hashtable.
