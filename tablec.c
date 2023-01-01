#include <stdlib.h>
#include <string.h>

#include "tablec.h"

void tablec_init(struct hashtable *tablec, size_t max_capacity, int secure_mode) {
  tablec->buckets = malloc(sizeof(struct hashtable_buckets) * max_capacity);
  tablec->capacity = max_capacity - 1;
  tablec->length = 0;
  tablec->secure_mode = secure_mode;

  while (max_capacity-- != 0) {
    tablec->buckets[max_capacity].capacity = 0;
    tablec->buckets[max_capacity].length = 0;
    tablec->buckets[max_capacity].array = malloc(sizeof(struct hashtable_buckets_array));
    tablec->buckets[max_capacity].array[0].key = NULL;
    tablec->buckets[max_capacity].array[0].value = NULL;
  }
}

void tablec_resize(struct hashtable *tablec, size_t new_max_capacity) {
  /* TODO: Add rehashing when resizing hashtable because it will cause __tablec_hash to not find the keys if not. */
  tablec->capacity = new_max_capacity - 1;
  tablec->buckets = realloc(tablec->buckets, sizeof(struct hashtable_buckets) * new_max_capacity);
}

size_t __tablec_hash(struct hashtable *tablec, char *key) {
  size_t hash = 0, i = 0;

  while (key[i] != '\0') hash = hash * 37 + (key[i++] & 255);

  return hash % tablec->capacity;
}

void tablec_set(struct hashtable *tablec, char *key, void *value) {
  size_t hash = __tablec_hash(tablec, key);

  if (tablec->buckets[hash].capacity == 0) {
    if (tablec->buckets[hash].array[0].key == NULL) {
      tablec->buckets[hash].array[0].key = key;
      tablec->buckets[hash].array[0].value = value;

      tablec->length++;

      return;
    } else {
      tablec->buckets[hash].capacity = 1;
      tablec->buckets[hash].array = realloc(tablec->buckets[hash].array, sizeof(struct hashtable_buckets_array) * 2);

      tablec->buckets[hash].array[1].key = key;
      tablec->buckets[hash].array[1].value = value;

      tablec->buckets[hash].length = 1;
      tablec->length++;

      return;
    }
  } else {
    size_t i = -1;

    while (i++ != tablec->buckets[hash].capacity) {
      if (tablec->buckets[hash].array[i].key == NULL) {
        tablec->buckets[hash].array[i].key = key;
        tablec->buckets[hash].array[i].value = value;

        tablec->buckets[hash].length++;
        tablec->length++;

        return;
      }
    }

    tablec->buckets[hash].capacity = (tablec->buckets[hash].capacity * 2) - 1;
    tablec->buckets[hash].array = realloc(tablec->buckets[hash].array, sizeof(struct hashtable_buckets_array) * (tablec->buckets[hash].capacity * 2));

    tablec->buckets[hash].array[tablec->buckets[hash].capacity].key = key;
    tablec->buckets[hash].array[tablec->buckets[hash].capacity].value = value;

    tablec->buckets[hash].length++;
    tablec->length++;

    return;
  }
}

void tablec_del(struct hashtable *tablec, char *key) {
  size_t hash = __tablec_hash(tablec, key);

  if (tablec->buckets[hash].capacity == 0) {
    tablec->buckets[hash].array[0].key = NULL;
    tablec->buckets[hash].array[0].value = NULL;

    tablec->length--;

    return;
  } else {
    size_t i = -1;

    while (i++ != tablec->buckets[hash].capacity) {
      if (tablec->buckets[hash].array[i].key != NULL && strcmp(tablec->buckets[hash].array[i].key, key) == 0) {
        tablec->buckets[hash].array[i].key = NULL;
        tablec->buckets[hash].array[i].value = NULL;

        tablec->length--;

        return;
      }
    }
  }
}

void *tablec_get(struct hashtable *tablec, char *key) {
  size_t hash = __tablec_hash(tablec, key);

  size_t i = -1;
  
  while (i++ != tablec->buckets[hash].capacity) {
    if (tablec->buckets[hash].array[i].key != NULL && strcmp(tablec->buckets[hash].array[i].key, key) == 0) {
      return tablec->buckets[hash].array[i].value;
    }
  }

  return NULL;
}

int tablec_full(struct hashtable *tablec) {
  return tablec->capacity == tablec->length - 1 ? -1 : tablec->capacity - tablec->length - 1;
}

void tablec_cleanup(struct hashtable *tablec) {
  while (tablec->capacity-- != 0) free(tablec->buckets[tablec->capacity].array);
  free(tablec->buckets);
  tablec = NULL;
}
