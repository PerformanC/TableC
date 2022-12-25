#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tablec.h"

void tablec_init(struct hashtable *tablec, size_t max_capacity, int secure_mode) {
  size_t i = 0;

  (*tablec).secure_mode = secure_mode;
  (*tablec).length = 0;
  (*tablec).capacity = max_capacity;
  (*tablec).buckets = malloc(sizeof(struct hashtable_buckets) * max_capacity);

  do {
    (*tablec).buckets[i].capacity = 1;
    (*tablec).buckets[i].emptyCapacity = 0;
    (*tablec).buckets[i].length = 0;
    (*tablec).buckets[i].array = calloc(sizeof(struct hashtable_buckets_array), 1);

    i++;
  } while (i < max_capacity);
}

void tablec_resize(struct hashtable *tablec, size_t new_max_capacity) {
  /* TODO: Add rehashing when resizing hashtable because it will cause __tablec_hash to not find the keys if not. */
  tablec->capacity = new_max_capacity;
  tablec->buckets = realloc(tablec->buckets, sizeof(struct hashtable_buckets) * new_max_capacity);
}

void __tablec_expandBucketArr(struct hashtable_buckets *bucket, size_t new_max_capacity) {
  bucket->capacity = new_max_capacity;
  bucket->array = realloc(bucket->array, sizeof(struct hashtable_buckets_array) * new_max_capacity);
}

size_t __tablec_hash(struct hashtable *tablec, char *key, size_t keyLength) {
  size_t hash = 0, i = 0;

  if (keyLength == 0) keyLength = strlen(key);

  do {
    hash = hash * 37 + (key[i] & 255);
    i++;
  } while (i < keyLength);

  return hash % tablec->capacity;
}

void tablec_set(struct hashtable *tablec, char *key, size_t keyLength, void *value) {
  size_t hash;
  if (tablec->length >= tablec->capacity) {
    if (tablec->secure_mode) {
      tablec_resize(tablec, tablec->capacity * 2);
    } else {
      printf("TableC error, the buckets are full. Use tablec_expand or secure mode to fix.\n");
    }
  }
  hash = __tablec_hash(tablec, key, keyLength);

  tablec->length++;

  if (tablec->buckets[hash].capacity == 1) {
    if (tablec->buckets[hash].array[0].key == NULL) {
      tablec->buckets[hash].array[0].key = key;
      tablec->buckets[hash].array[0].value = value;

      tablec->buckets[hash].length = 1;
      return;
    } else {
      __tablec_expandBucketArr(&tablec->buckets[hash], 2);

      tablec->buckets[hash].array[1].key = key;
      tablec->buckets[hash].array[1].value = value;

      tablec->buckets[hash].length = 2;
      return;
    }
  } else {
    switch(tablec->buckets[hash].emptyCapacity) {
      case 0: {
        size_t i = -1;

        do {
          i++;
          if (tablec->buckets[hash].array[i].key == NULL) {
            tablec->buckets[hash].array[i].key = key;
            tablec->buckets[hash].array[i].value = value;

            tablec->buckets[hash].length++;
            break;
          }

          if (i != tablec->buckets[hash].length - 1) continue;

          __tablec_expandBucketArr(&tablec->buckets[hash], tablec->buckets[hash].capacity * 2);

          tablec->buckets[hash].array[tablec->buckets[hash].capacity - 1].key = key;
          tablec->buckets[hash].array[tablec->buckets[hash].capacity - 1].value = value;

          tablec->buckets[hash].length++;

          break;
        } while (i < tablec->buckets[hash].length);

        break;
      }
      case 1: {
        if (tablec->buckets[hash].emptySlots[0].filled) {
          tablec->buckets[hash].array[tablec->buckets[hash].emptySlots[0].index].key = key;
          tablec->buckets[hash].array[tablec->buckets[hash].emptySlots[0].index].value = value;

          tablec->buckets[hash].emptySlots[0].index = 0;
          tablec->buckets[hash].emptySlots[0].filled = 0;

          break;
        }

         __tablec_expandBucketArr(&tablec->buckets[hash], tablec->buckets[hash].capacity * 2);

        tablec->buckets[hash].array[tablec->buckets[hash].emptySlots[0].index].key = key;
        tablec->buckets[hash].array[tablec->buckets[hash].emptySlots[0].index].value = value;

        tablec->buckets[hash].emptySlots[0].index = 0;
        tablec->buckets[hash].emptySlots[0].filled = 0;

        break;
      }
      default: {
        size_t i = 0;

        do {
          if (tablec->buckets[hash].emptySlots[i].filled) {
            tablec->buckets[hash].array[tablec->buckets[hash].emptySlots[i].index].key = key;
            tablec->buckets[hash].array[tablec->buckets[hash].emptySlots[i].index].value = value;

            tablec->buckets[hash].emptySlots[i].index = 0;
            tablec->buckets[hash].emptySlots[i].filled = 0;

            tablec->buckets[hash].length++;
            break;
          }

          if (i == tablec->buckets[hash].emptyCapacity - 1) {
            __tablec_expandBucketArr(&tablec->buckets[hash], tablec->buckets[hash].capacity * 2);

            tablec->buckets[hash].array[tablec->buckets[hash].capacity - 1].key = key;
            tablec->buckets[hash].array[tablec->buckets[hash].capacity - 1].value = value;

            tablec->buckets[hash].length++;
            break;
          }
        } while (i < tablec->buckets[hash].emptyCapacity);

        break;
      }
    }
  }
}

void tablec_del(struct hashtable *tablec, char *key, size_t keyLength) {
  size_t hash = __tablec_hash(tablec, key, keyLength);

  tablec->length--;

  if (tablec->buckets[hash].capacity == 1) {
    tablec->buckets[hash].array[0].key = NULL;
    tablec->buckets[hash].array[0].value = NULL;
  } else {
    size_t i = -1;
    do {
      i++;
      if (tablec->buckets[hash].array[i].key == NULL || strcmp(tablec->buckets[hash].array[i].key, key) != 0) continue;

      tablec->buckets[hash].array[i].key = NULL;
      tablec->buckets[hash].array[i].value = NULL;

      break;
    } while (i < tablec->buckets[hash].length);

    switch(tablec->buckets[hash].emptyCapacity) {
      case 0: {
        tablec->buckets[hash].emptyCapacity++;
        tablec->buckets[hash].emptySlots = malloc(sizeof(struct hashtable_buckets_array_empty));

        tablec->buckets[hash].emptySlots[0].index = i;
        tablec->buckets[hash].emptySlots[0].filled = 1;

        break;
      }
      case 1: {
        if (tablec->buckets[hash].emptySlots[0].filled) {
          tablec->buckets[hash].emptyCapacity++;
          tablec->buckets[hash].emptySlots = malloc(sizeof(struct hashtable_buckets_array_empty) * tablec->buckets[hash].emptyCapacity);

          tablec->buckets[hash].emptySlots[tablec->buckets[hash].emptyCapacity - 1].index = i;
          tablec->buckets[hash].emptySlots[tablec->buckets[hash].emptyCapacity - 1].filled = 1;

          break;
        }

        tablec->buckets[hash].emptySlots[0].index = i;
        tablec->buckets[hash].emptySlots[0].filled = 1;

        break;
      }
      default: {
        size_t j = 2;
        do {
          if (j >= tablec->buckets[hash].emptyCapacity - 1) {
            tablec->buckets[hash].emptyCapacity++;
            tablec->buckets[hash].emptySlots = realloc(tablec->buckets[hash].emptySlots, sizeof(struct hashtable_buckets_array_empty) * tablec->buckets[hash].emptyCapacity + 1);

            tablec->buckets[hash].emptySlots[j].index = i;
            tablec->buckets[hash].emptySlots[j].filled = 1;

            break;
          }

          if (!tablec->buckets[hash].emptySlots[j].filled) {
            tablec->buckets[hash].emptySlots[j].index = i;
            tablec->buckets[hash].emptySlots[j].filled = 1;

            break;
          }
          j++;
        } while (j < tablec->buckets[hash].emptyCapacity);

        break;
      }
    }
  }
}

void *tablec_get(struct hashtable *tablec, char *key, size_t keyLength) {
  size_t hash = __tablec_hash(tablec, key, keyLength);

  size_t i = 0;
  void *value = NULL;

  do {
    if (tablec->buckets[hash].array[i].key != NULL && strcmp(tablec->buckets[hash].array[i].key, key) == 0) {
      value = tablec->buckets[hash].array[i].value;
      break;
    }
    i++;
  } while (i < tablec->buckets[hash].length);

  return value;
}

void tablec_cleanup(struct hashtable *tablec) {
  size_t i = 0;
  do {
    if (tablec->buckets[i].emptyCapacity != 0) free(tablec->buckets[i].emptySlots);
    i++;
  } while (i < tablec->capacity);
  free(tablec->buckets);
  tablec = NULL;
}
