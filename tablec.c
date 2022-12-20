#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <coglink/tablec.h>

void tablec_init(struct hashtable *tablec, size_t max_capacity, _Bool secure_mode) {
  *tablec = (struct hashtable) {
    .secure_mode = secure_mode,
    .length = 0,
    .capacity = max_capacity,
    .buckets = malloc(sizeof(struct hashtable_buckets) * max_capacity - 1)
  };
  for (size_t i = 0;i < max_capacity;i++) {
    tablec->buckets[i] = (struct hashtable_buckets) {
      .capacity = 1,
      .emptyCapacity = 0,
      .length = 0,
      .array = malloc(sizeof(struct hashtable_buckets_array) * 1)
    };
  }
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
  size_t pos = 0;

  if (keyLength != 0) keyLength = strlen(key);

  size_t i = 0;
  do {
    pos = pos * 37 + key[i];
    i++;
  } while (i < keyLength);

  return pos % tablec->capacity;
}

void tablec_set(struct hashtable *tablec, char *key, size_t keyLength, void *value) {
  if (tablec->length >= tablec->capacity) {
    if (tablec->secure_mode) {
      tablec_resize(tablec, tablec->capacity + 1);
    } else {
      printf("TableC error, the buckets are full. Use tablec_expand or secure mode to fix.\n");
    }
  }
  size_t pos = __tablec_mkIndex(tablec, key, keyLength);

  tablec->length++;

  if (tablec->buckets[pos].capacity == 1) {
    if (!tablec->buckets[pos].array[0].filled) {
      tablec->buckets[pos].array[0] = (struct hashtable_buckets_array) {
        .key = key,
        .value = value,
        .filled = true
      };
      tablec->buckets[pos].length = 1;
      return;
    } else {
      __tablec_expandBucketArr(&tablec->buckets[pos], 2);
      tablec->buckets[pos].array[1] = (struct hashtable_buckets_array) {
        .key = key,
        .value = value,
        .filled = true
      };
      tablec->buckets[pos].length = 2;
      return;
    }
  } else {
    if (tablec->buckets[pos].emptyCapacity == 0) {
      __tablec_expandBucketArr(&tablec->buckets[pos], tablec->buckets[pos].capacity + 1);
      tablec->buckets[pos].array[tablec->buckets[pos].capacity - 1] = (struct hashtable_buckets_array) {
        .key = key,
        .value = value,
        .filled = true
      };
      tablec->buckets[pos].length++;
      return;
    }
    if (tablec->buckets[pos].emptyCapacity != 1) {
      if (!tablec->buckets[pos].emptySlots[0].filled) return;
        
      tablec->buckets[pos].array[tablec->buckets[pos].emptySlots[0].index] = (struct hashtable_buckets_array) {
        .key = key,
        .value = value,
        .filled = true
      };
      tablec->buckets[pos].emptySlots[0] = (struct hashtable_buckets_array_empty) {
        .index = 0,
        .filled = false
      };
    } else {
      size_t i = 0;

      do {
        if (tablec->buckets[pos].emptySlots[i].filled) {
          tablec->buckets[pos].array[tablec->buckets[pos].emptySlots[i].index] = (struct hashtable_buckets_array) {
            .key = key,
            .value = value,
            .filled = true
          };
          tablec->buckets[pos].emptySlots[i] = (struct hashtable_buckets_array_empty) {
            .index = 0,
            .filled = false
          };
          tablec->buckets[pos].length++;
          break;
        }

        if (i == tablec->buckets[pos].emptyCapacity - 1) {
          __tablec_expandBucketArr(&tablec->buckets[pos], tablec->buckets[pos].capacity + 1);
          tablec->buckets[pos].array[tablec->buckets[pos].capacity - 1] = (struct hashtable_buckets_array) {
            .key = key,
            .value = value,
            .filled = true
          };
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
    tablec->buckets[pos].array[0] = (struct hashtable_buckets_array) {
      .key = NULL,
      .value = NULL,
      .filled = false
    };
  } else {
    size_t i = 0;
    do {
      i++;
      if (!tablec->buckets[pos].array[i].filled || strcmp(tablec->buckets[pos].array[i].key, key) != 0) continue;
        
      tablec->buckets[pos].array[i] = (struct hashtable_buckets_array) {
        .key = NULL,
        .value = NULL,
        .filled = false
      };

      if (tablec->buckets[pos].emptyCapacity == 0) {
        tablec->buckets[pos].emptyCapacity = 1;
        tablec->buckets[pos].emptySlots = malloc(sizeof(struct hashtable_buckets_array_empty));
      }

      if (tablec->buckets[pos].emptyCapacity == 1) {
        if (!tablec->buckets[pos].emptySlots[0].filled) continue;
            
        tablec->buckets[pos].emptySlots[0] = (struct hashtable_buckets_array_empty) {
          .index = pos,
          .filled = true
        };
        break;
      } else {
        size_t j = 2;
        do {
          if (j >= tablec->buckets[pos].emptyCapacity - 1) {
            tablec->buckets[pos].emptyCapacity++;
            tablec->buckets[pos].emptySlots = realloc(tablec->buckets[pos].emptySlots, sizeof(struct hashtable_buckets_array_empty) * tablec->buckets[pos].emptyCapacity + 1);

            tablec->buckets[pos].emptySlots[j] = (struct hashtable_buckets_array_empty) {
              .index = pos,
              .filled = true
            };
            break;
          }

          if (!tablec->buckets[pos].emptySlots[j].filled) {
            tablec->buckets[pos].emptySlots[j] = (struct hashtable_buckets_array_empty) {
              .index = pos,
              .filled = true
            };
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
  free(tablec->emptySlots);
  tablec = NULL;
}
