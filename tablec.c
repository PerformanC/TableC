#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tablec.h"

void tablec_init(struct tablec_ht *tablec, size_t max_capacity) {
  tablec->length = 0;
  tablec->capacity = max_capacity - 1;
  tablec->buckets = malloc(sizeof(struct tablec_buckets) * max_capacity);
}

size_t __tablec_hash(struct tablec_ht *tablec, char *key) {
  size_t hash = 0, i = 0;

  while (key[i] != '\0') hash = hash * 37 + (key[i++] & 255);

  return hash % tablec->capacity;
}

struct tablec_ht tablec_resize(struct tablec_ht *tablec, size_t new_max_capacity) {
  size_t hash, old_capacity = tablec->capacity;
  long i = -1;
  
  struct tablec_ht newHashtable;
  newHashtable.buckets = calloc(sizeof(struct tablec_buckets) * new_max_capacity, 1);
  newHashtable.capacity = new_max_capacity;
  newHashtable.length = tablec->length;

  tablec->capacity = new_max_capacity - 1;

  while (i++ != (long)old_capacity) {
    if (tablec->buckets[i].key == NULL) continue;
      
    hash = __tablec_hash(tablec, tablec->buckets[i].key);

    if (newHashtable.buckets[hash].key != NULL) {
      while (newHashtable.buckets[hash++].key != NULL) {
        if (newHashtable.buckets[hash].key == NULL) {

        newHashtable.buckets[hash].key = tablec->buckets[i].key;
        newHashtable.buckets[hash].value = tablec->buckets[i].value;

        break;
        }
        break;
      }
    } else {
      newHashtable.buckets[hash].key = tablec->buckets[i].key;
      newHashtable.buckets[hash].value = tablec->buckets[i].value;
    }
  }

  free(tablec->buckets);
  return newHashtable;
}

void tablec_set(struct tablec_ht *tablec, char *key, void *value) {
  size_t hash;

  if (tablec->length - 1 == tablec->capacity) tablec_resize(tablec, tablec->capacity * 2);

  hash = __tablec_hash(tablec, key);

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

void tablec_del(struct tablec_ht *tablec, char *key) {
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

void *tablec_get(struct tablec_ht *tablec, char *key) {
  size_t hash = __tablec_hash(tablec, key);

  while (hash != tablec->capacity) {
    if (tablec->buckets[hash].key != NULL && strcmp(tablec->buckets[hash].key, key) == 0) return tablec->buckets[hash].value;
    hash++;
  }

  return NULL;
}

int tablec_full(struct tablec_ht *tablec) {
  return tablec->capacity == tablec->length - 1 ? -1 : tablec->capacity - tablec->length + 1;
}

void tablec_cleanup(struct tablec_ht *tablec) {
  free(tablec->buckets);
  tablec = NULL;
}
