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

`tablec_set` doesn't actually return anything, but if the hashtable is full, it will print to the console, enabling `secure mode` will make TableC handle it for you, and it will expand the hashtable, as you would manually do, but internally.

## What does it do internally?

`tablec_set` is by far the most complicated function of whole TableC, it will do a lot of things internally, and it will be explained resumidly in this section, take a look at them:

First, it will look if the first key of the hashtable is filled, if it's not, it will fill and it will rapidly be done, if not, it will search for empty slots in the empty slots array, and if it still doesn't find any available slot, the bucket array will be resized, and the new slot will be filled with the key and value.

## Stability

`tablec_set` is not stable, it is by far the most important function, and the biggest one, making it hard to predict and fix bugs, but it is stable enough for small projects.

## See also

*  [`tablec_get`](tablec_get.md) - Getting values based on a key.
*  [`tablec_del`](tablec_del.md) - Deleting keys of the hashtable.
