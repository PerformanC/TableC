#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tablec.h"

void tablec_init(struct hashtable *tablec, size_t max_capacity) {
  tablec->length = 0;
  tablec->capacity = max_capacity - 1;
  tablec->buckets = malloc(sizeof(struct hashtable_buckets) * max_capacity);
}

size_t __tablec_hash(struct hashtable *tablec, char *key) {
  size_t hash = 0, i = 0;

  while (key[i] != '\0') hash = hash * 37 + (key[i++] & 255);

  return hash % tablec->capacity;
}

void tablec_resize(struct hashtable *tablec, size_t new_max_capacity) {
  struct hashtable_buckets *new_buckets = calloc(sizeof(struct hashtable_buckets) * new_max_capacity, 1);

  size_t old_capacity = tablec->capacity;
  tablec->capacity = new_max_capacity - 1;

  long i = -1;
  while (i++ != old_capacity) {
    if (tablec->buckets[i].key == NULL) continue;
      
    size_t hash = __tablec_hash(tablec, tablec->buckets[i].key);

    if (new_buckets[hash].key != NULL) {
      while (new_buckets[hash++].key != NULL) {
        if (new_buckets[hash].key == NULL) {

        new_buckets[hash].key = tablec->buckets[i].key;
        new_buckets[hash].value = tablec->buckets[i].value;

        break;
        }
        break;
      }
    } else {
      new_buckets[hash].key = tablec->buckets[i].key;
      new_buckets[hash].value = tablec->buckets[i].value;
    }
  }

  free(tablec->buckets);
  tablec->buckets = new_buckets;
}

void tablec_set(struct hashtable *tablec, char *key, void *value) {
  if (tablec->length - 1 == tablec->capacity) tablec_resize(tablec, tablec->capacity * 2);

  size_t hash = __tablec_hash(tablec, key);

  while (hash != tablec->capacity) {
    if (tablec->buckets[hash].key == NULL) {
      tablec->buckets[hash].key = key;
      tablec->buckets[hash].value = value;

      tablec->length++;

      return;
    }
    hash++;
  }

  tablec_resize(tablec, tablec->capacity * 2);

  tablec->buckets[tablec->capacity].key = key;
  tablec->buckets[tablec->capacity].value = value;

  tablec->length++;

  return;
}

void tablec_del(struct hashtable *tablec, char *key) {
  size_t hash = __tablec_hash(tablec, key);

  while (hash != tablec->capacity) {
    if (tablec->buckets[hash].key != NULL && strcmp(tablec->buckets[hash].key, key) == 0) {
      tablec->buckets[hash].key = NULL;
      tablec->buckets[hash].value = NULL;

      tablec->length--;

      return;
    }
    hash++;
  }
}

void *tablec_get(struct hashtable *tablec, char *key) {
  size_t hash = __tablec_hash(tablec, key);

  while (hash != tablec->capacity) {
    if (tablec->buckets[hash].key != NULL && strcmp(tablec->buckets[hash].key, key) == 0) return tablec->buckets[hash].value;
    hash++;
  }

  return NULL;
}

int tablec_full(struct hashtable *tablec) {
  return tablec->capacity == tablec->length - 1 ? -1 : tablec->capacity - tablec->length + 1;
}

void tablec_cleanup(struct hashtable *tablec) {
  free(tablec->buckets);
  tablec = NULL;
}
