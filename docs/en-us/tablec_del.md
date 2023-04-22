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

`tablec_del` doesn't return any value, due to being a function with type `void`.

## What does it do internally?

`tablec_del` will first hash the key and then verify the length of the array that the key is in, in case it's 0, it will ignore and `return;`, in case it's 1 or more, it will iterate through the array, `strcmp`ing the keys, and if it finds the key, it will delete it, and if it doesn't find the key, it will ignore and `return;`.

## Stability

`tablec_del` is stable and can be used in a production environment flawlessly.

## See also

*  [`tablec_set`](tablec_set.md) - Setting values to keys.
*  [`tablec_get`](tablec_get.md) - Getting values based on a key.
