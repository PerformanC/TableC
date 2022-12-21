#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tablec.h"

void tablec_init(struct hashtable *tablec, size_t max_capacity, int secure_mode) {
  size_t i = 0;

  (*tablec).secure_mode = secure_mode;
  (*tablec).length = 0;
  (*tablec).capacity = max_capacity;
  (*tablec).buckets = malloc(sizeof(struct hashtable_buckets) * max_capacity - 1);

  do {
    (*tablec).buckets[i].capacity = 1;
    (*tablec).buckets[i].emptyCapacity = 0;
    (*tablec).buckets[i].length = 0;
    (*tablec).buckets[i].array = malloc(sizeof(struct hashtable_buckets_array) * 1);

    i++;
  } while (i < max_capacity);
}

void tablec_resize(struct hashtable *tablec, size_t new_max_capacity) {
  tablec->capacity = new_max_capacity;
  tablec->buckets = realloc(tablec->buckets, sizeof(struct hashtable_buckets) * new_max_capacity - 1);
}

void __tablec_expandBucketArr(struct hashtable_buckets *bucket, size_t new_max_capacity) {
  bucket->capacity = new_max_capacity;
  bucket->array = realloc(bucket->array, sizeof(struct hashtable_buckets_array) * new_max_capacity - 1);
}

size_t __tablec_mkIndex(struct hashtable *tablec, char *key, size_t keyLength) {
  size_t pos = 0, i = 0;

  if (keyLength != 0) keyLength = strlen(key);

  do {
    pos = pos * 37 + key[i];
    i++;
  } while (i < keyLength);

  return pos % tablec->capacity;
}

void tablec_set(struct hashtable *tablec, char *key, size_t keyLength, void *value) {
  size_t pos;
  if (tablec->length >= tablec->capacity) {
    if (tablec->secure_mode) {
      tablec_resize(tablec, tablec->capacity + 1);
    } else {
      printf("TableC error, the buckets are full. Use tablec_expand or secure mode to fix.\n");
    }
  }
  pos = __tablec_mkIndex(tablec, key, keyLength);

  tablec->length++;

  if (tablec->buckets[pos].capacity == 1) {
    if (!tablec->buckets[pos].array[0].filled) {
      tablec->buckets[pos].array[0].key = key;
      tablec->buckets[pos].array[0].value = value;
      tablec->buckets[pos].array[0].filled = 1;

      tablec->buckets[pos].length = 1;
      return;
    } else {
      __tablec_expandBucketArr(&tablec->buckets[pos], 2);

      tablec->buckets[pos].array[1].key = key;
      tablec->buckets[pos].array[1].value = value;
      tablec->buckets[pos].array[1].filled = 1;

      tablec->buckets[pos].length = 2;
      return;
    }
  } else {
    if (tablec->buckets[pos].emptyCapacity == 0) {
      size_t i = -1;

      do {
        i++;
        if (!tablec->buckets[pos].array[i].filled) {
          tablec->buckets[pos].array[i].key = key;
          tablec->buckets[pos].array[i].value = value;
          tablec->buckets[pos].array[i].filled = 1;

          tablec->buckets[pos].length++;
          break;
        }

        if (i == tablec->buckets[pos].capacity - 1) {
          __tablec_expandBucketArr(&tablec->buckets[pos], tablec->buckets[pos].capacity + 1);

          tablec->buckets[pos].array[tablec->buckets[pos].capacity - 1].key = key;
          tablec->buckets[pos].array[tablec->buckets[pos].capacity - 1].value = value;
          tablec->buckets[pos].array[tablec->buckets[pos].capacity - 1].filled = 1;

          tablec->buckets[pos].length++;
          break;
        }
      } while (i == tablec->buckets[pos].capacity - 1);
    }
    if (tablec->buckets[pos].emptyCapacity == 1) {
      if (!tablec->buckets[pos].emptySlots[0].filled) return;
        
      tablec->buckets[pos].array[tablec->buckets[pos].emptySlots[0].index].key = key;
      tablec->buckets[pos].array[tablec->buckets[pos].emptySlots[0].index].value = value;
      tablec->buckets[pos].array[tablec->buckets[pos].emptySlots[0].index].filled = 1;

      tablec->buckets[pos].emptySlots[0].index = 0;
      tablec->buckets[pos].emptySlots[0].filled = 0;
    } else if (tablec->buckets[pos].emptyCapacity > 1) {
      size_t i = 0;

      do {
        if (tablec->buckets[pos].emptySlots[i].filled) {
          tablec->buckets[pos].array[tablec->buckets[pos].emptySlots[i].index].key = key;
          tablec->buckets[pos].array[tablec->buckets[pos].emptySlots[i].index].value = value;
          tablec->buckets[pos].array[tablec->buckets[pos].emptySlots[i].index].filled = 1;

          tablec->buckets[pos].emptySlots[i].index = 0;
          tablec->buckets[pos].emptySlots[i].filled = 0;

          tablec->buckets[pos].length++;
          break;
        }

        if (i == tablec->buckets[pos].emptyCapacity - 1) {
          __tablec_expandBucketArr(&tablec->buckets[pos], tablec->buckets[pos].capacity + 1);

          tablec->buckets[pos].array[tablec->buckets[pos].capacity - 1].key = key;
          tablec->buckets[pos].array[tablec->buckets[pos].capacity - 1].value = value;
          tablec->buckets[pos].array[tablec->buckets[pos].capacity - 1].filled = 1;

          tablec->buckets[pos].length++;
          break;
        }
      } while (i - 1 == tablec->buckets[pos].emptyCapacity);
    }
  }
}

void tablec_del(struct hashtable *tablec, char *key, size_t keyLength) {
  size_t pos = __tablec_mkIndex(tablec, key, keyLength);

  tablec->length--;

  if (tablec->buckets[pos].capacity == 1) {
    tablec->buckets[pos].array[0].key = NULL;
    tablec->buckets[pos].array[0].value = NULL;
    tablec->buckets[pos].array[0].filled = 0;
  } else {
    size_t i = 0;
    do {
      i++;
      if (!tablec->buckets[pos].array[i].filled || strcmp(tablec->buckets[pos].array[i].key, key) != 0) continue;
        
      tablec->buckets[pos].array[i].key = NULL;
      tablec->buckets[pos].array[i].value = NULL;
      tablec->buckets[pos].array[i].filled = 0;

      if (tablec->buckets[pos].emptyCapacity == 0) {
        tablec->buckets[pos].emptyCapacity = 1;
        tablec->buckets[pos].emptySlots = malloc(sizeof(struct hashtable_buckets_array_empty));
      }
      
      if (tablec->buckets[pos].emptyCapacity == 1) {
        if (tablec->buckets[pos].emptySlots[0].filled) continue;
            
        tablec->buckets[pos].emptySlots[0].index = pos;
        tablec->buckets[pos].emptySlots[0].filled = 1;
        break;
      } else {
        size_t j = 2;
        do {
          if (j >= tablec->buckets[pos].emptyCapacity - 1) {
            tablec->buckets[pos].emptyCapacity++;
            tablec->buckets[pos].emptySlots = realloc(tablec->buckets[pos].emptySlots, sizeof(struct hashtable_buckets_array_empty) * tablec->buckets[pos].emptyCapacity + 1);

            tablec->buckets[pos].emptySlots[j].index = pos;
            tablec->buckets[pos].emptySlots[j].filled = 1;
            break;
          }

          if (!tablec->buckets[pos].emptySlots[j].filled) {
            tablec->buckets[pos].emptySlots[j].index = pos;
            tablec->buckets[pos].emptySlots[j].filled = 1;
            break;
          }
          j++;
        } while (j != tablec->buckets[pos].emptyCapacity - 1);
      }
    } while (i != tablec->buckets[pos].capacity - 1);
  }
}

void *tablec_get(struct hashtable *tablec, char *key, size_t keyLength) {
  size_t pos = __tablec_mkIndex(tablec, key, keyLength);

  if (tablec->buckets[pos].capacity == 1) {
    if (tablec->buckets[pos].array[0].filled) {
      return tablec->buckets[pos].array[0].value;
    } else {
      return NULL;
    }
  } else {
    size_t i = 1;
    void *value = NULL;

    do {
      if (tablec->buckets[pos].array[i].filled) {
        if (strcmp(tablec->buckets[pos].array[i].key, key) == 0) {
          value = tablec->buckets[pos].array[i].value;
          break;
        }
      }
      i++;
    } while (i <= tablec->buckets[pos].capacity);

    return value;
  }
}

void tablec_cleanup(struct hashtable *tablec) {
  free(tablec->buckets);
  tablec = NULL;
}
