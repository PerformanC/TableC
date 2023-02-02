# The tablec_full function

The `tablec_full` function is a basic function to allow you to check if the hashtable is full or not, and not break your code when any change happens to the structures.

## Usage

`tablec_full` uses basic math to check if the hashtable is full or not, and it will return a value, which is -1 if it's full, and the number of buckets that are not full if it's not full.

```c
struct tablec_ht tablec;
//           Table
tablec_full(&tablec);
```

## Parameters

```c
long tablec_full(
  struct tablec_ht *tablec
);
```

`tablec_init` has only one parameters, used to verify if the hashtable is full, take a look at it:

*  `Table`       - `struct tablec_ht` The hashtable variable, is used to save keys and values.

## Return value

`tablec_full` returns the value `-1` if the hashtable is full, and the number of buckets that are not full if it's not full.

## What does it do internally?

`tablec_full` does a simple math calculation, capacity - length, and returns the value.

## Stability

`tablec_full` is stable, since there is no possibility of failure.

## See also

*  [`tablec_resize`](tablec_resize.md) - Resizes the hashtable.
