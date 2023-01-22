# The tablec_del function

`tablec_del` is an important function since it's one of the systems used by TableC to accelerate the `tablec_set` function, using the empty slots array as one of its main features.

## Usage

`tablec_del` is the easiest function since it requires few parameters, and it's easy to understand, this will be an example of deleting the key `furry`:

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

`tablec_del` doesn't return anything, no successful or failed return, it will just delete the key and value related to it. and if it doesn't find a related key, it will just ignore it since this is something you should do, and this is a low-level API.

## What does it do internally?

`tablec_del` is a difficult function to explain what does it do, because of that, it will be explained differently, in a resumed way:

First, it will see what's the capacity of the bucket, and with it, it will define if it should use the `do {} while();` loop or not, since it might be required for searching for slots, and after finding the slot, it will add to the list of empty slots the slot that it found, and it will set the key and value to `NULL`.

## Stability


`tablec_del` is not stable, because of being complex and having many if statements, which makes it hard to debug, but even with that, it's safe to use it.

## See also

*  [`tablec_set`](tablec_set.md) - Setting values to keys.
*  [`tablec_get`](tablec_get.md) - Getting values based on a key.
