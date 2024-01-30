# The tablec_full function

The `tablec_full` function allows to check how many buckets are not full, and if the hashtable is full or not. This allows do to optimized resizes, by resizing before the hashtable is full.

## Usage

```c
struct tablec_ht tablec;
//           Table
tablec_full(&tablec);
```

## Parameters

```c
int tablec_full(
  struct tablec_ht *tablec
);
```

`tablec_init` has only one parameters, used to verify if the hashtable is full, take a look at it:

*  `Table` - `struct tablec_ht` The hashtable variable, is used to save keys and values.

## Return value

`tablec_full` returns the value `-1` if the hashtable is full, and the number of empty buckets if not.

## What does it do internally?

1. Checks if the hashtable is full
    - If it is, it will return `-1`
    - If it's not, it will calculate `capacity - length` and return the value

## Stability

`tablec_full` is stable and can be used in a production environment flawlessly.

## See also

*  [`tablec_resize`](tablec_resize.md) - Resizes the hashtable.
