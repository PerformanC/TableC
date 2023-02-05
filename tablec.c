#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#include "tablec.h"

void tablec_init(struct tablec_ht *tablec, size_t max_capacity) {
  tablec->buckets = malloc(sizeof(struct tablec_buckets) * max_capacity);
  tablec->capacity = max_capacity;
  tablec->length = 0;

  while (max_capacity--) {
    tablec->buckets[max_capacity].capacity = 1;
    tablec->buckets[max_capacity].length = 0;
    tablec->buckets[max_capacity].array = malloc(sizeof(struct tablec_buckets_array));
    tablec->buckets[max_capacity].array[0].key = NULL;
    tablec->buckets[max_capacity].array[0].value = NULL;
  }
}

size_t __tablec_hash(struct tablec_ht *tablec, char *key) {
  size_t hash = 0, i = 0;

  while (key[i] != '\0') hash = hash * 37 + (key[i++] & 255);

  return hash % tablec->capacity;
}

void tablec_resize(struct tablec_ht *tablec, size_t new_max_capacity) {
  size_t i = tablec->capacity;

  struct tablec_ht newHashtable;
  tablec_init(&newHashtable, new_max_capacity);

  if (tablec->length != 0) while (i--) {
    if (tablec->buckets[i].length == 0) continue;

    if (tablec->buckets[i].length == 1) {
      tablec_set(&newHashtable, tablec->buckets[i].array[0].key, tablec->buckets[i].array[0].value);
      
      continue;
    }

    while (tablec->buckets[i].capacity-- - 1) {
      if (tablec->buckets[i].array[tablec->buckets[i].capacity - 1].key) 
        tablec_set(&newHashtable, tablec->buckets[i].array[tablec->buckets[i].capacity - 1].key, tablec->buckets[i].array[tablec->buckets[i].capacity - 1].value);
    }
  }

  tablec_cleanup(tablec);
  *tablec = newHashtable;
}

void tablec_set(struct tablec_ht *tablec, char *key, void *value) {
  size_t hash = __tablec_hash(tablec, key);

  if (tablec->buckets[hash].length == 0) {
    if (tablec->buckets[hash].array[0].key == NULL) {
      tablec->buckets[hash].array[0].key = key;
      tablec->buckets[hash].array[0].value = value;

      tablec->length++;
      tablec->buckets[hash].length = 1;
    } else {
      tablec->buckets[hash].capacity = 2;
      tablec->buckets[hash].array = realloc(tablec->buckets[hash].array, sizeof(struct tablec_buckets_array) * 2);

      tablec->buckets[hash].array[1].key = key;
      tablec->buckets[hash].array[1].value = value;

      tablec->buckets[hash].length = 2;
      tablec->length++;
    }
  } else {
    size_t i = tablec->buckets[hash].capacity;
    struct tablec_buckets_array *newArray = NULL;

    while (i--) {
      if (tablec->buckets[hash].array[i].key) continue;

      tablec->buckets[hash].array[i].key = key;
      tablec->buckets[hash].array[i].value = value;

      tablec->buckets[hash].length++;
      tablec->length++;

      return;
    }

    i = tablec->buckets[hash].capacity;

    newArray = calloc(sizeof(struct tablec_buckets_array) * (tablec->buckets[hash].capacity * 2), 1);
    while (i--) {
      if (!tablec->buckets[hash].array[i].key) {
        newArray[i].key = NULL;
        newArray[i].value = NULL;

        continue;
      }
  
      newArray[i].key = tablec->buckets[hash].array[i].key;
      newArray[i].value = tablec->buckets[hash].array[i].value;
    }

    free(tablec->buckets[hash].array);

    tablec->buckets[hash].array = newArray;
    tablec->buckets[hash].capacity *= 2;

    tablec_set(tablec, key, value);

    return;
  }
}

void *tablec_get(struct tablec_ht *tablec, char *key) {
  size_t hash = __tablec_hash(tablec, key), i = tablec->buckets[hash].capacity;
  
  while (i--) {
    if (tablec->buckets[hash].array[i].key != NULL && strcmp(tablec->buckets[hash].array[i].key, key) == 0)
      return tablec->buckets[hash].array[i].value;
  }

  return NULL;
}

void tablec_del(struct tablec_ht *tablec, char *key) {
  size_t hash = __tablec_hash(tablec, key), i = tablec->buckets[hash].capacity;

  if (tablec->buckets[hash].length == 0) return;

  if (tablec->buckets[hash].length == 1) {
    tablec->buckets[hash].array[0].key = NULL;
    tablec->buckets[hash].array[0].value = NULL;

    tablec->length--;
    tablec->buckets[hash].length = 0;

    return;
  }

  while (i--) {
    if (tablec->buckets[hash].array[i].key && strcmp(tablec->buckets[hash].array[i].key, key) == 0) {
      tablec->buckets[hash].array[i].key = NULL;
      tablec->buckets[hash].array[i].value = NULL;

      tablec->length--;
      tablec->buckets[hash].length--;

      return;
    }
  }
}

long tablec_full(struct tablec_ht *tablec) {
  return tablec->capacity == tablec->length ? (long)-1 : (long)tablec->capacity - (long)tablec->length;
}

void tablec_cleanup(struct tablec_ht *tablec) {
  while (tablec->capacity--) free(tablec->buckets[tablec->capacity].array);
  free(tablec->buckets);
  tablec = NULL;
}
