#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#include "tablec.h"

void tablec_init(struct tablec_ht *tablec, size_t max_capacity) {
  tablec->buckets = malloc(sizeof(struct tablec_buckets) * max_capacity);
  tablec->capacity = max_capacity;
  tablec->length = 0;

  while (max_capacity-- != 0) {
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

struct tablec_ht tablec_resize(struct tablec_ht *tablec, size_t new_max_capacity) {
  new_max_capacity--;

  struct tablec_ht newHashtable;
  newHashtable.buckets = malloc(sizeof(struct tablec_buckets) * new_max_capacity);
  newHashtable.capacity = new_max_capacity;
  newHashtable.length = tablec->length;

  if (tablec->length != 0) while (new_max_capacity--) {
    if (tablec->buckets[new_max_capacity].length == 0) {
      newHashtable.buckets[new_max_capacity].capacity = tablec->buckets[new_max_capacity].capacity;
      newHashtable.buckets[new_max_capacity].length = tablec->buckets[new_max_capacity].length;
      newHashtable.buckets[new_max_capacity].array = malloc(sizeof(struct tablec_buckets_array));

      continue;
    }

    if (tablec->buckets[new_max_capacity].length == 1) {
      newHashtable.buckets[new_max_capacity].capacity = tablec->buckets[new_max_capacity].capacity;
      newHashtable.buckets[new_max_capacity].length = tablec->buckets[new_max_capacity].length;
      newHashtable.buckets[new_max_capacity].array = malloc(sizeof(struct tablec_buckets_array) * tablec->buckets[new_max_capacity].capacity);

      newHashtable.buckets[new_max_capacity].array[0].key = tablec->buckets[new_max_capacity].array[0].key;
      newHashtable.buckets[new_max_capacity].array[0].value = tablec->buckets[new_max_capacity].array[0].value;
    } else {
      newHashtable.buckets[new_max_capacity].capacity = tablec->buckets[new_max_capacity].capacity;
      newHashtable.buckets[new_max_capacity].length = tablec->buckets[new_max_capacity].length;
      newHashtable.buckets[new_max_capacity].array = malloc(sizeof(struct tablec_buckets_array) * tablec->buckets[new_max_capacity].capacity);

      memcpy(newHashtable.buckets[new_max_capacity].array, tablec->buckets[new_max_capacity].array, sizeof(struct tablec_buckets_array) * tablec->buckets[new_max_capacity].capacity);
    }
  }
  else while (new_max_capacity--) {
    newHashtable.buckets[new_max_capacity].capacity = 1;
    newHashtable.buckets[new_max_capacity].length = 0;
    newHashtable.buckets[new_max_capacity].array = malloc(sizeof(struct tablec_buckets_array));
    newHashtable.buckets[new_max_capacity].array[0].key = NULL;
    newHashtable.buckets[new_max_capacity].array[0].value = NULL;
  }

  free(tablec->buckets);
  return newHashtable;
}

void tablec_set(struct tablec_ht *tablec, char *key, void *value) {
  size_t hash = __tablec_hash(tablec, key);

  if (tablec->buckets[hash].length == 0) {
    if (tablec->buckets[hash].array[0].key == NULL) {
      tablec->buckets[hash].array[0].key = key;
      tablec->buckets[hash].array[0].value = value;

      tablec->length++;
      tablec->buckets[hash].length = 1;

      return;
    } else {
      tablec->buckets[hash].capacity = 2;
      tablec->buckets[hash].array = realloc(tablec->buckets[hash].array, sizeof(struct tablec_buckets_array) * 2);

      tablec->buckets[hash].array[1].key = key;
      tablec->buckets[hash].array[1].value = value;

      tablec->buckets[hash].length = 2;
      tablec->length++;

      return;
    }
  } else {
    size_t i = -1;

    while (i++ != tablec->buckets[hash].capacity - 1) {
      if (tablec->buckets[hash].array[i].key == NULL) {
        tablec->buckets[hash].array[i].key = key;
        tablec->buckets[hash].array[i].value = value;

        tablec->buckets[hash].length++;
        tablec->length++;

        return;
      }
    }

    tablec->buckets[hash].capacity = (tablec->buckets[hash].capacity * 2);
    tablec->buckets[hash].array = realloc(tablec->buckets[hash].array, sizeof(struct tablec_buckets_array) * (tablec->buckets[hash].capacity * 2));

    tablec->buckets[hash].array[tablec->buckets[hash].capacity - 1].key = key;
    tablec->buckets[hash].array[tablec->buckets[hash].capacity - 1].value = value;

    tablec->buckets[hash].length++;
    tablec->length++;

    return;
  }
}

void tablec_del(struct tablec_ht *tablec, char *key) {
  size_t hash = __tablec_hash(tablec, key);

  if (tablec->buckets[hash].length == 1) {
    tablec->buckets[hash].array[0].key = NULL;
    tablec->buckets[hash].array[0].value = NULL;

    tablec->length--;
    tablec->buckets[hash].length = 0;

    return;
  } else if (tablec->buckets[hash].length != 0) {
    size_t i = -1;

    while (i++ != tablec->buckets[hash].capacity - 1) {
      if (tablec->buckets[hash].array[i].key != NULL && strcmp(tablec->buckets[hash].array[i].key, key) == 0) {
        tablec->buckets[hash].array[i].key = NULL;
        tablec->buckets[hash].array[i].value = NULL;

        tablec->length--;
        tablec->buckets[hash].length--;

        return;
      }
    }
  }
}

void *tablec_get(struct tablec_ht *tablec, char *key) {
  size_t hash = __tablec_hash(tablec, key), i = -1;
  
  while (i++ != tablec->buckets[hash].capacity - 1) {
    if (tablec->buckets[hash].array[i].key != NULL && strcmp(tablec->buckets[hash].array[i].key, key) == 0) {
      return tablec->buckets[hash].array[i].value;
    }
  }

  return NULL;
}

int tablec_full(struct tablec_ht *tablec) {
  return tablec->capacity == tablec->length ? -1 : tablec->capacity - tablec->length;
}

void tablec_cleanup(struct tablec_ht *tablec) {
  while (tablec->capacity-- != 0) free(tablec->buckets[tablec->capacity].array);
  free(tablec->buckets);
  tablec = NULL;
}