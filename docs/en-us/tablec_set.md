# The tablec_set function

`tablec_set` is a function that saves a key and a value to the hashtable.

## Usage

`tablec_set` is a flexible function, which can allow you to save any type of value on it, with one limitation, the key must be a `char *`, but the value can be anything, and it will be saved as a `void *`, which means that you will need to cast it to the type you want to use it.

The example below will save a key named `furry` with the value `true`:

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

`tablec_set` will first hash the key and then verify the capacity of the array of the hash index, if it's 0, it will check the length of the array, if it's 1 (full), it will allocate a new space, copy the existing key to the new allocation and add the key to it, if it's 0 (empty), it will add the key to the array, now, if it's 1 or more, it will iterate through the array, checking for empty slots, if it finds one, it will add the key to it, if it doesn't, it will allocate new slots (capacity * 2) and copy the existing keys to the new slots, and then add the key to the first slot empty.

## Stability

`tablec_set` is stable and can be used in a production environment flawlessly.

## See also

*  [`tablec_get`](tablec_get.md) - Getting values based on a key.
*  [`tablec_del`](tablec_del.md) - Deleting keys of the hashtable.
